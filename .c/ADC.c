#include <SZC909.H>
#include "SystemConstant.h"
#include "PUMPDET_Lcd.h"
#include "PUMPDET_Timer.h"
#include "PUMPDET_ADC.h"
#include "PUMPDET_Work.h"
#include "PUMPDET_Key.h"

#define N 31
#define M 7

uint16 xdata PADC_Temp;
uint16 xdata IADC_Temp;

//void ADC_Meas_CH1_Init(void)
//{
//  ADCM1 &= 0xFE;				//Disable ADC			
//	VREG = 0xD8;				//Enable Band Gap & AVDDR & ACM + AVDDR = 3.3v + Charge pump clock = 500k Hz + Charge pump mode = Disable Mode
//	AMPM = 0x23;				//Disable GX Buf + PGIA chopper clock = 7.8kHz(/32) + PGIA Gain = x1 + Enable PGIA Chopper & PGIA 	
//	ADCM1= 0x56;				//Disable GR Buf + Vref = 0.99v + ADC Gain x1 + OP1/OP2 Chopper Enable + "Disable ADC	"(last enable)
//	ADCM2= 0x14;				//ADC Clock = 250kHz + OSR = 1953(2k)Hz(250k/128) + DRDY flag clear
//	CHS	 = 0x0C;				//AIN1 + AVSS	
//	
//	ADCM1 |= 0x01;			    //Enable ADC	
//}

//void ADC_Meas_CH2_Init(void)
//{
//	ADCM1 &= 0xFE;				//Disable ADC			
//	VREG = 0xD8;				//Enable Band Gap & AVDDR & ACM + AVDDR = 3.3v + Charge pump clock = 500k Hz + Charge pump mode = Disable Mode
//	AMPM = 0x23;				//Disable GX Buf + PGIA chopper clock = 7.8kHz(/32) + PGIA Gain = x1 + Enable PGIA Chopper & PGIA 	
//	ADCM1= 0x56;				//Disable GR Buf + Vref = 0.99v + ADC Gain x1 + OP1/OP2 Chopper Enable + "Disable ADC	"(last enable)
//	ADCM2= 0x14;				//ADC Clock = 250kHz + OSR = 1953(2k)Hz(250k/128) + DRDY flag clear
//	CHS	 = 0x1C;				//AIN2 + AVSS	

//	ADCM1 |= 0x01;			    //Enable ADC
//}

//void ADC_Meas_CH4_Init(void)
//{
//	ADCM1 &= 0xFE;				//Disable ADC			
//	VREG = 0xD8;				//Enable Band Gap & AVDDR & ACM + AVDDR = 3.3v + Charge pump clock = 500k Hz + Charge pump mode = Disable Mode
//	AMPM = 0x23;				//Disable GX Buf + PGIA chopper clock = 7.8kHz(/32) + PGIA Gain = x1 + Enable PGIA Chopper & PGIA 	
//	ADCM1= 0x56;				//Disable GR Buf + Vref = 0.99v + ADC Gain x1 + OP1/OP2 Chopper Enable + "Disable ADC	"(last enable)
//	ADCM2= 0x14;				//ADC Clock = 250kHz + OSR = 1953(2k)Hz(250k/128) + DRDY flag clear
//	CHS	 = 0x3C;				//AIN4 + AVSS	
//	
//	ADCM1 |= 0x01;			    //Enable ADC	
//}

//void ADC_Meas_CH7_Init(void)
//{
//	ADCM1 &= 0xFE;				//Disable ADC			
//	VREG = 0xD8;				//Enable Band Gap & AVDDR & ACM + AVDDR = 3.3v + Charge pump clock = 500k Hz + Charge pump mode = Disable Mode
//	AMPM = 0x23;				//Disable GX Buf + PGIA chopper clock = 7.8kHz(/32) + PGIA Gain = x1 + Enable PGIA Chopper & PGIA 	
//	ADCM1= 0x56;				//Disable GR Buf + Vref = 0.99v + ADC Gain x1 + OP1/OP2 Chopper Enable + "Disable ADC	"(last enable)
//	ADCM2= 0x14;				//ADC Clock = 250kHz + OSR = 1953(2k)Hz(250k/128) + DRDY flag clear
//	CHS	 = 0x6C;				//AIN7 + AVSS	
//    
//    OPM = 0x01;
//	
//	ADCM1 |= 0x01;			    //Enable ADC	
//}

//void ADC_Meas_CH3_Init(void)
//{
//  ADCM1 &= 0xFE;				//Disable ADC			
//	VREG = 0xD8;				//Enable Band Gap & AVDDR & ACM + AVDDR = 3.3v + Charge pump clock = 500k Hz + Charge pump mode = Disable Mode
//	AMPM = 0x23;				//Disable GX Buf + PGIA chopper clock = 7.8kHz(/32) + PGIA Gain = x1 + Enable PGIA Chopper & PGIA 	
//	ADCM1= 0x56;				//Disable GR Buf + Vref = 0.99v + ADC Gain x1 + OP1/OP2 Chopper Enable + "Disable ADC	"(last enable)
//	ADCM2= 0x14;				//ADC Clock = 250kHz + OSR = 1953(2k)Hz(250k/128) + DRDY flag clear
//	CHS	 = 0x2C;				//AIN1 + AVSS	
//	
//	ADCM1 |= 0x01;			    //Enable ADC	
//}

