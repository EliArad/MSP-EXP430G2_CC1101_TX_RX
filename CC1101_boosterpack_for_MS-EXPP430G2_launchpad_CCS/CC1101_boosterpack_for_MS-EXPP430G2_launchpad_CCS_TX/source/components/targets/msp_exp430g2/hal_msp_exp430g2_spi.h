/**************************************************************************/
//  @file       file name
//
//  @brief      describtion
//
//  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
//
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/****************************************************************************/

#ifndef HAL_MSP_EXP430G2_SPI_H
#define HAL_MSP_EXP430G2_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * INCLUDES
 */
#include "hal_types.h"
#include "hal_defs.h"  

/******************************************************************************
 * CONSTANTS
 */
#define     SPI_PORT_SEL          P1SEL
#define     SPI_PORT_DIR          P1DIR
#define     SPI_PORT_OUT          P1OUT
#define     SPI_PORT_IN           P1IN
  
#define     SPI_MOSI_PIN          BIT7
#define     SPI_MISO_PIN          BIT6
#define     SPI_SCLK              BIT5
  
#define     CS_N_PORT_SEL         P2SEL
#define     CS_N_PORT_DIR         P2DIR
#define     CS_N_PORT_OUT         P2OUT
  
#define     CS_N_PIN              BIT7
  
#define     RADIO_BURST_ACCESS    0x40
#define     RADIO_SINGLE_ACCESS   0x00
#define     RADIO_READ_ACCESS     0x80
#define     RADIO_WRITE_ACCESS    0x00  
 
/* Bit fields in the chip status byte */
#define STATUS_CHIP_RDYn_BM             0x80
#define STATUS_STATE_BM                 0x70
#define STATUS_FIFO_BYTES_AVAILABLE_BM  0x0F  
  
/******************************************************************************
 * MACROS
 */  
#define     SPI_BEGIN()           st( CS_N_PORT_OUT &= ~CS_N_PIN; )//NOP();
#define     SPI_TX(x)             st( IFG2 &= ~UCB0RXIFG; UCB0TXBUF= (x); )
#define     SPI_WAIT_DONE()       st( while(!(IFG2 & UCB0RXIFG)); )
#define     SPI_RX()              UCB0RXBUF
#define     SPI_END()             st(  CS_N_PORT_OUT |= CS_N_PIN; )//NOP();

/******************************************************************************
 * TYPEDEFS
 */

typedef struct
{
  uint16  addr;
  uint8   data;
}registerSetting_t;

typedef uint8 rfStatus_t;
/******************************************************************************
 * PROTOTYPES
 */
void exp430RfSpiInit(void);

uint8 trx8BitRegAccess(uint8 accessType, uint8 addrByte, uint8 *pData, uint16 len);
/* CC112X specific prototype function */
rfStatus_t trx16BitRegAccess(uint8 accessType, uint8 extAddr, uint8 regAddr, uint8 *pData, uint8 len);
rfStatus_t trxSpiCmdStrobe(uint8 cmd);

#ifdef  __cplusplus
}
#endif

#endif
