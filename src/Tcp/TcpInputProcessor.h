#ifndef TCPPROCE_H
#define TCPPROCE_H
#include "TcpTop.h"

enum class TcpProcState
{
    MacDest,
    MacSrc,
    Protocol,
    SrcIp,
    DestIp,
    SeqAckNumber,
};

enum class HttpProcessingState
{
    IpTcpHeader,
    HttpHeader,
    HttpHeader2,
    HttpHeader3,
    Payload,
    Discard,
};

class TcpHeaderProcessor
{
public:
    ap_uint<32> mSrcIp;
    ap_uint<64> mSrcMac;

    ap_uint<32> mDestIp;
    ap_uint<64> mDestMac;

    ap_uint<16> mType;
    ap_uint<16> mVersionAndHeaderLenDSCP;
    ap_uint<16> mEthHeaderLen;
    ap_uint<16> mIpTotalLength;
    ap_uint<16> mId;
    ap_uint<16> mFlags;
    ap_uint<16> mProtocol;

    ap_uint<16> mSrcPort;
    ap_uint<16> mDestPort;
    ap_uint<32> mSeqNum;
    ap_uint<32> mAckNum;

    ap_uint<8> mTcpHeaderLen;
    ap_uint<4> mTcpFlag;

    bool processSegment(EthernetAxi64 in)
    {
#pragma hls inline
        static TcpProcState state = TcpProcState::MacDest;
        switch (state)
        {
            case TcpProcState::MacDest:
            {
            //std::cout<<"case TcpProcState::MacDest:\n";
                mDestMac = in.data(63, 16);
                mSrcMac(47, 32) = in.data(15, 0);
                state = TcpProcState::MacSrc;
                break;
            }
            case TcpProcState::MacSrc:
            {
            //std::cout<<"case TcpProcState::MacSrc:\n";
                mSrcMac(31, 0) = in.data(63, 32);
                mType = in.data(31, 16); //0x0800 == ipv4
                mVersionAndHeaderLenDSCP = in.data(15, 0); //0x4500
                mEthHeaderLen = in.data(11, 8); //0x5
                state = TcpProcState::Protocol;
                break;
            }
            case TcpProcState::Protocol:
            {
            //std::cout<<"case TcpProcState::Protocol:\n";
                mIpTotalLength = in.data(63, 48); //0x4500
                mId = in.data(47, 32); //0x4500
                mFlags = in.data(31, 16); //0x4000 do not fragment
                mProtocol = in.data(7, 0); //TTL_PROTOCOL=6->Tcp
                state = TcpProcState::SrcIp;
                break;
            }
            case TcpProcState::SrcIp:
            {
            //std::cout<<"case TcpProcState::SrcIp:\n";
                mSrcIp = in.data(47, 16);
                mDestIp(31, 16) = in.data(15, 0);
                state = TcpProcState::DestIp;
                break;
            }
            case TcpProcState::DestIp:
            {
            //std::cout<<"case TcpProcState::DestIp:\n";
                mDestIp(15, 0) = in.data(63, 48);
                mSrcPort(15, 0) = in.data(47, 32);
                mDestPort(15, 0) = in.data(31, 16);
                mSeqNum(31, 16) = in.data(15, 0);
                state = TcpProcState::SeqAckNumber;
                break;
            }
            case TcpProcState::SeqAckNumber:
            {
            //std::cout<<"case TcpProcState::SeqAckNumber:\n";
                mSeqNum(15, 0) = in.data(63, 48);
                mAckNum(31, 0) = in.data(47, 16);
                mTcpHeaderLen(7, 0) = in.data(15, 12);
                mTcpFlag(3,0) = (in.data(4,4),in.data(2, 0)); //Ack Reset, Syn, Fin
                state = TcpProcState::MacDest;
                return true;
                break;
            }
        }
        return false;
    }
};

#endif