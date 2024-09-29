#ifndef __BSP_H__
#define __BSP_H__

#include <intrins.h>
#include <string.h>
#include <stdlib.h>
//#include "stdio.h"

#include "STC8.H"
#include "gpio.h"

// MCU 型号
#define BSP_MCU_STC8F2K64S2     1     
#define BSP_MCU_STC8F2K60S2     2
#define BSP_MCU_STC8F2K32S2     3
#define BSP_MCU_STC8F2K16S2     4

#define BSP_MCU_STC8F2K64S4     11     
#define BSP_MCU_STC8F2K60S4     12
#define BSP_MCU_STC8F2K32S4     13
#define BSP_MCU_STC8F2K16S4     14

typedef unsigned char           uint8_t;
typedef unsigned int            uint16_t;
typedef unsigned long           uint32_t;

typedef  char           				int8_t;
typedef  int            				int16_t;
typedef  long           				int32_t;

#define BSP_HW_RESET            IAP_CONTR |= 0x20

#endif
