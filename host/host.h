#ifndef HOST_H
#define HOST_H

#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1

#include <stdlib.h>
#include <fstream>
#include <iostream>

#include <CL/cl2.hpp>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <uuid/uuid.h>
#include <vector>
#include "xclhal2.h"
#include "experimental/xrt_xclbin.h"
#include "/root/Desktop/Vitis_Accel_Examples-2020.1/common/includes/xcl2/xcl2.hpp"
#include "/root/Desktop/Vitis_Accel_Examples-2020.1/common/includes/xcl2/xcl2.hpp"
#include "/opt/xilinx/xrt/include/experimental/xrt-next.h"

static const std::string error_message =
    "Error: Result mismatch:\n"
    "i = %d CPU result = %d Device result = %d\n";
class FPGA
{
public:
    cl::Device mDevice;
    cl::Platform mPlatform;
    cl::Context mContext;
    cl::CommandQueue mQueue;
    cl::Program mProgram;

    FPGA(char* xclbinFilename)
    {
        std::vector<cl::Device> devices;
        // cl::Device device;
        std::vector<cl::Platform> platforms;
        bool found_device = false;
        //traversing all Platforms To find Xilinx Platform and targeted Device in Xilinx Platform
        cl::Platform::get(&platforms);
        for(size_t i = 0; (i < platforms.size() ) & (found_device == false) ;i++){
            mPlatform = platforms[i];
            std::string platformName = mPlatform.getInfo<CL_PLATFORM_NAME>();
            if ( platformName == "Xilinx"){
                devices.clear();
                mPlatform.getDevices(CL_DEVICE_TYPE_ACCELERATOR, &devices);
            if (devices.size()){
                mDevice = devices[0];
                found_device = true;
                break;
            }
            }
        }
        if (found_device == false) {std::cout << "Error: Unable to find Target Device " << mDevice.getInfo<CL_DEVICE_NAME>() << std::endl;}

        // Creating Context and Command Queue for selected device
        mContext = cl::Context(mDevice);
        mQueue = cl::CommandQueue(mContext, mDevice, CL_QUEUE_PROFILING_ENABLE);

        // Load xclbin 
        std::cout << "Loading: '" << xclbinFilename << "'\n";
        std::ifstream bin_file(xclbinFilename, std::ifstream::binary);
        bin_file.seekg (0, bin_file.end);
        unsigned nb = bin_file.tellg();
        bin_file.seekg (0, bin_file.beg);
        char *buf = new char [nb];
        bin_file.read(buf, nb);
        
        // Creating Program from Binary File
        cl::Program::Binaries bins;
        bins.push_back({buf,nb});
        devices.resize(1);
        mProgram = cl::Program(mContext, devices, bins);
        
        m_krnl_vector_add = cl::Kernel(mProgram, "VaddTop");
        // mKernelEthOutTop = cl::Kernel(mProgram, "EthOutTop");
    }

    cl::Kernel m_krnl_vector_add ;
    cl::Kernel mKernelEthOutTop;

    void wait()
    {
        mQueue.finish();
    }
};

// Write to fpga: Creat read-only buffer on fpga -> map buffer from fpga to our memory -> write on our memory -> migrate to fpga memory
// Read from fpga: Creat write-only buffer on fpga -> map buffer from fpga to our memory -> write on fpga memory -> migrate to our memory
template<typename T>
class WriteToFpgaBuffer
{
public:
    cl::Buffer mBuffer;
    T* mPtr;
    size_t mSize;
    cl::CommandQueue mQueue;

    WriteToFpgaBuffer(cl::CommandQueue queue, cl::Context context, size_t sizeInBytes)
    {
        mQueue = queue;
        mSize = sizeInBytes;
        mBuffer = cl::Buffer(context, CL_MEM_READ_ONLY, sizeInBytes);
        mPtr = (T*) queue.enqueueMapBuffer (mBuffer , CL_TRUE , CL_MAP_WRITE , 0, sizeInBytes);
    }

    ~WriteToFpgaBuffer()
    {
        // mQueue.enqueueUnmapMemObject(mBuffer, mPtr);
    }

    cl_int syncBuffer()
    {   
        cl_int err = 0;
        OCL_CHECK(err, mQueue.enqueueMigrateMemObjects({mBuffer}, 0));
        if(err)
            std::cout << "Error in syncBuf\n";
        return err;
    }
};

template<typename T>
class ReadFromFpgaBuffer
{
public:
    cl::Buffer mBuffer;
    T* mPtr;
    size_t mSize;
    cl::CommandQueue mQueue;

    ReadFromFpgaBuffer(cl::CommandQueue queue, cl::Context context, size_t sizeInBytes)
    {
        mQueue = queue;
        mSize = sizeInBytes;
        mBuffer = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeInBytes);
        mPtr = (T*) queue.enqueueMapBuffer (mBuffer , CL_TRUE , CL_MAP_READ , 0, sizeInBytes);
    }

    ~ReadFromFpgaBuffer()
    {
        // mQueue.enqueueUnmapMemObject(mBuffer, mPtr);
    }

    cl_int syncBuffer()
    {
        cl_int err = 0;
        OCL_CHECK(err, mQueue.enqueueMigrateMemObjects({mBuffer},CL_MIGRATE_MEM_OBJECT_HOST));
        if(err)
            std::cout << "Error in syncBuf\n";
        return err;
    }
};

#endif