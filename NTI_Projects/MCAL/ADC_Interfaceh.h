


#ifndef ADC_INTERFACEH_H_
#define ADC_INTERFACEH_H_


#define ADC_MODE Free_Running_Mode
#define Free_Running_Mode 1
#define Single_Conversion_Mode 0
#define ADC_R ADC



typedef enum{
	VREF_AREF,
	VREF_AVCC,
	VREF_256V
}ADC_VoltRef_type;
typedef enum{
	ADC_SCALER_2=1, // as zero is = to 2 also 
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128,
}ADC_Prescaler_type;
typedef enum{
	CH_0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
}ADC_Channel_type;

void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler);

void ADC_voidEnable(void);

void ADC_voidInterrputEnable(void);

void ADC_voidInterrputDisable(void);

void ADC_voidDisable(void);

u16 ADC_16ReadADC(void);

void ADC_voidStartConversion(ADC_Channel_type ch);

void ADC_SetCallback( void (*ptr) (void) );

void ADC_Chain(ADC_Channel_type ch);

void ADC_SetChannel(ADC_Channel_type ch);


#endif /* ADC_INTERFACEH_H_ */