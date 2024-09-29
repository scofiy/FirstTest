#ifndef __WR_Android_H__
#define __WR_Android_H__

//*****************************************************


extern uint8_t ucError;             //������
extern uint8_t ucRunStatus;					//��ǰ�˶�״̬
extern uint8_t Heart;								//����

extern uint8_t KEY_UP_Value;					//��ֵ�ϴ�


extern uint8_t  TxGrade;        		//�·�����ֵ
extern uint8_t  TxSpeed;        		//�·��ٶ�ֵ
extern uint8_t  ucSpeed;		 				//�ٶ�ֵ
extern uint8_t  ucGrade;		 				//����ֵ
extern uint8_t  ucTarget_Speed;		 	//Ŀ���ٶ�ֵ

extern uint8_t ucWheelDIA;					//����ֱ��

extern uint8_t Min_Speed;
extern uint8_t Max_Speed;
extern uint8_t Min_INCLINE;
extern uint8_t Max_INCLINE;

extern bit KEY_UP_Flag;							//��ֵ�ϴ���־
extern bit MAXData_GET_Flag;				//��ȡ��ϵͳ������־(0δ��ȡ��1��ȡ)
extern bit btSetMotor_Flag;         //�¿�������ù��̲�����־
/*********************************************************************/
/*********************************************************************/
extern uint8_t APP_TxBuf[10];					//TFT_��������
extern uint8_t APP_RxLenth ;                  	//TFT_�������ݳ���
extern uint8_t APP_RST_WriteTime;				//�ȴ���������
/*********************************************************************/
/*********************************************************************/
void TarSpeedNowspeed(void);
void inital_TFT_Data(void);						//��ʼ��
void Examine_SystemData(void);
void Task_APP(void);							//׼����������
void Tx_APP_Data(uint8_t *_Data);				//UART�жϷ���
void Rx_APP_Data(uint8_t rData);				//UART�жϽ���
/*********************************************************************/
/*********************************************************************/

#endif

