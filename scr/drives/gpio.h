#ifndef __GPIO_H__
#define __GPIO_H__





//双向
#define GPIO_MODE_BOTHWAY(port,bit)                 port##M0 &= (~(1<<bit)), port##M1 &= (~(1<<bit))  
    
				//推挽
#define GPIO_MODE_PUSH_PULL_OUT(port,bit)           port##M0 |= (1<<bit), port##M1 &= (~(1<<bit))
    
				//上拉输入
#define GPIO_MODE_HIGH_IMPEDANCE_IN(port,bit)       port##M0 &= (~(1<<bit)), port##M1 |= (1<<bit)  
    
				//开漏输出
#define GPIO_MODE_OPEN_DRAIN(port,bit)              port##M0 |= (1<<bit), port##M1 |= (1<<bit)
    
				
#define PIN_DEF(port,pin)                           P##port##^##pin
#define GPIO_DEF(def,port,pin)                      sbit def = PIN_DEF(port, pin)
    
#define MODE_BOTHWAY_DEF(port,bit)                  P##port##M0 &= (~(1<<bit)), P##port##M1 &= (~(1<<bit))  
#define GPIO_MODE_BOTHWAY_DEF(port,bit)             MODE_BOTHWAY_DEF(port, bit)

#define MODE_PUSH_PULL_OUT_DEF(port,bit)            P##port##M0 |= (1<<bit), P##port##M1 &= (~(1<<bit))  
#define GPIO_MODE_PUSH_PULL_OUT_DEF(port,bit)       MODE_PUSH_PULL_OUT_DEF(port, bit)

#define MODE_HIGH_IMPEDANCE_IN_DEF(port,bit)        P##port##M0 &= (~(1<<bit)), P##port##M1 |= (1<<bit)  
#define GPIO_MODE_HIGH_IMPEDANCE_IN_DEF(port,bit)   MODE_HIGH_IMPEDANCE_IN_DEF(port, bit)

#define MODE_OPEN_DRAIN_DEF(port,bit)               p##port##M0 |= (1<<bit), p##port##M1 |= (1<<bit)  
#define GPIO_MODE_OPEN_DRAIN_DEF(port,bit)          MODE_OPEN_DRAIN_DEF(port, bit)




//------------------- 准双向  -------------------
#define P00_Quasi_Mode				    P0M0 &= ~0x01; P0M1 &= ~0x01
#define P01_Quasi_Mode				    P0M0 &= ~0x02; P0M1 &= ~0x02
#define P02_Quasi_Mode				    P0M0 &= ~0x04; P0M1 &= ~0x04
#define P03_Quasi_Mode				    P0M0 &= ~0x08; P0M1 &= ~0x08
#define P04_Quasi_Mode				    P0M0 &= ~0x10; P0M1 &= ~0x10
#define P05_Quasi_Mode				    P0M0 &= ~0x20; P0M1 &= ~0x20
#define P06_Quasi_Mode				    P0M0 &= ~0x40; P0M1 &= ~0x40
#define P07_Quasi_Mode				    P0M0 &= ~0x80; P0M1 &= ~0x80

#define P10_Quasi_Mode				    P1M0 &= ~0x01; P1M1 &= ~0x01
#define P11_Quasi_Mode				    P1M0 &= ~0x02; P1M1 &= ~0x02
#define P12_Quasi_Mode				    P1M0 &= ~0x04; P1M1 &= ~0x04
#define P13_Quasi_Mode				    P1M0 &= ~0x08; P1M1 &= ~0x08
#define P14_Quasi_Mode				    P1M0 &= ~0x10; P1M1 &= ~0x10
#define P15_Quasi_Mode				    P1M0 &= ~0x20; P1M1 &= ~0x20
#define P16_Quasi_Mode				    P1M0 &= ~0x40; P1M1 &= ~0x40
#define P17_Quasi_Mode				    P1M0 &= ~0x80; P1M1 &= ~0x80
 
