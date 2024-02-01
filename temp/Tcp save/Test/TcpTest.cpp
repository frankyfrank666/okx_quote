// #include "../TcpTop.h"
#include <iostream>
#include <pcap.h>
#include "/root/okx/src/common/utils.h"
#include "../TcpTop.h"

void replayPcap(const char* filename, hls::stream<EthernetAxi64>& stream_out) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* pcap = pcap_open_offline(filename, errbuf);

    if (pcap == nullptr) {
        std::cerr << "Error opening pcap file: " << errbuf << std::endl;
        return;
    }

    struct pcap_pkthdr* header;
    const u_char* packetData;
    int packetCount = 0;

    while (pcap_next_ex(pcap, &header, &packetData) == 1) {
        std::cout << "Packet " << ++packetCount << ":" << std::endl;

        ap_uint<8> keep = 0;
        for(int i = 0; i < header->caplen % 8; ++i)
        {
            keep(7-i,7-i) = ap_uint<1>(1);
        }

        // std::cout << std::hex << keep;

        // Print the packet data as 32-bit hexadecimal values
        for (int i = 0; i < header->caplen; i += 8) {
            uint64_t value = *(reinterpret_cast<const uint64_t*>(packetData + i));
            // std::cout << std::hex << byte_reverse<64>(value) << std::endl;

            EthernetAxi64 pkt;
            pkt.data = byte_reverse<64>(value);
            pkt.last = ((i + 8) < header->caplen ) ? 0 : 1;
            pkt.keep = ((i + 8) < header->caplen ) ? ap_uint<8>(0xFF) : keep;
            stream_out.write(pkt);
        }
    }

    pcap_close(pcap);
}

int main() {
    hls::stream<EthernetAxi64> ethernet_stream_input_stream("ethernet_stream_in_stream");
    replayPcap("/root/okx/src/Tcp/Test/pcaps/packet_6.pcap", ethernet_stream_input_stream);

    ap_uint<32> mDelaycycle = 10000;
    
    ap_uint<32> mMyIp = 0xc0a81203;
    ap_uint<48> mMyMac = 0x5c879c506405;
    ap_uint<48> mMyPort = 62231 ;
    ap_uint<32> mTargetIp = 0x12b59708;
    ap_uint<48> mTargetMac = 0xac8fa9a9ec21;
    ap_uint<48> mTargetPort = 6089;

    ap_uint<32> mCommand = 123;
    
    ap_uint<32> mAskPriceInt;
    ap_uint<32> mAskPriceDec;
    ap_uint<32> mAskVol;

    while(!ethernet_stream_input_stream.empty())
        TcpTop(mDelaycycle, mMyIp, mMyMac, mMyPort, mTargetIp, mTargetMac, mTargetPort, mCommand, mAskPriceInt, mAskPriceDec, mAskVol, ethernet_stream_input_stream);
    




    std::cout << mAskPriceInt << '.' << mAskPriceDec << ' ' << mAskVol;
    return 0;
}
