#ifndef	__PUMPDET_APP_H
#define	__PUMPDET_APP_H


extern uint8 xdata PUMPDET_FSM;
extern uint8 xdata Leakage;
extern uint8 xdata PT;
extern uint8 xdata Err_Flag;
extern uint8 xdata Finish_Flag;
extern uint8 xdata Time_Flag;
extern uint8 xdata LK_Flag;
extern uint16 xdata WorkI;
extern uint16 xdata Steady_30s;
extern uint16 xdata ST1;
extern uint16 xdata ST2;
extern uint16 xdata ST3;
//void Delay_10us(uint32 i);
////void Delay1000ms()	;
//void First_IO_Init(void);
//void Second_IO_Init(void);
void System_Init(void);
void PUMPDET_Process(void);


    
#endif					   
