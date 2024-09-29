/*************************************************************************************************************
沃锐--通讯协议

************************************************************************************************************
************************************************************************************************************
UART协议特性：9600，N,8,1
通讯间隔：>80mS
帧格式：头码0xFF + 数据包(N) + 校验码(B) + 结束码0xFE
**************************************************************************************************

**************************************************************************************************/
#include "config.h"
#include "JY_MOTOR.h"
#include "WR_Android.h"
/**************************************************************************************************/
/***************************************************************************************************/
uint8_t   Motor_TxLenth =0;                  	//发送数据长度
uint8_t   Motor_RxLenth =0;                  	//接收数据长度
uint8_t   Motor_TxBuf[10];                   	//发送数据组
uint8_t   Motor_RxBuf[10];                   	//接收数据组

bit btSetMotor_Flag=0;               			//设置电机参数标记
uint8_t  ucInc_StudyProcess=0;						//扬升学习步骤	0正常、1学习指令、2学习中、3、学习完成
uint16_t Motor_BackSpeed=0;								//反馈：速度
uint16_t Rx_stop_Cnt=0;										//下控通讯断开计时
uint8_t ucMotorState=0;
/***************************************************************************************************/
/***************************************************************************************************/


uint8_t Tempbuf[50];   					//测试
uint8_t tempLenth=0;   					//测试
void uTx_temp(uint8_t *_Data) 			//测试
{
	static uint8_t Number =0;
	if(Number <tempLenth)  
		S4BUF = _Data[++Number];  
	else if(tempLenth) 
	{
		Number =0; tempLenth =0;                 //发送完毕标记发送长度为0XFF
		memset(Tempbuf,0,sizeof(Tempbuf));       //数组清0
	}
}

/**************************************************************************************
*	功能说明: 数据复位
	位置：		main    
***************************************************************************************/
void inital_Motor_Data(void) 
{			
	ucInc_StudyProcess=0;
	Motor_BackSpeed=0;
	Rx_stop_Cnt=0;
	
	Motor_TxLenth =0;
	Motor_RxLenth =0; 
	memset(Motor_RxBuf,0x00,sizeof(Motor_RxBuf));
}

/**************************************************************************************
*	功能说明: 串口数据发送    
	位置：		UART4中断         
***************************************************************************************/
void Tx_MotorData(uint8_t *_Data) 
{
	static uint8_t Number =0;

	if(Number <Motor_TxLenth)  
	{
		SBUF = _Data[++Number];
	}		
	else if(Motor_TxLenth) 
	{
		Number =0; Motor_TxLenth =0;                //发送完毕标记发送长度为0XFF
		memset(Motor_TxBuf,0,sizeof(Motor_TxBuf));  //数组清0
	}
}

