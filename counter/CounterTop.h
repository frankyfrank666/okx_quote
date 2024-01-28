#include "../include/utils.h"
extern "C" {
    void CounterTop(ap_uint<32>& delay_ns = 3000000000, hls::stream<ap_uint<1>>& tick_stream_out);
}