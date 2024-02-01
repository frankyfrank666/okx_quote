#include "TcpTop.h"

extern "C" {
    
    void TcpTop(
        ap_uint<32> mDelaycycle, // 3s
        ap_uint<32> mMyIp, //FPGA IP and MAC
        ap_uint<48> mMyMac, 
        ap_uint<48> mMyPort,
        ap_uint<32> mTargetIp,
        ap_uint<48> mTargetMac, //Of course, it is the router, not the actual okx server, need ARP or static router in production. 
        ap_uint<48> mTargetPort,
        ap_uint<32> mCommand,

        ap_uint<32>& mAskPriceInt,
        ap_uint<32>& mAskPriceDec,
        ap_uint<32>& mAskVol,
        hls::stream<EthernetAxi64>& ethernet_stream_in
    )
    {
#pragma hls interface s_axilite port=mDelaycycle
#pragma hls interface s_axilite port=mMyIp
#pragma hls interface s_axilite port=mMyMac
#pragma hls interface s_axilite port=mMyPort
#pragma hls interface s_axilite port=mTargetIp
#pragma hls interface s_axilite port=mTargetMac
#pragma hls interface s_axilite port=mTargetPort
#pragma hls interface s_axilite port=mCommand
#pragma hls interface s_axilite port=mAskPriceInt
#pragma hls interface s_axilite port=mAskPriceDec
#pragma hls interface s_axilite port=mAskVol
#pragma hls interface axis port=ethernet_stream_in
#pragma hls interface ap_ctrl_none port=return

#pragma hls dataflow

        Configuration tcpConfig;
        tcpConfig.mDelaycycle = mDelaycycle;
        tcpConfig.mMyIp = mMyIp;
        tcpConfig.mMyMac = mMyMac;
        tcpConfig.mMyPort = mMyPort;
        tcpConfig.mTargetIp = mTargetIp;
        tcpConfig.mTargetMac = mTargetMac;
        tcpConfig.mTargetPort = mTargetPort;
        tcpConfig.mCommand = mCommand;

        hls::stream<EthernetAxi64> toPayloadParser;
        InputProcessor(tcpConfig, mAskPriceInt, mAskPriceDec, mAskVol, ethernet_stream_in);
        // , toPayloadParser);
        // PayloadParser(mAskPriceInt, mAskPriceDec, mAskVol, toPayloadParser);
    }
}

