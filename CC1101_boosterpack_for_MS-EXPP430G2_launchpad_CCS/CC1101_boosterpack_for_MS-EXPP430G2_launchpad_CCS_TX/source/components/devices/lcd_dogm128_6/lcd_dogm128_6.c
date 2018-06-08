//*****************************************************************************
//! @file       lcd_dogm128_6.c
//! @brief      Driver implementation for DOGM128W-6 LCD display. This file
//!             contains platform independent functions. Platform dependent
//!             functions are located in lcd_xxx.c where xxx is
//!             the target in question, for example, srf06eb or trxeb.
//!
//!             The (x,y) coordinate system
//!             used in this device driver is as described below:
//!             <pre>
//!             + ----->   x
//!             | +---------------------------------------------+
//!             | |(0,0)              PAGE 0             (127,0)|
//!             V |                   PAGE 1                    |
//!               |                    ...                      |
//!             y |                    ...                      |
//!               |                    ...                      |
//!               |                    ...                      |
//!               |                    ...                      |
//!               |(0,63)             PAGE 7            (127,63)|
//!               +---------------------------------------------+</pre>
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
#ifndef LCD_EXCLUDE


/**************************************************************************//**
* @addtogroup   lcd_dogm128_6_api
* @{
******************************************************************************/


/******************************************************************************
* INCLUDES
*/
#include "lcd_dogm128_6.h"


/******************************************************************************
* DEFINES
*/


/******************************************************************************
* VARIABLES AND LOCAL FUNCTIONS
*/
#ifndef LCD_NO_DEFAULT_BUFFER
char lcdDefaultBuffer[LCD_BYTES] = {0};
#endif

static void lcdBufferLine(char *pcBuffer, unsigned char ucXFrom,        \
                          unsigned char ucYFrom, unsigned char ucXTo,   \
                          unsigned char ucYTo, unsigned char ucDraw);


/******************************************************************************
* FUNCTIONS
*/
// TARGET SPECIFIC FUNCTIONS (NOT IMPLEMENTED HERE):
// void lcdInit(void)
// void lcdSpiInit(void)
// void lcdClear(void)
// void lcdSendCommand(const char *pcCmd, unsigned char ucLen)
// void lcdSendData(const char *pcData, unsigned short ucLen)
// void lcdSendBufferAnimated(const char *pcToBuffer, const char *pcFromBuffer,
//                            unsigned char ucMotion)


/**************************************************************************//**
* @brief    This function sends the specified buffer to the display. The buffer 
*           size is assumed to be 1024 bytes. Passing \e pcBuffer as 0 will
*           send the default buffer. If \b LCD_NO_DEFAULT_BUFFER is defined, 
*           passing \e pcBuffer as 0 will result in undefined behavior.
*
* @param    pcBuffer    is a pointer to the source buffer.
*
* @return   None
******************************************************************************/
void lcdSendBuffer(const char *pcBuffer)
{
    unsigned char ucPage;
    char *pcBuf = (char *)pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    // For each page
    for(ucPage=0; ucPage<8; ucPage++)
    {
        lcdGotoXY(0, ucPage);          // Set pointer to start of row/page
        lcdSendData(pcBuf + (ucPage*LCD_COLS), LCD_COLS); // Send one page
    }
}


/**************************************************************************//**
* @brief    This function sends the specfied part of \e pcBuffer to the 
*           corresponding part on the LCD. This function assumes 
*           \e ucXFrom <= \e ucXTo and \e ucPageFrom <= \e ucPageTo. The 
*           resolution is given in coulmns [0--127] and pages [0--7].
*
* @param    pcBuffer    is a pointer to the buffer to send. The default
*                       buffer is sent if \e pcBuffer is 0.
* @param    ucXFrom     is the lowest x-position (column) to write [0--127].
* @param    ucXTo       is the highest x-position to write [ucXFrom--127].
* @param    ucPageFrom  is the first page to write [0--7].
* @param    ucPageTo    is the last page to write [ucPageFrom--7].
*
* @return   None
******************************************************************************/
void lcdSendBufferPart(const char *pcBuffer, unsigned char ucXFrom,
                       unsigned char ucXTo, unsigned char ucPageFrom,
                       unsigned char ucPageTo)
{
    unsigned char ucXRange, ucY, ucYOffset, ucYRange;
    char *pcBuf = (char *)pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    // Assuming ucXFrom <= ucXTo
    ucXRange = ucXTo - ucXFrom + 1;

    // Assuming ucPageFrom <= ucPage To
    ucYRange = ucPageTo - ucPageFrom;

    // For each page
    for(ucY=0; ucY<=ucYRange; ucY++)
    {
        ucYOffset = ucPageFrom+ucY;
        lcdGotoXY(ucXFrom, ucYOffset);
        lcdSendData(pcBuf+(ucYOffset*LCD_COLS)+ucXFrom, ucXRange );
    }
}


/**************************************************************************//**
* @brief    This function sets the internal data cursor of the LCD to the 
*           location specified by \e ucX and \e ucY. When data is sent to the
*           display, data will start printing at internal cursor location.
*
* @param    ucX         is the column [0--127].
* @param    ucY         is the page [0--7].
*
* @return   None
******************************************************************************/
void lcdGotoXY(unsigned char ucX, unsigned char ucY)
{
    unsigned char cmd[] = {0xB0, 0x10, 0x00};   // Command array
    cmd[0] = cmd[0] + ucY;          // Add Y position to command
    cmd[2] = cmd[2] + (ucX & 0x0F); // Add X position (low nibble) to command
    cmd[1] = cmd[1] + (ucX >> 4);   // Add X position (high nibble) to command
    lcdSendCommand((char *)cmd, 3);
}


