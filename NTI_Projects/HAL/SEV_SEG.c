#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "DIO_Interface.h"
#include "SEV_SEG_Interface.h"
#define F_CPU 16000000
#include <util/delay.h>


void Enable_7seg(SEG_PIN seg)
{
	switch(seg)
	{
		case SEG1 :
		DIO_WritePin(PINA3,LOW);
		DIO_WritePin(PINA2,HIGH);
		DIO_WritePin(PINB5,HIGH);
		DIO_WritePin(PINB6,HIGH);
		break;
		
		case SEG10 :
		DIO_WritePin(PINA3,HIGH);
		DIO_WritePin(PINA2,LOW);
		DIO_WritePin(PINB5,HIGH);
		DIO_WritePin(PINB6,HIGH);
		break;
		
		case SEG100 :
		DIO_WritePin(PINA3,HIGH);
		DIO_WritePin(PINA2,HIGH);
		DIO_WritePin(PINB5,LOW);
		DIO_WritePin(PINB6,HIGH);
		break;
		
		case SEG1000 :
		DIO_WritePin(PINA3,HIGH);
		DIO_WritePin(PINA2,HIGH);
		DIO_WritePin(PINB5,HIGH);
		DIO_WritePin(PINB6,LOW);
		break;
		
	}
}



void Segment_display(u16 num)
{
	u8 d0=  num%10;
	u8 d1 = (num/10)%10;
	u8 d2 = (num/100)%10;
	u8 d3 = (num/1000)%10;
	
	Enable_7seg(SEG1);
	DIO_WritePin(PINB4,READ_BIT(d0,3));
	d0&=0x07;
	SEVSEG&=0xf8;
	SEVSEG|=d0;
	_delay_ms(5);
	
	Enable_7seg(SEG10);
	DIO_WritePin(PINB4,READ_BIT(d1,3));
	d1&=0x07;
	SEVSEG&=0xf8;
	SEVSEG|=d1;
	_delay_ms(5);
	
	Enable_7seg(SEG100);
	DIO_WritePin(PINB4,READ_BIT(d2,3));
	d2&=0x07;
	SEVSEG&=0xf8;
	SEVSEG|=d2;
	_delay_ms(5);
	
	Enable_7seg(SEG1000);
	DIO_WritePin(PINB4,READ_BIT(d3,3));
	d3&=0x07;
	SEVSEG&=0xf8;
	SEVSEG|=d3;
	_delay_ms(5);
}