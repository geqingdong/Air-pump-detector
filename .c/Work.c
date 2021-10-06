#include <SZC909.H>
#include "SystemConstant.h"
#include "PUMPDET_Lcd.h"
#include "PUMPDET_Timer.h"
#include "PUMPDET_ADC.h"
#include "PUMPDET_Work.h"
#include "PUMPDET_Key.h"

uint8 xdata PUMPDET_FSM;
uint8 xdata Leakage;
uint8 xdata PT=0;
uint8 xdata Err_Flag=0;
uint8 xdata Finish_Flag=0;
uint8 xdata Time_Flag=0;
uint8 xdata LK_Flag=0;
uint8 xdata offset_flag=0;
uint16 xdata WorkI;
uint16 xdata offset=0;
uint16 xdata Steady_30s;
uint16 xdata ST1=0;
uint16 xdata ST2=0;
uint16 xdata ST3=0;

//抓0函数
void GetZero()
{
	if(PADC_Temp>60000)
	{
		offset_flag=1;
		offset=65536-PADC_Temp;
	}
	else 
	{
		offset_flag=2;
		offset=PADC_Temp-0;
	}
}



//气泵进程函数
void PUMPDET_Process(void)
{
switch(PUMPDET_FSM)
{
case 0x00:              
{
	if(offset_flag==0)
	{
		GetZero();
	}
	while(offset_flag == 0);
//	Green_BackLight_Contrl(1);	
	LCD_Mode = LCD_ALL_OFF;
	PUMPDET_FSM = 0x10;
//	Exit_Normal_Mode_Check();
break;
}

case 0x01:              
{
	WTime = 0;
	Leakage = 0;
	WorkI =0;
	Time_Flag=0;
  LK_Flag=0;
	ST1=ST2=ST3=0;
	LCD_Mode = LCD_BD_SHOW;
	Green_BackLight_Contrl(1);	
	PUMPDET_FSM = 0x02;
//  Exit_Normal_Mode_Check();
break;
}

case 0x02:              
{	
	if(Pout() == 0)
	{	
	EMV=1;
	PUMP=1;
	PT=1;
	PUMPDET_FSM = 0x03;
	}
//	Exit_Normal_Mode_Check();
break;
}

case 0x03:
{	


	ST1=WTime;
	if((Pout() >= 300)||((WTime*10/1000) > InflationTime_set))
	{
		Delay_10ms(80);
		if((Pout() >= 300)||((WTime*10/1000) > InflationTime_set))
	{
		WorkI=Iout();
		PT=0;
		PUMP=0;
//		ST1=WTime;
		Time_Flag=1;

//		InflationTime_display();
	  if(((WTime*10/1000) < InflationTime_set)||(((WTime*10/1000) == InflationTime_set)&&((WTime*10/100%10) == 0)))
	   {
//			 Green_BackLight_Contrl(1);				
	     PUMPDET_FSM = 0x04;
//       RTime = 3000;
			 WTime=0;
	   }
		 else 
		 {
			EMV = 0;
      LCD_Mode = LCD_ALL_OFF;
			Err_Flag = 1; 
			PUMPDET_FSM = 0x08;
		 }
		 if(WorkI > WorkI_set)
		{
			EMV = 0;
      LCD_Mode = LCD_ALL_OFF;
			Err_Flag = 2; 
			PUMPDET_FSM = 0x08;
		}
	 }
	}
	Exit_Normal_Mode_Check();
break;

}

case 0x04:
{	
//  PUMP=0;
	PT=1;
	ST2=WTime;
//	InflationTime_display();

	if(Pout()<280)
	 {
		 EMV=0;
		 Err_Flag = 5;
		 LCD_Mode = LCD_ALL_OFF;	
		 PUMPDET_FSM = 0x08;
	 }
	
	if(ST2 >= 3000)
	{						
	PUMPDET_FSM = 0x05;
	Steady_30s=Pout();
//	RTime = 6000; 
	WTime=0;
	PT=0;
	}
	Exit_Normal_Mode_Check();
break;
}

case 0x05:                                  
{ 
	PT=1;
	ST3=WTime;
	if(Steady_30s>=Pout())Leakage=Steady_30s-Pout();
	if(ST3 >= 6000|| Leakage>Leakage_set)
	{ 
		LK_Flag=1;
		WTime=0;
	  PT=0;
//	LCD_Mode = LCD_ALL_OFF;
	PUMPDET_FSM = 0x06; 					
	}
	Exit_Normal_Mode_Check();
break;
}

case 0x06:
{
//  Leakage=Steady_30s-out();
  if(Steady_30s>=Pout())Leakage=Steady_30s-Pout();
	LK_Flag=1;
	LCD_Mode = LCD_LR;
//	Leakage_display();	
  EMV=0;
	if(Leakage <= Leakage_set)
	{
//		Green_BackLight_Contrl(1);
//    Finish_Flag = 1;
		ClearDisplay();
//		View_Con=1;
		PUMPDET_FSM = 0x11;
	}	
	else
	{
	 EMV=0;
	 Err_Flag = 3;
   LCD_Mode = LCD_ALL_OFF;	
	 PUMPDET_FSM = 0x08;
	}
	Exit_Normal_Mode_Check();
break;
}

case 0x07:
{
//  if(RTime == 0)
//	{
//	Finish_Flag = 1;
//	PUMPDET_FSM = 0x10;
//	}
//	Exit_Normal_Mode_Check();
break;
}

case 0x08:
{
  Green_BackLight_Contrl(0);	
	Red_BackLight_Contrl(1);
  LCD_Mode = LCD_ERR;
	PT=0;
  Finish_Flag = 1;
	PUMPDET_FSM = 0x10;
	Exit_Normal_Mode_Check();
break;
}

case 0x09:
{ 
  Orange_BackLight_Contrl(1);
	LCD_Mode = LCD_SET;
	Key_Scan();
	Key_Set();
	if(Set_Con == 0)
	{
	 Orange_BackLight_Contrl(0);
	 ClearDisplay();
	 PUMPDET_FSM = 0x10;
	}
break;
}

case 0x10:
{
	if(LKEY_Scan()==1)
	{
		if(Finish_Flag)
		{		
			Finish_Flag=0;
//			View_Con = 1;
			LCD_Mode = LCD_ALL_OFF;	
			PUMPDET_FSM = 0x11;
		}
		else
		{
//			LCD_Init();
			LCD_Mode = LCD_ALL_OFF;	
			PUMPDET_FSM = 0x01;
		}
	}
	else if(LKEY_Scan()==2)
	{
//		LCD_Init();
		LCD_Mode = LCD_ALL_OFF;	
		PUMPDET_FSM = 0x09;
	}
break;
}	

case 0x11:
{
	LCD_Mode = LCD_VIEW;

	Exit_Normal_Mode_Check();
break;
}

}
}
	

