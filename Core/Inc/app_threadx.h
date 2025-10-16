/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.h
  * @author  MCD Application Team
  * @brief   ThreadX applicative header file
  ******************************************************************************
    * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_THREADX_H
#define __APP_THREADX_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "tx_api.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "iwdg.h"
#include "rtc.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Private defines -----------------------------------------------------------*/
#define TX_APP_STACK_SIZE                       4096
#define TX_APP_THREAD_PRIO                      10
#define TX_APP_SINGLE_MSG_SIZE                  1
#define TX_APP_MSG_QUEUE_NB_MSG                 1
#define TX_APP_MSG_QUEUE_FULL_SIZE              TX_APP_SINGLE_MSG_SIZE * TX_APP_MSG_QUEUE_NB_MSG

/* USER CODE BEGIN PD */
/* Task timer definitions */
#define WATCHDOG_TIMER_PERIOD_TICKS     (5 * TX_TIMER_TICKS_PER_SECOND)    /* 5 seconds */
#define HOURLY_LOG_TIMER_PERIOD_TICKS   (60 * TX_TIMER_TICKS_PER_SECOND)   /* 60 seconds */
#define DAILY_LOG_TIMER_PERIOD_TICKS    (6 * 60 * TX_TIMER_TICKS_PER_SECOND) /* 6 hours */
#define VBAT_CHECK_TIMER_PERIOD_TICKS   (50 * 60 * TX_TIMER_TICKS_PER_SECOND) /* 50 minutes */

/* Task priority definitions */
#define WATCHDOG_TASK_PRIORITY          5
#define LOG_TASK_PRIORITY               10
#define VBAT_TASK_PRIORITY              8

/* Task stack size definitions */
#define WATCHDOG_TASK_STACK_SIZE       256
#define LOG_TASK_STACK_SIZE            512
#define VBAT_TASK_STACK_SIZE           256
/* USER CODE END PD */

/* Main thread defines -------------------------------------------------------*/
#ifndef TX_APP_THREAD_PREEMPTION_THRESHOLD
#define TX_APP_THREAD_PREEMPTION_THRESHOLD      TX_APP_THREAD_PRIO
#endif

#ifndef TX_APP_THREAD_TIME_SLICE
#define TX_APP_THREAD_TIME_SLICE                TX_NO_TIME_SLICE
#endif

#ifndef TX_APP_THREAD_AUTO_START
#define TX_APP_THREAD_AUTO_START                TX_AUTO_START
#endif
/* USER CODE BEGIN MTD */

/* USER CODE END MTD */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
UINT App_ThreadX_Init(VOID *memory_ptr);
void MX_ThreadX_Init(void);
void tx_app_thread_entry(ULONG thread_input);

/* USER CODE BEGIN EFP */
/* Task function declarations */
void watchdog_task_entry(ULONG thread_input);
void hourly_log_task_entry(ULONG thread_input);
void daily_log_task_entry(ULONG thread_input);
void vbat_check_task_entry(ULONG thread_input);

/* Timer callback function declarations */
void watchdog_timer_callback(ULONG timer_input);
void hourly_log_timer_callback(ULONG timer_input);
void daily_log_timer_callback(ULONG timer_input);
void vbat_check_timer_callback(ULONG timer_input);

/* Task initialization function declaration */
UINT init_periodic_tasks(VOID *memory_ptr);
/* USER CODE END EFP */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif /* __APP_THREADX_H */
