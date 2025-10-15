/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
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

/* Includes ------------------------------------------------------------------*/
#include "app_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "vbat_monitor.h"
#include "SEGGER_RTT.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TX_THREAD tx_app_thread;
TX_SEMAPHORE tx_app_semaphore;
TX_MUTEX tx_app_mutex;
TX_QUEUE tx_app_msg_queue;

/* USER CODE BEGIN PV */
/* Periodic task related variables */
TX_THREAD watchdog_thread;
TX_THREAD hourly_log_thread;
TX_THREAD daily_log_thread;
TX_THREAD vbat_check_thread;

TX_TIMER watchdog_timer;
TX_TIMER hourly_log_timer;
TX_TIMER daily_log_timer;
TX_TIMER vbat_check_timer;

TX_SEMAPHORE watchdog_semaphore;
TX_SEMAPHORE hourly_log_semaphore;
TX_SEMAPHORE daily_log_semaphore;
TX_SEMAPHORE vbat_check_semaphore;

/* Task stack space */
UCHAR watchdog_stack[WATCHDOG_TASK_STACK_SIZE];
UCHAR hourly_log_stack[LOG_TASK_STACK_SIZE];
UCHAR daily_log_stack[LOG_TASK_STACK_SIZE];
UCHAR vbat_check_stack[VBAT_TASK_STACK_SIZE];

/* Global variables */
extern IWDG_HandleTypeDef hiwdg;
extern RTC_HandleTypeDef hrtc;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

  /* USER CODE BEGIN App_ThreadX_MEM_POOL */

  /* USER CODE END App_ThreadX_MEM_POOL */
  CHAR *pointer;

  /* Allocate the stack for tx app thread  */
  if (tx_byte_allocate(byte_pool, (VOID**) &pointer,
                       TX_APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }
  /* Create tx app thread.  */
  if (tx_thread_create(&tx_app_thread, "tx app thread", tx_app_thread_entry, 0, pointer,
                       TX_APP_STACK_SIZE, TX_APP_THREAD_PRIO, TX_APP_THREAD_PREEMPTION_THRESHOLD,
                       TX_APP_THREAD_TIME_SLICE, TX_APP_THREAD_AUTO_START) != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }
  /* Allocate the stack for tx app queue.  */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                       TX_APP_MSG_QUEUE_FULL_SIZE * sizeof(ULONG), TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }
  /* Create tx app queue.  */
  if (tx_queue_create(&tx_app_msg_queue, "tx app queue", TX_APP_SINGLE_MSG_SIZE,
                      pointer, TX_APP_MSG_QUEUE_FULL_SIZE * sizeof(ULONG)) != TX_SUCCESS)
  {
    return TX_QUEUE_ERROR;
  }

  /* Create tx app semaphore.  */
  if (tx_semaphore_create(&tx_app_semaphore, "tx app semaphore", 0) != TX_SUCCESS)
  {
    return TX_SEMAPHORE_ERROR;
  }

  /* Create tx app mutex.  */
  if (tx_mutex_create(&tx_app_mutex, "tx app mutex", TX_NO_INHERIT) != TX_SUCCESS)
  {
    return TX_MUTEX_ERROR;
  }
  /* USER CODE BEGIN App_ThreadX_Init */
  /* Initialize RTT */
  SEGGER_RTT_Init();
  SEGGER_RTT_printf(0, "ThreadX application initialized\r\n");
  
  /* Initialize periodic tasks */
  ret = init_periodic_tasks(memory_ptr);
  if (ret != TX_SUCCESS)
  {
    SEGGER_RTT_printf(0, "Failed to initialize periodic tasks: %d\r\n", ret);
    return ret;
  }
  
  SEGGER_RTT_printf(0, "All periodic tasks initialized successfully\r\n");
  /* USER CODE END App_ThreadX_Init */

  return ret;
}
/**
  * @brief  Function implementing the tx_app_thread_entry thread.
  * @param  thread_input: Hardcoded to 0.
  * @retval None
  */
void tx_app_thread_entry(ULONG thread_input)
{
  /* USER CODE BEGIN tx_app_thread_entry */

  /* USER CODE END tx_app_thread_entry */
}

  /**
  * @brief  Function that implements the kernel's initialization.
  * @param  None
  * @retval None
  */
void MX_ThreadX_Init(void)
{
  /* USER CODE BEGIN Before_Kernel_Start */

  /* USER CODE END Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN Kernel_Start_Error */

  /* USER CODE END Kernel_Start_Error */
}

