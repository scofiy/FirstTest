/********************************************************************
*	模块名称 : 按键
*	文件名称 : KEY.c
*	版    本 : V1.0
*	说    明 : 
*********************************************************************/
#include "config.h"
#include "JY_MOTOR.h"
#include "WR_Android.h"
#include "Buzzer.h"
#include "KEY.h"
/*********************************************************************/
uint8_t ucKeyStatic =0;   //按键状态:0:按键松开/1:首次按键/2:连续按键/3:连续按键9次后+-10

/********************************************************************
*	功能说明:      数据复位
	位 置：			main     
*   说 明:      无
/********************************************************************/
void Safety_Key(void)
{
	static uint8_t ucSafetyClose_Cnt =0,ucSafetyOpen_Cnt =0;

	if(!SafetyKeyPin==0)					    	//检测到安全锁高电平
	{
		ucSafetyClose_Cnt = 0;
		if(ucSafetyOpen_Cnt++ >=33)     	//断开200mS判断有效
		{
			ucSafetyOpen_Cnt = 0;
			ucRunStatus=1;
			ucError =7;     								//置错误
		}                                                       
	}
	else																//检测到安全锁低电平
	{
		ucSafetyOpen_Cnt =0;
		if(ucSafetyClose_Cnt++ >=33)   		//合上200mS判断有效
		{
			ucSafetyClose_Cnt = 0;
			if(ucError == 7)
			{
				ucError =0; 
				ucRunStatus=1;
				inital_Motor_Data();
			}
		}
	}
}

	
/********************************************************************
*功能说明: 扶手按键
*形    参: 无
*返 回 值: 无
*********************************************************************/
void InclineUp_Key(uint8_t _key)
{ 
	 //按键状态（ucKeyStatic）:0:按键松开/1:首次按键/2:连续按键/3:连续按键9次后+-10
	if(ucKeyStatic==0)     return;
	if(ucRunStatus !=3)  	 return;
	if(_key!=KB_INCLINE_ADD) return;		//非+按键退出

	if(ucGrade >=Max_INCLINE) 
		ucGrade =Max_INCLINE;
	else
	{
		KEY_UP_Value=13;
		KEY_UP_Flag=1;
		Tone;
	}
}

void InclineDn_Key(uint8_t _key)
{
	if(ucKeyStatic==0)     return;
	if(ucRunStatus !=3)  	 return;
	if(_key!=KB_INCLINE_DEC) return;		//非+按键退出

	if(ucGrade) 
	{
		KEY_UP_Value=14;
		KEY_UP_Flag=1;
		Tone;	
	}
}

void Speedup_Key(uint8_t _key)
{
	if(ucKeyStatic==0)       return;
	if(ucRunStatus !=3)  	 	 return;
	if(_key!=KB_SPEED_ADD)   return;		//非+按键退出

	if(ucSpeed >=Max_Speed) 
		ucSpeed =Max_Speed;
	else
	{
		KEY_UP_Value=15;
		KEY_UP_Flag=1;
		Tone;
	}
}

void Speeddn_Key(uint8_t _key)
{
	if(ucKeyStatic==0)       	return;
	if(ucRunStatus !=3)  	 		return;
	if(_key!=KB_INCLINE_DEC) 	return;		//非+按键退出

	if(ucSpeed <=Min_Speed) 
		ucSpeed =Min_Speed;
	else
	{
		KEY_UP_Value=16;
		KEY_UP_Flag=1;
		Tone;
	}
}

/********************************************************************
*功能说明: 扫描物理按键
*形    参: 无
*返 回 值: 无
*********************************************************************/
uint8_t ReadKeyValue(void)
{
	static uint8_t Key_valueBack = 0;     //按键值备份
	static uint8_t  PressKey_Cnt=0;       //按键按下次数
	uint8_t Key_value = 0;
	uint8_t keyvalue = 0;                 //输出键值
	
	if(Key1==0)		Key_value |=KB_INCLINE_DEC;
	if(Key2==0)		Key_value |=KB_INCLINE_ADD;
	if(Key3==0)		Key_value |=KB_SPEED_ADD;
	if(Key4==0)		Key_value |=KB_SPEED_DEC;

	if(Key_value == 0)               		//无按键按下,清物理按键参数
	{
		Key_valueBack = 0;             		//清除备份
		ucKeyStatic = 0;               		//清除按键状态
		PressKey_Cnt = 0;              		//连续时间
	}
	else if(Key_value!=Key_valueBack)		//前后2次读的按键值不同
	{
		Key_valueBack =Key_value;      		//备份当前按键值
		PressKey_Cnt =0;
		ucKeyStatic=0;
	}
	else                             		//前后二次按键值相同,确认按键有效
	{
		if(ucKeyStatic ==0x00)         		//前次按键状态为松开,说明是首次按键
		{
			if(PressKey_Cnt++ >=3)			    // 首次按键5次按键值相同确认有效按键
			{
				PressKey_Cnt =0;
				ucKeyStatic = 0x01;        	  // 置按键状态:单击
				keyvalue =Key_value;       	  // 置按键值
			}
		}
		else if(ucKeyStatic ==0x01)    		//上次按键状态：单击
		{
			if(++PressKey_Cnt >=100)     	//累计大于100
			{
				PressKey_Cnt =0;
				ucKeyStatic =0x02;          //连续按键确认
			}
		}
		else if(ucKeyStatic ==0x02)    		//上次按键状态:连续按键
		{
			if(++PressKey_Cnt >=20)      	//连续按键确认
			{
				PressKey_Cnt =0;
				keyvalue =Key_value;       	//置按键值
			}
		}
	}
  return keyvalue;
}

/********************************************************************
*	功能说明: 按键程序服务
*	形    参: 无
*	返 回 值: 无
*********************************************************************/
void Exectue_Key(void)
{
	uint8_t	uckeyvalue = 0;             //输出键值
	
	uckeyvalue = ReadKeyValue();	 //读按键值
	
	if(uckeyvalue)
	{
		
		if((ucRunStatus==6)   // 6 暂停
			 ||(ucRunStatus==2) // 2 倒计时
		   ||(ucRunStatus==4) // 4 正在停机
		   ||ucError)	        // 报错状态，不接收以下按键处理
		{
			return;
		}
		
		Speedup_Key(uckeyvalue);           //速度加键
		
		Speeddn_Key(uckeyvalue);           //速度减键
		
		InclineUp_Key(uckeyvalue);         //扬升加键

		InclineDn_Key(uckeyvalue);         //扬升减键
	}
}