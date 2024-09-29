
/* device config file */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "bsp.h"

// <<< Use Configuration Wizard in Context Menu >>>

// <o>MCU Chip
//  <i>Default: STC8F2K60S4
//  <1=> STC8F2K64S2
//  <2=> STC8F2K60S2
//  <3=> STC8F2K32S2
//  <4=> STC8F2K16S2
//  <11=> STC8F2K64S4
//  <12=> STC8F2K60S4
//  <13=> STC8F2K32S4
//  <14=> STC8F2K16S4
#define MCU_MODULE 11

// <o>Device Type
//  <i>Default: Treadmill
//  <1=> Treadmill
#define DEVICE_TYPE 1

// <s.16>Module Name
//  <i>Module Name
//  <i>Default: "E5", max 16 char
#define MODULE_NAME "T26"

// <o>Module ID
//  <i>Module ID
//  <i>Default: 5
#define MODULE_ID 5

// <s.16>Vendor Name
//  <i>Vendor Name
//  <i>Default: "ZM", max 16 char
#define VENDOR_NAME "worui"

// <o>Vendor ID <0x00-0xFF>
//  <i>Vendor ID <0x00-0xFF>
//  <i>Default: 0x01
#define VENDOR_ID 0x1

// <o>Software Version <0-25>
//  <i>The range is 0 to 25
#define SOFTWARE_VERSION 1

// <o>Hardware Version <0-9>
//  <i>The range is 0 to 9
#define HARDWARE_VERSION 3

// <h>Developer Debug

// <c>Enable Printf
//#define EN_DEBUG
// </c>

#ifdef EN_DEBUG
#include <stdio.h>
#endif

// </h>

// <h>Safe-Lock

// <o>Safe-Lock Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
//  <5=> P5
#define SAFE_LOCK_PORT 3

// <o>Safe-Lock Pin <0-7>
//  <i>Pin Range is 0 to 7
#define SAFE_LOCK_PIN_NUM 2

GPIO_DEF(SAFE_LOCK_PIN, SAFE_LOCK_PORT, SAFE_LOCK_PIN_NUM);
#define SAFE_LOCK_MODE GPIO_MODE_BOTHWAY_DEF(SAFE_LOCK_PORT, SAFE_LOCK_PIN_NUM)
#define SAFE_LOCK_READ (!SAFE_LOCK_PIN)

// </h>

// <h>EEPROM

// <o>Sertor Size
//  <i>unit is byte
//  <i>Default: 512
#define EEPROM_SERTOR_SIZE 512

// <o>Base addr <0-1000>
//  <i>unit is a sertor
//  <i>Default: 0
#define EEPROM_SECTOR_BASE 0

// <o>Engineering Sertor Offset <0-20>
#define EEPROM_ENG_SETROR_BASE 0

// </h>

// <h>License
// <c>Enable License
//#define LICENSE_ENABLE
// </c>

// <o>IIC SCL Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define IIC_SCL_PORT 1

// <o>IIC SCL Pin <0-7>
//  <i>Pin Range is 0 to 7
#define IIC_SCL_PIN_NUM 7

GPIO_DEF(I2C_SCL_PIN, IIC_SCL_PORT, IIC_SCL_PIN_NUM);
#define I2C_SCL_OUT_MODE GPIO_MODE_PUSH_PULL_OUT_DEF(IIC_SCL_PORT, IIC_SCL_PIN_NUM)

// <o>IIC SDA Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define IIC_SDA_PORT 1

// <o>IIC SDA Pin <0-7>
//  <i>Pin Range is 0 to 7
#define IIC_SDA_PIN_NUM 6

GPIO_DEF(I2C_SDA_PIN, IIC_SDA_PORT, IIC_SDA_PIN_NUM);
#define I2C_SDA_OUT_MODE GPIO_MODE_PUSH_PULL_OUT_DEF(IIC_SDA_PORT, IIC_SDA_PIN_NUM)
#define I2C_SDA_IN_MODE  GPIO_MODE_HIGH_IMPEDANCE_IN_DEF(IIC_SDA_PORT, IIC_SDA_PIN_NUM)

// </h>

// <h>Motor

// <o>Motor Low Speed Ratio <1-20>
//  <i>Unit: 0.1
#define MOTOR_LOW_SPEED_RATIO 10

// <o>Motor Middle Speed Ratio <1-20>
//  <i>Unit: 0.1
#define MOTOR_MID_SPEED_RATIO 10

