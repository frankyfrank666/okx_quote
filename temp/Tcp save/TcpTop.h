#ifndef COUNTER_H
#define COUNTER_H
#include "../common/utils.h"
#include "../Configurator/ConfiguratorTop.h"

/// @brief Processes ethernet input streams
/// @param tcpConfig Tcp configurations
/// @param askPxInt Integer part of Ask Price (passed to host via register)
/// @param askPxDec Decimal part of Ask Price (passed to host via register)
/// @param askSz Ask Volume of Ask Price (passed to host via register)
/// @param ethernet_stream_in 64-bit ethernet stream
void InputProcessor(Configuration& tcpConfig, ap_uint<32>& askPxInt, ap_uint<32>& askPxDec, ap_uint<32>& askSz, hls::stream<EthernetAxi64>& ethernet_stream_in);//, hls::stream<EthernetAxi64>& toPayloadParser_out)
// void InputProcessor(Configuration& tcpConfig, hls::stream<EthernetAxi64>& ethernet_stream_in, hls::stream<EthernetAxi64>& payloadStreamOut);

/// @brief A that examines and parse the http body and obtain askPx and askSz 
/// (this should have been a separate module and obtain ethernet body stream but somehow this way it sucks at synthesis)
/// @param askPxInt Integer part of Ask Price
/// @param askPxDec Decimal part of Ask Price
/// @param askSz Ask Volume
/// @param last Last segment (last = 1 for all 1 ~ 8 bytes but we don't expect any wanted data there right now)
/// @param character 8-bit char
int PayloadParserHelper(ap_uint<32>& askPxInt, ap_uint<32>& askPxDec, ap_uint<32>& askSz, ap_uint<1> last, ap_uint<8> character); //too many adders to parse ASCII to num, no way to meet 3ns timing
// void PayloadParser(ap_uint<32>& askPxInt, ap_uint<32>& askPxDec, ap_uint<32>& askSz, hls::stream<EthernetAxi64>& payloadStreamIn);

extern "C" {
    /// @brief Tcp kernel, handles Tcp Connection and Response. With sub-modules communicating via internal streams. 
    /// (Config and Status Registers are used instead of configuration stream from other one-time kernels)
    /// @param mDelaycycle Input Register for counter period // Counter not included yet
    /// @param mMyIp Input Register Tcp Connection information
    /// @param mMyMac Input Register 
    /// @param mMyPort Input Register 
    /// @param mTargetIp Input Register 
    /// @param mTargetMac Input Register 
    /// @param mTargetPort Input Register 
    /// @param mCommand Input Register - command from host for connection / disconnection
    /// @param mAskPriceInt Output Register
    /// @param mAskPriceDec Output Register
    /// @param mAskVol Output Register
    /// @param ethernet_stream_in Ethernet Input
    /// @param ethernet_stream_out Ethernet Output // not implemented yet
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
        // hls::stream<EthernetAxi64>& ethernet_stream_out,
    );
}


#endif