#define P20_Quasi_Mode				    P2M0 &= ~0x01; P2M1 &= ~0x01
#define P21_Quasi_Mode				    P2M0 &= ~0x02; P2M1 &= ~0x02
#define P22_Quasi_Mode				    P2M0 &= ~0x04; P2M1 &= ~0x04
#define P23_Quasi_Mode				    P2M0 &= ~0x08; P2M1 &= ~0x08
#define P24_Quasi_Mode				    P2M0 &= ~0x10; P2M1 &= ~0x10
#define P25_Quasi_Mode				    P2M0 &= ~0x20; P2M1 &= ~0x20
#define P26_Quasi_Mode				    P2M0 &= ~0x40; P2M1 &= ~0x40
#define P27_Quasi_Mode				    P2M0 &= ~0x80; P2M1 &= ~0x80

#define P30_Quasi_Mode				    P3M0 &= ~0x01; P3M1 &= ~0x01
#define P31_Quasi_Mode				    P3M0 &= ~0x02; P3M1 &= ~0x02
#define P32_Quasi_Mode				    P3M0 &= ~0x04; P3M1 &= ~0x04
#define P33_Quasi_Mode				    P3M0 &= ~0x08; P3M1 &= ~0x08
#define P34_Quasi_Mode				    P3M0 &= ~0x10; P3M1 &= ~0x10
#define P35_Quasi_Mode				    P3M0 &= ~0x20; P3M1 &= ~0x20
#define P36_Quasi_Mode				    P3M0 &= ~0x40; P3M1 &= ~0x40
#define P37_Quasi_Mode				    P3M0 &= ~0x80; P3M1 &= ~0x80
#define P54_Quasi_Mode				    P5M0 &= ~0x10; P5M1 &= ~0x10
#define P55_Quasi_Mode				    P5M0 &= ~0x20; P5M1 &= ~0x20

//------------------- 准双向带上拉  -------------------
#define P00_QuasiPU_Mode				    P0M0 &= ~0x01; P0M1 &= ~0x01; P0PU |= 0x01
#define P01_QuasiPUPU_Mode				    P0M0 &= ~0x02; P0M1 &= ~0x02; P0PU |= 0x02
#define P02_QuasiPU_Mode				    P0M0 &= ~0x04; P0M1 &= ~0x04; P0PU |= 0x04
#define P03_QuasiPU_Mode				    P0M0 &= ~0x08; P0M1 &= ~0x08; P0PU |= 0x08
#define P04_QuasiPU_Mode				    P0M0 &= ~0x10; P0M1 &= ~0x10; P0PU |= 0x10
#define P05_QuasiPU_Mode				    P0M0 &= ~0x20; P0M1 &= ~0x20; P0PU |= 0x20
#define P06_QuasiPU_Mode				    P0M0 &= ~0x40; P0M1 &= ~0x40; P0PU |= 0x40
#define P07_QuasiPU_Mode				    P0M0 &= ~0x80; P0M1 &= ~0x80; P0PU |= 0x80

#define P10_QuasiPU_Mode				    P1M0 &= ~0x01; P1M1 &= ~0x01; P1PU |= 0x01
#define P11_QuasiPU_Mode				    P1M0 &= ~0x02; P1M1 &= ~0x02; P1PU |= 0x02
#define P12_QuasiPU_Mode				    P1M0 &= ~0x04; P1M1 &= ~0x04; P1PU |= 0x04
#define P13_QuasiPU_Mode				    P1M0 &= ~0x08; P1M1 &= ~0x08; P1PU |= 0x08
#define P14_QuasiPU_Mode				    P1M0 &= ~0x10; P1M1 &= ~0x10; P1PU |= 0x10
#define P15_QuasiPU_Mode				    P1M0 &= ~0x20; P1M1 &= ~0x20; P1PU |= 0x20
#define P16_QuasiPU_Mode				    P1M0 &= ~0x40; P1M1 &= ~0x40; P1PU |= 0x40
#define P17_QuasiPU_Mode				    P1M0 &= ~0x80; P1M1 &= ~0x80; P1PU |= 0x80
 
