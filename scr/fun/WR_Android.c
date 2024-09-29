/********************************************************************
*	模块名称 : 彩屏APP通讯模块
*	文件名称 : WR_Android.c
*	版    本 : V1.0
*	说    明 : 通讯协议：沃锐通讯协议2.1.1(带扬升学习)
1、UART协议特性：9600，N,8,1
2、帧格式：头码+ 数据包(N) + 校验码 + 结束码
*********************************************************************/
#include "config.h"
#include "WR_Android.h"
#include "JY_MOTOR.h"
#include "Buzzer.h"
#include "KEY.h"
/*********************************************************************/
/*********************************************************************/
uint8_t APP_TxBuf[10];					//TFT_发送数组
uint8_t APP_RxBuf[10];					//TFT_接收数组
uint8_t APP_TxLenth =0;         //TFT_发送数据长度
uint8_t APP_RxLenth =0;         //TFT_接收数据长度
/*********************************************************************/
uint8_t ucError=0;              //故障码
uint8_t ucRunStatus=0;					//当前运动状态(0:初始化/1:待机/2:倒计时/3:正在运行/4:正在停止/5:休眠/6:暂停
uint8_t Heart=0;								//心率
uint8_t ucSpeed=0;		 					//速度值
uint8_t ucGrade=0;		 					//升降值
/*********************************************************************/
uint8_t Min_Speed=1;						//最小速度
uint8_t Max_Speed=5;						//最大速度
uint8_t Min_INCLINE=2;					//最小坡度
uint8_t Max_INCLINE=10;					//最大坡度
/* 测试CS
uint8_t Min_Speed=0;						//最小速度
uint8_t Max_Speed=0;						//最大速度
uint8_t Min_INCLINE=0;					//最小坡度
uint8_t Max_INCLINE=0;					//最大坡度
/*********************************************************************/

bit KEY_UP_Flag =0;							//键值上传标志
bit MotorDIA_DN_Flag=1;					//APP工程参数下发标志
bit MAXData_DN_Flag=0;					//APP系统参数下发标志
bit MAXData_GET_Flag=0;					//获取到系统参数标志(0未获取，1获取)
uint8_t ucWheelDIA=0;						//轮子直径
uint8_t KEY_UP_Value=0;					//键值上传

/*********************************************************************/
uint8_t APP_Buf[10];						//其他
/*********************************************************************/

/**************************************************************************************
*	功能说明:      数据复位
	位置：			main     
***************************************************************************************/
void inital_TFT_Data(void) 
{
	ucRunStatus=1;			
	APP_TxLenth =0;
	APP_RxLenth =0; 
	memset(APP_RxBuf,0,sizeof(APP_RxBuf));
}

/**************************************************************************************
*	功能说明:   串口数据发送    
	位置：			UART2中断         
***************************************************************************************/
void Tx_APP_Data(uint8_t *_Data) 
{
	static uint8_t Number =0;

	if(Number <APP_TxLenth)  
		S2BUF = _Data[++Number];	
	else if(APP_TxLenth) 
	{
		Number =0;   APP_TxLenth =0;                 //发送完毕标记发送长度为0XFF
		memset(APP_TxBuf,0,sizeof(APP_TxBuf));       //数组清0
	}
}

/**************************************************************************************
*	功能说明:   接收数据校验（和校验）   
	位置： 			本页
***************************************************************************************/
uint8_t Rx_CRC_Cheack(uint8_t *pkt,uint8_t len) 
{
  uint8_t i =0, calculatedCRC =0;
	
	len -= 1;
	for(i =1; i <len; i++)
	{
		calculatedCRC += pkt[i];
	}
	return calculatedCRC;
}
/**************************************************************************************
*	功能说明:   接收数据校验（和校验）   
	位置： 			本页
***************************************************************************************/
uint8_t Tx_CRC_Cheack(uint8_t *pkt,uint8_t len) 
{
  uint8_t i =0, calculatedCRC =0;

	len -= 1; 
	for(i =1; i <len; i++)
	{
		calculatedCRC += pkt[i];
	}
	return calculatedCRC;
}

