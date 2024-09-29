#ifndef __BUZZER_H__
#define __BUZZER_H__




#define Buz_PIN      P34																	//����������
#define BUZ_PIN_ACTIVE  INTCLKO |= 0x02 									//��ʱ��T1ʱ�����P3.4
#define BUZ_PIN_FREEZE  INTCLKO &= ~0x02; Buz_PIN =0			//�رն�ʱ��T1ʱ���������������͡�


#define  Tone     ubToneOn =1    //������
#define  LongTone ubLongToneOn=1 //������

extern bit ubToneOn;				     //������
extern bit ubLongToneOn;				 //������

void Timer1_init( void );
void Task_Buzzer( void );

#endif
