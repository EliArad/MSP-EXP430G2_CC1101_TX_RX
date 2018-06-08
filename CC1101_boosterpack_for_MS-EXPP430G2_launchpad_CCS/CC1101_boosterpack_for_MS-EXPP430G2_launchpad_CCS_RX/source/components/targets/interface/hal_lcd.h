/*******************************************************************************
*  Filename:        hal_lcd.h
*  Revised:         $Date: 2013-04-22 10:29:55 +0200 (ma, 22 apr 2013) $
*  Revision:        $Revision: 9898 $
*
*  Description:     HAL LCD library header file.
*
*
*  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
*
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************/

#ifndef HAL_LCD_H
#define HAL_LCD_H
/*******************************************************************************
* If building with a C++ compiler, make all of the definitions in this header
* have a C binding.
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
* INCLUDES
*/
#include "hal_types.h"


/*******************************************************************************
* CONSTANTS AND DEFINES
*/
enum {
    HAL_LCD_RADIX_DEC,
    HAL_LCD_RADIX_HEX
};

enum {
    HAL_LCD_LINE_1 = 1,
    HAL_LCD_LINE_2,
    HAL_LCD_LINE_3,
    HAL_LCD_LINE_4,
    HAL_LCD_LINE_5,
    HAL_LCD_LINE_6,
    HAL_LCD_LINE_7,
    HAL_LCD_LINE_8,
};


/*******************************************************************************
* GLOBAL FUNCTIONS
*/
void halLcdInit(void);
void halLcdClear(void);
void halLcdClearLine(uint8 line);
void halLcdSetContrast(uint8 value);
uint8 halLcdGetLineLength(void);
uint8 halLcdGetNumLines(void);

void halLcdWriteChar(uint8 line, uint8 col, char text);
void halLcdWriteLine(uint8 line, const char XDATA *text);
void halLcdWriteLines(const char XDATA *line1, const char XDATA *line2, const char XDATA *line3);

void halLcdClearAllSpecChars(void);
void halLcdCreateSpecChar(uint8 index, const char XDATA *p5x8Spec);
void halLcdWriteSpecChar(uint8 line, uint8 col, uint8 index);

void halLcd7SegWriteLine(const char *text);
void halLcd7SegWriteSymbol(uint8 symbol, uint8 on);
void halLcd7SegWriteValue(uint16 value, uint8 radix);


/*******************************************************************************
* Mark the end of the C bindings section for C++ compilers.
*******************************************************************************/
#ifdef  __cplusplus
}
#endif
#endif // #ifndef HAL_LCD_H