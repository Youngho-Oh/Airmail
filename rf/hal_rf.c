/***********************************************************************************

  Filename:       hal_rf.c

  Description:    CC2530 radio interface.

***********************************************************************************/

/***********************************************************************************
* INCLUDES
*/
#include "hal_rf.h"

#include "hal/common.h"
#include "hal/util.h"
#include "hal/bool.h"
#include "hal/int/hal_int.h"

/***********************************************************************************
* CONSTANTS AND DEFINES
*/


/***********************************************************************************
* GLOBAL DATA
*/
#if INCLUDE_PA==2591 || INCLUDE_PA==2592
static const menuItem_t pPowerSettings[] =
{
  "0dBm", HAL_RF_TXPOWER_0_DBM,
  "13dBm", HAL_RF_TXPOWER_13_DBM,
  "16dBm", HAL_RF_TXPOWER_16_DBM,
  "18dBm", HAL_RF_TXPOWER_18_DBM,
  "20dBm", HAL_RF_TXPOWER_20_DBM
};
#else
static const menuItem_t pPowerSettings[] =
{
	{"-3dBm", HAL_RF_TXPOWER_MIN_3_DBM},
	{"0dBm", HAL_RF_TXPOWER_0_DBM},
	{"4dBm", HAL_RF_TXPOWER_4_DBM}
};
#endif

const menu_t powerMenu =
{
  pPowerSettings,
  N_ITEMS(pPowerSettings)
};

/***********************************************************************************
* LOCAL DATA
*/
#ifndef MRFI
static ISR_FUNC_PTR pfISR= NULL;
#endif
static unsigned char rssiOffset = RSSI_OFFSET;

/***********************************************************************************
* LOCAL FUNCTIONS
*/
static void halPaLnaInit(void);

/***********************************************************************************
* GLOBAL FUNCTIONS
*/

/***********************************************************************************
* @fn      halRfInit
*
* @brief   Power up, sets default tuning settings, enables autoack, enables random
*          generator.
*
* @param   none
*
* @return  SUCCESS always (for interface compatibility)
*/
unsigned char halRfInit(void)
{
    // Enable auto ack and auto crc
    FRMCTRL0 |= (AUTO_ACK | AUTO_CRC);

    // Recommended RX settings
    TXFILTCFG = 0x09;
    AGCCTRL1 = 0x15;
    FSCAL1 = 0x00;

    // Enable random generator -> Not implemented yet

    // Enable CC2591 with High Gain Mode
    halPaLnaInit();

    // Enable RX interrupt
    halRfEnableRxInterrupt();

    return SUCCESS;
}



/***********************************************************************************
* @fn      halRfGetChipId
*
* @brief   Get chip id
*
* @param   none
*
* @return  unsigned char - result
*/
unsigned char halRfGetChipId(void)
{
    return CHIPID;
}


/***********************************************************************************
* @fn      halRfGetChipVer
*
* @brief   Get chip version
*
* @param   none
*
* @return  unsigned char - result
*/
unsigned char halRfGetChipVer(void)
{
    // return major revision (4 upper bits)
    return CHVER>>4;
}

/***********************************************************************************
* @fn      halRfGetRandomByte
*
* @brief   Return random byte
*
* @param   none
*
* @return  unsigned char - random byte
*/
unsigned char halRfGetRandomByte(void)
{
    // Not yet implemented
//    HAL_ASSERT(false);
    return 0;
}


/***********************************************************************************
* @fn      halRfGetRssiOffset
*
* @brief   Return RSSI Offset
*
* @param   none
*
* @return  unsigned char - RSSI offset
*/
unsigned char halRfGetRssiOffset(void)
{
    return rssiOffset;
}

/***********************************************************************************
* @fn      halRfSetChannel
*
* @brief   Set RF channel in the 2.4GHz band. The Channel must be in the range 11-26,
*          11= 2005 MHz, channel spacing 5 MHz.
*
* @param   channel - logical channel number
*
* @return  none
*/
void halRfSetChannel(unsigned char channel)
{
    FREQCTRL = (MIN_CHANNEL + (channel - MIN_CHANNEL) * CHANNEL_SPACING);
}


/***********************************************************************************
* @fn      halRfSetShortAddr
*
* @brief   Write short address to chip
*
* @param   none
*
* @return  none
*/
void halRfSetShortAddr(unsigned short shortAddr)
{
	SHORTADDRL = LO_UINT16(shortAddr);
	SHORTADDRH = HI_UINT16(shortAddr);
}


/***********************************************************************************
* @fn      halRfSetPanId
*
* @brief   Write PAN Id to chip
*
* @param   none
*
* @return  none
*/
void halRfSetPanId(unsigned short panId)
{
	PANIDL = LO_UINT16(panId);
	PANIDH = HI_UINT16(panId);
}


