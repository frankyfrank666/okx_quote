#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "../include/utils.h"

struct Configuration
{
    ap_uint<32> mDelayCycle; // 3s
    ap_uint<32> mMyIp; //FPGA IP and MAC
    ap_uint<48> mMyMac; 
    ap_uint<48> mMyPort;
    ap_uint<32> mTargetIp;
    ap_uint<48> mTargetMac; //Of course, it is the router, not the actual okx server, need ARP or static router in production. 
    ap_uint<48> mTargetPort;
    ap_uint<32> mCommand; 
};

extern "C" {
    void ConfiguratorTop (
        ap_uint<32> mDelayCycle, // 3s
        ap_uint<32> mMyIp, //FPGA IP and MAC
        ap_uint<48> mMyMac, 
        ap_uint<48> mMyPort,
        ap_uint<32> mTargetIp,
        ap_uint<48> mTargetMac, //Of course, it is the router, not the actual okx server, need ARP or static router in production. 
        ap_uint<48> mTargetPort,
        ap_uint<32> mCommand, 
        hls::stream<ap_uint<32>>& delay_config_stream_out,
        hls::stream<Configuration>& tcp_config_stream_out
    );
}

#endif
