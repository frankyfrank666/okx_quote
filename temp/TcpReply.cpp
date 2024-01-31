#include "TcpTop.h"

struct TcpReply
{
    Configuration mTcpConfig,
    ap_uint<32> mSeq,
    ap_uint<32> mAck,

    ap_uint<1> mSyn,
    ap_uint<1> mAck,
    ap_uint<1> mFin,
    ap_uint<1> mRst,
    ap_uint<1> mReq,
};

void Reply(hls::stream<TcpReply>& tcp_reply_in, hls::stream<ethernetAxi64>& eth_out)
{
    static TcpReply replyConfig;
    static bool free = true;

    if (free && !tcp_reply_in.empty())
    {
        replyConfig = tcp_reply_in.read();
    }
    else
    {

    }

}