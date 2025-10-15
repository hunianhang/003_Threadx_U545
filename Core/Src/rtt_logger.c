/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    rtt_logger.c
  * @brief   RTT Logger module for debug output
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
#include "rtt_logger.h"
#include "SEGGER_RTT.h"
#include "tx_api.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* RTT Channel definitions */
#define RTT_CHANNEL_MAIN        0
#define RTT_CHANNEL_WATCHDOG    1
#define RTT_CHANNEL_LOG         2
#define RTT_CHANNEL_VBAT        3

/* Log level definitions */
#define LOG_LEVEL_ERROR         0
#define LOG_LEVEL_WARNING       1
#define LOG_LEVEL_INFO          2
#define LOG_LEVEL_DEBUG         3

/* Log buffer size */
#define LOG_BUFFER_SIZE         256
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
static uint8_t current_log_level = LOG_LEVEL_INFO;
static char log_buffer[LOG_BUFFER_SIZE];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/**
 * @brief Get log level string
 * @param level: Log level
 * @retval const char*: Log level string
 */
static const char* get_log_level_string(uint8_t level)
{
  switch (level)
  {
    case LOG_LEVEL_ERROR:
      return "ERROR";
    case LOG_LEVEL_WARNING:
      return "WARN ";
    case LOG_LEVEL_INFO:
      return "INFO ";
    case LOG_LEVEL_DEBUG:
      return "DEBUG";
    default:
      return "UNKNW";
  }
}

/**
 * @brief Get current system time string
 * @param buffer: Buffer to store time string
 * @param size: Buffer size
 * @retval None
 */
static void get_time_string(char* buffer, uint32_t size)
{
  uint32_t tick = tx_time_get();
  snprintf(buffer, size, "[%08lu]", tick);
}

/**
 * @brief Internal RTT log function
 * @param level: Log level
 * @param channel: RTT channel
 * @param format: Format string
 * @param ...: Variable arguments
 * @retval None
 */
static void rtt_log_internal(uint8_t level, uint8_t channel, const char* format, ...)
{
  va_list args;
  char time_str[16];
  
  /* Check log level */
  if (level > current_log_level)
  {
    return;
  }
  
  /* Get current time */
  get_time_string(time_str, sizeof(time_str));
  
  /* Format log message */
  va_start(args, format);
  vsnprintf(log_buffer, sizeof(log_buffer), format, args);
  va_end(args);
  
  /* Output to RTT */
  SEGGER_RTT_printf(channel, "%s [%s] %s\r\n", 
                    time_str, 
                    get_log_level_string(level), 
                    log_buffer);
}

/**
 * @brief Initialize RTT logger
 * @retval None
 */
void rtt_logger_init(void)
{
  /* Initialize RTT */
  SEGGER_RTT_Init();
  
  /* Set log level */
  current_log_level = LOG_LEVEL_INFO;
  
  /* Output initialization message */
  rtt_log_internal(LOG_LEVEL_INFO, RTT_CHANNEL_MAIN, 
                   "RTT Logger initialized successfully");
}

/**
 * @brief Set log level
 * @param level: Log level (0=ERROR, 1=WARNING, 2=INFO, 3=DEBUG)
 * @retval None
 */
void rtt_logger_set_level(uint8_t level)
{
  if (level <= LOG_LEVEL_DEBUG)
  {
    current_log_level = level;
    rtt_log_internal(LOG_LEVEL_INFO, RTT_CHANNEL_MAIN, 
                     "Log level set to %s", get_log_level_string(level));
  }
}

/**
 * @brief Log error message
 * @param format: Format string
 * @param ...: Variable arguments
 * @retval None
 */
void rtt_log_error(const char* format, ...)
{
  va_list args;
  char time_str[16];
  
  get_time_string(time_str, sizeof(time_str));
  
  va_start(args, format);
  vsnprintf(log_buffer, sizeof(log_buffer), format, args);
  va_end(args);
  
  SEGGER_RTT_printf(RTT_CHANNEL_MAIN, "%s [ERROR] %s\r\n", time_str, log_buffer);
}

