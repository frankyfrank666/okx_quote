#include "../include/utils.h"

extern "C" {
    /// @brief Reads in pcap bytes from memory and send it out as ethernet streams.
    /// @param in 
    /// @param len 
    /// @param keep 
    /// @param eth_stream_out 
    void EthInTop(
        ap_uint<64> *in,
        ap_uint<32> len,
        ap_uint<32> keep,
        hls::stream<eth_packet>& eth_stream_out
    )
    {
#pragma hls INTERFACE m_axi port=in
#pragma hls INTERFACE axis port=eth_stream_out
#pragma HLS INTERFACE ap_ctrl_hs port=return

        for (ap_uint<32> i = 0; i < len; ++i)
        {
            eth_packet x;
            x.data = in[i];
            x.last = i == (len-1) ? 1 : 0;
            x.keep = keep;
            eth_stream_out.write(x);
        }
    }
}