//ADC工作初始化函数
void ADC_WorkI_Init(void)
{
	ADCM1 &= 0xFE;				//Disable ADC			
	VREG = 0xD8;				//Enable Band Gap & AVDDR & ACM + AVDDR = 3.3v + Charge pump clock = 500k Hz + Charge pump mode = Disable Mode
	AMPM = 0xA0;				//Disable GX Buf + PGIA chopper clock = 7.8kHz(/32) + PGIA Gain = x1 + Enable PGIA Chopper & PGIA 	
	ADCM1= 0x76;				//Disable GR Buf + Vref = 0.99v + ADC Gain x1 + OP1/OP2 Chopper Enable + "Disable ADC	"(last enable)
	ADCM2= 0x14;				//ADC Clock = 250kHz + OSR = 1953(2k)Hz(250k/128) + DRDY flag clear
	CHS	 = 0x3C;				//AIN4 + AVSS	  

	ADCM1 |= 0x01;			    //Enable ADC
}


void ADC_SENSOR_Init(void)
{
	ADCM1 &= 0xFE;				//Disable ADC			
	VREG = 0xD8;				//Enable Band Gap & AVDDR & ACM + AVDDR = 3.3v + Charge pump clock = 500k Hz + Charge pump mode = Disable Mode
	AMPM = 0xA0;				//Disable GX Buf + PGIA chopper clock = 7.8kHz(/32) + PGIA Gain = x1 + Enable PGIA Chopper & PGIA 	
	ADCM1= 0x56;				//Disable GR Buf + Vref = 0.99v + ADC Gain x1 + OP1/OP2 Chopper Enable + "Disable ADC	"(last enable)
	ADCM2= 0x14;				//ADC Clock = 250kHz + OSR = 1953(2k)Hz(250k/128) + DRDY flag clear
	CHS	 = 0x10;				//AIN2 + AIN1
	OPM  = 0x01;   
	
	ADCM1 |= 0x01;			    //Enable ADC
}

//读气泵ADC的值
void Read_PUMP_ADC_Data(void)
{

	if(ADCM2 & 0x01)
	{	
			ADCM2 &=  0xFE;

			PADC_Temp = ADCDH;							
			PADC_Temp = PADC_Temp<<8;
			PADC_Temp = PADC_Temp+ADCDM;
//			if(offset_flag == 1)ADC_Temp = (ADC_Temp+offset);
//		  if(offset_flag == 2)ADC_Temp = (ADC_Temp-offset+2);
			if(offset_flag == 1)PADC_Temp = 0.2414*(PADC_Temp+offset+1);
		  if(offset_flag == 2)PADC_Temp = 0.2414*(PADC_Temp-offset+1);
    }
}

void Read_WorkI_ADC_Data(void)
{

	if(ADCM2 & 0x01)
	{	
			ADCM2 &=  0xFE;

			IADC_Temp = ADCDH;							
			IADC_Temp = IADC_Temp<<8;
			IADC_Temp = IADC_Temp+ADCDM;		
      IADC_Temp = 0.028619303692962752*IADC_Temp+1.4417072716699422;
//		  IADC_Temp = 0.02860368872010968*IADC_Temp+1.829647405385935	;																		

    }
}

void Read_PI_ADC_Data(void)
{
	ADC_SENSOR_Init();
	Delay_10ms(1);
	Read_PUMP_ADC_Data();
	ADC_WorkI_Init();
	Delay_10ms(1);
	Read_WorkI_ADC_Data();
}

unsigned  int Pout( void )    
{  
	static unsigned int value_buf[N];  
	static unsigned int count,i,j,temp;  
	for ( count=0;count<N;count++)  
	{  
			value_buf[count] = PADC_Temp;  
			
	}  
	for (j=0;j<N-1;j++)  
	{  
			for (i=0;i<N-j;i++)  
			{  
				if ( value_buf[i]>value_buf[i+1] )  
				{  
						temp = value_buf[i];  
						value_buf[i]= value_buf[i+1];   
						value_buf[i+1] = temp;  
				}  
			}  
	}  
	if(value_buf[(N-1)/2] >= 15000 ) return 0;
	return value_buf[(N-1)/2];  
}  

unsigned  int Iout( void )    
{  
	static unsigned int value_buf[M];  
	static unsigned int count,i,j,temp;  
	for ( count=0;count<M;count++)  
	{  
		  value_buf[count] = IADC_Temp;  
			
	}  
	for (j=0;j<M-1;j++)  
	{  
			for (i=0;i<M-j;i++)  
			{  
				if ( value_buf[i]>value_buf[i+1] )  
				{  
						temp = value_buf[i];  
						value_buf[i]= value_buf[i+1];   
						value_buf[i+1] = temp;  
				}  
			}  
	}  
	 
	if(value_buf[(M-1)/2] <= 5) return 0;
	else return value_buf[(M-1)/2]; 
}  
	