/**************************************************************************//**
* @brief    This function sets the LCD contrast.
*
* @param    ucContrast  is the contrast value [0--63].
*
* @return   None
******************************************************************************/
void lcdSetContrast(unsigned char ucContrast)
{
    char pCmd[2];
    pCmd[0] = 0x81;
    pCmd[1] = (ucContrast & 0x3f);
    lcdSendCommand(pCmd, 2);
}


/**************************************************************************//**
* @brief    This function empties the LCD buffer specified by argument 
*           \e pcBuffer by filling it with zeros.
*
* @param    pcBuffer    is a pointer to the target buffer.
*
* @return   None
******************************************************************************/
void lcdBufferClear(char *pcBuffer)
{
    unsigned short ucIdx;
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    for(ucIdx=0; ucIdx<LCD_BYTES; ucIdx++)
    {
        *(pcBuf + ucIdx) = 0x00;
    }
}


/**************************************************************************//**
* @brief    This function clears the page specified by \e ucPage in LCD buffer 
*           specified by \e pcBuffer.
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    ucPage      is the page to clear [0--7].
*
* @return   None
******************************************************************************/
void lcdBufferClearPage(char *pcBuffer, unsigned char ucPage)
{
    unsigned char ucIdx;
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    for(ucIdx=0; ucIdx<LCD_COLS; ucIdx++)
    {
        *(pcBuf + (ucPage*LCD_COLS + ucIdx)) = 0x00;
    }
}


/**************************************************************************//**
* @brief    This function clears the pixels in a given piece of a page. 
*           Resolution is given in coulmns [0--127] and pages [0--7]. The 
*           function assumes \e ucXFrom <= \e ucXTo and 
*           \e ucPageFrom <= \e ucPageTo.
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    ucXFrom     is the lowest x-position (column) to be cleared [0--127].
* @param    ucXTo       is the highest x-position to be cleared [ucXFrom--127].
* @param    ucPageFrom  is the first page cleared [0--7].
* @param    ucPageTo    is the last page cleared [ucPageFrom--7].
*
* @return   None
******************************************************************************/
void lcdBufferClearPart(char *pcBuffer, unsigned char ucXFrom,
                        unsigned char ucXTo, unsigned char ucPageFrom,
                        unsigned char ucPageTo)
{
    unsigned short usXFirstPos;
    unsigned char ucX, ucXRange, ucY, ucYRange;
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    // Expecting ucYFrom <= ucYTo
    ucXRange = ucXTo-ucXFrom;
    // Expecting ucYFrom <= ucYTo
    ucYRange = ucPageTo - ucPageFrom;

    for(ucY=0;ucY<=ucYRange;ucY++)
    {
        usXFirstPos = (ucPageFrom+ucY)*LCD_COLS+ucXFrom;
        for(ucX=0;ucX<=ucXRange;ucX++)
        {
            *(pcBuf + (usXFirstPos+ucX)) = 0x00;
        }
    }
}


/**************************************************************************//**
* @brief    This function inverts the pixels (bits) in a given region of the 
*           buffer specified by \e pcBuffer.
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    ucXFrom     is the first x-position (column) to invert [0--127].
* @param    ucYFrom     is the first y-position (row) to invert [0--63].
* @param    ucXTo       is the last x-position (column) to invert [0--127].
* @param    ucYTo       is the last y-position (row) to invert [0--63].
*
* @return   None
******************************************************************************/
void lcdBufferInvert(char *pcBuffer, unsigned char ucXFrom,
                     unsigned char ucYFrom, unsigned char ucXTo,
                     unsigned char ucYTo)
{
    unsigned char ucI, ucJ, ucPow;
    unsigned char ucFirstPage, ucLastPage, ucFirstPageMask, ucLastPageMask;
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    // Find the first and last page to invert on
    ucFirstPage = ucYFrom / LCD_PAGE_ROWS;
    ucLastPage = ucYTo / LCD_PAGE_ROWS;

    // Find the bitmask to invert with on first page
    ucFirstPageMask = 0xFF;
    ucPow = 1;

    for(ucI=0; ucI<LCD_PAGE_ROWS; ucI++)
    {
        if(ucYFrom-ucFirstPage*LCD_PAGE_ROWS>ucI)
        {
            ucFirstPageMask -= ucPow;
            ucPow *= 2;
        }
    }

    // Find the bitmask to invert with on the last page
    ucLastPageMask = 0x00;
    ucPow = 1;
    for(ucI=0; ucI<LCD_PAGE_ROWS; ucI++)
    {
        if(ucYTo-ucLastPage*LCD_PAGE_ROWS>=ucI)
        {
            ucLastPageMask += ucPow;
            ucPow *= 2;
        }
    }

    // Prevent error if ucFirstPage==ucLastPage
    if(ucFirstPage==ucLastPage)
    {
        ucLastPageMask ^= 0xFF;
    }

    // Invert the given part of the first page
    for(ucI=ucXFrom; ucI<=ucXTo; ucI++)
    {
        *(pcBuf + (ucFirstPage*LCD_COLS+ucI)) ^= ucFirstPageMask;
    }
    // Invert the pages between first and last in the given section
    for(ucI=ucFirstPage+1; ucI<=ucLastPage-1; ucI++)
    {
        for(ucJ=ucXFrom;ucJ<=ucXTo;ucJ++)
        {
            *(pcBuf + (ucI*LCD_COLS+ucJ)) ^= 0xFF;
        }
    }
    // Invert the given part of the last page
    for(ucI=ucXFrom; ucI<=ucXTo; ucI++)
    {
        *(pcBuf + (ucLastPage*LCD_COLS+ucI)) ^= ucLastPageMask;
    }
}


