/*************************************************************************
项目：金毅
PCB板：MCU=STC8C2K64S4、系统时钟24M

外设：安全锁+手扶按键

2024-08-15：由金莱特力量站程序改
************************************************************
************************************************************

**************************************************************************/
#include "config.h"
#include "bsp.h"

#include "tick.h"
#include "uart.h"

#include "JY_MOTOR.h"
#include "WR_Android.h"
#include "Buzzer.h"
#include "KEY.h"

void main( void )
{
	EA = 0;									  //关总中断

	Gpio_init();							//初始化_IO
	Timer0_init();						//初始化_定时器T0
	Timer1_init();						//初始化_定时器1（蜂鸣器）
	Uart4_Init();							//初始化_串口3（）
	Uart2_Init();							//初始化_串口2（）
	Uart1_Init();							//初始化_串口1（下控）
	EA = 1;										//打开总中断

	inital_TFT_Data();				//初始化_安卓通讯数据
	inital_Motor_Data();			//初始化_电控数据

	LongTone;
	
	while(1)
	{
		if(ubTime5mS)
		{
			ubTime5mS=0;
			
			Task_Buzzer();					// 蜂鸣器
			
			Safety_Key();					  // 安全锁
			
			Exectue_Key();					// 按键
		}

		if(ubTime50mS)
		{				
			ubTime50mS=0;
		}

		if(ubTime100mS)
		{
			ubTime100mS=0;
			
			TarSpeedNowspeed();
			
			Task_APP();      				  //APP通讯
			
			Task_Motor();       			//下控通讯 
		}
		
		if(ubTime200mS)
		{
			ubTime200mS=0;
		}

		if(ubTime1S)								
		{
			ubTime1S=0;
			
			Examine_SystemData();			//检查系统参数
		}
  }
}
