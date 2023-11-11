#include "stdtypes.h"
#include "ADC_Interfaceh.h"
#include "Sensors_Cfg.h"
#include "Sensors_Interface.h"


s16 Interpolation(s16 x1,s16 x2,s16 y1,s16 y2,s16 x)
{
	u16 y;
	s16 xdiff=x2-x1;
	s16 ydiff=y2-y1;
	
	y=(((((((s32)ydiff*(x-x1)))+.5*xdiff)/xdiff))+y1);
	return y;
}

u16 Temp_Read(void)
{
	u16 adc, temp;
	adc=ADC_16ReadADC();
	//temp=((adc*(u32)150)+512)/1024;//c (Temp ->adc)//vref 1.5v
	temp=((adc*(u32)1500))/308;//c (Temp ->adc)//vref 5v
	
	return temp;
}

