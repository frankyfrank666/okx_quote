#include "../common/utils.h"

extern "C" {
    /// @brief Reads the ethernet output stream and send to the memory. 
    /// @param out 
    /// @param buffSize 
    /// @param ethernet_stream_in 
    void EthOutTop(
        EthernetAxi64* out,
        ap_uint<32> buffSize, 
        hls::stream<EthernetAxi64>& ethernet_stream_in
    )
{
#pragma hls INTERFACE m_axi port=out
#pragma hls INTERFACE axis port=ethernet_stream_in
#pragma HLS INTERFACE ap_ctrl_hs port=return

        for (ap_uint<32> i = 0; i < buffSize; ++i)
        {
            if(!ethernet_stream_in.empty())
            {
                out[i] = ethernet_stream_in.read();
            }
        }
    }
}