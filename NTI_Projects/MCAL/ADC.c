
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "ADC_Interfaceh.h"

/******adc_read_asynch*********/
static void(* Adc_Fptr)(void)=NULL_PTR;

/******************************/
void ADC_voidDisable(void)
{
	CLR_BIT(ADCSRA,ADEN);
}

void ADC_voidEnable(void)
{
	SET_BIT(ADCSRA,ADEN);
}

void ADC_voidInterrputEnable(void)
{
	SET_BIT(ADCSRA,ADIE);
}

void ADC_voidInterrputDisable(void)
{
	CLR_BIT(ADCSRA,ADIE);
}

void ADC_voidStartConversion(ADC_Channel_type ch)
{
	/* set channel mux*/
	ADMUX &=0xE0;
	ch &=0x07;
	ADMUX|=ch;
	
	/*start conversion*/
	
	SET_BIT(ADCSRA,ADSC);
}
#if ADC_MODE==Free_Running_Mode
void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler)
{
	/********vref*****/
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break ;
		case VREF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break ;
		case VREF_256V:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break ;
	}
	
	/***********prescaler***********/
	
	ADCSRA &=0xf8;
	scaler &=0x07;
	ADCSRA |=scaler;
	
	SET_BIT(ADCSRA,ADATE);
	
	ADC_voidEnable();
	ADC_voidInterrputEnable();

	
	
}

#else
void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler)
{
	/********vref*****/
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break ;
		case VREF_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break ;
		case VREF_256V:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break ;
	}
	
	/***********prescaler***********/
	
	ADCSRA &=0xf8;
	scaler &=0x07;
	ADCSRA |=scaler;
	

	ADC_voidEnable();
	
	
}
#endif

u16 ADC_16ReadADC(void)
{
	//u16 r;
	/* w8 ADC finish**/
	
	#if ADC_MODE==Free_Running_Mode
	return ADC;
	#else
	while(READ_BIT(ADCSRA,ADSC));
	/*get read*/
	//CLR_BIT(ADMUX,ADLAR);
	//r=ADCL + (READ_BIT(ADCH,0)*256)+(READ_BIT(ADCH,1)*512);
	return ADC;
	#endif
}


void ADC_SetCallback( void (*local_fptr) (void) )
{
	Adc_Fptr=local_fptr;
}

void ADC_Chain(ADC_Channel_type ch)
{
	ADC_voidStartConversion(ch);
}

ISR(ADC_vect)
{
	if (Adc_Fptr!=NULL_PTR)
	{
		Adc_Fptr();
	}
	
}

/*u8 ADC_Read_Asynchoronus(u16* adc_ptr,ADC_Channel_type ch)
{
if(flag_adc)
{
*adc_ptr=Adc_Read_Asynch;
return 1;
}
return 0;
}



void ADC_SC(ADC_Channel_type ch)
{
//u16 r;
// set channel mux*
ADMUX &=0xE0;
ch &=0x07;
ADMUX|=ch;

//flag asychyn*******
flag_adc=0;

//adc interrupt enable /
SET_BIT(ADCSRA,ADIE);

/start conversion/
SET_BIT(ADCSRA,ADSC);
}

//adc start conversion *******************
ISR (ADC_vect)
{
flag_adc=1;
Adc_Read_Asynch=ADC;
CLR_BIT(ADCSRA,ADIE);
}

*/