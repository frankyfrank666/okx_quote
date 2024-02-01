#ifndef TCPMANAGER_H
#define TCPMANAGER_H

#include "../common/utils.h"
#include "TcpTop.h"

// Hardcoed Http Request, shoud be made into soft in the future. 
constexpr int REQUEST_LEN = 15;
const ap_uint<64> request [REQUEST_LEN] = {
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