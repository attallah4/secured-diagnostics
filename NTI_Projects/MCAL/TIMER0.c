
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "TIMER0_Interface.h"


static void (*Timer0_OVF_Fptr) (void)=NULL_PTR;
static void (*Timer0_OC_Fptr )(void)=NULL_PTR;

/*timer 0 functions*/
void TIMER0_Init(Timer0Mode_type mode)
{
	switch (mode)
	{
		case TIMER0_NORMAL_MODE:
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_PHASECORRECT_MODE:
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_CTC_MODE:
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
		case TIMER0_FASTPWM_MODE:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	}
	
}

void TIMER0_Start(Timer0Scaler_type scaler)
{
	TCCR0&=0XF8;//0b11111000
	TCCR0|=scaler;
}

void TIMER0_Stop(void)
{
	TCCR0&=0XF8;//0b11111000
}
/*
void TIMER0_OC0Mode(OC0Mode_type mode)
{
switch (mode)
{
case OC0_DISCONNECTED:
CLR_BIT(TCCR0,COM00);
CLR_BIT(TCCR0,COM01);
break;
case OC0_TOGGLE:
SET_BIT(TCCR0,COM00);
CLR_BIT(TCCR0,COM01);
break;
case OC0_NON_INVERTING:
CLR_BIT(TCCR0,COM00);
SET_BIT(TCCR0,COM01);
break;
case OC0_INVERTING:
SET_BIT(TCCR0,COM00);
SET_BIT(TCCR0,COM01);
break;
}
}
*/
void TIMER0_OV_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE0);
}
void TIMER0_OV_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE0);
}
void TIMER0_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE0);
}
void TIMER0_OC_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE0);
}

void TIMER0_OV_SetCallBack(void(*local_fptr)(void))
{
	Timer0_OVF_Fptr=local_fptr;
}
void TIMER0_OC_SetCallBack(void(*local_fptr)(void))
{
	Timer0_OC_Fptr=local_fptr;
}

/*************************************************************************/

/*************************TIMER0 ISR*************************************/

ISR(TIMER0_OVF_vect)
{
	if (Timer0_OVF_Fptr!=NULL_PTR)
	{
		Timer0_OVF_Fptr();
	}
}

ISR(TIMER0_OC_vect)
{
	if (Timer0_OC_Fptr!=NULL_PTR)
	{
		Timer0_OC_Fptr();
	}
}


/**********************************timer1 functions*********************/



/***********************************************************************/