/**************************************************************************************
*	功能说明:   TFT数据接收/解析  
	位置：        UART2中断
***************************************************************************************/
void Rx_APP_Data(uint8_t rData)
{    
	bit Rx_Clear_Flag = 0;   
	uint8_t Buf = rData;
	uint8_t DataLen=0;													
	uint8_t i=0;  
	
	APP_RxBuf[APP_RxLenth]=Buf;   				                   				 
	
	if(APP_RxBuf[0]==0xFB)
	{
		if(APP_RxLenth>=8)														 	//接收长度达标
		{
			if(APP_RxBuf[8]==0xFC)
			{
				if(APP_RxBuf[7] ==Rx_CRC_Cheack(&APP_RxBuf,APP_RxLenth))   				//校验
				{
					if(APP_RxBuf[1]==0x04)												//工程参数：轮径
					{
						MotorDIA_DN_Flag=1;
						ucWheelDIA=APP_RxBuf[2];
						APP_TxBuf[3]=APP_RxBuf[3];
						APP_TxBuf[4]=APP_RxBuf[4];
						APP_TxBuf[5]=APP_RxBuf[5];
						APP_TxBuf[6]=APP_RxBuf[6];
					}
					else if(APP_RxBuf[1]==0x05)											//系统参数：最大/小速度、最大/小坡度
					{
						MAXData_DN_Flag=1;
						MAXData_GET_Flag=1;
						Min_Speed=APP_RxBuf[2];
						Max_Speed=APP_RxBuf[3];
						Min_INCLINE=APP_RxBuf[4];
						Max_INCLINE=APP_RxBuf[5];
					}
					else if(APP_RxBuf[1]==0x06)											//运行参数：状态+坡度+速度+蜂鸣器
					{
						ucRunStatus=APP_RxBuf[2];
						ucGrade=APP_RxBuf[3];
						ucSpeed=APP_RxBuf[4];	
						if(APP_RxBuf[5])	Tone;	
					}
					else if(APP_RxBuf[1]==0x07)											//蜂鸣器控制
					{
						Tone;
					}
					else if(APP_RxBuf[1]==0x08)											//控制操作：20=坡度学习, 1开始学习，2结束
					{
						if(APP_RxBuf[2]==20)			                    //20=坡度学习, 1开始学习，2结束	
						{
							if(APP_RxBuf[3]==1)                         //1开始学习
								if(ucInc_StudyProcess==0) 
									ucInc_StudyProcess=1;
							else if(APP_RxBuf[3]==2)                    //2结束
								if(ucInc_StudyProcess>=2)
									ucInc_StudyProcess=0;
						}						
					}
				}
			}
			Rx_Clear_Flag=1;						//复位数据
		}
		APP_RxLenth =(APP_RxLenth+1)%9;
	}
	else
	{
		APP_RxLenth=0;
	}
	
	if(Rx_Clear_Flag)								//清空数据
	{
		Rx_Clear_Flag=0;
		APP_RxLenth=0;
		memset(APP_RxBuf,0x00,sizeof(APP_RxBuf));
	}
}