/**
 * @brief Log warning message
 * @param format: Format string
 * @param ...: Variable arguments
 * @retval None
 */
void rtt_log_warning(const char* format, ...)
{
  rtt_log_internal(LOG_LEVEL_WARNING, RTT_CHANNEL_MAIN, format);
}

/**
 * @brief Log info message
 * @param format: Format string
 * @param ...: Variable arguments
 * @retval None
 */
void rtt_log_info(const char* format, ...)
{
  rtt_log_internal(LOG_LEVEL_INFO, RTT_CHANNEL_MAIN, format);
}

/**
 * @brief Log debug message
 * @param format: Format string
 * @param ...: Variable arguments
 * @retval None
 */
void rtt_log_debug(const char* format, ...)
{
  rtt_log_internal(LOG_LEVEL_DEBUG, RTT_CHANNEL_MAIN, format);
}

/**
 * @brief Log watchdog message
 * @param format: Format string
 * @param ...: Variable arguments
 * @retval None
 */
void rtt_log_watchdog(const char* format, ...)
{
  va_list args;
  char time_str[16];
  
  get_time_string(time_str, sizeof(time_str));
  
  va_start(args, format);
  vsnprintf(log_buffer, sizeof(log_buffer), format, args);
  va_end(args);
  
  SEGGER_RTT_printf(RTT_CHANNEL_WATCHDOG, "%s [WATCHDOG] %s\r\n", time_str, log_buffer);
}

/**
 * @brief Log system log message
 * @param format: Format string
 * @param ...: Variable arguments
 * @retval None
 */
void rtt_log_system(const char* format, ...)
{
  va_list args;
  char time_str[16];
  
  get_time_string(time_str, sizeof(time_str));
  
  va_start(args, format);
  vsnprintf(log_buffer, sizeof(log_buffer), format, args);
  va_end(args);
  
  SEGGER_RTT_printf(RTT_CHANNEL_LOG, "%s [SYSTEM] %s\r\n", time_str, log_buffer);
}

/**
 * @brief Log VBAT message
 * @param format: Format string
 * @param ...: Variable arguments
 * @retval None
 */
void rtt_log_vbat(const char* format, ...)
{
  va_list args;
  char time_str[16];
  
  get_time_string(time_str, sizeof(time_str));
  
  va_start(args, format);
  vsnprintf(log_buffer, sizeof(log_buffer), format, args);
  va_end(args);
  
  SEGGER_RTT_printf(RTT_CHANNEL_VBAT, "%s [VBAT] %s\r\n", time_str, log_buffer);
}

/**
 * @brief Log task status
 * @param task_name: Task name
 * @param status: Task status
 * @retval None
 */
void rtt_log_task_status(const char* task_name, const char* status)
{
  rtt_log_info("Task %s: %s", task_name, status);
}

/**
 * @brief Log system statistics
 * @retval None
 */
void rtt_log_system_stats(void)
{
  TX_THREAD thread_info;
  TX_TIMER timer_info;
  
  /* Get thread information */
  if (tx_thread_info_get(&thread_info, TX_NULL, TX_NULL, TX_NULL, TX_NULL, TX_NULL, TX_NULL) == TX_SUCCESS)
  {
    rtt_log_info("Active threads: %lu", thread_info.tx_thread_run_count);
  }
  
  /* Get timer information */
  if (tx_timer_info_get(&timer_info, TX_NULL, TX_NULL, TX_NULL, TX_NULL) == TX_SUCCESS)
  {
    rtt_log_info("Active timers: %lu", timer_info.tx_timer_active_count);
  }
  
  rtt_log_info("System tick: %lu", tx_time_get());
}

/* USER CODE END 0 */
