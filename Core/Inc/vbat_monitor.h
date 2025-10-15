/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    vbat_monitor.h
  * @brief   VBAT电压监控模块头文件
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
#ifndef __VBAT_MONITOR_H__
#define __VBAT_MONITOR_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
/**
 * @brief VBAT status enumeration
 */
typedef enum
{
  VBAT_STATUS_NORMAL = 0,    /* Normal voltage */
  VBAT_STATUS_LOW,           /* Low voltage */
  VBAT_STATUS_HIGH,          /* High voltage */
  VBAT_STATUS_CRITICAL       /* Critical voltage */
} VBAT_Status;
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
 * @brief Read VBAT voltage
 * @retval uint32_t: VBAT voltage value (unit: mV)
 */
uint32_t read_vbat_voltage(void);

/**
 * @brief Check VBAT voltage status
 * @param voltage_mv: Voltage value (unit: mV)
 * @retval VBAT_Status: VBAT status
 */
VBAT_Status check_vbat_status(uint32_t voltage_mv);

/**
 * @brief Get VBAT status description string
 * @param status: VBAT status
 * @retval const char*: Status description string
 */
const char* get_vbat_status_string(VBAT_Status status);

/**
 * @brief VBAT monitoring task handler
 * @retval None
 */
void vbat_monitor_task_handler(void);

/**
 * @brief Get last detected VBAT voltage
 * @retval uint32_t: VBAT voltage value (unit: mV)
 */
uint32_t get_last_vbat_voltage(void);

/**
 * @brief Get VBAT check count
 * @retval uint32_t: Check count
 */
uint32_t get_vbat_check_count(void);
/* USER CODE END EFP */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif

#endif /* __VBAT_MONITOR_H__ */