// <o>Motor High Speed Ratio <1-20>
//  <i>Unit: 0.1
#define MOTOR_HIGH_SPEED_RATIO 15

// <o>Motor Tx Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define MT_TX_PIN_PORT 3

// <o>Motor Tx Pin <0-7>
//  <i>Pin Range is 0 to 7
#define MT_TX_PIN_NUM 7

GPIO_DEF(MT_TX_PIN, MT_TX_PIN_PORT, MT_TX_PIN_NUM);

#define MT_GPIO_TX_MODE  GPIO_MODE_BOTHWAY_DEF(MT_TX_PIN_PORT, MT_TX_PIN_NUM);

//sbit MT_TX_PIN = P2^1;
//#define MT_GPIO_TX_MODE  GPIO_MODE_BOTHWAY(P2, 1);
#define MT_GPIO_TX_SET   MT_TX_PIN = 0 
#define MT_GPIO_TX_RESET MT_TX_PIN = 1

// <o>Motor Rx Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define MT_RX_PIN_PORT 3

// <o>Motor Rx Pin <0-7>
//  <i>Pin Range is 0 to 7
#define MT_RX_PIN_NUM 6

GPIO_DEF(MT_RX_PIN, MT_RX_PIN_PORT, MT_RX_PIN_NUM);
#define MT_GPIO_RX_MODE  GPIO_MODE_HIGH_IMPEDANCE_IN_DEF(MT_RX_PIN_PORT, MT_RX_PIN_NUM)
#define MT_GPIO_RX_READ  MT_RX_PIN // (~MT_RX_PIN)

// </h>

// <h>Buz

// <o>Buz Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define BUZ_PIN_PORT 3

// <o>Buz Pin <0-7>
//  <i>Pin Range is 0 to 7
#define BUZ_PIN_NUM 4

GPIO_DEF(BUZ_PIN, BUZ_PIN_PORT, BUZ_PIN_NUM);
#define BUZ_PIN_MODE GPIO_MODE_PUSH_PULL_OUT_DEF(BUZ_PIN_PORT, BUZ_PIN_NUM)

// </h>

// <h>Heart Rate

// <c>Heart Rate Enable
#define HEART_RATE_ENABLE
// </c>

// <o>Heart Rate Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define HEART_RATE_PIN_PORT 3

// <o>Heart Rate Pin <0-7>
//  <i>Pin Range is 0 to 7
#define HEART_RATE_PIN_NUM 3

GPIO_DEF(HEART_RATE_PIN, HEART_RATE_PIN_PORT, HEART_RATE_PIN_NUM);
#define HEART_RATE_PIN_MODE GPIO_MODE_HIGH_IMPEDANCE_IN_DEF(HEART_RATE_PIN_PORT, HEART_RATE_PIN_NUM)

// <o>Heart Rate Debug Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define HEART_RATE_DEBUG_PIN_PORT 1

// <o>Heart Rate Pin <0-7>
//  <i>Pin Range is 0 to 7
#define HEART_RATE_DEBUG_PIN_NUM 4

GPIO_DEF(HEART_RATE_DEBUG_PIN, HEART_RATE_DEBUG_PIN_PORT, HEART_RATE_DEBUG_PIN_NUM);
#define HEART_RATE_DEBUG_PIN_MODE GPIO_MODE_BOTHWAY_DEF(HEART_RATE_DEBUG_PIN_PORT, HEART_RATE_DEBUG_PIN_NUM)


// </h>

// <h>Protocol

// <c>Enable Multi
#define MULTI_ENABLE
// </c>

// <o>Uart Select
//  <i>Default: UART1
//  <1=> UART1  <2=> UART2  <3=> UART3  <4=> UART4
#define MULTI_UART_PORT 2

#define MULTI_UART_STRUCT        UARTX_STRUCT(MULTI_UART_PORT)
#define MULTI_UART_GET_RX_PACKET UARTX_GET_RX_PACKET(MULTI_UART_PORT)
#define MULTI_UART_SEND          UARTX_SEND(MULTI_UART_PORT)

// <c>Enable Protocol
#define PROTOCOL_ENABLE
// </c>

// <c>Protocol Debug Enable
//#define PROTOCOL_DEBUG
// </c>

// <c>Enable ThinkFit
#define THINKFIT_ENABLE
// </c>