#define P20_QuasiPU_Mode				    P2M0 &= ~0x01; P2M1 &= ~0x01; P2PU |= 0x01
#define P21_QuasiPU_Mode				    P2M0 &= ~0x02; P2M1 &= ~0x02; P2PU |= 0x02
#define P22_QuasiPU_Mode				    P2M0 &= ~0x04; P2M1 &= ~0x04; P2PU |= 0x04
#define P23_QuasiPU_Mode				    P2M0 &= ~0x08; P2M1 &= ~0x08; P2PU |= 0x08
#define P24_QuasiPU_Mode				    P2M0 &= ~0x10; P2M1 &= ~0x10; P2PU |= 0x10
#define P25_QuasiPU_Mode				    P2M0 &= ~0x20; P2M1 &= ~0x20; P2PU |= 0x20
#define P26_QuasiPU_Mode				    P2M0 &= ~0x40; P2M1 &= ~0x40; P2PU |= 0x40
#define P27_QuasiPU_Mode				    P2M0 &= ~0x80; P2M1 &= ~0x80; P2PU |= 0x80

#define P30_QuasiPU_Mode				    P3M0 &= ~0x01; P3M1 &= ~0x01; P3PU |= 0x01
#define P31_QuasiPU_Mode				    P3M0 &= ~0x02; P3M1 &= ~0x02; P3PU |= 0x02
#define P32_QuasiPU_Mode				    P3M0 &= ~0x04; P3M1 &= ~0x04; P3PU |= 0x04
#define P33_QuasiPU_Mode				    P3M0 &= ~0x08; P3M1 &= ~0x08; P3PU |= 0x08
#define P34_QuasiPU_Mode				    P3M0 &= ~0x10; P3M1 &= ~0x10; P3PU |= 0x10
#define P35_QuasiPU_Mode				    P3M0 &= ~0x20; P3M1 &= ~0x20; P3PU |= 0x20
#define P36_QuasiPU_Mode				    P3M0 &= ~0x40; P3M1 &= ~0x40; P3PU |= 0x40
#define P37_QuasiPU_Mode				    P3M0 &= ~0x80; P3M1 &= ~0x80; P3PU |= 0x80

#define P54_QuasiPU_Mode				    P5M0 &= ~0x10; P5M1 &= ~0x10; P5PU |= 0x10
#define P55_QuasiPU_Mode				    P5M0 &= ~0x20; P5M1 &= ~0x20; P5PU |= 0x20

//------------------- 推挽输出 -------------------
#define P00_PushPull_Mode			    P0M0 |= 0x01; P0M1 &= ~0x01
#define P01_PushPull_Mode			    P0M0 |= 0x02; P0M1 &= ~0x02
#define P02_PushPull_Mode			    P0M0 |= 0x04; P0M1 &= ~0x04 
#define P03_PushPull_Mode			    P0M0 |= 0x08; P0M1 &= ~0x08
#define P04_PushPull_Mode			    P0M0 |= 0x10; P0M1 &= ~0x10
#define P05_PushPull_Mode			    P0M0 |= 0x20; P0M1 &= ~0x20
#define P06_PushPull_Mode			    P0M0 |= 0x40; P0M1 &= ~0x40
#define P07_PushPull_Mode			    P0M0 |= 0x80; P0M1 &= ~0x80

#define P10_PushPull_Mode			    P1M0 |= 0x01; P1M1 &= ~0x01
#define P11_PushPull_Mode			    P1M0 |= 0x02; P1M1 &= ~0x02
#define P12_PushPull_Mode			    P1M0 |= 0x04; P1M1 &= ~0x04 
#define P13_PushPull_Mode			    P1M0 |= 0x08; P1M1 &= ~0x08
#define P14_PushPull_Mode			    P1M0 |= 0x10; P1M1 &= ~0x10
#define P15_PushPull_Mode			    P1M0 |= 0x20; P1M1 &= ~0x20
#define P16_PushPull_Mode			    P1M0 |= 0x40; P1M1 &= ~0x40
#define P17_PushPull_Mode			    P1M0 |= 0x80; P1M1 &= ~0x80
							 
#define P20_PushPull_Mode			    P2M0 |= 0x01; P2M1 &= ~0x01
#define P21_PushPull_Mode			    P2M0 |= 0x02; P2M1 &= ~0x02
#define P22_PushPull_Mode			    P2M0 |= 0x04; P2M1 &= ~0x04 
#define P23_PushPull_Mode			    P2M0 |= 0x08; P2M1 &= ~0x08
#define P24_PushPull_Mode			    P2M0 |= 0x10; P2M1 &= ~0x10
#define P25_PushPull_Mode			    P2M0 |= 0x20; P2M1 &= ~0x20
#define P26_PushPull_Mode			    P2M0 |= 0x40; P2M1 &= ~0x40
#define P27_PushPull_Mode			    P2M0 |= 0x80; P2M1 &= ~0x80

