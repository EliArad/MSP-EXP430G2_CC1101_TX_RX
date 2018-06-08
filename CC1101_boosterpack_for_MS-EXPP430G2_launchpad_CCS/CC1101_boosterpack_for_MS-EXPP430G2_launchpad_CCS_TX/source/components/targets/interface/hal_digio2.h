//*****************************************************************************
//! @file       hal_digio2.h
//! @brief      Functions for simple set-up of interrupts on IO pins.
//!             (simplified version of the original hal_digio).
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
#ifndef HAL_DIGIO2_H
#define HAL_DIGIO2_H


/******************************************************************************
* INCLUDES
*/
#include "hal_types.h"
#include "hal_defs.h"
#include "hal_digio.h"


/******************************************************************************
* TYPEDEFS
*/
typedef struct {
    uint8 port;
    uint8 pin;
} digio;


/******************************************************************************
* GLOBAL FUNCTIONS
*/
uint8 halDigio2IntConnect(digio io, ISR_FUNC_PTR func);
uint8 halDigio2IntEnable (digio io);
uint8 halDigio2IntDisable(digio io);
uint8 halDigio2IntClear  (digio io);
uint8 halDigio2IntSetEdge(digio io, uint8 edge);


#endif // #ifndef HAL_DIGIO2_H
