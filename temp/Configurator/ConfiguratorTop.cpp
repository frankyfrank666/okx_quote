#include "ConfiguratorTop.h"

extern "C" {
    /// @brief Send configurations in a stream. Not used here.
    /// @param mDelayCycle 
    /// @param mMyIp 
    /// @param mMyMac 
    /// @param mMyPort 
    /// @param mTargetIp 
    /// @param mTargetMac 
    /// @param mTargetPort 
    /// @param mCommand 
    /// @param delay_config_stream_out 
    /// @param tcp_config_stream_out 
    void ConfiguratorTop(
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
    )
    {
#pragma hls interface axis port=tcp_config_stream_out
#pragma hls interface axis port=delay_config_stream_out
#pragma HLS INTERFACE mode=ap_ctrl_hs port=return
        
        delay_config_stream_out.write(config.mDelayCycle);
        Configuration config_in;
        config_in.mDelayCycle = mDelayCycle; 
        config_in.mMyIp = mMyIp; 
        config_in.mMyMac = mMyMac; 
        config_in.mMyPort = mMyPort; 
        config_in.mTargetIp = mTargetIp; 
        config_in.mTargetMac = mTargetMac; 
        config_in.mTargetPort = mTargetPort; 
        config_in.mCommand = mCommand;
        tcp_config_stream_out.write(config_in);
    }
}