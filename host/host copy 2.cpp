#include "host.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "Usage: " << argv[0] <<" <xclbin>" << std::endl;
        return EXIT_FAILURE;
    }
    char* xclbinFilename = argv[1];
    FPGA fpga(xclbinFilename);
    
    int buff_size = 20;
    WriteToFpgaBuffer<long> ethInBuffer(fpga.mQueue,fpga.mContext, buff_size * sizeof(long));
    ReadFromFpgaBuffer<long> ethOutBuffer(fpga.mQueue,fpga.mContext, buff_size * sizeof(long));

    for(int i = 0; i < 10; ++i)
    {
        ethInBuffer.mPtr[i] = i;
    }

    ethInBuffer.syncBuffer();

    fpga.mKernelEthInTop.setArg(0,ethInBuffer.mBuffer);
    fpga.mKernelEthInTop.setArg(1,10);
    fpga.mKernelEthInTop.setArg(2,0b1111);
    fpga.mQueue.enqueueTask(fpga.mKernelEthInTop);
    std::cout << "123\n";
    fpga.wait();

    fpga.mKernelEthOutTop.setArg(0,ethOutBuffer.mBuffer);
    fpga.mKernelEthOutTop.setArg(1,10);
    fpga.mQueue.enqueueTask(fpga.mKernelEthOutTop);
    std::cout << "456\n";

    fpga.wait();
    std::cout << "789\n";

    ethOutBuffer.syncBuffer();

    for(int i = 0; i < 11; i++)
    {
        std::cout << ethInBuffer.mPtr[i] << ' ';
        std::cout << ethOutBuffer.mPtr[i] << '\n';
        if ( (ap_uint<64> *)((void*)ethOutBuffer.mPtr[i]) == 0xeeeeeeeeffffffff)
            break;
    }
}