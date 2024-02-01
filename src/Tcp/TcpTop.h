#ifndef TCP_H
#define TCP_H

#include "../common/utils.h"

using EthernetAxi64 = ap_axiu<64,0,0,0>;

struct TcpConfig
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

class TcpCommand
{
public:
    static constexpr int Connect = 1;
    static constexpr int Close = 2;
    static constexpr int Reset = 3;
};

enum class TcpState
{
    Closed,
    SynSent,
    Establsihed,

    FinSent, //wait for finack and send ack and close
    FinSentWaitAck, //no need wait for their ack, send ack and close
    FinSentWaitFin, //wait for their fin and send ack and close

    FinAckSent, //they close, we finack and wait for thier ack
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

void InputProcessor(TcpConfig& tcpConfig, ap_uint<32>& askPxInt, ap_uint<32>& askPxDec, ap_uint<32>& askSz, ap_uint<32>& outputCount, hls::stream<EthernetAxi64>& ethernet_stream_in, hls::stream<TcpMeta>& tcp_recv_stream_out);
void PayloadParserHelper(ap_uint<32>& askPxInt, ap_uint<32>& askPxDec, ap_uint<32>& askSz, ap_uint<32>& outputCount, ap_uint<1> last, ap_uint<8> character);
void Manager(TcpConfig& tcpConfig, hls::stream<ap_uint<1>>& tick_stream_in, hls::stream<TcpMeta>& tcp_recv_stream_in, hls::stream<TcpMeta>& tcp_send_stream_out);
void Sender(TcpConfig& tcpConfig, hls::stream<TcpMeta>& tcp_send_stream_in, hls::stream<EthernetAxi64>& ethernet_stream_out);
void Counter(TcpConfig& tcpConfig, hls::stream<ap_uint<1>>& tick_stream_out);

extern "C" {
    void TcpTop(
        ap_uint<32> mDelayCycle, // 3s
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
        ap_uint<32>& mOutputCount, 
        
        hls::stream<EthernetAxi64>& ethernet_stream_in,
        hls::stream<EthernetAxi64>& ethernet_stream_out
    );
}

#endif