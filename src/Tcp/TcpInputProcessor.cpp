#include "TcpInputProcessor.h"

void InputProcessor(TcpConfig& tcpConfig, ap_uint<32>& askPxInt, ap_uint<32>& askPxDec, ap_uint<32>& askSz, ap_uint<32>& outputCount, 
hls::stream<EthernetAxi64>& ethernet_stream_in, hls::stream<TcpMeta>& tcp_recv_stream_out)
{
#pragma hls pipeline ii=1

    static TcpHeaderProcessor tcpHeaderProcessor;
    static HttpProcessingState inputProcState = HttpProcessingState::IpTcpHeader;
    EthernetAxi64 packetIn;

    if(ethernet_stream_in.read_nb(packetIn))
    {
        switch (inputProcState)
        {
            case HttpProcessingState::IpTcpHeader:
            {
            //std::cout << "case HttpProcessingState::IpTcpHeader:\n";
                if(tcpHeaderProcessor.processSegment(packetIn))
                {
                    // std::cout << std::hex << "\n" <<tcpHeaderProcessor.mDestMac;
                    // std::cout << std::hex << "\n" <<tcpConfig.mMyMac ;

                    // std::cout << std::hex << "\n" <<tcpHeaderProcessor.mDestIp ;
                    // std::cout << std::hex << "\n" <<tcpConfig.mMyIp ;

                    // std::cout << std::hex << "\n" <<tcpHeaderProcessor.mSrcIp ;
                    // std::cout << std::hex << "\n" <<tcpConfig.mTargetIp;
                    // std::cout << std::hex << "\n";
                    
                    if (
                        tcpHeaderProcessor.mDestMac != tcpConfig.mMyMac ||
                        tcpHeaderProcessor.mDestIp != tcpConfig.mMyIp ||
                        tcpHeaderProcessor.mDestPort != tcpConfig.mMyPort ||

                        tcpHeaderProcessor.mSrcIp != tcpConfig.mTargetIp ||
                        tcpHeaderProcessor.mSrcPort != tcpConfig.mTargetPort ||

                        tcpHeaderProcessor.mProtocol != 0x06 || //TCP
                        tcpHeaderProcessor.mType != 0x0800 || //IPv4
                        tcpHeaderProcessor.mVersionAndHeaderLenDSCP != 0x4500 //TCP
                    )
                    {
                        inputProcState = HttpProcessingState::Discard;
                    }
                    else
                    {
                        TcpMeta meta;
                        meta.mTcpPayloadLength = tcpHeaderProcessor.mTcpFlag(1,1) + tcpHeaderProcessor.mTcpFlag(0,0) +
                                                 tcpHeaderProcessor.mIpTotalLength - tcpHeaderProcessor.mEthHeaderLen * 4
                                                 - tcpHeaderProcessor.mTcpHeaderLen * 4;
                        meta.mSeqNum = tcpHeaderProcessor.mSeqNum;
                        meta.mAckNum = tcpHeaderProcessor.mAckNum;
                        meta.mAck = tcpHeaderProcessor.mTcpFlag(3,3);
                        meta.mRst = tcpHeaderProcessor.mTcpFlag(2,2);
                        meta.mSyn = tcpHeaderProcessor.mTcpFlag(1,1);
                        meta.mFin = tcpHeaderProcessor.mTcpFlag(0,0);
                        tcp_recv_stream_out.write(meta);
                        inputProcState = HttpProcessingState::HttpHeader;
                    }
                }
                break;
            }
            case HttpProcessingState::HttpHeader:
            {
            //std::cout << "case HttpProcessingState::HttpHeader:\n";
                if (packetIn.data(15, 0) != 0x4854 ) //"HT"
                    inputProcState = HttpProcessingState::Discard;
                else
                    inputProcState = HttpProcessingState::HttpHeader2;
                break;
            }
            case HttpProcessingState::HttpHeader2:
            {
            //std::cout << "case HttpProcessingState::HttpHeader2:\n";
                if (packetIn.data(63, 0) != 0x54502f312e312032) //"TP/1.1 2")
                    inputProcState = HttpProcessingState::Discard;
                else
                    inputProcState = HttpProcessingState::HttpHeader3;
                break;
            }
            case HttpProcessingState::HttpHeader3:
            {
            //std::cout << "case HttpProcessingState::HttpHeader3:\n";
                if (packetIn.data(63, 24) != 0x3030204f4b) //"00 OK\r\n")
                    inputProcState = HttpProcessingState::Discard;
                else
                    inputProcState = HttpProcessingState::Payload;
                break;
            }
            case HttpProcessingState::Payload:
            {
                //std::cout << "case HttpProcessingState::Payload:\n";
                for (int i = 63; i > 0; i = i-8 )
                {
            #pragma hls unroll 
                    PayloadParserHelper(askPxInt, askPxDec, askSz, outputCount, packetIn.last, packetIn.data(i, i - 7)); //Try make this single cycle.
                }
                break;
            }
            case HttpProcessingState::Discard:
            {
            // std::cout << "case HttpProcessingState::Discard:\n";
                break;
            }
        }

        if (packetIn.last)
            inputProcState = HttpProcessingState::IpTcpHeader;
    }
}