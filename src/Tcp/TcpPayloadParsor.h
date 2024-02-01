#ifndef TCPPAYLOAD_H
#define TCPPAYLOAD_H

#include "TcpTop.h"

const ap_uint<8> a = 0x61;
const ap_uint<8> s = 0x73;
const ap_uint<8> k = 0x6b;
const ap_uint<8> P = 0x50;
const ap_uint<8> x = 0x78;
const ap_uint<8> S = 0x53;
const ap_uint<8> z = 0x7a;
const ap_uint<8> dot = 0x2e;
const ap_uint<8> col = 0x3a; // :
const ap_uint<8> quote = 0x22; // "

enum class payloadState
{
    NA,
    a,
    as,
    ask,
    askP,
    askPx,
    askPxq,
    askPxqc,
    askPxqcqInt,
    askPxqcqDec,
    askS,
    askSz,
    askSzq,
    askSzqc,
    askSzqcq,
};

#endif