/**************************************************************************//**
* @brief    This function inverts a range of columns in the display buffer on a 
*           specified page (for example, \b LCD_PAGE_0). This function assumes 
*           \e ucXFrom <= \e ucXTo.
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    ucXFrom     is the first x-position (column) to invert [0--127].
* @param    ucXTo       is the last x-position  to invert [ucXFrom--127].
* @param    ucPage      is the page on which to invert [0--7].
*
* @return   None
******************************************************************************/
void lcdBufferInvertPage(char *pcBuffer, unsigned char ucXFrom,
                         unsigned char ucXTo, unsigned char ucPage)
{
    unsigned char ucI;
    unsigned short usFirstPos = ucPage*LCD_COLS + ucXFrom;
    unsigned char ucRange = ucXTo-ucXFrom;
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    for(ucI=0; ucI<=ucRange; ucI++)
    {
        *(pcBuf + (usFirstPos+ucI)) ^= 0xFF;
    }
}


/**************************************************************************//**
* @brief    Returns the length a c-string in number of characters by looking
*           for the end-of-string character '<tt>\\0</tt>'.
*           Multiply by \b LCD_CHAR_WIDTH to get length in pixels.
*
* @param    pcStr   C string.
*
* @return   Returns length of \e pcStr
******************************************************************************/
unsigned char lcdGetStringLength(const char *pcStr)
{
    unsigned char ucI = 0;
    while(pcStr[ucI] != '\0') ucI++;
    return ucI;
}


/**************************************************************************//**
* @brief    This function returns the character length an integer will use on 
*           the LCD display. For example, \e slNumber = 215 returns 3 
*           and \e slNumber = --215 returns 4 (add one for the minus character). 
*           Multiply result of lcdGetIntLength() by \b LCD_CHAR_WIDTH to 
*           determine the number of pixels needed by \e slNumber.
*
* @param    slNumber    is the number whose character length is determined.
*
* @return   Returns the character length of \e slNumber.
******************************************************************************/
unsigned char lcdGetIntLength(signed long slNumber)
{
    unsigned char ucNumOfDigits = 0;
    if(slNumber == 0)
    {
        return 1;           // The character zero also takes up one place
    }

    if(slNumber < 0)
    {
        slNumber *= (-1);
        ucNumOfDigits++;    // Add one character to length due to minus sign
    }

    while(slNumber >= 1)
    {
        slNumber /= 10;
        ucNumOfDigits++;
    }
    return ucNumOfDigits;
}


/**************************************************************************//**
* @brief    This function returns the character length a float will need on the 
*           LCD display. This function is used by lcdBufferPrintFloat() and 
*           lcdBufferPrintFloatAligned(). \e ucDecimals must be provided to 
*           limit the number of decimals.
*
* @param    fNumber     is the number whose character length is determined.
* @param    ucDecimals  is the desired number of decimals to use (maximum 10).
*
* @return   Returns the character length of \e fNumber.
******************************************************************************/
unsigned char lcdGetFloatLength(float fNumber, unsigned char ucDecimals)
{
    unsigned char ucI;
    unsigned char ucNumOfDigits = 0;

    float fThreshold = -0.5;         // The threshold which defines how low a
    for(ucI=0; ucI<ucDecimals; ucI++)// float must be to be considered
    {                                // negative. E.g. if a float is -0.001 and
        fThreshold *= 0.1;           // the number of decimals is 2, then the
    }                                // number will be considered as 0.00 and
                                     // not -0.00.

    if(fNumber <= fThreshold)// Add one character for minus sign if negative.
    {                        // This can not be done in halLcdIntLength because
        ucNumOfDigits++;     // -0.5 i.e. would cast to 0 and lose its sign.
        fNumber *= (-1);     // Work only with positive part afterwards.
    }

    ucNumOfDigits += lcdGetIntLength((signed long)fNumber); // integer part
    if(ucDecimals) ucNumOfDigits++;                         // comma
    ucNumOfDigits += ucDecimals;                            // decimal part
    return ucNumOfDigits;
}


/**************************************************************************//**
* @brief    This function writes a string to the buffer specified by 
*           \e pcBuffer.
*
* @param    pcBuffer    is a pointer to the output buffer.
* @param    pcStr       is a pointer to the string to print.
* @param    ucX         is the x-position (column) to begin printing [0--127].
* @param    ucPage      is the page on which to print [0--7].
*
* @return   None
******************************************************************************/
void lcdBufferPrintString(char *pcBuffer, const char *pcStr, unsigned char ucX,
                          unsigned char ucPage)
{
    unsigned char ucI, ucJ;
    unsigned short firstIndex;
    unsigned char ucStrSize = lcdGetStringLength(pcStr);
    unsigned short usFirstPos = ucPage*LCD_COLS+ucX;
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    // Running through each letter in input string
    for(ucI=0; ucI<ucStrSize; ucI++)
    {
        if(pcStr[ucI]==' ')
        {
            for(ucJ=0; ucJ<LCD_CHAR_WIDTH; ucJ++){
                *(pcBuf + (usFirstPos+LCD_CHAR_WIDTH*ucI+ucJ)) = 0x00; // Space character
            }
        }
        else
        {
            // The index to the beginning of the current letter in lcd_alphabet[]
            firstIndex = ((unsigned short)(pcStr[ucI])-33)*LCD_FONT_WIDTH;

            // Stores each vertical column of the current letter in the result
            for(ucJ=0;ucJ<LCD_FONT_WIDTH;ucJ++) {
                *(pcBuf + (usFirstPos+LCD_CHAR_WIDTH*ucI+ucJ)) = lcd_alphabet[firstIndex+ucJ];
            }
            *(pcBuf + (usFirstPos+LCD_CHAR_WIDTH*ucI+LCD_FONT_WIDTH)) = 0x00; // Spacing after letter
        }
    }
}