/**
  * @brief  App_ThreadX_LowPower_Timer_Setup
  * @param  count : TX timer count
  * @retval None
  */
void App_ThreadX_LowPower_Timer_Setup(ULONG count)
{
  /* USER CODE BEGIN  App_ThreadX_LowPower_Timer_Setup */

  /* USER CODE END  App_ThreadX_LowPower_Timer_Setup */
}

/**
  * @brief  App_ThreadX_LowPower_Enter
  * @param  None
  * @retval None
  */
void App_ThreadX_LowPower_Enter(void)
{
  /* USER CODE BEGIN  App_ThreadX_LowPower_Enter */

  /* USER CODE END  App_ThreadX_LowPower_Enter */
}

/**
  * @brief  App_ThreadX_LowPower_Exit
  * @param  None
  * @retval None
  */
void App_ThreadX_LowPower_Exit(void)
{
  /* USER CODE BEGIN  App_ThreadX_LowPower_Exit */

  /* USER CODE END  App_ThreadX_LowPower_Exit */
}

/**
  * @brief  App_ThreadX_LowPower_Timer_Adjust
  * @param  None
  * @retval Amount of time (in ticks)
  */
ULONG App_ThreadX_LowPower_Timer_Adjust(void)
{
  /* USER CODE BEGIN  App_ThreadX_LowPower_Timer_Adjust */
  return 0;
  /* USER CODE END  App_ThreadX_LowPower_Timer_Adjust */
}

/* USER CODE BEGIN 1 */

/**
 * @brief Initialize all periodic tasks
 * @param memory_ptr: Memory pool pointer
 * @retval UINT: Initialization result
 */
