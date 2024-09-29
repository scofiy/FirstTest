/*************************************************************************************
»ñÈ¡Ð¾Æ¬UID
**************************************************************************************/

#include "config.h"
#include "uid.h"

void uid_read_rom_id( uint8_t *id, uint8_t len )
{
    uint8_t i;
    char    *addr;

#if (MCU_MODULE == BSP_MCU_STC8F2K64S2 || MCU_MODULE == BSP_MCU_STC8F2K64S4)
    addr = (char code *)0xFDF9;	// STC8F2K64S2
#elif (MCU_MODULE == BSP_MCU_STC8F2K60S2 || MCU_MODULE == BSP_MCU_STC8F2K60S4)
	addr = (char code *)0xEFF9;	// STC8F2K60S2
//#elif (MCU_MODULE == BSP_MCU_STC8F2K32S2 || MCU_MODULE == BSP_MCU_STC8F2K32S4)
//	addr = (char code *)0x7FF9;	// STC8F2K32S2
//#elif (MCU_MODULE == BSP_MCU_STC8F2K16S2 || MCU_MODULE == BSP_MCU_STC8F2K16S4)
//	addr = (char code *)0x3FF9;	// STC8F2K16S2
#else
    #error "please define mcu module!!!"
#endif

    len = len > UID_ROM_MAX_NO_LENGTH ? UID_ROM_MAX_NO_LENGTH : len;

    for( i = 0; i < len; i++ ) 
    {
        id[i] = addr[i];
    }
}