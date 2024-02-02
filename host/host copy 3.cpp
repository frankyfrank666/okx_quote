#include "host.h"
#include "../src/common/utils.h"

int BUFFER_BLOCK = 256;

void Poll(FPGA& fpga, std::vector<EthernetAxi64, aligned_allocator<EthernetAxi64>>& ethernet_output_mem, cl::Buffer& ethernet_out_buf)
{
    fpga.mQueue.enqueueTask(fpga.mKernelEthOutTop);
    fpga.mQueue.enqueueMigrateMemObjects({ethernet_out_buf}, CL_MIGRATE_MEM_OBJECT_HOST);
    fpga.mQueue.finish();

    for(int i = 0; i < BUFFER_BLOCK; i++)
    {
        EthernetAxi64 x = ethernet_output_mem[i];
        std::cout << std::hex << x.data << '\n';
        if(x.last)
            break;
    }
}

void Input(const char* filename, FPGA& fpga, std::vector<EthernetAxi64, aligned_allocator<EthernetAxi64>>& ethernet_input_mem, cl::Buffer& ethernet_in_buf)
{

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
        // std::cout << std::dec <<  "Recv " << ++packetCount << std::endl;
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
            ethernet_input_mem[i/8] = (pkt);
            std::cout << std::hex << pkt.data << '\n';
        }
    }

    pcap_close(pcap);

    fpga.mQueue.enqueueMigrateMemObjects({ethernet_in_buf}, 0 /* 0 means from host*/);
    fpga.mQueue.enqueueTask(fpga.mKernelEthInTop);
    fpga.mQueue.finish();
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "Usage: " << argv[0] <<" <xclbin>" << std::endl;
        return EXIT_FAILURE;
    }
    char* xclbinFilename = argv[1];
    FPGA fpga(xclbinFilename);
    
    int buff_size = BUFFER_BLOCK * sizeof(EthernetAxi64);
    std::vector<EthernetAxi64, aligned_allocator<EthernetAxi64>> ethernet_input_mem(buff_size);
    std::vector<EthernetAxi64, aligned_allocator<EthernetAxi64>> ethernet_output_mem(buff_size);
    cl::Buffer ethernet_in_buf(fpga.mContext, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, buff_size,ethernet_input_mem.data());
    cl::Buffer ethernet_out_buf(fpga.mContext, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, buff_size,ethernet_output_mem.data());

    fpga.mKernelEthInTop.setArg(0, ethernet_in_buf);
    fpga.mKernelEthInTop.setArg(1, BUFFER_BLOCK);
    fpga.mKernelEthOutTop.setArg(0, ethernet_out_buf);
    fpga.mKernelEthOutTop.setArg(1, BUFFER_BLOCK);


    Poll(fpga, ethernet_output_mem, ethernet_out_buf);
    Input("/root/okx/src/Tcp/Test/pcaps/packet_2.pcap", fpga, ethernet_input_mem, ethernet_in_buf);

}