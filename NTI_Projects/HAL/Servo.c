#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#include "TIMER1_Interface.h"
#include "Servo_Interface.h"




void Servo_Init(void)
{
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE);
	Timer1_Start(TIMER1_SCALER_64);
	Timer1_OCRB1Mode(OCRA_NON_INVERTING);
	ICR1=4999;
}


void Servo_getAngel(u8 angel)
{
	SERVO_PWM_REG=((((angel*(u32)250)+90)/180)+249);
}