/**************************************************************************//**
* @brief    This function writes a string to buffer \e pcBuffer as 
*           specified by the \e ucAlignment argument.
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    pcStr       is a pointer to the string to print.
* @param    ucAlignment is the text alignment. Can be one of the following:
*                       \li \b LCD_ALIGN_LEFT
*                       \li \b LCD_ALIGN_CENTER
*                       \li \b LCD_ALIGN_RIGHT
* @param    ucPage      is the page on which to print [0--7].
*
* @return   None
******************************************************************************/
void lcdBufferPrintStringAligned(char *pcBuffer, const char *pcStr,
                                 unsigned char ucAlignment,
                                 unsigned char ucPage)
{
    unsigned char ucStrSize = lcdGetStringLength(pcStr);
    unsigned char ucX;

    switch(ucAlignment) {
    case LCD_ALIGN_CENTER:
        ucX = LCD_COLS/2 - ucStrSize*LCD_CHAR_WIDTH/2; break;
    case LCD_ALIGN_RIGHT:
        ucX = LCD_COLS - ucStrSize*LCD_CHAR_WIDTH; break;
    case LCD_ALIGN_LEFT:
    default:
        ucX = 0; break;
    }
    lcdBufferPrintString(pcBuffer, pcStr, ucX, ucPage);
}


/**************************************************************************//**
* @brief    This function writes an integer to the buffer specified by 
*           \e pcBuffer.
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    slNumber    is the number to print.
* @param    ucX         is the x-position (column) to begin printing [0--127].
* @param    ucPage      is the page on which to print [0--7].
*
* @return   None
******************************************************************************/
void lcdBufferPrintInt(char *pcBuffer, signed long slNumber,
                       unsigned char ucX, unsigned char ucPage)
{
    signed char scI;
    unsigned char ucJ, ucNumOfDigits;
    signed long slTemp, slDigit, slFirstIdx;
    unsigned short usFirstPos = ucPage*LCD_COLS + ucX;
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    // if number is negative:
    // write a minus at first position, increment first position by one
    // character and multiply number by (-1).
    if(slNumber < 0){
        for(ucJ=0; ucJ<LCD_FONT_WIDTH; ucJ++)
        {
            *(pcBuf + (usFirstPos + ucJ)) = lcd_alphabet[12*LCD_FONT_WIDTH+ucJ];
        }
        *(pcBuf + (usFirstPos + LCD_FONT_WIDTH)) = 0x00;   // Spacing
        usFirstPos += LCD_CHAR_WIDTH;
        slNumber *= (-1);
    }

    // Finding numbers of digits in slNumber (except for minus character)
    ucNumOfDigits = lcdGetIntLength(slNumber);

    // running through each digit, starting with MSD, and writing to buffer
    for(scI=ucNumOfDigits-1; scI >= 0; scI--){
        slTemp = slNumber/10;
        slDigit = slNumber-slTemp*10;
        slFirstIdx = (slDigit+15)*LCD_FONT_WIDTH;
        for(ucJ=0; ucJ<LCD_FONT_WIDTH; ucJ++)
        {
            *(pcBuf + (usFirstPos + LCD_CHAR_WIDTH*scI + ucJ)) = lcd_alphabet[slFirstIdx+ucJ];
        }
        // Spacing
        *(pcBuf + (usFirstPos + LCD_CHAR_WIDTH*scI + LCD_FONT_WIDTH)) = 0x00;
        slNumber = slTemp;
    }
}


/**************************************************************************//**
* @brief    This function writes an integer to buffer \e pcBuffer as 
*           specified by the \e ucAlignment argument.
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    slNumber    is the number to be printed.
* @param    ucAlignment is the text alignment. Can be one of the following:
*                       \li \b LCD_ALIGN_LEFT
*                       \li \b LCD_ALIGN_CENTER
*                       \li \b LCD_ALIGN_RIGHT
* @param    ucPage      is the page on which to print [0--7].
*
* @return   None
******************************************************************************/
void lcdBufferPrintIntAligned(char *pcBuffer, signed long slNumber,
                              unsigned char ucAlignment, unsigned char ucPage)
{
    unsigned char ucStrSize = lcdGetIntLength(slNumber);
    unsigned char ucX;

    switch(ucAlignment) {
    case LCD_ALIGN_CENTER:
        ucX = LCD_COLS/2 - ucStrSize*LCD_CHAR_WIDTH/2; break;
    case LCD_ALIGN_RIGHT:
        ucX = LCD_COLS - ucStrSize*LCD_CHAR_WIDTH; break;
    case LCD_ALIGN_LEFT:
    default:
        ucX = 0; break;
    }
    lcdBufferPrintInt(pcBuffer, slNumber, ucX, ucPage);
}


