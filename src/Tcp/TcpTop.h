#ifndef TCP_H
#define TCP_H

#include "../common/utils.h"

struct TcpConfig
{
    ap_uint<32> mDelayCycle; // 3s
    ap_uint<32> mMyIp; //FPGA IP and MAC
    ap_uint<64> mMyMac; 
    ap_uint<64> mMyPort;
    ap_uint<32> mTargetIp;
    ap_uint<64> mTargetMac; //Of course, it is the router, not the actual okx server, need ARP or static router in production. 
    ap_uint<64> mTargetPort;
    ap_uint<32> mCommand; 
};

class TcpCommand
{
public:
    static constexpr int Connect = 1;
    static constexpr int Close = 2;
    static constexpr int Reset = 3;
};

struct TcpMeta
{
    ap_uint<32> mTcpPayloadLength = 0;
    ap_uint<32> mSeqNum = 0;
    ap_uint<32> mAckNum = 0;
    ap_uint<1>  mSyn = 0;
    ap_uint<1>  mAck = 0;
    ap_uint<1>  mFin = 0;
    ap_uint<1>  mPsh = 0;
    ap_uint<1>  mRst = 0;
    ap_uint<1>  mIsRequest = 0;
};

/// @brief Ethernet input processor
///
/// Process input data from Ethernet stream, parse the Json payload for askPx and Sz and forward important Tcp data to Tcp Manager..
///
/// @param tcpConfig The TCP configuration.
/// @param askPxInt The register to store the ask price integer.
/// @param askPxDec The register to store the ask price decimal.
/// @param askSz The register to store the ask size.
/// @param outputCount The register to store the output count, to indicate valid and new outputs.
/// @param ethernet_stream_in Ethernet stream input.
/// @param tcp_recv_stream_out Output TCP metadata to TCP Manager.
void InputProcessor(TcpConfig& tcpConfig, 
ap_uint<32>& askPxInt,ap_uint<32>& askPxDec, 
ap_uint<32>& askSz, 
ap_uint<32>& outputCount, 
hls::stream<EthernetAxi64>& ethernet_stream_in, 
hls::stream<TcpMeta>& tcp_recv_stream_out);

/// @brief Helper function for parsing payload data.
///
/// This function is a helper function for parsing payload data. It updates the values of the provided registers based on the received payload character.
///
/// @param askPxInt The register to store the ask price integer.
/// @param askPxDec The register to store the ask price decimal.
/// @param askSz The register to store the ask size.
/// @param outputCount The register to store the output count.
/// @param last Indicates whether it is the last segment in the payload.
/// @param character A payload character.
void PayloadParserHelper(ap_uint<32>& askPxInt, 
ap_uint<32>& askPxDec, 
ap_uint<32>& askSz, 
ap_uint<32>& outputCount, 
ap_uint<1> last, 
ap_uint<8> character);

/// @brief TCP Manager function.
///
/// This function managest TCP connection, including processing ticks and commands and tells sender to send packets accordingly.
///
/// @param tcpConfig The TCP configuration.
/// @param tick_stream_in The input tick stream.
/// @param tcp_recv_stream_in The TCP meta data received.
/// @param tcp_send_stream_out The TCP meta data to send out.
void Manager(
    TcpConfig& tcpConfig, 
    hls::stream<ap_uint<1>>& tick_stream_in, 
    hls::stream<TcpMeta>& tcp_recv_stream_in, 
    hls::stream<TcpMeta>& tcp_send_stream_out
);

/// @brief TCP sender function.
///
/// This function handles sending TCP packets according to the instruction from Manager.
///
/// @param tcpConfig The TCP configuration.
/// @param tcp_send_stream_in The input TCP information to send.
/// @param ethernet_stream_out The output Ethernet stream.
void Sender(
    TcpConfig& tcpConfig, 
    hls::stream<TcpMeta>& tcp_send_stream_in, 
    hls::stream<EthernetAxi64>& ethernet_stream_out
);

/// @brief Counter function.
///
/// This function send ticks to regularly send GET.
///
/// @param tcpConfig The TCP configuration.
/// @param tick_stream_out The output tick stream.
void Counter(
    TcpConfig& tcpConfig,
    hls::stream<ap_uint<1>>& tick_stream_out
);


extern "C" {
/// @brief Top-level TCP function.
///
/// This is the top-level function for the TCP operation.
///
/// @param mDelayCycle The delay cycle value. These are registers.
/// @param mMyIp The IP address of the FPGA.
/// @param mMyMac The MAC address of the FPGA.
/// @param mMyPort The port number of the FPGA.
/// @param mTargetIp The target IP address.
/// @param mTargetMac The target MAC address.
/// @param mTargetPort The target port number.
/// @param mCommand The TCP command.
/// @param mAskPriceInt The register to store the ask price integer.
/// @param mAskPriceDec The register to store the ask price decimal.
/// @param mAskVol The register to store the ask volume.
/// @param mOutputCount The register to store the output count.
/// @param ethernet_stream_in The input Ethernet stream.
/// @param ethernet_stream_out The output Ethernet stream.
    void TcpTop(
        ap_uint<32> mDelayCycle, // 3s
        ap_uint<32> mMyIp, //FPGA IP and MAC
        ap_uint<64> mMyMac, 
        ap_uint<64> mMyPort,
        ap_uint<32> mTargetIp,
        ap_uint<64> mTargetMac, //Of course, it is the router, not the actual okx server, need ARP or static router in production. 
        ap_uint<64> mTargetPort,
        ap_uint<32> mCommand,

        ap_uint<32>& mAskPriceInt,
        ap_uint<32>& mAskPriceDec,
        ap_uint<32>& mAskVol, 
        ap_uint<32>& mOutputCount, 
        
        hls::stream<EthernetAxi64>& ethernet_stream_in,
        hls::stream<EthernetAxi64>& ethernet_stream_out
    );
}

#endif