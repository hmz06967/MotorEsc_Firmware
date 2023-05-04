/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pwm.h"
#include "input.h"
#include "adc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern pwm_signal_t signal;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */

  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel 1 interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */
    if (LL_DMA_IsActiveFlag_TC1(DMA1)) {
        LL_DMA_ClearFlag_TC1(DMA1);

        updateAdcValues();
    }
  /* USER CODE END DMA1_Channel1_IRQn 0 */

  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel 2 and 3 interrupts.
  */
void DMA1_Channel2_3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel2_3_IRQn 0 */
    if (LL_DMA_IsActiveFlag_TC2(DMA1)) {
      LL_DMA_ClearFlag_GI2(DMA1);
    }
    if (LL_DMA_IsActiveFlag_TC3(DMA1)) {
      LL_DMA_ClearFlag_GI3(DMA1);
    }
  /* USER CODE END DMA1_Channel2_3_IRQn 0 */

  /* USER CODE BEGIN DMA1_Channel2_3_IRQn 1 */

  /* USER CODE END DMA1_Channel2_3_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel 4 and 5 interrupts.
  */
void DMA1_Channel4_5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel4_5_IRQn 0 */
    if (LL_DMA_IsActiveFlag_TC5(DMA1)) {
      LL_DMA_ClearFlag_GI5(DMA1);
    }
  /* USER CODE END DMA1_Channel4_5_IRQn 0 */

  /* USER CODE BEGIN DMA1_Channel4_5_IRQn 1 */
    if(LL_DMA_IsActiveFlag_HT4(DMA1)){
        LL_TIM_IC_SetPolarity(IC_TIMER_REGISTER, IC_TIMER_CHANNEL, LL_TIM_IC_POLARITY_FALLING);
        LL_DMA_ClearFlag_HT4(DMA1);
    }

    if (LL_DMA_IsActiveFlag_TC4(DMA1)) {
      signal.dmac = 1;
      LL_TIM_IC_SetPolarity(IC_TIMER_REGISTER, IC_TIMER_CHANNEL, LL_TIM_IC_POLARITY_RISING);
      LL_DMA_ClearFlag_GI4(DMA1);
      //LL_DMA_DisableChannel(DMA1, INPUT_DMA_CHANNEL);
      //IC_TIMER_REGISTER->CNT = 0;
    }
    else if (0 != LL_DMA_IsActiveFlag_TE4(DMA1))
    {
      LL_DMA_ClearFlag_TE4(DMA1);
    }
  /* USER CODE END DMA1_Channel4_5_IRQn 1 */
}

/**
  * @brief This function handles TIM1 break, update, trigger and commutation interrupts.
  */
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 0 */

    if(LL_TIM_IsActiveFlag_UPDATE(IC_TIMER_REGISTER) == 1){
        LL_TIM_ClearFlag_UPDATE(IC_TIMER_REGISTER);
    }

    timer_sinus_callback();
  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 0 */
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 1 */

  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
#if 0
    if(LL_TIM_IsActiveFlag_CC1(IC_TIMER_REGISTER) == 1){

      LL_TIM_ClearFlag_CC1(IC_TIMER_REGISTER);
    }

    if(LL_TIM_IsActiveFlag_UPDATE(IC_TIMER_REGISTER) == 1){
        LL_TIM_ClearFlag_UPDATE(IC_TIMER_REGISTER);

    }
#else
    if(LL_TIM_IsActiveFlag_CC1(IC_TIMER_REGISTER) == 1){
        if(LL_TIM_IC_GetPolarity(IC_TIMER_REGISTER, IC_TIMER_CHANNEL) == LL_TIM_IC_POLARITY_RISING) // yükselen kenar ile mi tetiklenmiş ?
        {
            signal.rise = IC_TIMER_REGISTER->CCR1;
            LL_TIM_IC_SetPolarity(IC_TIMER_REGISTER, IC_TIMER_CHANNEL, LL_TIM_IC_POLARITY_FALLING);
        }
        else{
            signal.dmac = 1;
            signal.fall = IC_TIMER_REGISTER->CCR1;
            signal.capture  = signal.fall - signal.rise;
            if(signal.capture < 0)signal.capture += 0xFFFF;// eger sonuc negatifse taban tumleme yap
            LL_TIM_IC_SetPolarity(IC_TIMER_REGISTER, IC_TIMER_CHANNEL, LL_TIM_IC_POLARITY_RISING);
            LL_TIM_SetCounter(IC_TIMER_REGISTER, 0);

        }
        //LL_TIM_ClearFlag_UPDATE(IC_TIMER_REGISTER);
    }
#endif
  /* USER CODE END TIM3_IRQn 0 */
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles TIM14 global interrupt.
  */
void TIM14_IRQHandler(void)
{
  /* USER CODE BEGIN TIM14_IRQn 0 */
    //300hz timer
    if(LL_TIM_IsActiveFlag_CC1(TIM14) == 1){
      LL_TIM_ClearFlag_CC1(TIM14);
    }

    if(LL_TIM_IsActiveFlag_UPDATE(TIM14) == 1){
        LL_TIM_ClearFlag_UPDATE(TIM14);
    }

    comutate_timer_callback();
  /* USER CODE END TIM14_IRQn 0 */
  /* USER CODE BEGIN TIM14_IRQn 1 */

  /* USER CODE END TIM14_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
