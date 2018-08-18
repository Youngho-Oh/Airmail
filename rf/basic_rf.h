/***********************************************************************************
  Filename:     basic_rf.h

  Description:  Basic RF library header file

***********************************************************************************/
#ifndef BASIC_RF_H
#define BASIC_RF_H

/***********************************************************************************
    The "Basic RF" library contains simple functions for packet transmission and
    reception with the IEEE 802.15.4 compliant radio devices. The intention of this
    library is to demonstrate how the radio devices are operated, and not to provide
    a complete and fully-functional packet protocol. The protocol uses 802.15.4 MAC compliant data
    and acknowledgment packets, however it contains only a small subset of  the
    802.15.4 standard:
    - Association, scanning nor beacons are not implemented
    - No defined coordinator/device roles (peer-to-peer, all nodes are equal)
    - Waits for the channel to become ready, but does not check CCA twice
    (802.15.4 CSMA-CA)
    - Does not retransmit packets

    INSTRUCTIONS:
    Startup:
    1. Create a basicRfCfg_t structure, and initialize the members:
    2. Call basicRfInit() to initialize the packet protocol.

    Transmission:
    1. Create a buffer with the payload to send
    2. Call basicRfSendPacket()

    Reception:
    1. Check if a packet is ready to be received by highger layer with
    basicRfPacketIsReady()
    2. Call basicRfReceive() to receive the packet by higher layer

    FRAME FORMATS:
    Data packets (without security):
    [Preambles (4)][SFD (1)][Length (1)][Frame control field (2)]
    [Sequence number (1)][PAN ID (2)][Dest. address (2)][Source address (2)]
    [Payload (Length - 2+1+2+2+2)][Frame check sequence (2)]

    Acknowledgment packets:
    [Preambles (4)][SFD (1)][Length = 5 (1)][Frame control field (2)]
    [Sequence number (1)][Frame check sequence (2)]
***********************************************************************************/

/***********************************************************************************
* INCLUDES
*/
#include "../hal/common.h"

/***********************************************************************************
* TYPEDEFS
*/

typedef struct {
    unsigned short myAddr;
    unsigned short panId;
    unsigned char channel;
    unsigned char ackRequest;
    #ifdef SECURITY_CCM
    unsigned char* securityKey;
    unsigned char* securityNonce;
    #endif
} basicRfCfg_t;

/***********************************************************************************
* GLOBAL FUNCTIONS
*/
unsigned char basicRfInit(basicRfCfg_t* pRfConfig);
unsigned char basicRfSendPacket(unsigned short destAddr, unsigned char* pPayload, unsigned char length);
unsigned char basicRfPacketIsReady(void);
char basicRfGetRssi(void);
unsigned char basicRfReceive(unsigned char* pRxData, unsigned char len, short* pRssi);
void basicRfReceiveOn(void);
void basicRfReceiveOff(void);

/***********************************************************************************
  Copyright 2007 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
***********************************************************************************/

#endif