#define P30_PushPull_Mode			    P3M0 |= 0x01; P3M1 &= ~0x01
#define P31_PushPull_Mode			    P3M0 |= 0x02; P3M1 &= ~0x02
#define P32_PushPull_Mode			    P3M0 |= 0x04; P3M1 &= ~0x04 
#define P33_PushPull_Mode			    P3M0 |= 0x08; P3M1 &= ~0x08
#define P34_PushPull_Mode			    P3M0 |= 0x10; P3M1 &= ~0x10
#define P35_PushPull_Mode			    P3M0 |= 0x20; P3M1 &= ~0x20
#define P36_PushPull_Mode			    P3M0 |= 0x40; P3M1 &= ~0x40
#define P37_PushPull_Mode			    P3M0 |= 0x80; P3M1 &= ~0x80

#define P54_PushPull_Mode			    P5M0 |= 0x10; P5M1 &= ~0x10
#define P55_PushPull_Mode			    P5M0 |= 0x20; P5M1 &= ~0x20

//------------------- 高阻输入 -------------------
#define P00_Input_Mode				    P0M0 &= ~0x01; P0M1 |= 0x01
#define P01_Input_Mode				    P0M0 &= ~0x02; P0M1 |= 0x02 
#define P02_Input_Mode				    P0M0 &= ~0x04; P0M1 |= 0x04
#define P03_Input_Mode				    P0M0 &= ~0x08; P0M1 |= 0x08
#define P04_Input_Mode				    P0M0 &= ~0x10; P0M1 |= 0x10
#define P05_Input_Mode				    P0M0 &= ~0x20; P0M1 |= 0x20
#define P06_Input_Mode				    P0M0 &= ~0x40; P0M1 |= 0x40
#define P07_Input_Mode				    P0M0 &= ~0x80; P0M1 |= 0x80

#define P10_Input_Mode				    P1M0 &= ~0x01; P1M1 |= 0x01
#define P11_Input_Mode				    P1M0 &= ~0x02; P1M1 |= 0x02
#define P12_Input_Mode				    P1M0 &= ~0x04; P1M1 |= 0x04
#define P13_Input_Mode				    P1M0 &= ~0x08; P1M1 |= 0x08
#define P14_Input_Mode				    P1M0 &= ~0x10; P1M1 |= 0x10
#define P15_Input_Mode				    P1M0 &= ~0x20; P1M1 |= 0x20
#define P16_Input_Mode				    P1M0 &= ~0x40; P1M1 |= 0x40
#define P17_Input_Mode				    P1M0 &= ~0x80; P1M1 |= 0x80

#define P20_Input_Mode				    P2M0 &= ~0x01; P2M1 |= 0x01
#define P21_Input_Mode				    P2M0 &= ~0x02; P2M1 |= 0x02
#define P22_Input_Mode				    P2M0 &= ~0x04; P2M1 |= 0x04
#define P23_Input_Mode				    P2M0 &= ~0x08; P2M1 |= 0x08
#define P24_Input_Mode				    P2M0 &= ~0x10; P2M1 |= 0x10
#define P25_Input_Mode				    P2M0 &= ~0x20; P2M1 |= 0x20
#define P26_Input_Mode				    P2M0 &= ~0x40; P2M1 |= 0x40
#define P27_Input_Mode				    P2M0 &= ~0x80; P2M1 |= 0x80

#define P30_Input_Mode				    P3M0 &= ~0x01; P3M1 |= 0x01
#define P31_Input_Mode				    P3M0 &= ~0x02; P3M1 |= 0x02
#define P32_Input_Mode				    P3M0 &= ~0x04; P3M1 |= 0x04
#define P33_Input_Mode				    P3M0 &= ~0x08; P3M1 |= 0x08
#define P34_Input_Mode				    P3M0 &= ~0x10; P3M1 |= 0x10
#define P35_Input_Mode				    P3M0 &= ~0x20; P3M1 |= 0x20
#define P36_Input_Mode				    P3M0 &= ~0x40; P3M1 |= 0x40
#define P37_Input_Mode				    P3M0 &= ~0x80; P3M1 |= 0x80