UINT init_periodic_tasks(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
//  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;
//  CHAR *pointer;

  /* Create watchdog task semaphore */
  if (tx_semaphore_create(&watchdog_semaphore, "watchdog semaphore", 0) != TX_SUCCESS)
  {
    SEGGER_RTT_printf(0, "Failed to create watchdog semaphore\r\n");
    return TX_SEMAPHORE_ERROR;
  }

  /* Create hourly log task semaphore */
  if (tx_semaphore_create(&hourly_log_semaphore, "hourly log semaphore", 0) != TX_SUCCESS)
  {
    SEGGER_RTT_printf(0, "Failed to create hourly log semaphore\r\n");
    return TX_SEMAPHORE_ERROR;
  }

  /* Create daily log task semaphore */
  if (tx_semaphore_create(&daily_log_semaphore, "daily log semaphore", 0) != TX_SUCCESS)
  {
    SEGGER_RTT_printf(0, "Failed to create daily log semaphore\r\n");
    return TX_SEMAPHORE_ERROR;
  }

  /* Create vbat check task semaphore */
  if (tx_semaphore_create(&vbat_check_semaphore, "vbat check semaphore", 0) != TX_SUCCESS)
  {
    SEGGER_RTT_printf(0, "Failed to create vbat check semaphore\r\n");
    return TX_SEMAPHORE_ERROR;
  }

  /* Create watchdog task */
  if (tx_thread_create(&watchdog_thread, "watchdog task", watchdog_task_entry, 0,
                       watchdog_stack, WATCHDOG_TASK_STACK_SIZE,
                       WATCHDOG_TASK_PRIORITY, WATCHDOG_TASK_PRIORITY,
                       TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
  {
    SEGGER_RTT_printf(0, "Failed to create watchdog task\r\n");
    return TX_THREAD_ERROR;
  }

  /* Create hourly log task */
  if (tx_thread_create(&hourly_log_thread, "hourly log task", hourly_log_task_entry, 0,
                       hourly_log_stack, LOG_TASK_STACK_SIZE,
                       LOG_TASK_PRIORITY, LOG_TASK_PRIORITY,
                       TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
  {
    SEGGER_RTT_printf(0, "Failed to create hourly log task\r\n");
    return TX_THREAD_ERROR;
  }

  /* Create daily log task */
  if (tx_thread_create(&daily_log_thread, "daily log task", daily_log_task_entry, 0,
                       daily_log_stack, LOG_TASK_STACK_SIZE,
                       LOG_TASK_PRIORITY, LOG_TASK_PRIORITY,
                       TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
  {
    SEGGER_RTT_printf(0, "Failed to create daily log task\r\n");
    return TX_THREAD_ERROR;
  }

  /* Create vbat check task */
  if (tx_thread_create(&vbat_check_thread, "vbat check task", vbat_check_task_entry, 0,
                       vbat_check_stack, VBAT_TASK_STACK_SIZE,
                       VBAT_TASK_PRIORITY, VBAT_TASK_PRIORITY,
                       TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
  {
    SEGGER_RTT_printf(0, "Failed to create vbat check task\r\n");
    return TX_THREAD_ERROR;
  }

  /* Create watchdog timer */
  if (tx_timer_create(&watchdog_timer, "watchdog timer", watchdog_timer_callback, 0,
                      WATCHDOG_TIMER_PERIOD_TICKS, WATCHDOG_TIMER_PERIOD_TICKS,
                      TX_AUTO_ACTIVATE) != TX_SUCCESS)
  {
    SEGGER_RTT_printf(0, "Failed to create watchdog timer\r\n");
    return TX_TIMER_ERROR;
  }

  /* Create hourly log timer */
  if (tx_timer_create(&hourly_log_timer, "hourly log timer", hourly_log_timer_callback, 0,
                      HOURLY_LOG_TIMER_PERIOD_TICKS, HOURLY_LOG_TIMER_PERIOD_TICKS,
                      TX_AUTO_ACTIVATE) != TX_SUCCESS)
  {
    SEGGER_RTT_printf(0, "Failed to create hourly log timer\r\n");
    return TX_TIMER_ERROR;
  }

  /* Create daily log timer */
  if (tx_timer_create(&daily_log_timer, "daily log timer", daily_log_timer_callback, 0,
                      DAILY_LOG_TIMER_PERIOD_TICKS, DAILY_LOG_TIMER_PERIOD_TICKS,
                      TX_AUTO_ACTIVATE) != TX_SUCCESS)
  {
    SEGGER_RTT_printf(0, "Failed to create daily log timer\r\n");
    return TX_TIMER_ERROR;
  }

  /* Create vbat check timer */
  if (tx_timer_create(&vbat_check_timer, "vbat check timer", vbat_check_timer_callback, 0,
                      VBAT_CHECK_TIMER_PERIOD_TICKS, VBAT_CHECK_TIMER_PERIOD_TICKS,
                      TX_AUTO_ACTIVATE) != TX_SUCCESS)
  {
    SEGGER_RTT_printf(0, "Failed to create vbat check timer\r\n");
    return TX_TIMER_ERROR;
  }

  SEGGER_RTT_printf(0, "All tasks and timers created successfully\r\n");
  return ret;
}

/**
 * @brief Watchdog task entry function
 * @param thread_input: Thread input parameter
 * @retval None
 */
void watchdog_task_entry(ULONG thread_input)
{
  static uint32_t refresh_count = 0;
  
  SEGGER_RTT_printf(0, "Watchdog task started\r\n");
  
  while (1)
  {
    /* Wait for semaphore */
    tx_semaphore_get(&watchdog_semaphore, TX_WAIT_FOREVER);
    
    /* Refresh watchdog */
    HAL_IWDG_Refresh(&hiwdg);
    refresh_count++;
    
    /* Log watchdog refresh every 10 times (50 seconds) */
    if (refresh_count % 10 == 0)
    {
      SEGGER_RTT_printf(0, "Watchdog refreshed %lu times\r\n", refresh_count);
    }
  }
}

/**
 * @brief Hourly log task entry function
 * @param thread_input: Thread input parameter
 * @retval None
 */
void hourly_log_task_entry(ULONG thread_input)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  static uint32_t log_count = 0;
  
  SEGGER_RTT_printf(0, "Hourly log task started\r\n");
  
  while (1)
  {
    /* Wait for semaphore */
    tx_semaphore_get(&hourly_log_semaphore, TX_WAIT_FOREVER);
    
    /* Get current time */
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
    
    log_count++;
    
    /* Log hourly system status */
    SEGGER_RTT_printf(0, "Hourly Log #%lu - Date: %02d/%02d/%04d Time: %02d:%02d:%02d Tick: %lu\r\n",
                      log_count,
                      sDate.Date, sDate.Month, sDate.Year,
                      sTime.Hours, sTime.Minutes, sTime.Seconds,
                      tx_time_get());
    
    /* Other hourly level log processing can be added here */
  }
}

/**
 * @brief Daily log task entry function
 * @param thread_input: Thread input parameter
 * @retval None
 */
void daily_log_task_entry(ULONG thread_input)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  static uint32_t daily_log_count = 0;
  
  SEGGER_RTT_printf(0, "Daily log task started\r\n");
  
  while (1)
  {
    /* Wait for semaphore */
    tx_semaphore_get(&daily_log_semaphore, TX_WAIT_FOREVER);
    
    /* Get current time */
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
    
    daily_log_count++;
    
    /* Log daily system status */
    SEGGER_RTT_printf(0, "Daily Log #%lu - Date: %02d/%02d/%04d Time: %02d:%02d:%02d Tick: %lu\r\n",
                      daily_log_count,
                      sDate.Date, sDate.Month, sDate.Year,
                      sTime.Hours, sTime.Minutes, sTime.Seconds,
                      tx_time_get());
    
    /* Log task status */
    SEGGER_RTT_printf(0, "All tasks running normally\r\n");
    
    /* Other daily level log processing can be added here, such as system status statistics */
  }
}

/**
 * @brief VBAT check task entry function
 * @param thread_input: Thread input parameter
 * @retval None
 */
void vbat_check_task_entry(ULONG thread_input)
{
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  uint32_t vbat_voltage;
  VBAT_Status vbat_status;
  static uint32_t check_count = 0;
  
  SEGGER_RTT_printf(0, "VBAT check task started\r\n");
  
  while (1)
  {
    /* Wait for semaphore */
    tx_semaphore_get(&vbat_check_semaphore, TX_WAIT_FOREVER);
    
    /* Get current time */
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
    
    /* Execute VBAT monitoring task */
    vbat_monitor_task_handler();
    
    /* Get VBAT voltage and status */
    vbat_voltage = get_last_vbat_voltage();
    vbat_status = check_vbat_status(vbat_voltage);
    
    check_count++;
    
    /* Log VBAT check result */
    SEGGER_RTT_printf(0, "VBAT Check #%lu - Date: %02d/%02d/%04d Time: %02d:%02d:%02d VBAT: %lu mV (%s)\r\n",
                      check_count,
                      sDate.Date, sDate.Month, sDate.Year,
                      sTime.Hours, sTime.Minutes, sTime.Seconds,
                      vbat_voltage, get_vbat_status_string(vbat_status));
    
    /* Execute corresponding processing based on VBAT status */
    switch (vbat_status)
    {
      case VBAT_STATUS_CRITICAL:
        /* Critical voltage processing - may need to enter low power mode */
        SEGGER_RTT_printf(0, "ERROR: VBAT CRITICAL: %lu mV - Emergency action required!\r\n", vbat_voltage);
        /* Emergency handling logic can be added here */
        break;
        
      case VBAT_STATUS_LOW:
        /* Low voltage processing - may need to reduce system load */
        SEGGER_RTT_printf(0, "WARNING: VBAT LOW: %lu mV - Power saving mode recommended\r\n", vbat_voltage);
        /* Power saving processing logic can be added here */
        break;
        
      case VBAT_STATUS_HIGH:
        /* High voltage processing - may need to check charging circuit */
        SEGGER_RTT_printf(0, "WARNING: VBAT HIGH: %lu mV - Check charging circuit\r\n", vbat_voltage);
        /* Charging control logic can be added here */
        break;
        
      case VBAT_STATUS_NORMAL:
      default:
        /* Normal voltage - no special processing needed */
        break;
    }
  }
}

/**
 * @brief Watchdog timer callback function
 * @param timer_input: Timer input parameter
 * @retval None
 */
void watchdog_timer_callback(ULONG timer_input)
{
  /* Release semaphore to wake up watchdog task */
  tx_semaphore_put(&watchdog_semaphore);
}

/**
 * @brief Hourly log timer callback function
 * @param timer_input: Timer input parameter
 * @retval None
 */
void hourly_log_timer_callback(ULONG timer_input)
{
  /* Release semaphore to wake up hourly log task */
  tx_semaphore_put(&hourly_log_semaphore);
}

/**
 * @brief Daily log timer callback function
 * @param timer_input: Timer input parameter
 * @retval None
 */
void daily_log_timer_callback(ULONG timer_input)
{
  /* Release semaphore to wake up daily log task */
  tx_semaphore_put(&daily_log_semaphore);
}

/**
 * @brief VBAT check timer callback function
 * @param timer_input: Timer input parameter
 * @retval None
 */
void vbat_check_timer_callback(ULONG timer_input)
{
  /* Release semaphore to wake up vbat check task */
  tx_semaphore_put(&vbat_check_semaphore);
}

/* USER CODE END 1 */
