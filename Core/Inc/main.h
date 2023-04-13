/**
  ******************************************************************************
  * @file    TIM/TIM_PWMOutput/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"

#include "stm32h5xx_nucleo.h"
#include "stm32h5xx_ll_bus.h"
#include "stm32h5xx_ll_rcc.h"
#include "stm32h5xx_ll_system.h"
#include "stm32h5xx_ll_utils.h"
#include "stm32h5xx_ll_gpio.h"
#include "stm32h5xx_ll_exti.h"
#include "stm32h5xx_ll_usart.h"

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/* IRQ Handler treatment functions */
void UART_CharReception_Callback(void); 
void UART_Error_Callback(void); 

//#define PRESCALER_VALUE     (uint32_t)(((SystemCoreClock) / 100) - 1)

/* Compute the prescaler value to have TIM1 counter clock equal to 100 Hz */
#define PRESCALER_VALUE     (uint32_t)(( (SystemCoreClock/8) / 100000) - 1)
// #define PRESCALER_VALUE     (uint32_t)(( (SystemCoreClock/8) / 100) - 1)

/* -----------------------------------------------------------------------
TIM1 Configuration: generate 4 PWM signals with 4 different duty cycles.

    In this example TIM1 input clock (TIM1CLK) is set to APB2 clock (PCLK2),
    since APB1 prescaler is equal to 1.
      TIM1CLK = PCLK2
      PCLK2 = HCLK
      => TIM1CLK = HCLK = SystemCoreClock

    To get TIM1 counter clock at 1 MHz, the prescaler is computed as follows:
       Prescaler = (TIM1CLK / TIM1 counter clock) - 1
       Prescaler = ((SystemCoreClock) /1 MHz) - 1

    To get TIM1 output clock at 24 KHz, the period (ARR)) is computed as follows:
       ARR = (TIM1 counter clock / TIM1 output clock) - 1
           = 40

    TIM1 Channel1 duty cycle = (TIM1_CCR1/ TIM1_ARR + 1)* 100 = 50%
    TIM1 Channel2 duty cycle = (TIM1_CCR2/ TIM1_ARR + 1)* 100 = 37.5%
    TIM1 Channel3 duty cycle = (TIM1_CCR3/ TIM1_ARR + 1)* 100 = 25%
    TIM1 Channel4 duty cycle = (TIM1_CCR4/ TIM1_ARR + 1)* 100 = 12.5%

    Note:
     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32h5xx.c file.
     Each time the core clock (HCLK) changes, user had to update SystemCoreClock
     variable value. Otherwise, any configuration based on this variable will be incorrect.
     This variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetSysClockFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
  ----------------------------------------------------------------------- */

/* Initialize TIMx peripheral as follows:
   + Prescaler = (SystemCoreClock / 1000000) - 1
   + Period = (40 - 1)
   + ClockDivision = 0
   + Counter direction = Up
*/
// #define  PERIOD_VALUE       (uint32_t)(200 - 1)              /* Period Value  */
// #define  PULSE1_VALUE       (uint32_t)(200 / 2)              /* Capture Compare 1 Value  */
#define  PERIOD_VALUE       (uint32_t)(250 - 1)              /* Period Value  */
// #define  PULSE1_VALUE       (uint32_t)(250 / 2)              /* Capture Compare 1 Value  */
#define  PULSE1_VALUE       (uint32_t)(250 * 82 / 100)              /* Capture Compare 1 Value  */
#define  PULSE2_VALUE       (uint32_t)(40 * 37.5 / 100)     /* Capture Compare 2 Value  */
#define  PULSE3_VALUE       (uint32_t)(40 / 4)              /* Capture Compare 3 Value  */
#define  PULSE4_VALUE       (uint32_t)(40 * 12.5 /100)      /* Capture Compare 4 Value  */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