// <o>Uart Select
//  <i>Default: UART1
//  <1=> UART1  <2=> UART2  <3=> UART3  <4=> UART4
#define THINKFIT_UART_PORT 3

#define THINKFIT_UART_STRUCT        UARTX_STRUCT(THINKFIT_UART_PORT)
#define THINKFIT_UART_GET_RX_PACKET UARTX_GET_RX_PACKET(THINKFIT_UART_PORT)
#define THINKFIT_UART_SEND          UARTX_SEND(THINKFIT_UART_PORT)

// <c>Enable iRunning
#define IRUNNING_ENABLE
// </c>

// <o>Uart Select
//  <i>Default: UART1
//  <1=> UART1  <2=> UART2  <3=> UART3  <4=> UART4
#define IRUNNING_UART_PORT 4

#define IRUNNING_UART_STRUCT        UARTX_STRUCT(IRUNNING_UART_PORT)
#define IRUNNING_UART_GET_RX_PACKET UARTX_GET_RX_PACKET(IRUNNING_UART_PORT)
#define IRUNNING_UART_SEND          UARTX_SEND(IRUNNING_UART_PORT)

// </h>

// <h>Key

// <c>Key Enable
#define KEY_ENABLE
// </c>

// <o>KEY1 Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define KEY1_PIN_PORT 2

// <o>KEY1 Pin <0-7>
//  <i>Pin Range is 0 to 7
#define KEY1_PIN_NUM 1

GPIO_DEF(KEY1_PIN, KEY1_PIN_PORT, KEY1_PIN_NUM);
#define KEY1_PIN_MODE GPIO_MODE_BOTHWAY_DEF(KEY1_PIN_PORT, KEY1_PIN_NUM)

// <o>KEY2 Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define KEY2_PIN_PORT 2

// <o>KEY2 Pin <0-7>
//  <i>Pin Range is 0 to 7
#define KEY2_PIN_NUM 2

GPIO_DEF(KEY2_PIN, KEY2_PIN_PORT, KEY2_PIN_NUM);
#define KEY2_PIN_MODE GPIO_MODE_BOTHWAY_DEF(KEY2_PIN_PORT, KEY2_PIN_NUM)

// <o>KEY3 Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define KEY3_PIN_PORT 2

// <o>KEY3 Pin <0-7>
//  <i>Pin Range is 0 to 7
#define KEY3_PIN_NUM 3

GPIO_DEF(KEY3_PIN, KEY3_PIN_PORT, KEY3_PIN_NUM);
#define KEY3_PIN_MODE GPIO_MODE_BOTHWAY_DEF(KEY3_PIN_PORT, KEY3_PIN_NUM)

// <o>KEY4 Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define KEY4_PIN_PORT 2

// <o>KEY4 Pin <0-7>
//  <i>Pin Range is 0 to 7
#define KEY4_PIN_NUM 4

GPIO_DEF(KEY4_PIN, KEY4_PIN_PORT, KEY4_PIN_NUM);
#define KEY4_PIN_MODE GPIO_MODE_BOTHWAY_DEF(KEY4_PIN_PORT, KEY4_PIN_NUM)

// <o>KEY5 Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define KEY5_PIN_PORT 2

// <o>KEY5 Pin <0-7>
//  <i>Pin Range is 0 to 7
#define KEY5_PIN_NUM 5

GPIO_DEF(KEY5_PIN, KEY5_PIN_PORT, KEY5_PIN_NUM);
#define KEY5_PIN_MODE GPIO_MODE_BOTHWAY_DEF(KEY5_PIN_PORT, KEY5_PIN_NUM)

// <o>KEY6 Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define KEY6_PIN_PORT 2

// <o>KEY6 Pin <0-7>
//  <i>Pin Range is 0 to 7
#define KEY6_PIN_NUM 6

GPIO_DEF(KEY6_PIN, KEY6_PIN_PORT, KEY6_PIN_NUM);
#define KEY6_PIN_MODE GPIO_MODE_BOTHWAY_DEF(KEY6_PIN_PORT, KEY6_PIN_NUM)

// <o>KEY7 Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define KEY7_PIN_PORT 2

// <o>KEY7 Pin <0-7>
//  <i>Pin Range is 0 to 7
#define KEY7_PIN_NUM 7

GPIO_DEF(KEY7_PIN, KEY7_PIN_PORT, KEY7_PIN_NUM);
#define KEY7_PIN_MODE GPIO_MODE_BOTHWAY_DEF(KEY7_PIN_PORT, KEY7_PIN_NUM)

