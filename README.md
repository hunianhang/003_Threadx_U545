# STM32U545 ThreadX 定时任务框架

这个项目实现了一个基于ThreadX的定时任务框架，用于处理四个主要的定时任务。

## 任务概述

### 1. Watchdog刷新任务
- **频率**: 每5秒执行一次
- **功能**: 刷新独立看门狗（IWDG），防止系统复位
- **优先级**: 5（最高优先级）

### 2. 小时日志输出任务
- **频率**: 每1小时执行一次
- **功能**: 输出系统状态日志，记录当前时间和系统运行状态
- **优先级**: 10

### 3. 日日志输出任务
- **频率**: 每6小时执行一次（一天4次）
- **功能**: 输出详细的系统日志，包括系统统计信息
- **优先级**: 10

### 4. VBAT电压检测任务
- **频率**: 每50分钟执行一次
- **功能**: 检测电池电压，监控电池状态
- **优先级**: 8

## 框架架构

### 核心组件

1. **定时器 (TX_TIMER)**
   - 每个任务都有对应的定时器
   - 定时器到期时触发回调函数
   - 回调函数通过信号量唤醒对应的任务

2. **信号量 (TX_SEMAPHORE)**
   - 用于任务间的同步
   - 定时器回调函数释放信号量
   - 任务等待信号量来执行

3. **任务 (TX_THREAD)**
   - 每个定时任务都是独立的线程
   - 具有独立的栈空间和优先级
   - 任务在无限循环中等待信号量

### 文件结构

```
Core/
├── Inc/
│   ├── app_threadx.h          # ThreadX应用头文件
│   └── vbat_monitor.h         # VBAT监控模块头文件
└── Src/
    ├── app_threadx.c          # ThreadX应用实现
    └── vbat_monitor.c         # VBAT监控模块实现
```

## 使用方法

### 1. 基本配置

框架已经集成到 `App_ThreadX_Init()` 函数中，会在ThreadX初始化时自动创建所有任务和定时器。

### 2. 自定义任务行为

你可以修改各个任务函数来实现自定义的行为：

#### Watchdog任务
```c
void watchdog_task_entry(ULONG thread_input)
{
    while (1)
    {
        tx_semaphore_get(&watchdog_semaphore, TX_WAIT_FOREVER);
        
        // 刷新watchdog
        HAL_IWDG_Refresh(&hiwdg);
        
        // 添加自定义逻辑
    }
}
```

#### 日志任务
```c
void hourly_log_task_entry(ULONG thread_input)
{
    while (1)
    {
        tx_semaphore_get(&hourly_log_semaphore, TX_WAIT_FOREVER);
        
        // 获取当前时间
        HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
        
        // 添加自定义日志逻辑
    }
}
```

#### VBAT检测任务
```c
void vbat_check_task_entry(ULONG thread_input)
{
    while (1)
    {
        tx_semaphore_get(&vbat_check_semaphore, TX_WAIT_FOREVER);
        
        // 执行VBAT监控
        vbat_monitor_task_handler();
        
        // 添加自定义处理逻辑
    }
}
```

### 3. VBAT监控模块

VBAT监控模块提供了以下功能：

- `read_vbat_voltage()`: 读取VBAT电压
- `check_vbat_status()`: 检查VBAT状态
- `get_vbat_status_string()`: 获取状态描述
- `vbat_monitor_task_handler()`: VBAT监控任务处理

#### VBAT状态定义
- `VBAT_STATUS_NORMAL`: 正常电压 (3.0V - 4.2V)
- `VBAT_STATUS_LOW`: 低电压 (< 3.0V)
- `VBAT_STATUS_HIGH`: 高电压 (> 4.2V)
- `VBAT_STATUS_CRITICAL`: 临界电压 (< 2.8V)

### 4. 配置参数

你可以在 `app_threadx.h` 中修改以下参数：

```c
/* 任务定时器定义 */
#define WATCHDOG_TIMER_PERIOD_TICKS     (5 * TX_TIMER_TICKS_PER_SECOND)    /* 5秒 */
#define HOURLY_LOG_TIMER_PERIOD_TICKS   (60 * TX_TIMER_TICKS_PER_SECOND)   /* 60秒 */
#define DAILY_LOG_TIMER_PERIOD_TICKS    (6 * 60 * TX_TIMER_TICKS_PER_SECOND) /* 6小时 */
#define VBAT_CHECK_TIMER_PERIOD_TICKS   (50 * 60 * TX_TIMER_TICKS_PER_SECOND) /* 50分钟 */

/* 任务优先级定义 */
#define WATCHDOG_TASK_PRIORITY          5
#define LOG_TASK_PRIORITY               10
#define VBAT_TASK_PRIORITY              8

/* 任务栈大小定义 */
#define WATCHDOG_TASK_STACK_SIZE       256
#define LOG_TASK_STACK_SIZE            512
#define VBAT_TASK_STACK_SIZE           256
```

## 注意事项

### 1. ADC配置
VBAT检测功能需要配置ADC来读取VBAT电压。在 `vbat_monitor.c` 中的 `read_vbat_voltage()` 函数需要根据实际硬件配置进行调整。

### 2. 日志输出
框架中的日志输出函数被注释掉了，你需要根据实际需求实现日志输出功能（如UART、RTT等）。

### 3. 内存使用
框架使用了静态分配的栈空间，确保有足够的内存来运行所有任务。

### 4. 实时性
Watchdog任务具有最高优先级，确保系统能够及时刷新看门狗。

## 扩展功能

### 1. 添加新任务
要添加新的定时任务，需要：
1. 在头文件中定义新的常量和函数声明
2. 在 `init_periodic_tasks()` 中创建新的任务、定时器和信号量
3. 实现任务入口函数和定时器回调函数

### 2. 动态调整定时器
可以使用 `tx_timer_change()` 函数动态调整定时器周期。

### 3. 任务间通信
可以使用队列、事件标志组等ThreadX同步机制来实现任务间通信。

## 调试建议

1. 使用ThreadX Trace功能来监控任务执行情况
2. 在任务中添加调试输出（如LED闪烁）来验证任务是否正常执行
3. 监控系统内存使用情况，确保没有内存泄漏
4. 使用RTC来验证定时器的准确性

## 故障排除

### 常见问题

1. **任务不执行**: 检查定时器是否正确创建和激活
2. **系统复位**: 检查watchdog是否正常刷新
3. **内存不足**: 减少任务栈大小或优化代码
4. **定时不准确**: 检查系统时钟配置和定时器设置

### 调试技巧

1. 使用 `tx_thread_info_get()` 获取任务信息
2. 使用 `tx_timer_performance_system_info_get()` 获取定时器性能统计信息
3. 使用 `tx_semaphore_info_get()` 获取信号量信息
4. 使用 `tx_time_get()` 获取系统运行时间
