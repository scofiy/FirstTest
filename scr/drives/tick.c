/*************************************************************************************
定时器
**************************************************************************************/

#include "config.h"
#include "tick.h"


uint8_t  idata ucT5mS_Cnt =0;  		//5毫秒定时计数器
uint8_t  idata ucT50mS_Cnt =0;  	//50毫秒定时计数器
uint8_t  idata ucT80mS_Cnt =0;  	//80毫秒定时计数器
uint8_t  idata ucT100mS_Cnt =0;  	//100毫秒定时计数器
uint8_t  idata ucT200mS_Cnt =0;  	//500毫秒定时计数器
uint8_t  idata ucT1S_Cnt =0;  		//1秒定时计数器

bit  ubTime5mS=0;									//6mS标志
bit  ubTime50mS=0;								//50mS标志
bit  ubTime80mS=0;								//50mS标志
bit  ubTime100mS=0;								//100mS标志
bit  ubTime200mS=0;								//50mS标志
bit  ubTime1S=0;									//1S标志

#define Fosc 		24000000   				//系统时钟
#define T500uS  2000      				//定时时间500uS(设置方法:1s/0.0001=10000)


/********************************************************************
*功能说明: 初始化定时器T0，定时500us
*形    参: 
*返 回 值: 
/********************************************************************/
void Timer0_init( void )
{   																					// 0.5ms@24MHz timer period
	AUXR |= 0X80;                               //定时器0不分频      
	TMOD |= 0X00;                               //定时器0模式0,16位自动重装
	
	TL0   = (65536-(Fosc/T500uS));              //定时0.0004S中断重装低8位数
	TH0   = (65536-(Fosc/T500uS))>>8;           //定时0.0004S中断重装高8位数	
	TF0 = 0;									//清除TF0标志
	TR0   = 1;                                  //定时器0启动
	IP |= 0X20;//最高优先级
	IPH |= 0X20;//最高优先级
	ET0   = 1;                                   //开定时器0中断
}


void Timer0_isr() interrupt 1
{
		if(++ucT5mS_Cnt>=10)
		{
			ucT5mS_Cnt=0; ubTime5mS=1;					//5毫秒定时
			
			if(++ucT50mS_Cnt>=10)
			{
				ucT50mS_Cnt=0; 
				ubTime50mS=1;			//50毫秒定时
			}
			if(++ucT80mS_Cnt>=16)
			{
				ucT80mS_Cnt=0; 
				ubTime80mS=1;			//80毫秒定时
			}
			if(++ucT100mS_Cnt>=20)
			{
				ucT100mS_Cnt=0; 
				ubTime100mS=1;		//100毫秒定时
			}
			if(++ucT200mS_Cnt>=40)
			{
				ucT200mS_Cnt=0; 
				ubTime200mS=1;		//200毫秒定时
			}				
			if(++ucT1S_Cnt>=200)          
			{
				ucT1S_Cnt=0; 
				ubTime1S=1;				//1秒定时
			}
		}
}


