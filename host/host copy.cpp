#include "host.h"

static const int DATA_SIZE = 4096;

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "Usage: " << argv[0] <<" <xclbin>" << std::endl;
        return EXIT_FAILURE;
    }

    char* xclbinFilename = argv[1];
    FPGA fpga(xclbinFilename);
    
    size_t size_in_bytes = DATA_SIZE * sizeof(int);


    ReadFromFpgaBuffer<int> buffer_result(fpga.mQueue,fpga.mContext, size_in_bytes);
    WriteToFpgaBuffer<int> buffer_a(fpga.mQueue,fpga.mContext, size_in_bytes);
    WriteToFpgaBuffer<int> buffer_b(fpga.mQueue,fpga.mContext, size_in_bytes);
    
    int *ptr_a = buffer_a.mPtr; 
    int *ptr_b = buffer_b.mPtr; 

    //setting input data
    for(int i = 0 ; i< DATA_SIZE; i++){
	    ptr_a[i] = 10;
	    ptr_b[i] = 20;
    }

    // Data will be migrated to kernel space
    buffer_a.SyncBuffer();
    buffer_b.SyncBuffer();

    //Launch the Kernel
    //set the kernel Arguments
    int narg=0;
    fpga.m_krnl_vector_add.setArg(narg++,buffer_a.mBuffer);
    fpga.m_krnl_vector_add.setArg(narg++,buffer_b.mBuffer);
    fpga.m_krnl_vector_add.setArg(narg++,buffer_result.mBuffer);
    fpga.m_krnl_vector_add.setArg(narg++,DATA_SIZE);
    fpga.mQueue.enqueueTask(fpga.m_krnl_vector_add);

    // The result of the previous kernel execution will need to be retrieved in
    // order to view the results. This call will transfer the data from FPGA to
    // source_results vector

    buffer_result.SyncBuffer();
    fpga.mQueue.finish();

    //Verify the result
    int match = 0;
    for (int i = 0; i < DATA_SIZE; i++) {
        int host_result = ptr_a[i] + ptr_b[i];
        if (buffer_result.mPtr[i] != host_result) {
            printf(error_message.c_str(), i, host_result, buffer_result.mPtr[i]);
            match = 1;
            break;
        }
    }

    std::cout << "TEST " << (match ? "FAILED" : "PASSED") << std::endl; 
}