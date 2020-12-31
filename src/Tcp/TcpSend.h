#ifndef TCPSEND_H
#define TCPSEND_H

#include "TcpTop.h"

ap_uint<16> BASE_ID = 0x260a;

const ap_uint<32> iPv4Dscp = 0x08004500;
const ap_uint<16> totalLen = 0x0028;
const ap_uint<16> totalLenGET = 0x009a;  
const ap_uint<32> doNotFragTtlTcp = 0x40008006;
const ap_uint<8> headerLen = 0x50;
const ap_uint<8> flagsAck = 0b00010000;
const ap_uint<8> flagsPsh = 0b00001000;
const ap_uint<8> flagsRst = 0b00000100;
const ap_uint<8> flagsSyn = 0b00000010;
const ap_uint<8> flagsFin = 0b00000001;
const ap_uint<16> window = 0xffff;
const ap_uint<16> urgent = 0;

enum class TcpSendState
{
    DestMac,
    SrcMac,
    TotalLenDSCPTcp,
    HeaderChecksumAndDestIp,
    SeqNumber,
    AckNumber,
    TcpChecksum,
    Request,
};

constexpr int REQUEST_LEN = 15;

const ap_uint<64> request[REQUEST_LEN] = {
0x0000000000004745,
0x54202f6170692f76,
0x352f6d61726b6574,
0x2f7469636b657273,
0x3f696e7374547970,

0x653d535741502675,
0x6c793d4254432d55,
0x534420485454502f,
0x312e310d0a486f73,
0x743a2031382e3138,

0x312e3135312e383a,
0x363038390d0a436f,
0x6e6e656374696f6e,
0x3a206b6565702d61,
0x6c6976650d0a0d0a
};

#endif