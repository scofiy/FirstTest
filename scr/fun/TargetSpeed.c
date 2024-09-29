/********************************************************************
*	模块名称 : 发送下控速度计算模块
*	文件名称 : TargetSpeed.c
*	版    本 : V1.0
*	说    明 : 
*********************************************************************/
#include "config.h"
#include "bsp.h"
#include "WR_Android.h"
/*********************************************************************/
uint8_t TxSpeed=0;      //下发速度值
uint8_t TxGrade=0;			//下发扬升
/*********************************************************************/

/*********************************************************************
缓冲给控制器的速度值:
  1:发送给控制器的速度做缓升,缓降.
  2:每秒最大变化值2.0km/h.
*********************************************************************/
void TarSpeedNowspeed(void)
{
	// 有系统错误，下发速度为0
	if(ucError != 0)
	{
		TxSpeed =0;
		ucRunStatus =1; 	     // 1:待机
		return;
	}

	//运行状态最低值0.8,其他+/-1
	else if(ucRunStatus ==3)													 //运行状态
	{
		//TxGrade=ucGrade;
		TxSpeed=ucSpeed;																//下控做减速
		if(Max_INCLINE)
			TxGrade=(uint16_t)ucGrade*255/Max_INCLINE;
		else
			TxGrade=0;
//		if(TxSpeed>ucSpeed)	TxSpeed--;			             	//控制器速度大于目标速度       			
//		if(TxSpeed<ucSpeed)	TxSpeed++;		                //控制器速度小于目标速度
//		if(TxSpeed <=3) 	TxSpeed =3;											//运行时最低下发速度不能小于0.3
	}
	else						
	{
		TxSpeed=0;
		TxGrade=0;	
//		if(TxSpeed>=3)	TxSpeed--;
//		else			TxSpeed=0;	
//		if((ucRunStatus==4)&&(TxSpeed==0))
//			ucRunStatus=1;
	}

}
/**********************************************/
