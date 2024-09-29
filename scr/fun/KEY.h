
#ifndef __KEY_H__
#define __KEY_H__


#define SafetyKeyPin 		P32    //安全锁输入口

#define Key1	       P15          //手握按键		//3线
#define Key2	       P54          //手握按键
#define Key3         P55          //手握按键
#define Key4         P35          //手握按键

//#define Key1	      P15          //手握按键		//5线
//#define Key2	      P21          //手握按键
//#define Key3        P54          //手握按键
//#define Key4        P35          //手握按键

/* 结构体定义 */
typedef enum
{
  //按键宏定义          按键值
	//KB_START_KEY      = 0x10,  //开始键
	//KB_STOP_KEY       = 0x20,  //停止键
	
	KB_SPEED_ADD      = 0x01,  //速度连续键加
	KB_SPEED_DEC      = 0x02,  //速度连续键减 
	
	KB_INCLINE_ADD    = 0x04,  //扬升连续键加
	KB_INCLINE_DEC    = 0x08,  //扬升连续键减  
};

void Safety_Key(void);
void Exectue_Key(void);



#endif
