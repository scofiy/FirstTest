/********************************************************************
*	ģ������ : ����APPͨѶģ��
*	�ļ����� : WR_Android.c
*	��    �� : V1.0
*	˵    �� : ͨѶЭ�飺����ͨѶЭ��2.1.1(������ѧϰ)
1��UARTЭ�����ԣ�9600��N,8,1
2��֡��ʽ��ͷ��+ ���ݰ�(N) + У���� + ������
*********************************************************************/
#include "config.h"
#include "WR_Android.h"
#include "JY_MOTOR.h"
#include "Buzzer.h"
#include "KEY.h"
/*********************************************************************/
/*********************************************************************/
uint8_t APP_TxBuf[10];					//TFT_��������
uint8_t APP_RxBuf[10];					//TFT_��������
uint8_t APP_TxLenth =0;         //TFT_�������ݳ���
uint8_t APP_RxLenth =0;         //TFT_�������ݳ���
/*********************************************************************/
uint8_t ucError=0;              //������
uint8_t ucRunStatus=0;					//��ǰ�˶�״̬(0:��ʼ��/1:����/2:����ʱ/3:��������/4:����ֹͣ/5:����/6:��ͣ
uint8_t Heart=0;								//����
uint8_t ucSpeed=0;		 					//�ٶ�ֵ
uint8_t ucGrade=0;		 					//����ֵ
/*********************************************************************/
uint8_t Min_Speed=1;						//��С�ٶ�
uint8_t Max_Speed=5;						//����ٶ�
uint8_t Min_INCLINE=2;					//��С�¶�
uint8_t Max_INCLINE=10;					//����¶�
/* ����CS
uint8_t Min_Speed=0;						//��С�ٶ�
uint8_t Max_Speed=0;						//����ٶ�
uint8_t Min_INCLINE=0;					//��С�¶�
uint8_t Max_INCLINE=0;					//����¶�
/*********************************************************************/

bit KEY_UP_Flag =0;							//��ֵ�ϴ���־
bit MotorDIA_DN_Flag=1;					//APP���̲����·���־
bit MAXData_DN_Flag=0;					//APPϵͳ�����·���־
bit MAXData_GET_Flag=0;					//��ȡ��ϵͳ������־(0δ��ȡ��1��ȡ)
uint8_t ucWheelDIA=0;						//����ֱ��
uint8_t KEY_UP_Value=0;					//��ֵ�ϴ�

/*********************************************************************/
uint8_t APP_Buf[10];						//����
/*********************************************************************/

/**************************************************************************************
*	����˵��:      ���ݸ�λ
	λ�ã�			main     
***************************************************************************************/
void inital_TFT_Data(void) 
{
	ucRunStatus=1;			
	APP_TxLenth =0;
	APP_RxLenth =0; 
	memset(APP_RxBuf,0,sizeof(APP_RxBuf));
}

/**************************************************************************************
*	����˵��:   �������ݷ���    
	λ�ã�			UART2�ж�         
***************************************************************************************/
void Tx_APP_Data(uint8_t *_Data) 
{
	static uint8_t Number =0;

	if(Number <APP_TxLenth)  
		S2BUF = _Data[++Number];	
	else if(APP_TxLenth) 
	{
		Number =0;   APP_TxLenth =0;                 //������ϱ�Ƿ��ͳ���Ϊ0XFF
		memset(APP_TxBuf,0,sizeof(APP_TxBuf));       //������0
	}
}

