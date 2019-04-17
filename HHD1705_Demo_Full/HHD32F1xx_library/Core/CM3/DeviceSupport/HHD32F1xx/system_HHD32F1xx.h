/**************************************************************************//**
 * $Id: system_HHD32f1xx.h,v 1.2 2015/10/26 08:52:47 Exp $
 *
 * @file     system_HHD32f1xx.h
 * @brief    CMSIS Cortex-M3 Device Peripheral Access Layer Header File
 *           for the XT103ZG Device Series
 * @version  1.0
 * @date     26. Sep. 2015
 * @author   MCU Team
 *
 * @note
 * Copyright (C) 2015 Semiconductors. All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 *  Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product.  Semiconductors
 * reserves the right to make changes in the software without
 * notification.  Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 ******************************************************************************/

#ifndef __SYSTEM_XT103_H
#define __SYSTEM_XT103_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */
extern uint32_t MainClock;           /*!< Main Clock Frequency (Main Clock)    */

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_XT103_H */
