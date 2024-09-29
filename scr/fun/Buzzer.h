#ifndef __BUZZER_H__
#define __BUZZER_H__




#define Buz_PIN      P34																	//蜂鸣器引脚
#define BUZ_PIN_ACTIVE  INTCLKO |= 0x02 									//定时器T1时钟输出P3.4
#define BUZ_PIN_FREEZE  INTCLKO &= ~0x02; Buz_PIN =0			//关闭定时器T1时钟输出，引脚输出低。


#define  Tone     ubToneOn =1    //短声音
#define  LongTone ubLongToneOn=1 //长声音

extern bit ubToneOn;				     //短声音
extern bit ubLongToneOn;				 //长声音

void Timer1_init( void );
void Task_Buzzer( void );

#endif
