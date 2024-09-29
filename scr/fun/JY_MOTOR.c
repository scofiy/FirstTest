/*************************************************************************************************************
����--ͨѶЭ��

************************************************************************************************************
************************************************************************************************************
UARTЭ�����ԣ�9600��N,8,1
ͨѶ�����>80mS
֡��ʽ��ͷ��0xFF + ���ݰ�(N) + У����(B) + ������0xFE
**************************************************************************************************

**************************************************************************************************/
#include "config.h"
#include "JY_MOTOR.h"
#include "WR_Android.h"
/**************************************************************************************************/
/***************************************************************************************************/
uint8_t   Motor_TxLenth =0;                  	//�������ݳ���
uint8_t   Motor_RxLenth =0;                  	//�������ݳ���
uint8_t   Motor_TxBuf[10];                   	//����������
uint8_t   Motor_RxBuf[10];                   	//����������

bit btSetMotor_Flag=0;               			//���õ���������
uint8_t  ucInc_StudyProcess=0;						//����ѧϰ����	0������1ѧϰָ�2ѧϰ�С�3��ѧϰ���
uint16_t Motor_BackSpeed=0;								//�������ٶ�
uint16_t Rx_stop_Cnt=0;										//�¿�ͨѶ�Ͽ���ʱ
uint8_t ucMotorState=0;
/***************************************************************************************************/
/***************************************************************************************************/


uint8_t Tempbuf[50];   					//����
uint8_t tempLenth=0;   					//����
void uTx_temp(uint8_t *_Data) 			//����
{
	static uint8_t Number =0;
	if(Number <tempLenth)  
		S4BUF = _Data[++Number];  
	else if(tempLenth) 
	{
		Number =0; tempLenth =0;                 //������ϱ�Ƿ��ͳ���Ϊ0XFF
		memset(Tempbuf,0,sizeof(Tempbuf));       //������0
	}
}

/**************************************************************************************
*	����˵��: ���ݸ�λ
	λ�ã�		main    
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
*	����˵��: �������ݷ���    
	λ�ã�		UART4�ж�         
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
		Number =0; Motor_TxLenth =0;                //������ϱ�Ƿ��ͳ���Ϊ0XFF
		memset(Motor_TxBuf,0,sizeof(Motor_TxBuf));  //������0
	}
}

/**************************************************************************************
*	����˵��: ����У��(��У��)
	У��ֵ�� 		��ҳ
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
*	����˵��: ����У��(��У��)
	У��ֵ�� 		��ҳ
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
*	����˵��:   �¿����ݽ���/����  
λ�ã�        	UART4�ж�    
***************************************************************************************/
void Rx_MotorData(uint8_t rData)
{    
	bit Rx_Clear_Flag = 0;   
	uint8_t Buf = rData;

	Motor_RxBuf[Motor_RxLenth]=Buf;   				          																											
	if(Motor_RxBuf[0]==0xFD)                                         		//ͷ��
	{	
		if(Motor_RxLenth >=5)
		{
			if(Motor_RxBuf[5]==0xFB)													//�жϽ�����
			{
				Rx_Clear_Flag = 1;   
				if(Motor_RxBuf[4]= Rx_CRC(Motor_RxBuf,Motor_RxLenth))		//У�����ȶ�
				{
					Rx_stop_Cnt=0;
					if(Motor_RxBuf[1]==0x12)											//�־������Ƿ�ɹ�����	
					{
						if(Motor_RxBuf[2]==1)	btSetMotor_Flag=1;    // �ɹ�����
						else									btSetMotor_Flag=0;
					}
					else if(Motor_RxBuf[1]==0x20)									//�������ݣ�״̬+ʵ���ٶ�
					{		
						 // ����
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
						/*Motor_BackSpeed=Motor_RxBuf[3];							//ʵ���ٶ�
						if(Motor_RxBuf[2]==0x52)										//״̬������ѧϰ��		
							ucInc_StudyProcess=2;
						else if(Motor_RxBuf[2]==0x51)								//״̬������ͣ��
							{
						     ucMotorState=Motor_RxBuf[2];
								 if(!Motor_BackSpeed)                   //״̬������ͣ��,�����ٶ�Ϊ0��������״̬��Ϊ������
								    ucRunStatus=1;
							}
						else																				//״̬������
						{
							if(ucError!=7)														//�ǰ�ȫ�����ϣ����չ���
							{
								if(Motor_RxBuf[2] <16)
									ucError=Motor_RxBuf[2];
							}
							if((Motor_RxBuf[2]==0) && (ucInc_StudyProcess==2))		//�¿���������������ѧϰ���̣���ʾ����ѧϰ���
								ucInc_StudyProcess=3;
						}*/
					}
				}
			}
		}
		Motor_RxLenth = (++Motor_RxLenth)%7; 	//�����޳�6�ֽ�
	}
	else
		Rx_Clear_Flag = 1;
	
    if(Rx_Clear_Flag)
    {
				Rx_Clear_Flag=0;
        Motor_RxLenth = 0;
        memset(Motor_RxBuf,0,sizeof(Motor_RxBuf)); //������0
    }
}

/********************************************************************
����˵��: ׼�����͸��¿ص�����
λ�ã�       Main       100ms/��
/********************************************************************/
void Task_Motor(void)
{	
	if(MAXData_GET_Flag==0)										//��׿δ����ǰ�����·���������ʱ����
	{
		return;
	}
	
	/*if(++Rx_stop_Cnt>20)											//ͨѶ�Ͽ���ʱ��0.1*20=2S,			//���Կ���ʱ����
	{
		Rx_stop_Cnt=20;
		if(ucError==0)
			ucError=1;
	}*/
	
  if(ucError)		// ֻҪ���д����Ҫ���ͼ�ָͣ�Э�����ǰ�ȫ������ŷ�20ָ�										
	{
		Motor_TxBuf[0]=0xFD;
		Motor_TxBuf[1]=0x20;//��ͣ
		Motor_TxBuf[2]=0x01;
		Motor_TxBuf[3]=0x00;
	}
	else if((btSetMotor_Flag==0)&&(ucRunStatus <=1))		// �ϵ����õ���־�,�����ڴ���״̬
	{
		Motor_TxBuf[0]=0xFD;
		Motor_TxBuf[1]=0x12;//�·��־�
		Motor_TxBuf[2]=ucWheelDIA;
		//Motor_TxBuf[2]=60;   // ����
		Motor_TxBuf[3]=0x00;
	}
	else if(ucInc_StudyProcess==1)									//����ѧϰ
	{
		Motor_TxBuf[0]=0xFD;
		Motor_TxBuf[1]=0x21;//����ѧϰָ��
		Motor_TxBuf[2]=0x01;
		Motor_TxBuf[3]=0x00;
	}
	else																					//����״̬���ٶ�/�¶�
	{
		Motor_TxBuf[0]=0xFD;
		Motor_TxBuf[1]=0x22;
		Motor_TxBuf[2]=TxSpeed;  //�·��ٶ�
		Motor_TxBuf[3]=TxGrade;  //�·��¶�                      //((uint16_t)TxGrade*255/Max_INCLINE);
	}
	 //Motor_TxBuf[4]=Motor_TxBuf[0]+Motor_TxBuf[1]+Motor_TxBuf[2]+Motor_TxBuf[3];
	Motor_TxLenth=5;
	Motor_TxBuf[4]=Tx_CRC(Motor_TxBuf,Motor_TxLenth);
	Motor_TxBuf[5]=0xFB;
	SBUF=Motor_TxBuf[0];
}

//**************************************************
