#include "TcpTop.h"

struct CounterConfig
{
    ap_uint<32> mDelayCycle = 1000000000; //3s
};

void Counter(hls::stream<ap_uint<1>>& tick_stream_out)
{
#pragma hls latency max=1

    static ap_uint<32> counter = 1;
    static CounterConfig config;

    if (counter == config.mDelayCycle && config.mDelayCycle != 0) // 0 disables the output.
    {
        counter = 1;
        tick_stream_out.write(ap_uint<1>(1));
    }
    else
    {
        ++counter;
    }
}