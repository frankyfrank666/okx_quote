#ifndef UTILS_H
#define UTILS_H

#include "ap_int.h"
#include "ap_axi_sdata.h"
#include "hls_stream.h"

template <int N>
ap_uint<N> byte_reverse(ap_uint<N> value) {
    constexpr int bytes = N / 8;
    ap_uint<N> result = 0;
    for (int i = 0; i < bytes; ++i) {
// #pragma HLS unroll
        result((bytes - i) * 8 - 1, (bytes - i) * 8 - 8) = value(i * 8 + 7, i * 8);
    }
    return result;
}

using ethernetAxi64 = ap_axiu<64,0,0,0>;

enum TcpCommand
{
    Connect,
    Close,
    Reset
};

enum TcpState
{
    Closed,
    SynSent,
    Establsihed,

    FinSent, //wait for finack and send ack and close
    FinSentWaitAck, //no need wait for their ack, send ack and close
    FinSentWaitFin, //wait for their fin and send ack and close

    FinAckSent, //they close, we finack and wait for thier ack
};

#endif