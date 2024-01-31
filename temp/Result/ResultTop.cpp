#include "ResultTop.h"

extern "C" {
    void ResultTop(
        ap_uint<32> price_out,   //8 ascii chars
        ap_uint<32> volume_out,  //8 ascii chars
        TcpState tcp_state,
        hls::stream<TcpState>& tcp_state_stream_in,
        hls::stream<ap_uint<64>>& ask_price_volume_stream_in
    )
    {
#pragma hls INTERFACE axis port=ask_price_volume_stream_in
#pragma HLS INTERFACE ap_ctrl_hs port=return

        static ap_uint<64> bbo;
        while (!ask_price_volume_stream_in.empty())
        {
            ask_price_volume_stream_in.read_nb(bbo);
        }
        price_out = bbo(63, 32);
        volume_out = bbo(31, 0);

        static TcpState tcp_state_temp;
        while (!tcp_state_stream_in.empty())
        {
            tcp_state_stream_in.read_nb(tcp_state_temp);
        }

        tcp_state = tcp_state_temp;
    }
}