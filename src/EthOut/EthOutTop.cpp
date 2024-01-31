#include "../include/utils.h"

extern "C" {
    /// @brief Reads the ethernet output stream and send to the memory. 
    /// @param out 
    /// @param buff_size 
    /// @param eth_stream_in 
    void EthOutTop(
        ap_uint<64> *out,
        ap_uint<32> buff_size, 
        hls::stream<eth_packet>& eth_stream_in
    )
{
#pragma hls INTERFACE m_axi port=out
#pragma hls INTERFACE axis port=eth_stream_in
#pragma HLS INTERFACE ap_ctrl_hs port=return

        for (ap_uint<32> i = 0; i < buff_size - 1; ++i)
        {
            static bool wasLast = false;
            if(wasLast)
            {
                out[i] = 0xEEEEEEEEFFFFFFFF;
                wasLast = false;
            }
            else
            {
                eth_packet pkt;
                if (eth_stream_in.read_nb(pkt))
                {
                    out[i] = pkt.data;
                    if (pkt.last)
                        wasLast = true;
                }
                else
                    return;
            }
        }
    }
}