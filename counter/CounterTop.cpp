#include "counter.h"

extern "C" {
    void CounterTop(ap_uint<32>& delay_ns_in = 3000000000, hls::stream<ap_uint<1>>& tick_stream_out)
    {
#pragma hls latency max = 1
#pragma hls interface s_axilite port = delay_ns_in

        static ap_uint<32> counter = 0;
        if (counter == delay)
        {
            counter = 0;
            tick_stream_out.write(ap_uint<1>(1));
        } 
        else
        {
            ++counter;
        }
    }
}