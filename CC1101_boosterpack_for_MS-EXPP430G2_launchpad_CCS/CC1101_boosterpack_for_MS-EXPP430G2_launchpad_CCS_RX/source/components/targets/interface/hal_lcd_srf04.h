//*****************************************************************************
//! @file       hal_lcd_srf04.h
//! @brief      HAL LCD header file for SmartRF04EB display
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
#ifndef HAL_LCD_SRF04EB_H
#define HAL_LCD_SRF04EB_H


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
* CONSTANTS AND DEFINES
*/
enum {
    HAL_LCD_SYMBOL_ARROW_LEFT      = 0x10,
    HAL_LCD_SYMBOL_ARROW_RIGHT     = 0x11,
    HAL_LCD_SYMBOL_ARROW_UP        = 0x12,
    HAL_LCD_SYMBOL_ARROW_DOWN      = 0x13
};

#define HAL_LCD_LINE_SIZE          16


/******************************************************************************
* Mark the end of the C bindings section for C++ compilers.
******************************************************************************/
#ifdef  __cplusplus
}
#endif
#endif // #ifndef HAL_LCD_SRF04EB_H