/**************************************************************************************
*	����˵��:   ��������У�飨��У�飩   
	λ�ã� 			��ҳ
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
*	����˵��:   ��������У�飨��У�飩   
	λ�ã� 			��ҳ
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
*	����˵��:   TFT���ݽ���/����  
	λ�ã�        UART2�ж�
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
		if(APP_RxLenth>=8)														 	//���ճ��ȴ��
		{
			if(APP_RxBuf[8]==0xFC)
			{
				if(APP_RxBuf[7] ==Rx_CRC_Cheack(&APP_RxBuf,APP_RxLenth))   				//У��
				{
					if(APP_RxBuf[1]==0x04)												//���̲������־�
					{
						MotorDIA_DN_Flag=1;
						ucWheelDIA=APP_RxBuf[2];
						APP_TxBuf[3]=APP_RxBuf[3];
						APP_TxBuf[4]=APP_RxBuf[4];
						APP_TxBuf[5]=APP_RxBuf[5];
						APP_TxBuf[6]=APP_RxBuf[6];
					}
					else if(APP_RxBuf[1]==0x05)											//ϵͳ���������/С�ٶȡ����/С�¶�
					{
						MAXData_DN_Flag=1;
						MAXData_GET_Flag=1;
						Min_Speed=APP_RxBuf[2];
						Max_Speed=APP_RxBuf[3];
						Min_INCLINE=APP_RxBuf[4];
						Max_INCLINE=APP_RxBuf[5];
					}
					else if(APP_RxBuf[1]==0x06)											//���в�����״̬+�¶�+�ٶ�+������
					{
						ucRunStatus=APP_RxBuf[2];
						ucGrade=APP_RxBuf[3];
						ucSpeed=APP_RxBuf[4];	
						if(APP_RxBuf[5])	Tone;	
					}
					else if(APP_RxBuf[1]==0x07)											//����������
					{
						Tone;
					}
					else if(APP_RxBuf[1]==0x08)											//���Ʋ�����20=�¶�ѧϰ, 1��ʼѧϰ��2����
					{
						if(APP_RxBuf[2]==20)			                    //20=�¶�ѧϰ, 1��ʼѧϰ��2����	
						{
							if(APP_RxBuf[3]==1)                         //1��ʼѧϰ
								if(ucInc_StudyProcess==0) 
									ucInc_StudyProcess=1;
							else if(APP_RxBuf[3]==2)                    //2����
								if(ucInc_StudyProcess>=2)
									ucInc_StudyProcess=0;
						}						
					}
				}
			}
			Rx_Clear_Flag=1;						//��λ����
		}
		APP_RxLenth =(APP_RxLenth+1)%9;
	}
	else
	{
		APP_RxLenth=0;
	}
	
	if(Rx_Clear_Flag)								//�������
	{
		Rx_Clear_Flag=0;
		APP_RxLenth=0;
		memset(APP_RxBuf,0x00,sizeof(APP_RxBuf));
	}
}


/********************************************************************
*	����˵��:���ϵͳ����
	λ�ã�  	Main
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
*	����˵��:׼�����͸�TFT������:
	λ�ã�  	Main
/********************************************************************/
void Task_APP(void) 
{
	static uint8_t type =0;
			
	//���̲����ظ����־�
	if(MotorDIA_DN_Flag==1)
	{
		MotorDIA_DN_Flag=0;
		APP_TxBuf[0]=0xFD;
		APP_TxBuf[1]=0x04;
		APP_TxBuf[2]=ucWheelDIA;		// ���������ڽ����Ѿ���ֵ
		btSetMotor_Flag=0;          // ��ȡ���־�����Ҫ������¿��·�
		// ���������ڽ����Ѿ���ֵ
		/*APP_TxBuf[3]=APP_RxBuf[3];
		APP_TxBuf[4]=APP_RxBuf[4];
		APP_TxBuf[5]=APP_RxBuf[5];
		APP_TxBuf[6]=APP_RxBuf[6];*/
	}
	//ϵͳ�����ظ�
	else if((MAXData_DN_Flag==1)||(MAXData_GET_Flag==0))
	{
		MAXData_DN_Flag=0;
		APP_TxBuf[0]=0xFD;
		APP_TxBuf[1]=0x05;
		APP_TxBuf[2]=Min_Speed;
		APP_TxBuf[3]=Max_Speed;
		APP_TxBuf[4]=Min_INCLINE;
		APP_TxBuf[5]=Max_INCLINE;
		APP_TxBuf[6]=0;							//1���ã�MCU������û�й��̲�����ϵͳ����ʱ���յ����в���ʱ��Ҫ�������ã�
		if(MAXData_GET_Flag==0)
			APP_TxBuf[6]=1;	
	}
	//������
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
	
	//����ѧϰ��
	else if(ucInc_StudyProcess)							
	{
		APP_TxBuf[0]=0xFD;
		APP_TxBuf[1]=0x08;
		APP_TxBuf[2]=06;
		APP_TxBuf[3]=0x01;						 //1=ѧϰ�У�2=�ɹ���3=ʧ��
		if(ucInc_StudyProcess==3)
		{
			//ucInc_StudyProcess=0;
			APP_TxBuf[3]=2;
		}
		APP_TxBuf[4]=0;    
		APP_TxBuf[5]=0;
		APP_TxBuf[6]=0;
	}
	
	//����
	else if(KEY_UP_Flag)
	{
		KEY_UP_Flag=0;
		APP_TxBuf[0]=0xFD;
		APP_TxBuf[1]=0x01;         // ������ֵ
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
		if(ucRunStatus==4)				//����ֹͣ����������ֵ
			type=0;

		//���в���
		if(type==0)
		{
			APP_TxBuf[0]=0xFD;
			APP_TxBuf[1]=0x06;     // ���в���
			APP_TxBuf[2]=ucRunStatus;
			APP_TxBuf[3]=ucGrade;
			APP_TxBuf[4]=ucSpeed;    
			APP_TxBuf[5]=Motor_BackSpeed;
			APP_TxBuf[6]=0;
		}
		else
		{
			
			APP_TxBuf[0]=0xFD;
			APP_TxBuf[1]=0x07;     // ����
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