/**************************************************************************//**
* @brief    This function writes a number of data type float on the display
*           at a specified column and page. Use this function instead of 
*           performing a float to c-string conversion and then using 
*           lcdBufferPrintString().
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    fNumber     is the number to print.
* @param    ucDecimals  is the number of decimals to print, MAX = 10.
* @param    ucX         is the x-position (column) to begin printing [0--127].
* @param    ucPage      is the page on which to print [0--7].
*
* @return   None
******************************************************************************/
void lcdBufferPrintFloat(char *pcBuffer, float fNumber,
                         unsigned char ucDecimals, unsigned char ucX,
                         unsigned char ucPage)
{
    unsigned char ucI, ucRoundUp;
    signed char scJ;
    signed long integerPart, tmpInteger1;
    unsigned char decimalArray[11];
    unsigned char numNeg = 0;
    float fThreshold;
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    fThreshold = -0.5;               // The threshold which defines how low a
    for(ucI=0; ucI<ucDecimals; ucI++)// float must be to be considered negative.
    {                                // I.e. if a float is -0.001 and the number
        fThreshold *= 0.1;           // of decimals is 2 then the number will be
    }                                // considered as 0.00 and not -0.00.

    if(fNumber <= fThreshold)
    {
        fNumber *= -1;
        numNeg = 1;
    }

    // Extracting integer part
    integerPart = (signed long)fNumber;

    // Storing ucDecimals+1 decimals in an array
    for(ucI=0; ucI<ucDecimals+1; ucI++)
    {
        fNumber   = fNumber*10;
        tmpInteger1 = (signed long)fNumber;
        tmpInteger1 = tmpInteger1 % 10;
        decimalArray[ucI] = tmpInteger1;
    }

    // Perform upwards rounding: This can correct the truncation error that
    // occurs when passing a float argument that is generated by division. ex:
    // (59/100)*100 = 58.9999961. If printing with 2 decimals, this will give
    // 59.00. This also indicates that many decimals should not be used ...
    if(decimalArray[ucDecimals] > 4)
    {
        ucRoundUp = 1;
        for(scJ=ucDecimals-1; scJ>=0; scJ--)
        {
            decimalArray[scJ] = decimalArray[scJ] + ucRoundUp;
            if(decimalArray[scJ] == 10)
            {
                decimalArray[scJ] = 0;
            }
            else
            {
                ucRoundUp = 0;
            }
        }
        if(ucRoundUp == 1)
        {
            integerPart++;
        }
    }

    // Printing the decimal number to screen
    // - print sign if applicable
    // - print integer number
    // - print comma
    // - print number of decimals
    if(numNeg == 1)
    {
        lcdBufferPrintString(pcBuf, "-", ucX, ucPage);
        ucX += LCD_CHAR_WIDTH;
    }
    lcdBufferPrintInt(pcBuf, integerPart, ucX, ucPage);
    ucX += lcdGetIntLength(integerPart) * LCD_CHAR_WIDTH;
    lcdBufferPrintString(pcBuf, ".", ucX, ucPage);
    ucX += LCD_CHAR_WIDTH;
    for(ucI = 0; ucI< ucDecimals; ucI++)
    {
        lcdBufferPrintInt(pcBuf,decimalArray[ucI],ucX,ucPage);
        ucX += LCD_CHAR_WIDTH;
    }
}


/**************************************************************************//**
* @brief    This function writes a float number to buffer \e pcBuffer as 
*           specified by the \e ucAlignment argument.
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    fNumber     is the number to be printed.
* @param    ucDecimals  is the number of decimals to be printed, MAX = 10.
* @param    ucAlignment is the text alignment. Can be one of the following:
*                       \li \b LCD_ALIGN_LEFT
*                       \li \b LCD_ALIGN_CENTER
*                       \li \b LCD_ALIGN_RIGHT
* @param    ucPage      is the page on which to [0--7].
*
* @return   None
******************************************************************************/
void lcdBufferPrintFloatAligned(char *pcBuffer, float fNumber,
                                unsigned char ucDecimals,
                                unsigned char ucAlignment, unsigned char ucPage)
{
    unsigned char ucStrSize = lcdGetFloatLength(fNumber, ucDecimals);
    unsigned char ucX;

    switch(ucAlignment) {
    case LCD_ALIGN_CENTER:
        ucX = LCD_COLS/2 - ucStrSize*LCD_CHAR_WIDTH/2; break;
    case LCD_ALIGN_RIGHT:
        ucX = LCD_COLS - ucStrSize*LCD_CHAR_WIDTH; break;
    case LCD_ALIGN_LEFT:
    default:
        ucX = 0; break;
    }
    lcdBufferPrintFloat(pcBuffer, fNumber, ucDecimals, ucX, ucPage);
}


/**************************************************************************//**
* @brief    This function draws a line in buffer \e pcBuffer from 
*           (\e ucXFrom,\e ucYFrom) to (\e ucXTo,\e ucYTo). The function
*           uses Bresenham's line algorithm.
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    ucXFrom     is the start column [0--127].
* @param    ucXTo       is the end column [0--127].
* @param    ucYFrom     is the start row [0--63].
* @param    ucYTo       is the end row [0--63].
*
* @return   None
******************************************************************************/
void lcdBufferSetLine(char *pcBuffer, unsigned char ucXFrom,
                      unsigned char ucYFrom, unsigned char ucXTo,
                      unsigned char ucYTo)
{
    // Draw line
    lcdBufferLine(pcBuffer, ucXFrom, ucYFrom, ucXTo, ucYTo, 1);
}


