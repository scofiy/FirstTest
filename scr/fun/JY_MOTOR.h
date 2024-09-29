#ifndef __JY_MOTOR_H__
#define __JY_MOTOR_H__

/*********************************************************************/
/*********************************************************************/
extern uint8_t  Motor_TxBuf[10];                	//发送数据组
extern uint8_t  Motor_RxLenth;						//接收长度



extern uint8_t ucInc_StudyProcess;							//设置扬升学习标记
extern uint16_t Motor_BackSpeed;					//反馈：速度
/*********************************************************************/
void Rx_MotorData(uint8_t rData);					//UATR中断接收
void Tx_MotorData(uint8_t *_Data);					//UATR中断发送
void inital_Motor_Data(void);						//初始化
void Task_Motor(void);								//准备发送的数据
/*********************************************************************/

void uTx_temp(uint8_t *_Data) ;   	//测试
extern uint8_t Tempbuf[50];   		//测试
void temp2printf(void);   			//测试
extern uint8_t tempLenth;  			//测试
#endif





