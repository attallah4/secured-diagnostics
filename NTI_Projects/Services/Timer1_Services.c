
#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#include "TIMER1_Interface.h"
#include "Timer1_Services.h"



volatile u8 flag=0;
volatile u16 t1=0;
volatile u16 t2=0;
volatile u16 t3=0;




void PWM_HW_Init(void)
{
	Timer1_Init(TIMER1_NORMAL_MODE);
	Timer1_Start(TIMER1_SCALER_64);
	//Timer1_OCRA1Mode(OCRA_NON_INVERTING);	
	
}

/*
void PWM_Measure_SW(u32* Pfreq,u8* Pduty)
{
	u16 Ton,Toff;
	flag=0;
	TCNT1=0;
	while (DIO_ReadPin(PIND6));
	while (!DIO_ReadPin(PIND6));
	TCNT1=0;
	while (DIO_ReadPin(PIND6));
	Ton=TCNT1;
	TCNT1=0;
	while (!DIO_ReadPin(PIND6));
	Toff=TCNT1;
	*Pduty=((u32)Ton*100)/(Ton+Toff);
	*Pfreq=((u32)FREQ_CPU/SCALER_FOR_PWM)/((u32)Toff+Ton);
}
*/
static void Func_ICU(void);
void PWM_Measure_HW(u32* Pfreq,u8* Pduty)
{
	u16 Ton,Toff;
	//TCNT1=0;
	Timer1_ICU_SetCallBack(Func_ICU);
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_InterruptEnable();
	flag=0;
	while(flag<3);
	
	if (flag==3)
	{
			
		Ton=t2-t1;//+c*65535
		Toff=t3-t2;

		*Pduty=((u32)Ton*100)/((u32)Ton+Toff);
		*Pfreq=((u32)FREQ_CPU/SCALER_FOR_PWM)/((u32)Toff+Ton);
	}
}
static void Func_ICU(void)
{
	if (flag==0)
	{
		t1=ICR1;
		Timer1_InputCaptureEdge(FALLING);
		flag=1;
	}
	else if (flag==1)
	{
		t2=ICR1;
		Timer1_InputCaptureEdge(RISING);
		flag=2;
	}
	else if (flag==2)
	{
		t3=ICR1;
		Timer1_ICU_InterruptDisable();
		flag=3;
		
	}

}