/**************************************************************************************
*	功能说明: 数据校验(和校验)
	校验值： 		本页
***************************************************************************************/
uint8_t Rx_CRC(uint8_t *pkt,uint8_t len) 
{
  uint8_t i =0, calculatedCRC =0;
	
	len -= 1;
	for(i =0; i <len; i++)
	{
		calculatedCRC += pkt[i];
	}
	return calculatedCRC;
}
/**************************************************************************************
*	功能说明: 数据校验(和校验)
	校验值： 		本页
***************************************************************************************/
uint8_t Tx_CRC(uint8_t *pkt,uint8_t len) 
{
  uint8_t i =0, calculatedCRC =0;
	
	len -= 1;
	for(i =0; i <len; i++)
	{
		calculatedCRC += pkt[i];
	}
	return calculatedCRC;
}
/**************************************************************************************
*	功能说明:   下控数据接收/解析  
位置：        	UART4中断    
***************************************************************************************/
void Rx_MotorData(uint8_t rData)
{    
	bit Rx_Clear_Flag = 0;   
	uint8_t Buf = rData;

	Motor_RxBuf[Motor_RxLenth]=Buf;   				          																											
	if(Motor_RxBuf[0]==0xFD)                                         		//头码
	{	
		if(Motor_RxLenth >=5)
		{
			if(Motor_RxBuf[5]==0xFB)													//判断结束码
			{
				Rx_Clear_Flag = 1;   
				if(Motor_RxBuf[4]= Rx_CRC(Motor_RxBuf,Motor_RxLenth))		//校验结果比对
				{
					Rx_stop_Cnt=0;
					if(Motor_RxBuf[1]==0x12)											//轮径参数是否成功接收	
					{
						if(Motor_RxBuf[2]==1)	btSetMotor_Flag=1;    // 成功接收
						else									btSetMotor_Flag=0;
					}
					else if(Motor_RxBuf[1]==0x20)									//运行数据：状态+实际速度
					{		
						 // 测试
						 Motor_BackSpeed=80;
						 if(ucInc_StudyProcess==1)
							 ucInc_StudyProcess=2;
						 if(ucInc_StudyProcess==2)
							 ucInc_StudyProcess=3;
						  if(ucRunStatus==4)
							{
								Motor_BackSpeed=0;
								ucRunStatus=1;
							}
						/*Motor_BackSpeed=Motor_RxBuf[3];							//实际速度
						if(Motor_RxBuf[2]==0x52)										//状态：扬升学习中		
							ucInc_StudyProcess=2;
						else if(Motor_RxBuf[2]==0x51)								//状态：正在停机
							{
						     ucMotorState=Motor_RxBuf[2];
								 if(!Motor_BackSpeed)                   //状态：正在停机,并且速度为0，则将运行状态改为待运行
								    ucRunStatus=1;
							}
						else																				//状态：故障
						{
							if(ucError!=7)														//非安全锁故障，接收故障
							{
								if(Motor_RxBuf[2] <16)
									ucError=Motor_RxBuf[2];
							}
							if((Motor_RxBuf[2]==0) && (ucInc_StudyProcess==2))		//下控正常，且有扬升学习流程，表示扬升学习完成
								ucInc_StudyProcess=3;
						}*/
					}
				}
			}
		}
		Motor_RxLenth = (++Motor_RxLenth)%7; 	//接收限长6字节
	}
	else
		Rx_Clear_Flag = 1;
	
    if(Rx_Clear_Flag)
    {
				Rx_Clear_Flag=0;
        Motor_RxLenth = 0;
        memset(Motor_RxBuf,0,sizeof(Motor_RxBuf)); //数组清0
    }
}

/********************************************************************
功能说明: 准备发送给下控的数据
位置：       Main       100ms/次
/********************************************************************/
void Task_Motor(void)
{	
	if(MAXData_GET_Flag==0)										//安卓未起来前，不下发参数。暂时屏蔽
	{
		return;
	}
	
	/*if(++Rx_stop_Cnt>20)											//通讯断开计时，0.1*20=2S,			//测试可暂时屏蔽
	{
		Rx_stop_Cnt=20;
		if(ucError==0)
			ucError=1;
	}*/
	
  if(ucError)		// 只要是有错误就要发送急停指令（协议中是安全锁脱落才发20指令）										
	{
		Motor_TxBuf[0]=0xFD;
		Motor_TxBuf[1]=0x20;//急停
		Motor_TxBuf[2]=0x01;
		Motor_TxBuf[3]=0x00;
	}
	else if((btSetMotor_Flag==0)&&(ucRunStatus <=1))		// 上电设置电机轮径,必须在待机状态
	{
		Motor_TxBuf[0]=0xFD;
		Motor_TxBuf[1]=0x12;//下发轮经
		Motor_TxBuf[2]=ucWheelDIA;
		//Motor_TxBuf[2]=60;   // 测试
		Motor_TxBuf[3]=0x00;
	}
	else if(ucInc_StudyProcess==1)									//扬升学习
	{
		Motor_TxBuf[0]=0xFD;
		Motor_TxBuf[1]=0x21;//扬升学习指令
		Motor_TxBuf[2]=0x01;
		Motor_TxBuf[3]=0x00;
	}
	else																					//运行状态：速度/坡度
	{
		Motor_TxBuf[0]=0xFD;
		Motor_TxBuf[1]=0x22;
		Motor_TxBuf[2]=TxSpeed;  //下发速度
		Motor_TxBuf[3]=TxGrade;  //下发坡度                      //((uint16_t)TxGrade*255/Max_INCLINE);
	}
	 //Motor_TxBuf[4]=Motor_TxBuf[0]+Motor_TxBuf[1]+Motor_TxBuf[2]+Motor_TxBuf[3];
	Motor_TxLenth=5;
	Motor_TxBuf[4]=Tx_CRC(Motor_TxBuf,Motor_TxLenth);
	Motor_TxBuf[5]=0xFB;
	SBUF=Motor_TxBuf[0];
}

//**************************************************
