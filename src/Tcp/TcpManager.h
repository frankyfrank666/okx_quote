#ifndef TCPMANAGER_H
#define TCPMANAGER_H

#include "../common/utils.h"
#include "TcpTop.h"

ap_uint<32> BASE_SEQ = 0x06f6bd27;

enum class TcpState
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