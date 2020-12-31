#include "TcpManager.h"


void Manager(TcpConfig& tcpConfig, hls::stream<ap_uint<1>>& tick_stream_in, hls::stream<TcpMeta>& tcp_recv_stream_in, hls::stream<TcpMeta>& tcp_send_stream_out)
{   
#pragma hls pipeline ii=1

    static bool pendingRequest = false;
    static TcpMeta recvTcp;
    static TcpState connectionState = TcpState::Closed;

    static ap_uint<32> ourPrevSeq = 0;
    static ap_uint<32> ourPrevPayload = 0;
    static ap_uint<32> ourPrevAck = 0;
    TcpMeta toSend;
    ap_uint<1> tick;
    bool reset = false;

    if (connectionState != TcpState::Establsihed)
        tick_stream_in.read_nb(tick);

    switch (connectionState)
    {
        case TcpState::Closed:
        {
            tcp_recv_stream_in.read_nb(recvTcp);

            ourPrevSeq = 0;
            ourPrevPayload = 0;
            ourPrevAck = 0;

            if (tcpConfig.mCommand == TcpCommand::Connect) //send Syn, but without tcp options unlike the example
            {
                //Build Packet
                toSend.mSeqNum = BASE_SEQ; 
                toSend.mSyn = 1;

                //Send                
                tcp_send_stream_out.write(toSend);

                //Upodate Prev
                ourPrevSeq = toSend.mSeqNum;
                ourPrevAck = toSend.mAckNum;
                ourPrevPayload = 1;

                //Update State
                connectionState = TcpState::SynSent;
            }
            break;
        }
        case TcpState::SynSent:
        {
            if (tcp_recv_stream_in.read_nb(recvTcp))
            {
                if (recvTcp.mSyn && recvTcp.mAck && recvTcp.mAckNum == ourPrevSeq + ourPrevPayload) //Check they ack our prev packet number
                {
                    //Build Packet
                    toSend.mSeqNum = ourPrevSeq + ourPrevPayload; 
                    toSend.mAckNum = recvTcp.mSeqNum + recvTcp.mTcpPayloadLength; 
                    toSend.mAck = 1;
                    //Send
                    tcp_send_stream_out.write(toSend);
                    //Update Prev
                    ourPrevSeq = toSend.mSeqNum;
                    ourPrevAck = toSend.mAckNum;
                    ourPrevPayload = 0;
                    //Update State
                    connectionState = TcpState::Establsihed;
                }
                else
                    reset = true;
            }
            break;
        }

        case TcpState::Establsihed:
        {

            if (tcp_recv_stream_in.read_nb(recvTcp))
            {
                if (recvTcp.mAck && recvTcp.mAckNum == ourPrevSeq + ourPrevPayload && recvTcp.mSeqNum == ourPrevAck) //Check they ack our prev packet number
                {
                    //Build Packet
                    toSend.mSeqNum = ourPrevSeq + ourPrevPayload; 
                    toSend.mAckNum = recvTcp.mSeqNum + recvTcp.mTcpPayloadLength; //We ack their next packet
                    toSend.mAck = 1;
                    toSend.mIsRequest = 0;
                    
                    //Send                
                    if (recvTcp.mTcpPayloadLength > 0) //we don't Ack an pure Ack
                        tcp_send_stream_out.write(toSend);
                    
                    //Update Prev
                    ourPrevAck = toSend.mAckNum;
                    ourPrevSeq = toSend.mSeqNum;
                    ourPrevPayload = 0;
                }
                else if (recvTcp.mAck && recvTcp.mAckNum == ourPrevSeq + ourPrevPayload && recvTcp.mSeqNum == ourPrevAck - 1) //Keep Alive
                {
                    //Build Packet
                    toSend.mSeqNum = ourPrevSeq;
                    toSend.mAckNum = ourPrevAck;
                    toSend.mAck = 1;
                    toSend.mIsRequest = 0;
                    //Send                
                    tcp_send_stream_out.write(toSend);
                    //Upodate Prev
                    ourPrevAck = toSend.mAckNum;
                    ourPrevSeq = toSend.mSeqNum;
                    ourPrevPayload = 0;
                }
                else
                    reset = true;
            }
            else if (tick_stream_in.read_nb(tick))
            {
                //Build Packet
                toSend.mSeqNum = ourPrevSeq + ourPrevPayload;
                toSend.mAckNum = ourPrevAck;
                toSend.mAck = 1;
                toSend.mPsh = 1;
                toSend.mIsRequest = 1;
                //Send                
                tcp_send_stream_out.write(toSend);
                //Upodate Prev
                ourPrevAck = toSend.mAckNum;
                ourPrevSeq = toSend.mSeqNum;
                ourPrevPayload = 114;
            }
            else if (tcpConfig.mCommand == TcpCommand::Close)
            {
                // std::cout << "CLOSE" << std::endl;
                //Build Packet
                toSend.mSeqNum = ourPrevSeq + ourPrevPayload;
                toSend.mAckNum = ourPrevAck;
                toSend.mAck = 1;
                toSend.mFin = 1;
                //Send
                tcp_send_stream_out.write(toSend);
                //Upodate Prev
                ourPrevAck = toSend.mAckNum;    
                ourPrevSeq = toSend.mSeqNum;
                ourPrevPayload = 1;
                //Update State
                connectionState = TcpState::FinSent;
            }

            break;
        }
        case TcpState::FinSent:
        {
            if (tcp_recv_stream_in.read_nb(recvTcp))
            {    
                if (recvTcp.mAck && recvTcp.mFin && recvTcp.mAckNum == ourPrevSeq + ourPrevPayload && recvTcp.mSeqNum == ourPrevAck)
                {
                    //Build Packet
                    toSend.mSeqNum = ourPrevSeq + ourPrevPayload;
                    toSend.mAckNum = ourPrevAck + recvTcp.mTcpPayloadLength;
                    toSend.mAck = 1;
                    //Send
                    tcp_send_stream_out.write(toSend);
                    //Upodate Prev
                    ourPrevAck = toSend.mAckNum;
                    ourPrevSeq = toSend.mSeqNum;
                    ourPrevPayload = 0;
                    //Update State
                    connectionState = TcpState::Closed;
                }
                else
                    reset=true;
            }
            // else if (tick_stream_in.read_nb(tick))
            //     reset=true;
        }
        default:
            break;
    }

    if (reset)
    {
        toSend.mRst = 1;
        connectionState = TcpState::Closed;
        tcp_send_stream_out.write(toSend);
    }
}