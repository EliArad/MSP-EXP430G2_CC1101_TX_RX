/*******************************************************************************
*  Filename:        hal_mcu.h
*  Revised:         $Date: 2013-04-22 10:29:55 +0200 (ma, 22 apr 2013) $
*  Revision:        $Revision: 9898 $
*
*  Description:     HAL MCU library header file
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


#ifndef HAL_MCU_H
#define HAL_MCU_H
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
#include <hal_types.h>


/*******************************************************************************
 * CONSTANTS AND DEFINES
 */
enum {                  // Input values to halMcuSetLowPowerMode()
    HAL_MCU_LPM_0,
    HAL_MCU_LPM_1,
    HAL_MCU_LPM_2,
    HAL_MCU_LPM_3,
    HAL_MCU_LPM_4
};

enum {                  // Return values of halMcuGetResetCause()
    HAL_MCU_RESET_CAUSE_POR,
    HAL_MCU_RESET_CAUSE_EXTERNAL,
    HAL_MCU_RESET_CAUSE_WATCHDOG
};

enum {
    HAL_MCU_SYSCLK_1MHZ  = 0,
    HAL_MCU_SYSCLK_4MHZ  = 1,
    HAL_MCU_SYSCLK_8MHZ  = 2,
    HAL_MCU_SYSCLK_12MHZ = 3,
    HAL_MCU_SYSCLK_16MHZ = 4,
    HAL_MCU_SYSCLK_20MHZ = 5,
    HAL_MCU_SYSCLK_25MHZ = 6
};


/*******************************************************************************
 * GLOBAL FUNCTIONS
 */
void halMcuInit(void);

// SW timer
void halMcuWaitUs(uint16 usec);
void halMcuWaitMs(uint16 msec);

void halMcuSetLowPowerMode(uint8 mode);
uint8 halMcuGetResetCause(void);

// Watchdog
void halMcuWdInit(uint8 interval);
void halMcuWdClear(void);
void halMcuReset(void);

void halMcuStartXT1(void);
void halMcuSetSystemClock(unsigned char systemClockSpeed);
/* NOTE: function holds the syctem clock speed set by a call to halMcuSetSystemClock */
uint8 halMcuGetSystemClock(void);
void halMcuDisablePeripheralClockRequest(uint16 bitMask);

void halMcuSetRfIrqPriority(uint8 level);


/*******************************************************************************
* Mark the end of the C bindings section for C++ compilers.
*******************************************************************************/
#ifdef  __cplusplus
}
#endif
#endif // #ifndef HAL_MCU_H