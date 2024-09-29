/*************************************************************************************
定时器
**************************************************************************************/

#include "config.h"
#include "tick.h"
#include "gpio.h"


/********************************************************************
*功能说明: 配置IO口
*形    参: 
*返 回 值: 
/********************************************************************/
void Gpio_init( void )
{
	//P30_Quasi_Mode;						//UART1_RX
	P30_Input_Mode;							//UART1_RX
	P31_PushPull_Mode;						//UART1_TX
	
	P36_Input_Mode;							//UART1_RX
	P37_PushPull_Mode;						//UART1_TX
	
	P10_Input_Mode;							//UART2_RX
	P11_PushPull_Mode;						//UART2_TX
	
//	P00_Input_Mode;							//UART3_RX
//	P01_PushPull_Mode;						//UART3_TX
	
	P02_Input_Mode;							//UART4_RX
	P03_PushPull_Mode;						//UART4_TX
	
	P32_Input_Mode;							//安全锁
	P34_PushPull_Mode; P34=0;				//蜂鸣器
	
	P15_Input_Mode;					//Key_L11	//3线
	P54_Input_Mode;					//Key_L12
	P55_Input_Mode;					//Key_L13
	P35_Input_Mode;					//Key_L14

//	P22_PushPull_Mode;P22=0;				//Key_L2
//	P55_PushPull_Mode;P55=0;				//Key_L13
//	P15_Input_Mode;					//Key_L11	5线
//	P21_Input_Mode;					//Key_L1	5线
//	P54_Input_Mode;					//Key_L12
//	P35_Input_Mode;					//Key_L14
}
	
	
	
	
