#ifndef RESULT_H
#define RESULT_H

#include "../include/utils.h"

// class BBO
// {
//     ap_uint<32>  mBestPrice;
//     ap_uint<32> mBestVolume;

//     using BBO::Packed = ap_uint<64>

//     static BBO Unpack(BBO::Packed packed)
//     {
//         BBO bbo;
//         bbo.mBestPrice = packed(63, 32);
//         bbo.mBestVolume = packed(31, 0);
//         return bbo;
//     }

//     BBO Pack()
//     {
//         return (mBestPrice, mBestVolume);
//     }
// };

extern "C" {
    void ResultTop(
        ap_uint<32> price_out,   //8 ascii chars
        ap_uint<32> volume_out,  //8 ascii chars
        TcpState tcp_state,
        hls::stream<TcpState>& tcp_state_stream_in,
        hls::stream<ap_uint<64>>& ask_price_volume_stream_in
    );
}

#endif