/**************************************************************************//**
* @brief    This function clears a line in buffer \e pcBuffer from 
*           (\e ucXFrom,\e ucYFrom) to (\e ucXTo,\e ucYTo). The function uses 
*           Bresenham's line algorithm.
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    ucXFrom     is the start column [0--127].
* @param    ucXTo       is the end column [0--127].
* @param    ucYFrom     is the start row [0--63].
* @param    ucYTo       is the end row [0--63].
*
* @return   None
******************************************************************************/
void lcdBufferClearLine(char *pcBuffer, unsigned char ucXFrom,
                        unsigned char ucYFrom, unsigned char ucXTo,
                        unsigned char ucYTo)
{
    // Clear line
    lcdBufferLine(pcBuffer, ucXFrom, ucYFrom, ucXTo, ucYTo, 0);
}


/**************************************************************************//**
* @brief    This function draws a horizontal line from (\e ucXFrom,\e ucY) to 
*           (\e ucXTo,\e ucY) into buffer \e pcBuffer.
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    ucXFrom     is the start column [0--127].
* @param    ucXTo       is the end column [0--127].
* @param    ucY         is the row [0--63].
*
* @return   None
******************************************************************************/
void lcdBufferSetHLine(char *pcBuffer, unsigned char ucXFrom,
                       unsigned char ucXTo, unsigned char ucY)
{
    unsigned char ucI;
    unsigned char ucPage = ucY/LCD_PAGE_ROWS;
    unsigned char bit  = ucY%LCD_PAGE_ROWS;
    unsigned char bitmask = 1<<bit;
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    // Switch draw direction if ucXTo < ucXFrom
    if(ucXTo < ucXFrom)
    {
        unsigned char ucTemp = ucXFrom;
        ucXFrom = ucXTo;
        ucXTo = ucTemp;
    }

    for(ucI=ucXFrom; ucI<=ucXTo; ucI++)
    {
        *(pcBuf + (ucPage*LCD_COLS+ucI)) |= bitmask;
    }
}


/**************************************************************************//**
* @brief    this function Clears a horizontal line from (\e ucXFrom,\e ucY) to 
*           (\e ucXTo,\e ucY) from buffer \e pcBuffer.
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    ucXFrom     is the start column [0--127].
* @param    ucXTo       is the end column [0--127].
* @param    ucY         is the row [0--63].
*
* @return   None
******************************************************************************/
void lcdBufferClearHLine(char *pcBuffer, unsigned char ucXFrom,
                         unsigned char ucXTo, unsigned char ucY)
{
    unsigned char ucI;
    unsigned char ucPage = ucY/LCD_PAGE_ROWS;
    unsigned char ucBit  = ucY%LCD_PAGE_ROWS;
    unsigned char ucBitmask = 1<<ucBit;
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif

    // Switch draw direction if ucXTo < ucXFrom
    if(ucXTo < ucXFrom)
    {
        unsigned char ucTemp = ucXFrom;
        ucXFrom = ucXTo;
        ucXTo = ucTemp;
    }

    for(ucI=ucXFrom; ucI<=ucXTo; ucI++)
    {
        *(pcBuf + (ucPage*LCD_COLS+ucI)) &= ~ucBitmask;
    }
}

/**************************************************************************//**
* @brief    This function draws a vertical line from (ucX,ucYFrom) to 
*           (ucX,ucYTo) into buffer \e pcBuffer.
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    ucX         is the x-position (column) of the line [0--127].
* @param    ucYFrom     is the start row [0--63].
* @param    ucYTo       is the end row [0--63].
*
* @return   None
******************************************************************************/
void lcdBufferSetVLine(char *pcBuffer, unsigned char ucX,
                       unsigned char ucYFrom, unsigned char ucYTo)
{
    unsigned char ucI, ucPow;
    unsigned char ucPage, ucFirstPage, ucLastPage;
    unsigned char ucFirstPageMask, ucLastPageMask;
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    ucFirstPage = ucYFrom/LCD_PAGE_ROWS;
    ucLastPage = ucYTo/LCD_PAGE_ROWS;

    //  Finds the bitmask to use with the first page
    ucFirstPageMask = 0xFF;
    ucPow = 1;
    for(ucI=0; ucI<LCD_PAGE_ROWS; ucI++)
    {
        if(ucYFrom-ucFirstPage*LCD_PAGE_ROWS>ucI)
        {
            ucFirstPageMask -= ucPow;
            ucPow *= 2;
        }
    }

    // Finds the bitmask to use with the last page
    ucLastPageMask = 0x00;
    ucPow = 1;
    for(ucI=0; ucI<LCD_PAGE_ROWS; ucI++)
    {
        if(ucYTo-ucLastPage*LCD_PAGE_ROWS>=ucI)
        {
            ucLastPageMask += ucPow;
            ucPow *= 2;
        }
    }

    if(ucLastPage==ucFirstPage)
    {
        ucFirstPageMask &= ucLastPageMask;
        ucLastPageMask = ucFirstPageMask;
    }
    *(pcBuf + (ucFirstPage*LCD_COLS+ucX)) |= ucFirstPageMask;
    for(ucPage=ucFirstPage+1; ucPage<=ucLastPage-1; ucPage++)
    {
        *(pcBuf + (ucPage*LCD_COLS+ucX)) |= 0xFF;
    }
    *(pcBuf + (ucLastPage*LCD_COLS+ucX)) |= ucLastPageMask;
}


