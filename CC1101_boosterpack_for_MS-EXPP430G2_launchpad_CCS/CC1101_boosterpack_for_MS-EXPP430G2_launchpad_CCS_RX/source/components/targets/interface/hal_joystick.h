/*******************************************************************************
*  Filename:        hal_joystick.h
*  Revised:         $Date: 2013-04-22 10:29:55 +0200 (ma, 22 apr 2013) $
*  Revision:        $Revision: 9898 $
*
*  Description:     HAL joystick control header file.
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

#ifndef HAL_JOYSTICK_H
#define HAL_JOYSTICK_H
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
    HAL_JOYSTICK_EVT_UP,
    HAL_JOYSTICK_EVT_DOWN,
    HAL_JOYSTICK_EVT_LEFT,
    HAL_JOYSTICK_EVT_RIGHT,
    HAL_JOYSTICK_EVT_CENTER,
    HAL_JOYSTICK_EVT_PUSHED,
    HAL_JOYSTICK_EVT_MAX,
    HAL_JOYSTICK_EVT_INVALID
};


/*******************************************************************************
 * GLOBAL FUNCTIONS and MACROS
 */
void  halJoystickInit(void);
uint8 halJoystickIntConnect(uint8 event, ISR_FUNC_PTR func);
uint8 halJoystickIntEnable(uint8 event);
void  halJoystickIntDisable(void);
uint8 halJoystickPushed(void);
uint8 halJoystickGetDir(void);


/*******************************************************************************
* Mark the end of the C bindings section for C++ compilers.
*******************************************************************************/
#ifdef  __cplusplus
}
#endif
#endif // #ifndef HAL_JOYSTICK_H
