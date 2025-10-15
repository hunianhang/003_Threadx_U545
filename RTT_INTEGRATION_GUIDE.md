# RTT Logger Integration Guide

## Overview

This project now includes a comprehensive RTT (Real-Time Transfer) logging system that provides real-time debug output to the RTT terminal. The RTT logger is integrated with all four periodic tasks and provides categorized logging with different channels.

## RTT Logger Features

### 🎯 **Multi-Channel Logging**
- **Channel 0 (Main)**: General application logs, errors, warnings, info, debug
- **Channel 1 (Watchdog)**: Watchdog refresh logs
- **Channel 2 (System)**: Hourly and daily system logs
- **Channel 3 (VBAT)**: Battery voltage monitoring logs

### 📊 **Log Levels**
- **ERROR (0)**: Critical errors that require immediate attention
- **WARNING (1)**: Warning messages for potential issues
- **INFO (2)**: General information messages (default level)
- **DEBUG (3)**: Detailed debug information

### ⏰ **Timestamped Logs**
All log messages include system tick timestamps for precise timing analysis.

## RTT Logger Functions

### **Initialization**
```c
void rtt_logger_init(void);
```
Initializes the RTT logger and sets default log level to INFO.

### **Log Level Control**
```c
void rtt_logger_set_level(uint8_t level);
```
Sets the log level (0=ERROR, 1=WARNING, 2=INFO, 3=DEBUG).

### **Logging Functions**
```c
void rtt_log_error(const char* format, ...);
void rtt_log_warning(const char* format, ...);
void rtt_log_info(const char* format, ...);
void rtt_log_debug(const char* format, ...);
void rtt_log_watchdog(const char* format, ...);
void rtt_log_system(const char* format, ...);
void rtt_log_vbat(const char* format, ...);
```

### **System Statistics**
```c
void rtt_log_system_stats(void);
void rtt_log_task_status(const char* task_name, const char* status);
```

## Task Integration

### **1. Watchdog Task**
- **Frequency**: Every 5 seconds
- **Channel**: Watchdog (Channel 1)
- **Logs**: 
  - Task startup
  - Refresh count every 50 seconds (10 refreshes)
  - Error conditions

### **2. Hourly Log Task**
- **Frequency**: Every 1 hour
- **Channel**: System (Channel 2)
- **Logs**:
  - Hourly system status with timestamp
  - System statistics (threads, timers, ticks)
  - Task status overview

### **3. Daily Log Task**
- **Frequency**: Every 6 hours (4 times per day)
- **Channel**: System (Channel 2)
- **Logs**:
  - Daily system report
  - Detailed system statistics
  - All task statuses
  - System health summary

### **4. VBAT Check Task**
- **Frequency**: Every 50 minutes
- **Channel**: VBAT (Channel 3)
- **Logs**:
  - VBAT voltage readings with status
  - Voltage level warnings/errors
  - Battery health monitoring

## RTT Terminal Setup

### **Using J-Link RTT Viewer**
1. Connect J-Link debugger to your STM32U545 board
2. Open J-Link RTT Viewer
3. Select your target device (STM32U545)
4. Connect to RTT
5. You should see 4 channels:
   - **Terminal 0**: Main application logs
   - **Terminal 1**: Watchdog logs
   - **Terminal 2**: System logs
   - **Terminal 3**: VBAT logs

### **Using SEGGER RTT Terminal**
1. Open SEGGER RTT Terminal
2. Select your J-Link connection
3. Connect to RTT
4. Monitor the output in real-time

## Expected Log Output

### **System Startup**
```
[00000000] [INFO ] RTT Logger initialized successfully
[00000001] [INFO ] ThreadX application initialized
[00000002] [INFO ] All periodic tasks initialized successfully
[00000003] [INFO ] All tasks and timers created successfully
[00000004] [WATCHDOG] Watchdog task started
[00000005] [SYSTEM] Hourly log task started
[00000006] [SYSTEM] Daily log task started
[00000007] [VBAT] VBAT check task started
```

### **Watchdog Logs (Channel 1)**
```
[00000050] [WATCHDOG] Watchdog refreshed 10 times
[00000100] [WATCHDOG] Watchdog refreshed 20 times
[00000150] [WATCHDOG] Watchdog refreshed 30 times
```

### **System Logs (Channel 2)**
```
[00000360] [SYSTEM] Hourly Log #1 - Date: 01/01/2025 Time: 12:00:00 Tick: 3600
[00000361] [SYSTEM] Active threads: 4
[00000362] [SYSTEM] Active timers: 4
[00000363] [SYSTEM] System tick: 3600
```

### **VBAT Logs (Channel 3)**
```
[00000300] [VBAT] VBAT Check #1 - Date: 01/01/2025 Time: 12:00:00 VBAT: 3200 mV (Normal)
[00000301] [DEBUG] VBAT NORMAL: 3200 mV
```

## Configuration Options

### **Log Level Control**
You can change the log level at runtime:
```c
rtt_logger_set_level(LOG_LEVEL_DEBUG);  // Enable all logs
rtt_logger_set_level(LOG_LEVEL_INFO);   // Default level
rtt_logger_set_level(LOG_LEVEL_WARNING); // Only warnings and errors
rtt_logger_set_level(LOG_LEVEL_ERROR);  // Only errors
```

### **Custom Log Messages**
You can add custom log messages in your code:
```c
rtt_log_info("Custom message: %d", value);
rtt_log_error("Error occurred: %s", error_string);
rtt_log_debug("Debug info: %lu", debug_value);
```

## Troubleshooting

### **No RTT Output**
1. Check J-Link connection
2. Verify RTT is enabled in your debugger settings
3. Ensure RTT files are included in your project
4. Check if `rtt_logger_init()` is called

### **Missing Channels**
1. Verify RTT channel configuration in `rtt_logger.c`
2. Check if all channels are properly initialized
3. Ensure RTT buffer sizes are adequate

### **Performance Impact**
- RTT logging has minimal performance impact
- Logs are buffered and sent asynchronously
- Consider reducing log level in production builds

## File Structure

```
Core/
├── Inc/
│   └── rtt_logger.h          # RTT logger header
├── Src/
│   └── rtt_logger.c          # RTT logger implementation
└── RTT/                      # SEGGER RTT library files
    ├── SEGGER_RTT.h
    ├── SEGGER_RTT.c
    ├── SEGGER_RTT_printf.c
    └── SEGGER_RTT_Conf.h
```

## Benefits

1. **Real-time Debugging**: See system behavior in real-time
2. **Categorized Output**: Different channels for different types of logs
3. **Timestamped**: All logs include precise timing information
4. **Non-intrusive**: Minimal impact on system performance
5. **Professional**: Industry-standard debugging tool
6. **Multi-level**: Configurable log levels for different environments

The RTT logger provides a comprehensive debugging solution that makes it easy to monitor and troubleshoot your embedded system in real-time!
