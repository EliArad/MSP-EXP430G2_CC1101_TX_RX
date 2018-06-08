//*****************************************************************************
//! @file       lcd_dogm128_6.h
//! @brief      Device driver header file for DOGM128-6 LCD display.
//!
//!             The DOGM128-6 LCD display is a 128x64 dot matrix and is divided
//!             into 8 pages (\c LCD_PAGE_0 through \c LCD_PAGE_7),
//!             each 8 px high.
//!
//! Datasheet   http://www.lcd-module.com/eng/pdf/grafik/dogm128e.pdf
//!
//! Revised     $Date: 2012-12-12 10:20:32 +0100 (on, 12 des 2012) $
//! Revision    $Revision: 9000 $
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
#ifndef __LCD_DOGM128_6_H__
#define __LCD_DOGM128_6_H__


/******************************************************************************
* If building with a C++ compiler, make all of the definitions in this header
* have a C binding.
******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif


/******************************************************************************
* INCLUDES
*/


/******************************************************************************
* DEFINES
*/
#define LCD_PIXELS    8192      //!< Number of pixels in LCD display
#define LCD_BYTES     1024      //!< Number of bytes needed in LCD buffer
#define LCD_COLS      128       //!< Number of pixel columns
#define LCD_ROWS      64        //!< Number of pixel rows
#define LCD_PAGES     8         //!< Number of pages
#define LCD_PAGE_ROWS 8         //!< Number of pixel rows per LCD page

// The difference between LCD_CHAR_WIDTH and LCD_FONT_WIDTH
// equals the character spacing on the LCD display.
#define LCD_CHAR_WIDTH    6     //!< Space used for each character
#define LCD_FONT_WIDTH    5     //!< The actual width of the font's character

//! LCD animation enum. Used by lcdSendBufferAnimated
enum {
    LCD_NO_MOTION = 0,
    LCD_SLIDE_RIGHT = 1,
    LCD_SLIDE_LEFT = 2
};

//! LCD alignment enum. Used by lcdPrintxxxAligned functions
enum {
    LCD_ALIGN_LEFT = 0,
    LCD_ALIGN_CENTER = 1,
    LCD_ALIGN_RIGHT = 2
};

//! LCD page enum. Used for page argument in lcdBufferxxx function
enum {
    LCD_PAGE_0 = 0,
    LCD_PAGE_1 = 1,
    LCD_PAGE_2 = 2,
    LCD_PAGE_3 = 3,
    LCD_PAGE_4 = 4,
    LCD_PAGE_5 = 5,
    LCD_PAGE_6 = 6,
    LCD_PAGE_7 = 7
};

//! LCD x-axis enum. Used for x argument in lcdBufferxxx functions
enum {
    LCD_X_FIRST = 0,
    LCD_X_LAST  = (LCD_COLS-1)
};

//! LCD y-axis enum. Used for y argument in lcdBufferxxx functions
enum {
    LCD_Y_FIRST = 0,
    LCD_Y_LAST  = (LCD_ROWS-1)
};

/******************************************************************************
* EXTERNAL VARIABLES
*/

extern const unsigned char lcd_alphabet[];

#ifndef LCD_NO_DEFAULT_BUFFER
extern char lcdDefaultBuffer[LCD_BYTES];
#endif


/******************************************************************************
* FUNCTION PROTOTYPES
*/
// Functions accessing LCD
void lcdInit(void);
void lcdClear(void);
void lcdSpiInit(void);
void lcdSendCommand(const char *pcCmd, unsigned char ucLen);
void lcdSendData(const char *pcData, unsigned short usLen);
void lcdSendBufferAnimated(const char *pcToBuffer,
                           const char *pcFromBuffer, unsigned char ucMotion);

void lcdSendBuffer(const char *pcBuffer);
void lcdSendBufferPart(const char *pcBuffer, unsigned char ucXFrom,
                       unsigned char ucXTo, unsigned char ucPageFrom,
                       unsigned char ucPageTo);
void lcdGotoXY(unsigned char ucX, unsigned char ucY);
void lcdSetContrast(unsigned char ucContrast);

// Buffer manipulation functions
void lcdBufferClear(char *pcBuffer);
void lcdBufferClearPage(char *pcBuffer, unsigned char ucPage);
void lcdBufferClearPart(char *pcBuffer, unsigned char ucXFrom,
                        unsigned char ucXTo, unsigned char ucPageFrom,
                        unsigned char ucPageTo);
void lcdBufferInvert(char *pcBuffer, unsigned char ucXFrom,
                     unsigned char ucYFrom, unsigned char ucXTo,
                     unsigned char ucYTo);
void lcdBufferInvertPage(char *pcBuffer, unsigned char ucXFrom,
                         unsigned char ucXTo, unsigned char ucPage);
unsigned char lcdGetStringLength(const char *pcStr);
unsigned char lcdGetIntLength(signed long slNumber);
unsigned char lcdGetFloatLength(float fNumber, unsigned char ucDecimals);
void lcdBufferPrintString(char *pcBuffer, const char *pcStr, unsigned char ucX,
                          unsigned char ucPage);
void lcdBufferPrintStringAligned(char *pcBuffer, const char *pcStr,
                                 unsigned char ucAlignment,
                                 unsigned char ucPage);
void lcdBufferPrintInt(char *pcBuffer, signed long slNumber,
                       unsigned char ucX, unsigned char ucPage);
void lcdBufferPrintIntAligned(char *pcBuffer, signed long slNumber,
                              unsigned char ucAlignment, unsigned char ucPage);
void lcdBufferPrintFloat(char *pcBuffer, float fNumber,
                         unsigned char ucDecimals, unsigned char ucX,
                         unsigned char ucPage);
void lcdBufferPrintFloatAligned(char *pcBuffer, float fNumber,
                                unsigned char ucDecimals,
                                unsigned char ucAlignment,
                                unsigned char ucPage);
void lcdBufferSetLine(char *pcBuffer, unsigned char ucXFrom,
                      unsigned char ucYFrom, unsigned char ucXTo,
                      unsigned char ucYTo);
void lcdBufferClearLine(char *pcBuffer, unsigned char ucXFrom,
                        unsigned char ucYFrom, unsigned char ucXTo,
                        unsigned char ucYTo);
void lcdBufferSetHLine(char *pcBuffer, unsigned char ucXFrom,
                       unsigned char ucXTo, unsigned char ucY);
void lcdBufferClearHLine(char *pcBuffer, unsigned char ucXFrom,
                         unsigned char ucXTo, unsigned char ucY);
void lcdBufferSetVLine(char *pcBuffer, unsigned char ucX,
                       unsigned char ucYFrom, unsigned char ucYTo);
void lcdBufferClearVLine(char *pcBuffer, unsigned char ucX,
                         unsigned char ucYFrom, unsigned char ucYTo);
void lcdBufferHArrow(char *pcBuffer, unsigned char ucXFrom,
                     unsigned char ucXTo, unsigned char ucY);
void lcdBufferVArrow(char *pcBuffer, unsigned char ucX, unsigned char ucYFrom,
                     unsigned char ucYTo);
void lcdBufferSetPx(char *pcBuffer, unsigned char ucX, unsigned char ucY);
void lcdBufferClearPx(char *pcBuffer, unsigned char ucX, unsigned char ucY);
void lcdBufferCopy(const char *pcFromBuffer, char *pcToBuffer);


/******************************************************************************
* Mark the end of the C bindings section for C++ compilers.
******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* #ifndef __LCD_DOGM128_6_H__ */