/***********************************************************************************
* @fn      halRfSetPower
*
* @brief   Set TX output power
*
* @param   unsigned char power - power level: TXPOWER_MIN_4_DBM, TXPOWER_0_DBM,
*                        TXPOWER_4_DBM
*
* @return  unsigned char - SUCCESS or FAILED
*/
unsigned char halRfSetTxPower(unsigned char power)
{
    unsigned char n;

    switch(power)
    {
#if INCLUDE_PA==2591 || INCLUDE_PA==2592
    case HAL_RF_TXPOWER_0_DBM: n = CC2530_91_TXPOWER_0_DBM; break;
    case HAL_RF_TXPOWER_13_DBM: n = CC2530_91_TXPOWER_13_DBM; break;
    case HAL_RF_TXPOWER_16_DBM: n = CC2530_91_TXPOWER_16_DBM; break;
    case HAL_RF_TXPOWER_18_DBM: n = CC2530_91_TXPOWER_18_DBM; break;
    case HAL_RF_TXPOWER_20_DBM: n = CC2530_91_TXPOWER_20_DBM; break;
#else
    case HAL_RF_TXPOWER_MIN_3_DBM: n = CC2530_TXPOWER_MIN_3_DBM; break;
    case HAL_RF_TXPOWER_0_DBM: n = CC2530_TXPOWER_0_DBM; break;
    case HAL_RF_TXPOWER_4_DBM: n = CC2530_TXPOWER_4_DBM; break;
#endif
    default:
        return FAILED;
    }

    // Set TX power
    TXPOWER = n;

    return SUCCESS;
}


/***********************************************************************************
* @fn      halRfSetGain
*
* @brief   Set gain mode - only applicable for units with CC2590/91.
*
* @param   unsigned char - gain mode
*
* @return  none
*/
void halRfSetGain(unsigned char gainMode)
{
    if (gainMode==HAL_RF_GAIN_LOW) {
        HAL_PA_LNA_RX_LGM();
        rssiOffset = RSSI_OFFSET_LNA_LOWGAIN;
    } else {
        HAL_PA_LNA_RX_HGM();
        rssiOffset = RSSI_OFFSET_LNA_HIGHGAIN;
    }
}

/***********************************************************************************
* @fn      halRfWriteTxBuf
*
* @brief   Write to TX buffer
*
* @param   unsigned char* pData - buffer to write
*          unsigned char length - number of bytes
*
* @return  none
*/
void halRfWriteTxBuf(unsigned char* pData, unsigned char length)
{
    unsigned char i;

    ISFLUSHTX();         	 // Making sure that the TX FIFO is empty.

    RFIRQF1 = ~IRQ_TXDONE;   // Clear TX done interrupt

    // Insert data
    for(i=0;i<length;i++){
        RFD = pData[i];
    }
}


/***********************************************************************************
* @fn      halRfAppendTxBuf
*
* @brief   Write to TX buffer
*
* @param   unsigned char* pData - buffer to write
*          unsigned char length - number of bytes
*
* @return  none
*/
void halRfAppendTxBuf(unsigned char* pData, unsigned char length)
{
    unsigned char i;

    // Insert data
    for(i=0;i<length;i++){
        RFD = pData[i];
    }
}


/***********************************************************************************
* @fn      halRfReadRxBuf
*
* @brief   Read RX buffer
*
* @param   unsigned char* pData - data buffer. This must be allocated by caller.
*          unsigned char length - number of bytes
*
* @return  none
*/
void halRfReadRxBuf(unsigned char* pData, unsigned char length)
{
    // Read data
    while (length>0) {
        *pData++= RFD;
        length--;
    }
}


/***********************************************************************************
* @fn      halRfReadMemory
*
* @brief   Read RF device memory
*
* @param   unsigned short addr - memory address
*          unsigned char* pData - data buffer. This must be allocated by caller.
*          unsigned char length - number of bytes
*
* @return  Number of bytes read
*/
unsigned char halRfReadMemory(unsigned short addr, unsigned char* pData, unsigned char length)
{
	//WOW TODO
	(void)addr;
	(void)pData;
	(void)length;

    return 0;
}


/***********************************************************************************
* @fn      halRfWriteMemory
*
* @brief   Write RF device memory
*
* @param   unsigned short addr - memory address
*          unsigned char* pData - data buffer. This must be allocated by caller.
*          unsigned char length - number of bytes
*
* @return  Number of bytes written
*/
unsigned char halRfWriteMemory(unsigned short addr, unsigned char* pData, unsigned char length)
{
    return 0;
}

