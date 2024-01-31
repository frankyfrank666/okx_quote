#include "CounterTop.h"

extern "C" {
    void CounterTop(hls::stream<CounterConfig>& delay_cycle_stream_in, hls::stream<ap_uint<1>>& tick_stream_out)
    {
#pragma hls latency max=1
#pragma hls interface axis port=delay_cycle_stream_in
#pragma hls interface axis port=tick_stream_out
#pragma hls interface ap_ctrl_none port=return

        static ap_uint<32> counter = 1;
        static CounterConfig config;
        delay_cycle_stream_in.read_nb(config);

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
}
