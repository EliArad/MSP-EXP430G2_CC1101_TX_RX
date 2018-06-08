//*****************************************************************************
//! @file       hal_rf_security.h
//! @brief      HAL radio interface header file for security operations.
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
#ifndef HAL_RF_SECURITY_H
#define HAL_RF_SECURITY_H


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
#include <hal_types.h>

/******************************************************************************
* TYPEDEFS
*/


/******************************************************************************
* CONSTANTS AND DEFINES
*/

// IEEE 802.15.4 security (AES-128)
#define KEY_LENGTH                     16
#define NONCE_LENGTH                   16

#define SECURITY_CONTROL               0x06     // MIC-64


/******************************************************************************
* GLOBAL FUNCTIONS
*/
// CCM security interface, IEEE 802.15.4
void  halRfSecurityInit(uint8* key, uint8* nonceRx, uint8* nonceTx);
uint8 halRfReadRxBufSecure(uint8* pData, uint8 length, uint8 encrLength, 
                           uint8 authLength, uint8 m);
void  halRfWriteTxBufSecure(uint8* pData, uint8 length, uint8 encrLength, 
                            uint8 authLength, uint8 m);
void  halRfIncNonceTx(void);


/******************************************************************************
* Mark the end of the C bindings section for C++ compilers.
******************************************************************************/
#ifdef  __cplusplus
}
#endif
#endif // #ifndef HAL_RF_SECURITY_H
