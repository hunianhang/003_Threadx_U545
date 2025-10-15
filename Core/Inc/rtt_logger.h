/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    rtt_logger.h
  * @brief   RTT Logger module header file
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
#ifndef __RTT_LOGGER_H__
#define __RTT_LOGGER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdarg.h>
#include <stdio.h>

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */
/**
 * @brief Initialize RTT logger
 * @retval None
 */
void rtt_logger_init(void);

/**
 * @brief Set log level
 * @param level: Log level (0=ERROR, 1=WARNING, 2=INFO, 3=DEBUG)
 * @retval None
 */
void rtt_logger_set_level(uint8_t level);

/**
 * @brief Log error message
 * @param format: Format string
 * @param ...: Variable arguments
 * @retval None
 */
void rtt_log_error(const char* format, ...);

/**
 * @brief Log warning message
 * @param format: Format string
 * @param ...: Variable arguments
 * @retval None
 */
void rtt_log_warning(const char* format, ...);

/**
 * @brief Log info message
 * @param format: Format string
 * @param ...: Variable arguments
 * @retval None
 */
void rtt_log_info(const char* format, ...);

/**
 * @brief Log debug message
 * @param format: Format string
 * @param ...: Variable arguments
 * @retval None
 */
void rtt_log_debug(const char* format, ...);

/**
 * @brief Log watchdog message
 * @param format: Format string
 * @param ...: Variable arguments
 * @retval None
 */
void rtt_log_watchdog(const char* format, ...);

/**
 * @brief Log system log message
 * @param format: Format string
 * @param ...: Variable arguments
 * @retval None
 */
void rtt_log_system(const char* format, ...);

/**
 * @brief Log VBAT message
 * @param format: Format string
 * @param ...: Variable arguments
 * @retval None
 */
void rtt_log_vbat(const char* format, ...);

/**
 * @brief Log task status
 * @param task_name: Task name
 * @param status: Task status
 * @retval None
 */
void rtt_log_task_status(const char* task_name, const char* status);

/**
 * @brief Log system statistics
 * @retval None
 */
void rtt_log_system_stats(void);
/* USER CODE END EFP */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif

#endif /* __RTT_LOGGER_H__ */