/********************************************************************
*	功能说明:检查系统参数
	位置：  	Main
/********************************************************************/
void Examine_SystemData(void)
{
	if( MAXData_GET_Flag==0 )  	return;
	if( (ucWheelDIA==0)||(ucWheelDIA==0xff) )	MAXData_GET_Flag=0;
	if( (Min_Speed==0)||(Min_Speed==0xff) )	  MAXData_GET_Flag=0;
	if( (Max_Speed==0)||(Max_Speed==0xff) )	  MAXData_GET_Flag=0;
	if( Max_INCLINE>=30 ) 									  MAXData_GET_Flag=0;
}
/********************************************************************
*	功能说明:准备发送给TFT的数据:
	位置：  	Main
/********************************************************************/
void Task_APP(void) 
{
	static uint8_t type =0;
			
	//工程参数回复：轮经
	if(MotorDIA_DN_Flag==1)
	{
		MotorDIA_DN_Flag=0;
		APP_TxBuf[0]=0xFD;
		APP_TxBuf[1]=0x04;
		APP_TxBuf[2]=ucWheelDIA;		// 其他数据在接收已经赋值
		btSetMotor_Flag=0;          // 获取到轮径，需要往电机下控下发
		// 以下数据在接收已经赋值
		/*APP_TxBuf[3]=APP_RxBuf[3];
		APP_TxBuf[4]=APP_RxBuf[4];
		APP_TxBuf[5]=APP_RxBuf[5];
		APP_TxBuf[6]=APP_RxBuf[6];*/
	}
	//系统参数回复
	else if((MAXData_DN_Flag==1)||(MAXData_GET_Flag==0))
	{
		MAXData_DN_Flag=0;
		APP_TxBuf[0]=0xFD;
		APP_TxBuf[1]=0x05;
		APP_TxBuf[2]=Min_Speed;
		APP_TxBuf[3]=Max_Speed;
		APP_TxBuf[4]=Min_INCLINE;
		APP_TxBuf[5]=Max_INCLINE;
		APP_TxBuf[6]=0;							//1重置（MCU重启或没有工程参数或系统参数时，收到运行参数时需要申请重置）
		if(MAXData_GET_Flag==0)
			APP_TxBuf[6]=1;	
	}
	//故障码
	else if(ucError)
	{
		APP_TxBuf[0]=0xFD;
		APP_TxBuf[1]=0x03;
		APP_TxBuf[2]=ucError;
		APP_TxBuf[3]=0;
		APP_TxBuf[4]=0;
		APP_TxBuf[5]=0;
		APP_TxBuf[6]=0;
	}
	
	//扬升学习中
	else if(ucInc_StudyProcess)							
	{
		APP_TxBuf[0]=0xFD;
		APP_TxBuf[1]=0x08;
		APP_TxBuf[2]=06;
		APP_TxBuf[3]=0x01;						 //1=学习中，2=成功，3=失败
		if(ucInc_StudyProcess==3)
		{
			//ucInc_StudyProcess=0;
			APP_TxBuf[3]=2;
		}
		APP_TxBuf[4]=0;    
		APP_TxBuf[5]=0;
		APP_TxBuf[6]=0;
	}
	
	//按键
	else if(KEY_UP_Flag)
	{
		KEY_UP_Flag=0;
		APP_TxBuf[0]=0xFD;
		APP_TxBuf[1]=0x01;         // 单击键值
		APP_TxBuf[2]=KEY_UP_Value; 
		APP_TxBuf[3]=0;
		APP_TxBuf[4]=0;
		APP_TxBuf[5]=0;
		APP_TxBuf[6]=0;
	}
	else
	{
		if(type)		type=0;
		else        type=1;
		if(ucRunStatus==4)				//正在停止，不发心率值
			type=0;

		//运行参数
		if(type==0)
		{
			APP_TxBuf[0]=0xFD;
			APP_TxBuf[1]=0x06;     // 运行参数
			APP_TxBuf[2]=ucRunStatus;
			APP_TxBuf[3]=ucGrade;
			APP_TxBuf[4]=ucSpeed;    
			APP_TxBuf[5]=Motor_BackSpeed;
			APP_TxBuf[6]=0;
		}
		else
		{
			
			APP_TxBuf[0]=0xFD;
			APP_TxBuf[1]=0x07;     // 心跳
			APP_TxBuf[2]=Heart;
			APP_TxBuf[3]=0;
			APP_TxBuf[4]=0;
			APP_TxBuf[5]=0;
			APP_TxBuf[6]=0;
		}
	}
	APP_TxLenth=8;
	APP_TxBuf[7]=Tx_CRC_Cheack(APP_TxBuf,APP_TxLenth);
	APP_TxBuf[8]=0xFE;
	S2BUF=APP_TxBuf[0];
}

/********************************************************************/