#define P54_Input_Mode				    P5M0 &= ~0x10; P5M1 |= 0x10
#define P55_Input_Mode				    P5M0 &= ~0x20; P5M1 |= 0x20
//------------------- 高阻带上拉输入 -------------------
#define P00_InputPU_Mode				    P0M0 &= ~0x01; P0M1 |= 0x01; P0PU |= 0x01
#define P01_InputPU_Mode				    P0M0 &= ~0x02; P0M1 |= 0x02; P0PU |= 0x02
#define P02_InputPU_Mode				    P0M0 &= ~0x04; P0M1 |= 0x04; P0PU |= 0x04
#define P03_InputPU_Mode				    P0M0 &= ~0x08; P0M1 |= 0x08; P0PU |= 0x08
#define P04_InputPU_Mode				    P0M0 &= ~0x10; P0M1 |= 0x10; P0PU |= 0x10
#define P05_InputPU_Mode				    P0M0 &= ~0x20; P0M1 |= 0x20; P0PU |= 0x20
#define P06_InputPU_Mode				    P0M0 &= ~0x40; P0M1 |= 0x40; P0PU |= 0x40
#define P07_InputPU_Mode				    P0M0 &= ~0x80; P0M1 |= 0x80; P0PU |= 0x80

#define P10_InputPU_Mode				    P1M0 &= ~0x01; P1M1 |= 0x01; P1PU |= 0x01
#define P11_InputPU_Mode				    P1M0 &= ~0x02; P1M1 |= 0x02; P1PU |= 0x02 
#define P12_InputPU_Mode				    P1M0 &= ~0x04; P1M1 |= 0x04; P1PU |= 0x04
#define P13_InputPU_Mode				    P1M0 &= ~0x08; P1M1 |= 0x08; P1PU |= 0x08
#define P14_InputPU_Mode				    P1M0 &= ~0x10; P1M1 |= 0x10; P1PU |= 0x10
#define P15_InputPU_Mode				    P1M0 &= ~0x20; P1M1 |= 0x20; P1PU |= 0x20
#define P16_InputPU_Mode				    P1M0 &= ~0x40; P1M1 |= 0x40; P1PU |= 0x40
#define P17_InputPU_Mode				    P1M0 &= ~0x80; P1M1 |= 0x80; P1PU |= 0x80

#define P20_InputPU_Mode				    P2M0 &= ~0x01; P2M1 |= 0x01; P2PU |= 0x01
#define P21_InputPU_Mode				    P2M0 &= ~0x02; P2M1 |= 0x02; P2PU |= 0x02
#define P22_InputPU_Mode				    P2M0 &= ~0x04; P2M1 |= 0x04; P2PU |= 0x04
#define P23_InputPU_Mode				    P2M0 &= ~0x08; P2M1 |= 0x08; P2PU |= 0x08
#define P24_InputPU_Mode				    P2M0 &= ~0x10; P2M1 |= 0x10; P2PU |= 0x10
#define P25_InputPU_Mode				    P2M0 &= ~0x20; P2M1 |= 0x20; P2PU |= 0x20
#define P26_InputPU_Mode				    P2M0 &= ~0x40; P2M1 |= 0x40; P2PU |= 0x40
#define P27_InputPU_Mode				    P2M0 &= ~0x80; P2M1 |= 0x80; P2PU |= 0x80

#define P30_InputPU_Mode				    P3M0 &= ~0x01; P3M1 |= 0x01; P3PU |= 0x01
#define P31_InputPU_Mode				    P3M0 &= ~0x02; P3M1 |= 0x02; P3PU |= 0x02
#define P32_InputPU_Mode				    P3M0 &= ~0x04; P3M1 |= 0x04; P3PU |= 0x04
#define P33_InputPU_Mode				    P3M0 &= ~0x08; P3M1 |= 0x08; P3PU |= 0x08
#define P34_InputPU_Mode				    P3M0 &= ~0x10; P3M1 |= 0x10; P3PU |= 0x10
#define P35_InputPU_Mode				    P3M0 &= ~0x20; P3M1 |= 0x20; P3PU |= 0x20
#define P36_InputPU_Mode				    P3M0 &= ~0x40; P3M1 |= 0x40; P3PU |= 0x40
#define P37_InputPU_Mode				    P3M0 &= ~0x80; P3M1 |= 0x80; P3PU |= 0x80

