#include "TcpPayloadParsor.h"

void PayloadParserHelper(ap_uint<32>& askPxInt, ap_uint<32>& askPxDec, ap_uint<32>& askSz, ap_uint<32>& outputCount, ap_uint<1> last, ap_uint<8> character) //too many adders, no way to meet timing
{
#pragma hls inline

    static payloadState state = payloadState::NA;
    static ap_uint<32> tempAskPxInt;
    static ap_uint<32> tempAskPxDec;
    static ap_uint<32> tempAskSz;
    static ap_uint<32> tempOutputCount = 0;

    switch (state)
    {
        case payloadState::NA:
        {
            if (character == a) state = payloadState::a;
            else state = payloadState::NA;
            break;
        }
        case payloadState::a:
        {
            if (character == s) state = payloadState::as;
            else state = payloadState::NA;
            break;
        }
        case payloadState::as:
        {
            if (character == k) state = payloadState::ask;
            else state = payloadState::NA;
            break;
        }
        case payloadState::ask:
        {
            if (character == P) state = payloadState::askP;
            else if (character == S) state = payloadState::askS;
            else state = payloadState::NA;
            break;
        }
        case payloadState::askP:
        {
            if (character == x) state = payloadState::askPx;
            else state = payloadState::NA;
            break;
        }
        case payloadState::askS:
        {
            if (character == z) state = payloadState::askSz;
            else state = payloadState::NA;
            break;
        }
        case payloadState::askPx:
        {
            tempAskPxInt = 0;
            tempAskPxDec = 0;
            tempAskSz = 0;
            if (character == quote) state = payloadState::askPxq;
            else state = payloadState::NA;
            break;
        }
        case payloadState::askSz:
        {
            if (character == quote) state = payloadState::askSzq;
            else state = payloadState::NA;
            break;
        }
        case payloadState::askPxq:
        {
            if (character == col) state = payloadState::askPxqc;
            else state = payloadState::NA;
            break;
        }
        case payloadState::askSzq:
        {
            if (character == col) state = payloadState::askSzqc;
            else state = payloadState::NA;
            break;
        }
        case payloadState::askPxqc:
        {
            if (character == quote) state = payloadState::askPxqcqInt;
            else state = payloadState::NA;
            break;
        }
        case payloadState::askSzqc:
        {
            if (character == quote) state = payloadState::askSzqcq;
            else state = payloadState::NA;
            break;
        }
        case payloadState::askPxqcqInt: // Assume no Malformed Json String
        {
            if (character == quote) 
            {
                state = payloadState::NA;
            }
            else if (character == dot)
            {
                state = payloadState::askPxqcqDec;
            }
            else tempAskPxInt = (tempAskPxInt << 3) + (tempAskPxInt << 1) + (character - 0x30);
            break;
        }
        case payloadState::askPxqcqDec:
        {
             if (character == quote) 
            {
                state = payloadState::NA;
            }
            else tempAskPxDec = (tempAskPxDec << 3) + (tempAskPxDec << 1) + (character - 0x30);
            break;
        }
        case payloadState::askSzqcq:
        {
            if (character == quote)
            {
                askPxInt(31,0) = tempAskPxInt(31,0) ;
                askPxDec(31,0) = tempAskPxDec(31,0) ;
                askSz(31,0) = tempAskSz(31,0) ;
                outputCount = tempOutputCount;
                ++tempOutputCount;
                state = payloadState::NA;
            } 
            else tempAskSz = (tempAskSz << 3) + (tempAskSz << 1) + (character - 0x30);
            break;
        }
    }

    if (last)
        state = payloadState::NA;
}