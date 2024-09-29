
#ifndef __KEY_H__
#define __KEY_H__


#define SafetyKeyPin 		P32    //��ȫ�������

#define Key1	       P15          //���հ���		//3��
#define Key2	       P54          //���հ���
#define Key3         P55          //���հ���
#define Key4         P35          //���հ���

//#define Key1	      P15          //���հ���		//5��
//#define Key2	      P21          //���հ���
//#define Key3        P54          //���հ���
//#define Key4        P35          //���հ���

/* �ṹ�嶨�� */
typedef enum
{
  //�����궨��          ����ֵ
	//KB_START_KEY      = 0x10,  //��ʼ��
	//KB_STOP_KEY       = 0x20,  //ֹͣ��
	
	KB_SPEED_ADD      = 0x01,  //�ٶ���������
	KB_SPEED_DEC      = 0x02,  //�ٶ��������� 
	
	KB_INCLINE_ADD    = 0x04,  //������������
	KB_INCLINE_DEC    = 0x08,  //������������  
};

void Safety_Key(void);
void Exectue_Key(void);



#endif
