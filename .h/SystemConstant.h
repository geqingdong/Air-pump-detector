#ifndef _CONSTANT_H
#define _CONSTANT_H

#define uint8   unsigned char
#define uint16  unsigned int
#define uint32  unsigned long int


#define Enable 		1
#define Disable 	0
#define ON 			1
#define OFF		 	0

#define	TIME_VALUE_20MS         19
#define TIME_DISPLAY            20

#define AD_OFFSET				0x80

#define LCD_RAM_SIZE		    18	

#define LCD_ALL_ON              0x00
#define LCD_ALL_OFF             0x01
#define LCD_BD_SHOW             0x02
#define LCD_ERR                 0x03
#define LCD_SET                 0x04
#define LCD_LR                  0x05
#define LCD_VIEW                0x06

#define PUMP 						  P07       //充气泵
#define EMV  							P06       //电磁阀

#define GAS  						  P00       //气路切换
#define CH6V  						P31       //6V电源切换
#define CH3V7  						P30       //3V7电源切换

#define KEY_SET		        P12	      //按键 设置
#define KEY_ADD			      P13       //按键 增
#define KEY_SUB			      P14	      //按键 减

#define BL_LED4					P22	            //背光控制LED4
#define BL_LED3					P23	            //背光控制LED3
#define BL_LED2					P50	            //背光控制LED2
#define BL_LED1					P51	            //背光控制LED1

#define LED1					P57	            //低气压不良
#define LED2					P56	            //电流不良
#define LED3					P55	            //气密不良


#endif




