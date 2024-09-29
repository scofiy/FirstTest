#ifndef __WR_Android_H__
#define __WR_Android_H__

//*****************************************************


extern uint8_t ucError;             //故障码
extern uint8_t ucRunStatus;					//当前运动状态
extern uint8_t Heart;								//心率

extern uint8_t KEY_UP_Value;					//键值上传


extern uint8_t  TxGrade;        		//下发扬升值
extern uint8_t  TxSpeed;        		//下发速度值
extern uint8_t  ucSpeed;		 				//速度值
extern uint8_t  ucGrade;		 				//升降值
extern uint8_t  ucTarget_Speed;		 	//目标速度值

extern uint8_t ucWheelDIA;					//轮子直径

extern uint8_t Min_Speed;
extern uint8_t Max_Speed;
extern uint8_t Min_INCLINE;
extern uint8_t Max_INCLINE;

extern bit KEY_UP_Flag;							//键值上传标志
extern bit MAXData_GET_Flag;				//获取到系统参数标志(0未获取，1获取)
extern bit btSetMotor_Flag;         //下控马达设置工程参数标志
/*********************************************************************/
/*********************************************************************/
extern uint8_t APP_TxBuf[10];					//TFT_发送数组
extern uint8_t APP_RxLenth ;                  	//TFT_接收数据长度
extern uint8_t APP_RST_WriteTime;				//等待数据清零
/*********************************************************************/
/*********************************************************************/
void TarSpeedNowspeed(void);
void inital_TFT_Data(void);						//初始化
void Examine_SystemData(void);
void Task_APP(void);							//准备发送数据
void Tx_APP_Data(uint8_t *_Data);				//UART中断发送
void Rx_APP_Data(uint8_t rData);				//UART中断接收
/*********************************************************************/
/*********************************************************************/

#endif

