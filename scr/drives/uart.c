/*************************************************************************************
串口配置
串口中断
**************************************************************************************/

#include "uart.h"
#include "tick.h"
#include "JY_MOTOR.h"
#include "WR_Android.h"
#include <string.h>
#include "stdio.h"

void Uart1_Init(void)	//9600bps@24.000MHz			//下控
{
	SCON = 0x50;		 //8位数据,可变波特率  //9600bps@24.000MHz 
	AUXR |= 0x01;		 //串口1选择定时器2为波特率发生器  （定时器1被用于蜂鸣器）
	AUXR |= 0x04;		 //定时器时钟1T模式
	P_SW1 = (P_SW1 & ~0xc0) | 0x40;		//UART1用: RxD(P3.6), TxD(P3.7)
	T2L = 0x8F;			 //设置定时初始值
	T2H = 0xFD;			 //设置定时初始值
	AUXR |= 0x10;		 //定时器2开始计时
	ES = 1;				   //使能串口1中断
}

void Uart2_Init(void)								//安卓
{
	S2CON = 0x50;		//8位数据,可变波特率  //9600bps@24.000MHz
	AUXR |= 0x04;		//定时器时钟1T模式		
	T2L = 0x8F;			//设置定时初始值
	T2H = 0xFD;			//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时
	IE2 |= 0x01;		//使能串口2中断
}

void Uart4_Init(void)							//打印
{
	S4CON = 0x10;		   //8位数据,可变波特率	 //115200bps@24.000MHz
	S4CON |= 0x40;		 //串口4选择定时器4为波特率发生器
	T4T3M |= 0x20;		 //定时器时钟1T模式
	T4L = 0x8F;			   //设置定时初始值
	T4H = 0xFD;			   //设置定时初始值
	T4T3M |= 0x80;		 //定时器4开始计时
	IE2 |= 0x10;		   //使能串口4中断
}


void Uart1_Isr(void) interrupt 4
{
	if (RI)				//检测串口1接收中断
	{
		RI = 0;			//清除串口1接收中断请求位
		Rx_MotorData(SBUF);
	}
	if (TI)				//检测串口1发送中断
	{
		TI = 0;			//清除串口1发送中断请求位
		Tx_MotorData(Motor_TxBuf);
	}
}

void Uart2_Isr(void) interrupt 8
{
	if (S2CON & 0x01)	//检测串口2接收中断
	{
		S2CON &= ~0x01;	//清除串口2接收中断请求位
		Rx_APP_Data(S2BUF);
	}
	if (S2CON & 0x02)	//检测串口2发送中断
	{
		S2CON &= ~0x02;	//清除串口2发送中断请求位
		Tx_APP_Data(APP_TxBuf);
	}
}


void Uart4_Isr(void) interrupt 18
{
	if (S4CON & 0x01)	//检测串口4接收中断
	{
		S4CON &= ~0x01;	//清除串口4接收中断请求位
//		Rx_MotorL_Data(S4BUF);
	}
	if (S4CON & 0x02)	//检测串口4发送中断
	{
		S4CON &= ~0x02;	//清除串口4发送中断请求位
		uTx_temp(Tempbuf);        //测试 （打印数据）
	}
}