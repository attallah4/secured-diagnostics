/*
 * Timer1_Services.h
 *
 * Created: 28/10/2023 13:38:51
 *  Author: Alahram
 */ 


#ifndef TIMER1_SERVICES_H_
#define TIMER1_SERVICES_H_

#define SCALER_FOR_PWM 64

#define FREQ_CPU	16000000

void PWM_Measure_HW(u32* Pfreq,u8* Pduty);

void PWM_Measure_SW(u32* Pfreq,u8* Pduty);

void PWM_HW_Init(void);



#endif /* TIMER1_SERVICES_H_ */