#define P54_InputPU_Mode				    P5M0 &= ~0x10; P5M1 |= 0x10; P5PU |= 0x10
#define P55_InputPU_Mode				    P5M0 &= ~0x20; P5M1 |= 0x20; P5PU |= 0x20
//------------------- 高阻带下拉输入 -------------------
#define P00_InputPD_Mode				    P0M0 &= ~0x01; P0M1 |= 0x01; P0PD |= 0x01
#define P01_InputPD_Mode				    P0M0 &= ~0x02; P0M1 |= 0x02; P0PD |= 0x02
#define P02_InputPD_Mode				    P0M0 &= ~0x04; P0M1 |= 0x04; P0PD |= 0x04
#define P03_InputPD_Mode				    P0M0 &= ~0x08; P0M1 |= 0x08; P0PD |= 0x08
#define P04_InputPD_Mode				    P0M0 &= ~0x10; P0M1 |= 0x10; P0PD |= 0x10
#define P05_InputPD_Mode				    P0M0 &= ~0x20; P0M1 |= 0x20; P0PD |= 0x20
#define P06_InputPD_Mode				    P0M0 &= ~0x40; P0M1 |= 0x40; P0PD |= 0x40
#define P07_InputPD_Mode				    P0M0 &= ~0x80; P0M1 |= 0x80; P0PD |= 0x80

#define P10_InputPD_Mode				    P1M0 &= ~0x01; P1M1 |= 0x01; P1PD |= 0x01
#define P11_InputPD_Mode				    P1M0 &= ~0x02; P1M1 |= 0x02; P1PD |= 0x02 
#define P12_InputPD_Mode				    P1M0 &= ~0x04; P1M1 |= 0x04; P1PD |= 0x04
#define P13_InputPD_Mode				    P1M0 &= ~0x08; P1M1 |= 0x08; P1PD |= 0x08
#define P14_InputPD_Mode				    P1M0 &= ~0x10; P1M1 |= 0x10; P1PD |= 0x10
#define P15_InputPD_Mode				    P1M0 &= ~0x20; P1M1 |= 0x20; P1PD |= 0x20
#define P16_InputPD_Mode				    P1M0 &= ~0x40; P1M1 |= 0x40; P1PD |= 0x40
#define P17_InputPD_Mode				    P1M0 &= ~0x80; P1M1 |= 0x80; P1PD |= 0x80

#define P20_InputPD_Mode				    P2M0 &= ~0x01; P2M1 |= 0x01; P2PD |= 0x01
#define P21_InputPD_Mode				    P2M0 &= ~0x02; P2M1 |= 0x02; P2PD |= 0x02
#define P22_InputPD_Mode				    P2M0 &= ~0x04; P2M1 |= 0x04; P2PD |= 0x04
#define P23_InputPD_Mode				    P2M0 &= ~0x08; P2M1 |= 0x08; P2PD |= 0x08
#define P24_InputPD_Mode				    P2M0 &= ~0x10; P2M1 |= 0x10; P2PD |= 0x10
#define P25_InputPD_Mode				    P2M0 &= ~0x20; P2M1 |= 0x20; P2PD |= 0x20
#define P26_InputPD_Mode				    P2M0 &= ~0x40; P2M1 |= 0x40; P2PD |= 0x40
#define P27_InputPD_Mode				    P2M0 &= ~0x80; P2M1 |= 0x80; P2PD |= 0x80

#define P30_InputPD_Mode				    P3M0 &= ~0x01; P3M1 |= 0x01; P3PD |= 0x01
#define P31_InputPD_Mode				    P3M0 &= ~0x02; P3M1 |= 0x02; P3PD |= 0x02
#define P32_InputPD_Mode				    P3M0 &= ~0x04; P3M1 |= 0x04; P3PD |= 0x04
#define P33_InputPD_Mode				    P3M0 &= ~0x08; P3M1 |= 0x08; P3PD |= 0x08
#define P34_InputPD_Mode				    P3M0 &= ~0x10; P3M1 |= 0x10; P3PD |= 0x10
#define P35_InputPD_Mode				    P3M0 &= ~0x20; P3M1 |= 0x20; P3PD |= 0x20
#define P36_InputPD_Mode				    P3M0 &= ~0x40; P3M1 |= 0x40; P3PD |= 0x40
#define P37_InputPD_Mode				    P3M0 &= ~0x80; P3M1 |= 0x80; P3PD |= 0x80

