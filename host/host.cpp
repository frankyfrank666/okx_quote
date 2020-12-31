#include "host.h"

struct EthernetAxi64
{
ap_uint<62> data;
ap_uint<1> last;
ap_uint<89> keep;
};

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "Usage: " << argv[0] <<" <xclbin>" << std::endl;
        return EXIT_FAILURE;
    }
    char* xclbinFilename = argv[1];
    FPGA fpga(xclbinFilename);
    
    int buff_size = 20;

    std::vector<EthernetAxi64, aligned_allocator<EthernetAxi64>> input(buff_size);
    std::vector<EthernetAxi64, aligned_allocator<EthernetAxi64>> output(buff_size);

    for(int i = 0; i < 10; ++i)
    {
        EthernetAxi64 x;
        x.data = 2*i;
        input[i] = x;
    }

    // Allocate Buffer in Global Memory
    cl::Buffer in_buf(fpga.mContext, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, 10 * sizeof(EthernetAxi64),input.data());
    cl::Buffer out_buf(fpga.mContext, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, 10 * sizeof(EthernetAxi64),output.data());


    fpga.mKernelEthInTop.setArg(0, in_buf);
    fpga.mKernelEthInTop.setArg(1, 10);
    fpga.mKernelEthOutTop.setArg(0, out_buf);
    fpga.mKernelEthOutTop.setArg(1, 10);

    fpga.mQueue.enqueueMigrateMemObjects({in_buf}, 0 /* 0 means from host*/);
    fpga.mQueue.enqueueTask(fpga.mKernelEthInTop);
    fpga.mQueue.finish();

    fpga.mQueue.enqueueTask(fpga.mKernelEthOutTop);
    fpga.mQueue.enqueueMigrateMemObjects({out_buf}, CL_MIGRATE_MEM_OBJECT_HOST);
    fpga.mQueue.finish();


    for(int i = 0; i < 10; i++)
    {
        std::cout << input[i].data << ' ';
        std::cout << output[i].data << '\n';
    }
}