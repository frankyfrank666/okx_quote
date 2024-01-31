#ifndef COUNTER_H
#define COUNTER_H

#include "../include/utils.h"

struct CounterConfig
{
    ap_uint<32> mDelayCycle = 1000000000; //3s
};

extern "C" {
    void CounterTop(hls::stream<CounterConfig>& delay_cycle_stream_in, hls::stream<ap_uint<1>>& tick_stream_out);
}

#endif