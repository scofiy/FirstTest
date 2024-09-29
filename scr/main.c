/*************************************************************************
��Ŀ������
PCB�壺MCU=STC8C2K64S4��ϵͳʱ��24M

���裺��ȫ��+�ַ�����

2024-08-15���ɽ���������վ�����
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
	EA = 0;									  //�����ж�

	Gpio_init();							//��ʼ��_IO
	Timer0_init();						//��ʼ��_��ʱ��T0
	Timer1_init();						//��ʼ��_��ʱ��1����������
	Uart4_Init();							//��ʼ��_����3����
	Uart2_Init();							//��ʼ��_����2����
	Uart1_Init();							//��ʼ��_����1���¿أ�
	EA = 1;										//�����ж�

	inital_TFT_Data();				//��ʼ��_��׿ͨѶ����
	inital_Motor_Data();			//��ʼ��_�������

	LongTone;
	
	while(1)
	{
		if(ubTime5mS)
		{
			ubTime5mS=0;
			
			Task_Buzzer();					// ������
			
			Safety_Key();					  // ��ȫ��
			
			Exectue_Key();					// ����
		}

		if(ubTime50mS)
		{				
			ubTime50mS=0;
		}

		if(ubTime100mS)
		{
			ubTime100mS=0;
			
			TarSpeedNowspeed();
			
			Task_APP();      				  //APPͨѶ
			
			Task_Motor();       			//�¿�ͨѶ 
		}
		
		if(ubTime200mS)
		{
			ubTime200mS=0;
		}

		if(ubTime1S)								
		{
			ubTime1S=0;
			
			Examine_SystemData();			//���ϵͳ����
		}
  }
}
