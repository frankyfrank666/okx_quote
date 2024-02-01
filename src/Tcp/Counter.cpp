#include "TcpTop.h"

void Counter(TcpConfig& tcpConfig, hls::stream<ap_uint<1>>& tick_stream_out)
{
#pragma hls latency max=1

    static ap_uint<32> counter = 1;

    if (tcpConfig.mDelayCycle == 0)
    {
        counter = 1;
    }
    else if (counter == tcpConfig.mDelayCycle) // 0 disables the output.
    {
        counter = 1;
        tick_stream_out.write(ap_uint<1>(1));
    }
    else
    {
        ++counter;
    }
}