#include "xilinx_include/ap_int.h"
#include "xilinx_include/hls_stream.h"

template <int N>
ap_uint<N> byte_reverse(ap_uint<N> value) {
    constexpr int bytes = N / 8;
    ap_uint<N> result = 0;
    for (int i = 0; i < bytes; ++i) {
#pragma HLS unroll
        result((bytes - i) * 8 - 1, (bytes - i) * 8 - 8) = value(i * 8 + 7, i * 8)
    }
    return result;
}