// <o>KEY8 Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define KEY8_PIN_PORT 1

// <o>KEY8 Pin <0-7>
//  <i>Pin Range is 0 to 7
#define KEY8_PIN_NUM 2

GPIO_DEF(KEY8_PIN, KEY8_PIN_PORT, KEY8_PIN_NUM);
#define KEY8_PIN_MODE GPIO_MODE_BOTHWAY_DEF(KEY8_PIN_PORT, KEY8_PIN_NUM)

// <o>KEY9 Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define KEY9_PIN_PORT 1

// <o>KEY9 Pin <0-7>
//  <i>Pin Range is 0 to 7
#define KEY9_PIN_NUM 3

GPIO_DEF(KEY9_PIN, KEY9_PIN_PORT, KEY9_PIN_NUM);
#define KEY9_PIN_MODE GPIO_MODE_BOTHWAY_DEF(KEY9_PIN_PORT, KEY9_PIN_NUM)

// <o>KEY10 Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define KEY10_PIN_PORT 1

// <o>KEY10 Pin <0-7>
//  <i>Pin Range is 0 to 7
#define KEY10_PIN_NUM 4

GPIO_DEF(KEY10_PIN, KEY10_PIN_PORT, KEY10_PIN_NUM);
#define KEY10_PIN_MODE GPIO_MODE_BOTHWAY_DEF(KEY10_PIN_PORT, KEY10_PIN_NUM)

// <o>KEY11 Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
#define KEY11_PIN_PORT 1

// <o>KEY11 Pin <0-7>
//  <i>Pin Range is 0 to 7
#define KEY11_PIN_NUM 5

GPIO_DEF(KEY11_PIN, KEY11_PIN_PORT, KEY11_PIN_NUM);
#define KEY11_PIN_MODE GPIO_MODE_BOTHWAY_DEF(KEY11_PIN_PORT, KEY11_PIN_NUM)

// <o>KEY12 Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
//  <5=> P5
#define KEY12_PIN_PORT 5

// <o>KEY12 Pin <0-7>
//  <i>Pin Range is 0 to 7
#define KEY12_PIN_NUM 4

GPIO_DEF(KEY12_PIN, KEY12_PIN_PORT, KEY12_PIN_NUM);
#define KEY12_PIN_MODE GPIO_MODE_BOTHWAY_DEF(KEY12_PIN_PORT, KEY12_PIN_NUM)

// <o>KEY13 Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
//  <5=> P5
#define KEY13_PIN_PORT 5

// <o>KEY13 Pin <0-7>
//  <i>Pin Range is 0 to 7
#define KEY13_PIN_NUM 5

GPIO_DEF(KEY13_PIN, KEY13_PIN_PORT, KEY13_PIN_NUM);
#define KEY13_PIN_MODE GPIO_MODE_BOTHWAY_DEF(KEY13_PIN_PORT, KEY13_PIN_NUM)

// <o>KEY14 Port
//  <i>Default: P1
//  <0=> P0 <1=> P1 <2=> P2 <3=> P3 <4=> P4 <5=> P5
#define KEY14_PIN_PORT 3

// <o>KEY14 Pin <0-7>
//  <i>Pin Range is 0 to 7
#define KEY14_PIN_NUM 5

GPIO_DEF(KEY14_PIN, KEY14_PIN_PORT, KEY14_PIN_NUM);
#define KEY14_PIN_MODE GPIO_MODE_BOTHWAY_DEF(KEY14_PIN_PORT, KEY14_PIN_NUM)

// </h>

// <h>Fan

// <c>Fan Enable
#define FAN_ENABLE
// </c>

// <o>Fan Port
//  <i>Default: P1
//  <0=> P0
//  <1=> P1
//  <2=> P2
//  <3=> P3
//  <4=> P4
//  <5=> P5
#define FAN_PIN_PORT 2

// <o>Fan Pin <0-7>
//  <i>Pin Range is 0 to 7
#define FAN_PIN_NUM 0

GPIO_DEF(FAN_PIN, FAN_PIN_PORT, FAN_PIN_NUM);
#define FAN_PIN_MODE GPIO_MODE_BOTHWAY_DEF(FAN_PIN_PORT, FAN_PIN_NUM)

// </h>

// <<< end of configuration section >>>

#endif
