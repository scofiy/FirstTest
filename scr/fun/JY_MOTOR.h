#ifndef __JY_MOTOR_H__
#define __JY_MOTOR_H__

/*********************************************************************/
/*********************************************************************/
extern uint8_t  Motor_TxBuf[10];                	//����������
extern uint8_t  Motor_RxLenth;						//���ճ���



extern uint8_t ucInc_StudyProcess;							//��������ѧϰ���
extern uint16_t Motor_BackSpeed;					//�������ٶ�
/*********************************************************************/
void Rx_MotorData(uint8_t rData);					//UATR�жϽ���
void Tx_MotorData(uint8_t *_Data);					//UATR�жϷ���
void inital_Motor_Data(void);						//��ʼ��
void Task_Motor(void);								//׼�����͵�����
/*********************************************************************/

void uTx_temp(uint8_t *_Data) ;   	//����
extern uint8_t Tempbuf[50];   		//����
void temp2printf(void);   			//����
extern uint8_t tempLenth;  			//����
#endif