/***********************************************************************************
* @fn      halRfTransmit
*
* @brief   Transmit frame with Clear Channel Assessment.
*
* @param   none
*
* @return  unsigned char - SUCCESS or FAILED
*/
unsigned char halRfTransmit(void)
{
    unsigned char status;

    ISTXON(); // Sending

    // Waiting for transmission to finish
    while(!(RFIRQF1 & IRQ_TXDONE) );

    RFIRQF1 = ~IRQ_TXDONE;
    status= SUCCESS;

    return status;
}



/***********************************************************************************
* @fn      halRfReceiveOn
*
* @brief   Turn receiver on
*
* @param   none
*
* @return  none
*/
void halRfReceiveOn(void)
{
    ISFLUSHRX();     // Making sure that the TX FIFO is empty.
    ISRXON();
}

/***********************************************************************************
* @fn      halRfReceiveOff
*
* @brief   Turn receiver off
*
* @param   none
*
* @return  none
*/
void halRfReceiveOff(void)
{
    ISRFOFF();
    ISFLUSHRX();    // Making sure that the TX FIFO is empty.
}


#ifndef MRFI
/***********************************************************************************
* @fn      halRfDisableRxInterrupt
*
* @brief   Clear and disable RX interrupt.
*
* @param   none
*
* @return  none
*/
void halRfDisableRxInterrupt(void)
{
    // disable RXPKTDONE interrupt
    RFIRQM0 &= ~BV(6);
    // disable general RF interrupts
    IEN2 &= ~BV(0);
}


/***********************************************************************************
* @fn      halRfEnableRxInterrupt
*
* @brief   Enable RX interrupt.
*
* @param   none
*
* @return  none
*/
void halRfEnableRxInterrupt(void)
{
    // enable RXPKTDONE interrupt
    RFIRQM0 |= BV(6);
    // enable general RF interrupts
    IEN2 |= BV(0);
}


/***********************************************************************************
* @fn      halRfRxInterruptConfig
*
* @brief   Configure RX interrupt.
*
* @param   none
*
* @return  none
*/
void halRfRxInterruptConfig(ISR_FUNC_PTR pf)
{
    unsigned char x;
    HAL_INT_LOCK(x);
    pfISR= pf;
    HAL_INT_UNLOCK(x);
}

#endif

/***********************************************************************************
* @fn      halRfWaitTransceiverReady
*
* @brief   Wait until the transciever is ready (SFD inactive).
*
* @param   none
*
* @return  none
*/
void halRfWaitTransceiverReady(void)
{
    // Wait for SFD not active and TX_Active not active
    while (FSMSTAT1 & (BV(1) | BV(5) ));
}

#ifndef MRFI
/************************************************************************************
* @fn          rfIsr
*
* @brief       Interrupt service routine that handles RFPKTDONE interrupt.
*
* @param       none
*
* @return      none
*/
void rf_isr(void) __interrupt(RF_VECTOR)
{
    unsigned char x;

    HAL_INT_LOCK(x);

    if( RFIRQF0 & IRQ_RXPKTDONE )
    {
        if(pfISR){
            (*pfISR)();                 // Execute the custom ISR
        }
        S1CON= 0;                   // Clear general RF interrupt flag
        RFIRQF0&= ~IRQ_RXPKTDONE;   // Clear RXPKTDONE interrupt
    }
    HAL_INT_UNLOCK(x);
}
#endif

/***********************************************************************************
* LOCAL FUNCTIONS
*/
/***********************************************************************************
* LOCAL FUNCTIONS
*/
static void halPaLnaInit(void)
{
#if INCLUDE_PA==2591
    // Initialize CC2591 to RX high gain mode
    static unsigned char fFirst= TRUE;

    if(fFirst) {
        AGCCTRL1  = 0x15;
        FSCAL1 = 0x0; 
        RFC_OBS_CTRL0 = 0x68;
        RFC_OBS_CTRL1 = 0x6A;
        OBSSEL1 = 0xFB;
        OBSSEL4 = 0xFC;
        P0DIR |= 0x80;
        halRfSetGain(HAL_RF_GAIN_HIGH);
    }
#elif INCLUDE_PA==2592// crazyboy 20150814
    // Initialize CC2592 to RX high gain mode
    static unsigned char fFirst= TRUE;

    if(fFirst) {
        AGCCTRL1  = 0x15;
        FSCAL1 = 0x0; 
        RFC_OBS_CTRL0 = 0x68;
        RFC_OBS_CTRL1 = 0x6A;
        OBSSEL1 = 0xFB;
        OBSSEL0 = 0xFC;
        P0DIR |= 0x80;
        halRfSetGain(HAL_RF_GAIN_HIGH);
    }    
#endif
}


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
PROVIDED �AS IS?WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
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
