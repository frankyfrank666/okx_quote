#include <iostream>
#include <pcap.h>
#include "../TcpTop.h"

hls::stream<EthernetAxi64> ethernet_stream_in("ethernet_stream_in");
hls::stream<EthernetAxi64> ethernet_stream_out("ethernet_stream_out");
static int packetCount = 0;

void replayPcap(const char* filename) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* pcap = pcap_open_offline(filename,errbuf);

    if (pcap == nullptr)
    {
        std::cerr << "Error opening pcap file: " << errbuf << std::endl;
        return;
    }

    struct pcap_pkthdr* header;
    const u_char* packetData;

    while (pcap_next_ex(pcap,&header,&packetData) == 1) {
        std::cout << std::dec <<  "Recv " << ++packetCount << std::endl;
        ap_uint<8> keep = 0;
        for(int i = 0; i < header->caplen % 8; ++i)
        {
            keep(7-i,7-i) = ap_uint<1>(1);
        }

        for (int i = 0; i < header->caplen; i += 8) {
            uint64_t value = *(reinterpret_cast<const uint64_t*>(packetData + i));
            EthernetAxi64 pkt;
            pkt.data = byte_reverse<64>(value);
            pkt.last = ((i + 8) < header->caplen ) ? 0 : 1;
            pkt.keep = ((i + 8) < header->caplen ) ? ap_uint<8>(0xFF) : keep;
            ethernet_stream_in.write(pkt);
        }
    }

    pcap_close(pcap);
}

static ap_uint<32> mCommand; //Bug when passed as arg.
void run(int n, int tick)
{
    ap_uint<32> mDelayCycle = tick;
    ap_uint<32> mMyIp = 0xc0a81203;
    ap_uint<48> mMyMac = 0x5c879c506405;
    ap_uint<48> mMyPort = 0xde1b ;
    ap_uint<32> mTargetIp = 0x12b59708;
    ap_uint<48> mTargetMac = 0xac8fa9a9ec21;
    ap_uint<48> mTargetPort = 0x17c9;

    ap_uint<32> mAskPriceInt;
    ap_uint<32> mAskPriceDec;
    ap_uint<32> mAskVol;
    ap_uint<32> mOutputCount;

    static int tempOutputCount = -1;
    
    for(int i; i < n; ++i)
    {
        TcpTop(mDelayCycle,mMyIp,mMyMac,mMyPort,mTargetIp,mTargetMac,mTargetPort,mCommand,mAskPriceInt,mAskPriceDec,mAskVol,mOutputCount,ethernet_stream_in,ethernet_stream_out);
        if (!ethernet_stream_out.empty())
        {
            auto x = ethernet_stream_out.read();
            std::cout << std::hex << x.data <<std::endl;
            if(x.last)
            {
                std::cout << std::dec << "^Sent " << ++packetCount << std::endl;
            }
        }
        if (tempOutputCount + 1 == mOutputCount)
        {
            tempOutputCount = mOutputCount;
            std::cout << "New Quote " << mOutputCount << std::dec << " " << mAskPriceInt << '.' << mAskPriceDec << ' ' << mAskVol << "\n";
        }
    }
}


int main() {
    mCommand = TcpCommand::Connect;;
    run(500,0); //Send SYN 1
    replayPcap("/root/okx/src/Tcp/Test/pcaps/packet_2.pcap");
    run(500,300); //Send Ack 3 Send GET 4
    replayPcap("/root/okx/src/Tcp/Test/pcaps/packet_5.pcap"); 
    run(500,0); //Must not reply the Ack to our GET
    replayPcap("/root/okx/src/Tcp/Test/pcaps/packet_6.pcap");
    run(500,300); //Reply Ack to Json + Send GET 8
    replayPcap("/root/okx/src/Tcp/Test/pcaps/packet_9.pcap");
    replayPcap("/root/okx/src/Tcp/Test/pcaps/packet_10.pcap");
    run(500,0); //Ack for json 11
    replayPcap("/root/okx/src/Tcp/Test/pcaps/packet_12.pcap"); // keep alive
    run(500,300); //Reply Ack to Json 13 + GET 14
    replayPcap("/root/okx/src/Tcp/Test/pcaps/packet_15.pcap"); 
    replayPcap("/root/okx/src/Tcp/Test/pcaps/packet_16.pcap"); 
    run(500,0); //Reply Ack to Json 17
    replayPcap("/root/okx/src/Tcp/Test/pcaps/packet_18.pcap"); 
    run(500,0); //Reply Ack to Keep Alive 19
    replayPcap("/root/okx/src/Tcp/Test/pcaps/packet_20.pcap"); 
    run(500,0); //Reply Ack to Keep Alive 21
    mCommand = TcpCommand::Close;
    run(500,0); //Close 22
    replayPcap("/root/okx/src/Tcp/Test/pcaps/packet_23.pcap"); 
    run(500,0); //Ack to FinAck

    return 0;
}
