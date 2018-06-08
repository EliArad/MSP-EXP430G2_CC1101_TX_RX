//*****************************************************************************
//! @file       hal_uart.h
//! @brief      HAL UART library header file
//!
//! Revised     $Date: 2012-11-22 13:38:18 +0100 (to, 22 nov 2012) $
//! Revision    $Revision: 8830 $
//
//  Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/
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
//****************************************************************************/
#ifndef HAL_UART_H
#define HAL_UART_H


/******************************************************************************
* If building with a C++ compiler, make all of the definitions in this header
* have a C binding.
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
* INCLUDES
*/
#include "hal_types.h"


/******************************************************************************
 * CONSTANTS AND DEFINES
 */
/* Serial Port Baudrate Settings */
#define HAL_UART_BAUDRATE_4800        0x01
#define HAL_UART_BAUDRATE_9600        0x02
#define HAL_UART_BAUDRATE_19200       0x03
#define HAL_UART_BAUDRATE_38400       0x04
#define HAL_UART_BAUDRATE_57600       0x05
#define HAL_UART_BAUDRATE_115200      0x06
#define HAL_UART_BAUDRATE_230400      0x07
#define HAL_UART_BAUDRATE_460800      0x08

/* Stop Bits */
#define HAL_UART_ONE_STOP_BIT         0x01
#define HAL_UART_TWO_STOP_BITS        0x02

/* Parity settings */
#define HAL_UART_NO_PARITY            0x04
#define HAL_UART_EVEN_PARITY          0x08
#define HAL_UART_ODD_PARITY           0x10

/* Number of bits in data field */
#define HAL_UART_7_BIT_DATA           0x20
#define HAL_UART_8_BIT_DATA           0x40


/******************************************************************************
 * GLOBAL FUNCTIONS
 */
void   halUartInit(uint8 baudrate, uint8 options);
uint8  halUartWrite(const uint8* buf, uint8 length);
uint8  halUartBufferedWrite(const uint8* buf, uint8 length);
uint8  halUartRead(uint8* buf, uint8 length);
uint8  halUartGetNumRxBytes(void);
void   halUartEnableRxFlow(uint8 enable);


/******************************************************************************
* Mark the end of the C bindings section for C++ compilers.
******************************************************************************/
#ifdef  __cplusplus
}
#endif
#endif // #ifndef HAL_UART_H
