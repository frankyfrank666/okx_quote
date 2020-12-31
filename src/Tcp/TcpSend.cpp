#include "TcpSend.h"

void Sender(TcpConfig& tcpConfig, hls::stream<TcpMeta>& tcp_send_stream_in, hls::stream<EthernetAxi64>& ethernet_stream_out)
{
#pragma hls pipeline ii=1
    static bool busy = false;
    static TcpSendState sendState = TcpSendState::DestMac;
    static TcpMeta replyConfig;
    static ap_uint<32> requestPointer;
    static ap_uint<16> ourId = BASE_ID;

    static ap_uint<32> headerChecksum = 0;
    static ap_uint<32> tcpChecksum = 0;

    EthernetAxi64 ethernetPacket;
    ethernetPacket.keep = 0xff;
    ethernetPacket.last = 0;

    if (!busy)
    {
       if (!tcp_send_stream_in.empty())
       {
            replyConfig = tcp_send_stream_in.read();
            busy = true;
       }
    }
    else
    {
        switch (sendState)
        {
            case TcpSendState::DestMac:
            {
                ethernetPacket.data(63, 16) = tcpConfig.mTargetMac;
                ethernetPacket.data(15, 0) = tcpConfig.mMyMac(47, 32);
                sendState = TcpSendState::SrcMac;
                break;
            }
            case TcpSendState::SrcMac:
            {
                ethernetPacket.data(63, 32) = tcpConfig.mMyMac(31, 0);
                ethernetPacket.data(31, 0) = iPv4Dscp;
                sendState = TcpSendState::TotalLenDSCPTcp;
                break;
            }
            case TcpSendState::TotalLenDSCPTcp:
            {
                if (replyConfig.mIsRequest==1)
                    ethernetPacket.data(63, 48) = totalLenGET;
                else
                    ethernetPacket.data(63, 48) = totalLen;
                ethernetPacket.data(47, 32) = ourId++;
                ethernetPacket.data(31, 0) = doNotFragTtlTcp;

                sendState = TcpSendState::HeaderChecksumAndDestIp;
                break;
            }
            case TcpSendState::HeaderChecksumAndDestIp:
            {
                ethernetPacket.data(63, 48) = headerChecksum;
                ethernetPacket.data(47, 16) = tcpConfig.mMyIp;
                ethernetPacket.data(15, 0) = tcpConfig.mTargetIp(31,16);
                sendState = TcpSendState::SeqNumber;
                break;
            }
            case TcpSendState::SeqNumber:
            {
                ethernetPacket.data(63, 48) = tcpConfig.mTargetIp(15,0);
                ethernetPacket.data(47, 32) = tcpConfig.mMyPort;
                ethernetPacket.data(31, 16) = tcpConfig.mTargetPort;
                ethernetPacket.data(15, 0) = replyConfig.mSeqNum(31,16);
                sendState = TcpSendState::AckNumber;
                break;
            }
            case TcpSendState::AckNumber:
            {
                ethernetPacket.data(63, 48) = replyConfig.mSeqNum(15,0);
                ethernetPacket.data(47, 16) = replyConfig.mAckNum(31,0);
                ethernetPacket.data(15, 8) = 0x50;

                ethernetPacket.data(7, 0) = 0;
                if (replyConfig.mSyn)
                    ethernetPacket.data(7, 0) |= flagsSyn;
                if (replyConfig.mAck)
                    ethernetPacket.data(7, 0) |= flagsAck;
                if (replyConfig.mFin)
                    ethernetPacket.data(7, 0) |= flagsFin;
                if (replyConfig.mPsh)
                    ethernetPacket.data(7, 0) |= flagsPsh;
                if (replyConfig.mRst)
                    ethernetPacket.data(7, 0) |= flagsRst;

                sendState = TcpSendState::TcpChecksum;
                break;
            }
            case TcpSendState::TcpChecksum:
            {
                ethernetPacket.data(63, 48) = window;
                ethernetPacket.data(47, 32) = tcpChecksum;
                ethernetPacket.data(31, 0)  = 0;
                if (replyConfig.mIsRequest == 1)
                {
                    sendState = TcpSendState::Request;
                    ethernetPacket.data |= request[0];
                    requestPointer = 1;
                }
                else
                {
                    ethernetPacket.keep = 0b11111100;
                    ethernetPacket.last = 1;
                    sendState = TcpSendState::DestMac;
                    busy = false;
                }
                break;
            }
            case TcpSendState::Request:
            {
                ethernetPacket.data = request[requestPointer];
                if (requestPointer < REQUEST_LEN)
                {
                    sendState = TcpSendState::Request;

                    if (requestPointer == REQUEST_LEN - 1)
                    {
                        requestPointer = 0;
                        ethernetPacket.last = 1;
                        sendState = TcpSendState::DestMac;
                        busy = false;
                    }
                    else
                    {
                        ++requestPointer;
                    }
                }

                break;
            }
        }
        ethernet_stream_out.write(ethernetPacket);
    }
}