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


}
    // cl_uint cuidx;
    // xcl::Ext::getComputeUnitInfo(fpga.mKernelTcpTop.get(), 0, XCL_COMPUTE_UNIT_INDEX, sizeof(cuidx), &cuidx, nullptr);
    // xclDeviceHandle handle;
    // clGetDeviceInfo(fpga.mDevice.get(), CL_DEVICE_HANDLE, sizeof(handle), &handle, nullptr);

    // size_t mDelayCycleOffset;      uint32_t mDelayCycle = 0;
    // size_t mMyIpOffset;      uint32_t mMyIp = 0xc0a81203;
    // size_t mMyMacOffset;      uint64_t mMyMac = 0x5c879c506405;
    // size_t mMyPortOffset;      uint64_t mMyPort = 0xde1b ;
    // size_t mTargetIpOffset;      uint32_t mTargetIp = 0x12b59708;
    // size_t mTargetMacOffset;      uint64_t mTargetMac = 0xac8fa9a9ec21;
    // size_t mTargetPortOffset;      uint64_t mTargetPort = 0x17c9;
    // size_t mCommandOffset;      uint32_t mCommand = 1;
    // size_t mAskPriceIntOffset;      uint32_t mAskPriceInt;
    // size_t mAskPriceDecOffset;      uint32_t mAskPriceDec;
    // size_t mAskVolOffset;      uint32_t mAskVol;
    // size_t mOutputCountOffset;      uint32_t mOutputCount;
    // clGetKernelArgInfo(fpga.mKernelTcpTop.get(), 0, CL_KERNEL_ARG_OFFSET, sizeof(mDelayCycleOffset), &mDelayCycleOffset, nullptr); //uint32_t mDelayCycle,
    // clGetKernelArgInfo(fpga.mKernelTcpTop.get(), 1, CL_KERNEL_ARG_OFFSET, sizeof(mMyIpOffset), &mMyIpOffset, nullptr); //uint32_t mMyIp,
    // clGetKernelArgInfo(fpga.mKernelTcpTop.get(), 2, CL_KERNEL_ARG_OFFSET, sizeof(mMyMacOffset), &mMyMacOffset, nullptr); //uint64_t mMyMac, 
    // clGetKernelArgInfo(fpga.mKernelTcpTop.get(), 3, CL_KERNEL_ARG_OFFSET, sizeof(mMyPortOffset), &mMyPortOffset, nullptr); //uint64_t mMyPort,
    // clGetKernelArgInfo(fpga.mKernelTcpTop.get(), 4, CL_KERNEL_ARG_OFFSET, sizeof(mTargetIpOffset), &mTargetIpOffset, nullptr); //uint32_t mTargetIp,
    // clGetKernelArgInfo(fpga.mKernelTcpTop.get(), 5, CL_KERNEL_ARG_OFFSET, sizeof(mTargetMacOffset), &mTargetMacOffset, nullptr); //uint64_t mTargetMac,
    // clGetKernelArgInfo(fpga.mKernelTcpTop.get(), 6, CL_KERNEL_ARG_OFFSET, sizeof(mTargetPortOffset), &mTargetPortOffset, nullptr); //uint64_t mTargetPort,
    // clGetKernelArgInfo(fpga.mKernelTcpTop.get(), 7, CL_KERNEL_ARG_OFFSET, sizeof(mCommandOffset), &mCommandOffset, nullptr); //uint32_t mCommand,
    // clGetKernelArgInfo(fpga.mKernelTcpTop.get(), 8, CL_KERNEL_ARG_OFFSET, sizeof(mAskPriceIntOffset), &mAskPriceIntOffset, nullptr); //uint32_t mAskPriceInt,
    // clGetKernelArgInfo(fpga.mKernelTcpTop.get(), 9, CL_KERNEL_ARG_OFFSET, sizeof(mAskPriceDecOffset), &mAskPriceDecOffset, nullptr); //uint32_t mAskPriceDec,
    // clGetKernelArgInfo(fpga.mKernelTcpTop.get(),10, CL_KERNEL_ARG_OFFSET, sizeof(mAskVolOffset), &mAskVolOffset, nullptr); //uint32_t mAskVol, 
    // clGetKernelArgInfo(fpga.mKernelTcpTop.get(),11, CL_KERNEL_ARG_OFFSET, sizeof(mOutputCountOffset), &mOutputCountOffset, nullptr); //uint32_t mOutputCount, 
    // xclOpenContext(handle, xclbinId, cuidx, false);
    // xclRegWrite(handle, cuidx, mDelayCycleOffset, mDelayCycle);
    // xclRegWrite(handle, cuidx, mMyIpOffset, mMyIp);
    // xclRegWrite(handle, cuidx, mMyMacOffset, mMyMac);
    // xclRegWrite(handle, cuidx, mMyPortOffset, mMyPort);
    // xclRegWrite(handle, cuidx, mTargetIpOffset, mTargetIp);
    // xclRegWrite(handle, cuidx, mTargetMacOffset, mTargetMac);
    // xclRegWrite(handle, cuidx, mTargetPortOffset, mTargetPort);
    // xclRegWrite(handle, cuidx, mCommandOffset, mCommand);
    // xclRegRead(handle, cuidx, mAskPriceIntOffset, &mAskPriceInt);
    // xclRegRead(handle, cuidx, mAskPriceDecOffset, &mAskPriceDec);
    // xclRegRead(handle, cuidx, mAskVolOffset     , &mAskVol);
    // xclRegRead(handle, cuidx, mOutputCountOffset, &mOutputCount);
    // xclCloseContext(handle, xclbinId, cuidx);

    // Poll(fpga, ethernet_output_mem, ethernet_out_buf);
    // Input("/root/okx/src/Tcp/Test/pcaps/packet_2.pcap", fpga, ethernet_input_mem, ethernet_in_buf);
