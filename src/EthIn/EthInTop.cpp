#include "../common/utils.h"

extern "C" {
    /// @brief Reads in pcap bytes from memory and send it out as ethernet streams.
    /// @param in 
    /// @param buffSize 
    /// @param ethernet_stream_out 
    void EthInTop(
        EthernetAxi64 *in,
        ap_uint<32> buffSize,
        ap_uint<32> keep,
        hls::stream<EthernetAxi64>& ethernet_stream_out
    )
    {
#pragma hls INTERFACE m_axi port=in
#pragma hls INTERFACE axis port=ethernet_stream_out
#pragma HLS INTERFACE ap_ctrl_hs port=return

        for (ap_uint<32> i = 0; i < buffSize; ++i)
        {
            ethernet_stream_out.write(in[i]);
        }
    }
}