/**************************************************************************//**
* @brief    This function clears a vertical line from (\e ucX,\e ucYFrom) to 
*           (\e ucX,\e ucYTo) from buffer specified by argument \e pcBuffer.
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    ucX         is the x-position (column) of the line [0--127].
* @param    ucYFrom     is the start row [0--63].
* @param    ucYTo       is the end row [0--63].
*
* @return   None
******************************************************************************/
void lcdBufferClearVLine(char *pcBuffer, unsigned char ucX,
                         unsigned char ucYFrom, unsigned char ucYTo)
{
    unsigned char ucI, ucPow;
    unsigned char ucPage, ucFirstPage, ucLastPage;
    unsigned char ucFirstPageMask, ucLastPageMask;
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    ucFirstPage = ucYFrom/LCD_PAGE_ROWS;
    ucLastPage = ucYTo/LCD_PAGE_ROWS;

    // Finds the bitmask to use with the first page
    ucFirstPageMask = 0xFF;
    ucPow = 1;
    for(ucI=0; ucI<LCD_PAGE_ROWS; ucI++)
    {
        if(ucYFrom-ucFirstPage*LCD_PAGE_ROWS>ucI)
        {
            ucFirstPageMask -= ucPow;
            ucPow *= 2;
        }
    }

    // Finds the bitmask to use with the last page
    ucLastPageMask = 0x00;
    ucPow = 1;
    for(ucI=0; ucI<LCD_PAGE_ROWS; ucI++)
    {
        if(ucYTo-ucLastPage*LCD_PAGE_ROWS>=ucI)
        {
            ucLastPageMask += ucPow;
            ucPow *= 2;
        }
    }

    if(ucLastPage==ucFirstPage)
    {
        ucFirstPageMask &= ucLastPageMask;
        ucLastPageMask = ucFirstPageMask;
    }

    *(pcBuf + (ucFirstPage*LCD_COLS+ucX)) &= ~ucFirstPageMask;
    for(ucPage=ucFirstPage+1; ucPage<=ucLastPage-1; ucPage++)
    {
        *(pcBuf + (ucPage*LCD_COLS+ucX)) &= 0x00;
    }
    *(pcBuf + (ucLastPage*LCD_COLS+ucX)) &= ~ucLastPageMask;
}


/**************************************************************************//**
* @brief    This function draws a horizontal arrow from (\e ucXFrom,\e ucY) to 
*           (\e ucXTo,\e ucY) to buffer specified by \e pcBuffer. The function 
*           assumes \e ucY to be in the range [2--61] in order for arrowhead to 
*           fit on the LCD.
*
* @param    pcBuffer    is a pointer to target buffer.
* @param    ucXFrom     is the start column [0--127].
* @param    ucXTo       is the end column [0--127].
* @param    ucY         is the the y-position (row) of the arrow [2--61].
*
* @return   None
******************************************************************************/
void lcdBufferHArrow(char *pcBuffer, unsigned char ucXFrom,
                     unsigned char ucXTo, unsigned char ucY)
{
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif

    if(ucXTo > ucXFrom)
    {
        lcdBufferSetHLine(pcBuf, ucXFrom, ucXTo, ucY);
        lcdBufferSetVLine(pcBuf, ucXTo-1, ucY-1, ucY+1);
        lcdBufferSetVLine(pcBuf, ucXTo-2, ucY-2, ucY+2);
    }
    else if(ucXTo < ucXFrom)
    {
        lcdBufferSetHLine(pcBuf, ucXTo, ucXFrom, ucY);
        lcdBufferSetVLine(pcBuf, ucXTo+1, ucY-1, ucY+1);
        lcdBufferSetVLine(pcBuf, ucXTo+2, ucY-2, ucY+2);
    }
}


/**************************************************************************//**
* @brief    This function draws a vertical arrow from (\e ucX,\e ucYFrom) to 
*           (\e ucX,\e ucYTo) to the buffer specified by \e pcBuffer.
*           The function assumes that \e ucX is in the range [2--125] for the
*           arrowhead to fit on the LCD.
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    ucX         is the the x-position (column) of the arrow [2--125].
* @param    ucYFrom     is the start row [0--63].
* @param    ucYTo       is the end row [0--63].
*
* @return   None
******************************************************************************/
void lcdBufferVArrow(char *pcBuffer, unsigned char ucX, unsigned char ucYFrom,
                     unsigned char ucYTo)
{
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    // Draw the line
    lcdBufferSetVLine(pcBuf, ucX, ucYFrom, ucYTo);

    // Draw arrowhead
    lcdBufferSetHLine(pcBuf, ucX-1, ucX+1, ucYTo-1);
    lcdBufferSetHLine(pcBuf, ucX-2, ucX+2, ucYTo-2);
}


/**************************************************************************//**
* @brief    This function sets a pixel on (\e ucX,\e ucY).
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    ucX         is the pixel x-position (column) [0--127].
* @param    ucY         is the pixel y-position (row) [0--63].
*
* @return   None
******************************************************************************/
void lcdBufferSetPx(char *pcBuffer, unsigned char ucX, unsigned char ucY)
{
    char ucPage = ucY/LCD_PAGE_ROWS;
    char bit  = ucY%LCD_PAGE_ROWS;
    char bitmask = 1<<bit;
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    *(pcBuf + (ucPage*LCD_COLS+ucX)) |= bitmask;
}