#define P54_InputPD_Mode				    P5M0 &= ~0x10; P5M1 |= 0x10; P5PD |= 0x10
#define P55_InputPD_Mode				    P5M0 &= ~0x20; P5M1 |= 0x20; P5PD |= 0x20
//-------------------开漏输出 -------------------
#define P00_OpenDrain_Mode		    P0M0 |= 0x01; P0M1 |= 0x01
#define P01_OpenDrain_Mode		    P0M0 |= 0x02; P0M1 |= 0x02 
#define P02_OpenDrain_Mode		    P0M0 |= 0x04; P0M1 |= 0x04
#define P03_OpenDrain_Mode		    P0M0 |= 0x08; P0M1 |= 0x08
#define P04_OpenDrain_Mode		    P0M0 |= 0x10; P0M1 |= 0x10
#define P05_OpenDrain_Mode		    P0M0 |= 0x20; P0M1 |= 0x20
#define P06_OpenDrain_Mode		    P0M0 |= 0x40; P0M1 |= 0x40
#define P07_OpenDrain_Mode		    P0M0 |= 0x80; P0M1 |= 0x80
 
#define P10_OpenDrain_Mode		    P1M0 |= 0x01; P1M1 |= 0x01
#define P11_OpenDrain_Mode		    P1M0 |= 0x02; P1M1 |= 0x02 
#define P12_OpenDrain_Mode		    P1M0 |= 0x04; P1M1 |= 0x04
#define P13_OpenDrain_Mode		    P1M0 |= 0x08; P1M1 |= 0x08
#define P14_OpenDrain_Mode		    P1M0 |= 0x10; P1M1 |= 0x10
#define P15_OpenDrain_Mode		    P1M0 |= 0x20; P1M1 |= 0x20
#define P16_OpenDrain_Mode		    P1M0 |= 0x40; P1M1 |= 0x40
#define P17_OpenDrain_Mode		    P1M0 |= 0x80; P1M1 |= 0x80

#define P20_OpenDrain_Mode		    P2M0 |= 0x01; P2M1 |= 0x01
#define P21_OpenDrain_Mode		    P2M0 |= 0x02; P2M1 |= 0x02 
#define P22_OpenDrain_Mode		    P2M0 |= 0x04; P2M1 |= 0x04
#define P23_OpenDrain_Mode		    P2M0 |= 0x08; P2M1 |= 0x08
#define P24_OpenDrain_Mode		    P2M0 |= 0x10; P2M1 |= 0x10
#define P25_OpenDrain_Mode		    P2M0 |= 0x20; P2M1 |= 0x20
#define P26_OpenDrain_Mode		    P2M0 |= 0x40; P2M1 |= 0x40
#define P27_OpenDrain_Mode		    P2M0 |= 0x80; P2M1 |= 0x80

#define P30_OpenDrain_Mode		    P3M0 |= 0x01; P3M1 |= 0x01
#define P31_OpenDrain_Mode		    P3M0 |= 0x02; P3M1 |= 0x02 
#define P32_OpenDrain_Mode		    P3M0 |= 0x04; P3M1 |= 0x04
#define P33_OpenDrain_Mode		    P3M0 |= 0x08; P3M1 |= 0x08
#define P34_OpenDrain_Mode		    P3M0 |= 0x10; P3M1 |= 0x10
#define P35_OpenDrain_Mode		    P3M0 |= 0x20; P3M1 |= 0x20
#define P36_OpenDrain_Mode		    P3M0 |= 0x40; P3M1 |= 0x40
#define P37_OpenDrain_Mode		    P3M0 |= 0x80; P3M1 |= 0x80

#define P54_OpenDrain_Mode		    P5M0 |= 0x10; P5M1 |= 0x10
#define P55_OpenDrain_Mode		    P5M0 |= 0x20; P5M1 |= 0x20



void Gpio_init( void );

#endif

