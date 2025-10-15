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
 * @brief VBAT状态枚举
 */
typedef enum
{
  VBAT_STATUS_NORMAL = 0,    /* 正常电压 */
  VBAT_STATUS_LOW,           /* 低电压 */
  VBAT_STATUS_HIGH,          /* 高电压 */
  VBAT_STATUS_CRITICAL       /* 临界电压 */
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
 * @brief 读取VBAT电压
 * @retval uint32_t: VBAT电压值（单位：mV）
 */
uint32_t read_vbat_voltage(void);

/**
 * @brief 检查VBAT电压状态
 * @param voltage_mv: 电压值（单位：mV）
 * @retval VBAT_Status: VBAT状态
 */
VBAT_Status check_vbat_status(uint32_t voltage_mv);

/**
 * @brief 获取VBAT状态描述字符串
 * @param status: VBAT状态
 * @retval const char*: 状态描述字符串
 */
const char* get_vbat_status_string(VBAT_Status status);

/**
 * @brief VBAT监控任务处理函数
 * @retval None
 */
void vbat_monitor_task_handler(void);

/**
 * @brief 获取最后一次检测的VBAT电压
 * @retval uint32_t: VBAT电压值（单位：mV）
 */
uint32_t get_last_vbat_voltage(void);

/**
 * @brief 获取VBAT检测次数
 * @retval uint32_t: 检测次数
 */
uint32_t get_vbat_check_count(void);
/* USER CODE END EFP */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif

#endif /* __VBAT_MONITOR_H__ */