/**************************************************************************//**
* @brief    This function clears the pixel at (\e ucX,\e ucY).
*
* @param    pcBuffer    is a pointer to the target buffer.
* @param    ucX         is the pixel x-position (column) [0--127].
* @param    ucY         is the pixel y-position (row) [0--63].
*
* @return   None
******************************************************************************/
void lcdBufferClearPx(char *pcBuffer, unsigned char ucX, unsigned char ucY)
{
    char ucPage = ucY/LCD_PAGE_ROWS;
    char bit  = ucY%LCD_PAGE_ROWS;
    char bitmask = 1<<bit;
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    *(pcBuf + (ucPage*LCD_COLS+ucX)) &= ~bitmask;
}



/**************************************************************************//**
* @brief    This function copies the content of \e pcFromBuffer to 
*           \e pcToBuffer. If either of the two arguments are 0, the default 
*           buffer is used for this argument.
*
* @param    pcToBuffer      is a pointer to the destination buffer.
* @param    pcFromBuffer    is a pointer to the target buffer.
*
* @return   None
******************************************************************************/
void lcdBufferCopy(const char *pcFromBuffer, char *pcToBuffer)
{
    char *pcTmpToBuf = pcToBuffer;
    char *pcTmpFromBuf = (char *)pcFromBuffer;
    register unsigned short i;

    // If buffers are the same, do nothing
    if(pcFromBuffer == pcToBuffer) {
        return;
    }

#ifndef LCD_NO_DEFAULT_BUFFER
    // Use default buffer if null pointer
    if(!pcTmpFromBuf) pcTmpFromBuf = lcdDefaultBuffer;
    else if(!pcTmpToBuf) pcTmpToBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    // Copy
    for(i=0; i<LCD_BYTES;i++) {
        pcTmpToBuf[i] = pcTmpFromBuf[i];
    }
}


/******************************************************************************
* LOCAL FUNCTIONS
*/
/**************************************************************************//**
* @brief    Local function. Draws or clears a line from \e (ucXFrom,ucYFrom) 
*           to \e (ucXTo,ucYTo). Uses Bresenham's line algorithm.
*
* @param    pcBuffer    Pointer to target buffer.
* @param    ucXFrom     Start column.
* @param    ucXTo       End column.
* @param    ucYFrom     Start row.
* @param    ucYTo       End row.
* @param    ucDraw      Draw or clear line (1= Draw line, 0= Clear line).
*
* @return   None
******************************************************************************/
static void lcdBufferLine(char *pcBuffer, unsigned char ucXFrom,
                          unsigned char ucYFrom, unsigned char ucXTo,
                          unsigned char ucYTo, unsigned char ucDraw)
{
    signed char scX, scY, scDeltaY, scDeltaX, scD;
    signed char scXDir, scYDir;
    char *pcBuf = pcBuffer;

#ifndef LCD_NO_DEFAULT_BUFFER
    if(!pcBuf) pcBuf = lcdDefaultBuffer;
#endif // LCD_NO_DEFAULT_BUFFER

    if(ucXFrom==ucXTo)
    {
        // Vertical Line
        if(ucDraw) lcdBufferSetVLine(pcBuf, ucXFrom, ucYFrom, ucYTo);
        else     lcdBufferClearVLine(pcBuf, ucXFrom, ucYFrom, ucYTo);
    }
    else if(ucYFrom==ucYTo)
    {
        // Horizontal Line
        if(ucDraw) lcdBufferSetHLine(pcBuf, ucXFrom, ucXTo, ucYFrom);
        else     lcdBufferClearHLine(pcBuf, ucXFrom, ucXTo, ucYFrom);
    }
    else
    {
        // Diagonal Line => Bresenham's algorithm
        if (ucXFrom > ucXTo) scXDir = -1;
        else                 scXDir = 1;
        if (ucYFrom > ucYTo) scYDir = -1;
        else                 scYDir = 1;

        scX = ucXFrom;
        scY = ucYFrom;

        scDeltaY = ucYTo - ucYFrom;
        scDeltaX = ucXTo - ucXFrom;
        if(scDeltaY<0)  scDeltaY *= -1;   // absolute value
        if(scDeltaX<0)  scDeltaX *= -1;   // absolute value

        if (scDeltaX >= scDeltaY)
        {
            scD = (scDeltaY << 1) - scDeltaX;
            while (scX != ucXTo)
            {
                if(ucDraw) lcdBufferSetPx(pcBuf, scX, scY);
                else       lcdBufferClearPx(pcBuf, scX, scY);
                if ( scD < 0 )
                    scD += (scDeltaY << 1);
                else
                {
                    scD += ((scDeltaY - scDeltaX) << 1);
                    scY += scYDir;
                }
                scX += scXDir;
            }
        }
        else
        {
            scD = (scDeltaX << 1) - scDeltaY;
            while (scY != ucYTo)
            {
                if(ucDraw) lcdBufferSetPx(pcBuf, scX, scY);
                else       lcdBufferClearPx(pcBuf, scX, scY);
                if ( scD < 0 )
                    scD += (scDeltaX << 1);
                else
                {
                    scD += ((scDeltaX - scDeltaY) << 1);
                    scX += scXDir;
                }
                scY += scYDir;
            }
        }
    }
}


/**************************************************************************//**
* Close the Doxygen group.
* @}
******************************************************************************/
#endif // ifndef LCD_EXCLUDE
