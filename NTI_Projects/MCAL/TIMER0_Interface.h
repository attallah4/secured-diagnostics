


#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_



typedef enum{
	TIMER0_STOP=0,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	EXTERNALl_FALLING,
	EXTERNAL_RISING
}Timer0Scaler_type;

typedef enum
{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE

}Timer0Mode_type;


typedef enum
{
	OC0_DISCONNECTED=0,
	OC0_TOGGLE,
	OC0_NON_INVERTING,
	OC0_INVERTING

}OC0Mode_type;

void TIMER0_Init(Timer0Mode_type mode);

void TIMER0_Stop(void);

void TIMER0_Start(Timer0Scaler_type scaler);

void TIMER0_OC0Mode(OC0Mode_type mode);

void TIMER0_OV_InterruptEnable(void);

void TIMER0_OV_InterruptDisable(void);

void TIMER0_OC_InterruptEnable(void);

void TIMER0_OC_InterruptDisable(void);

void TIMER0_OV_SetCallBack(void(*local_fptr)(void));

void TIMER0_OC_SetCallBack(void(*local_fptr)(void));


#endif /* TIMER0_INTERFACE_H_ */