#include "TcpInputProcessor.h"

void InputProcessor(Configuration& tcpConfig, ap_uint<32>& askPxInt, ap_uint<32>& askPxDec, ap_uint<32>& askSz, hls::stream<ethernetAxi64>& eth_in)//, hls::stream<ethernetAxi64>& toPayloadParser_out)
{
    static TcpHeaderProcessor TcpHeaderProcessor;
    static HttpProcessingState inputProcState = HttpProcessingState::IpTcpHeader;
    ethernetAxi64 packet_in;

    if(eth_in.read_nb(packet_in))
    {
        switch (inputProcState)
        {
            case HttpProcessingState::IpTcpHeader:
            {
            //std::cout << "case HttpProcessingState::IpTcpHeader:\n";
                if(TcpHeaderProcessor.processSegment(packet_in))
                {
                    //std::cout << std::hex << "\n" <<TcpHeaderProcessor.mDestMac;
                    //std::cout << std::hex << "\n" <<tcpConfig.mMyMac ;

                    //std::cout << std::hex << "\n" <<TcpHeaderProcessor.mDestIp ;
                    //std::cout << std::hex << "\n" <<tcpConfig.mMyIp ;

                    //std::cout << std::hex << "\n" <<TcpHeaderProcessor.mSrcIp ;
                    //std::cout << std::hex << "\n" <<tcpConfig.mTargetIp;
                    //std::cout << std::hex << "\n";
                    
                    if (
                        TcpHeaderProcessor.mDestMac != tcpConfig.mMyMac ||
                        TcpHeaderProcessor.mDestIp != tcpConfig.mMyIp ||
                        TcpHeaderProcessor.mDestPort != tcpConfig.mMyPort ||

                        TcpHeaderProcessor.mSrcIp != tcpConfig.mTargetIp ||
                        TcpHeaderProcessor.mSrcPort != tcpConfig.mTargetPort ||

                        TcpHeaderProcessor.mProtocol != 0x06 || //TCP
                        TcpHeaderProcessor.mType != 0x0800 || //IPv4
                        TcpHeaderProcessor.mVersionAndHeaderLenDSCP != 0x4500 //TCP
                    )
                    {
                        inputProcState = HttpProcessingState::Discard;
                    }
                    else
                    {
                        inputProcState = HttpProcessingState::HttpHeader;
                    }
                }
                break;
            }
            case HttpProcessingState::HttpHeader:
            {
            //std::cout << "case HttpProcessingState::HttpHeader:\n";
                if (packet_in.data(15, 0) != 0x4854 ) //"HT"
                    inputProcState = HttpProcessingState::Discard;
                else
                    inputProcState = HttpProcessingState::HttpHeader2;
                break;
            }
            case HttpProcessingState::HttpHeader2:
            {
            //std::cout << "case HttpProcessingState::HttpHeader2:\n";
                if (packet_in.data(63, 0) != 0x54502f312e312032) //"TP/1.1 2")
                    inputProcState = HttpProcessingState::Discard;
                else
                    inputProcState = HttpProcessingState::HttpHeader3;
                break;
            }
            case HttpProcessingState::HttpHeader3:
            {
            //std::cout << "case HttpProcessingState::HttpHeader3:\n";
                if (packet_in.data(63, 24) != 0x3030204f4b) //"00 OK\r\n")
                    inputProcState = HttpProcessingState::Discard;
                else
                    inputProcState = HttpProcessingState::Payload;
                break;
            }
            case HttpProcessingState::Payload:
            {
                //std::cout << "case HttpProcessingState::Payload:\n";
                // toPayloadParser_out.write(packet_in);
                for (int i = 63; i > 0; i = i-8 )
                {
            #pragma hls unroll 
                    PayloadParserHelper(askPxInt, askPxDec, askSz, packet_in.last, packet_in.data(i, i - 7)); //Try make this single cycle.
                }
                break;
            }
            case HttpProcessingState::Discard:
            {
            //std::cout << "case HttpProcessingState::Discard:\n";
                break;
            }
        }

        if (packet_in.last)
            inputProcState = HttpProcessingState::IpTcpHeader;
    }
}