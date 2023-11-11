


#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_Cfg.h"
#include "LCD_Interface.h"





#if LCD_8_BIT ==1
static void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
void LCD_Init(void)
{
	_delay_ms(35);
	WriteIns(0x38);// set function
	WriteIns(0x08);//0x0c  , 0x0e  courser enable
	WriteIns(0x01);//clear
	_delay_ms(1);
	WriteIns(0x06);
}
#else
static void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
void LCD_Init(void)
{
	_delay_ms(35);
	WriteIns(0x02);// set function
	WriteIns(0x28);
	WriteIns(0x0c);//0x0c  , 0x0e  cursor enable
	WriteIns(0x01);//clear
	_delay_ms(1);
	WriteIns(0x06);
}
#endif

void LCD_GoTo(u8 line,u8 cell)
{
	if (line ==1)
	{
		WriteIns(0x80+cell);

	}
	else if (line==2)
	{
		WriteIns(0xc0+cell);
	}
	else if (line==3)
	{
		WriteIns(0x94+cell);
	}
	else if (line==4)
	{
		WriteIns(0xd4+cell);
	}
	
}

void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}

void LCD_WriteString(c8* str)
{
	u8 i=0;
	for (i=0;str[i];i++)
	{
		WriteData(str[i]);
	}
}


void LCD_WriteNumber(u32 num)
{
	u8 str[10],i;
	
	
	if (num==0)
	{
		LCD_WriteChar('0');
	}
	else if (num<0)
	{
		LCD_WriteChar('-');
		num = num*-1;
	}
	
	for (i=0;num>0;i++)
	{
		str[i] = ((num%10)+'0');
		num = num/10;
	}
	for (i=i-1;i!=255;i--)
	{
		LCD_WriteChar(str[i]);
	}
	
}

void LCD_WriteBinary(u8 data)
{
	s8 i;
	for (i=7;i>=0;i--)
	{
		LCD_WriteChar('0'+ READ_BIT(data,i));
	}
}

void LCD_WriteHex(u8 data)
{
	u8 hex[16]={48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70};
	//LCD_WriteChar('0');
	//LCD_WriteChar('x');
	LCD_WriteChar(hex[(data>>4)]);
	LCD_WriteChar(hex[(data&0x0f)]);
}
void LCD_CustomerChar(u8 address , u8*character)
{
	
	WriteIns(0x40+(address*8));
	
	for(u8 i=0;i<8;i++)
	{
		WriteData(character[i]);
	}
	WriteIns(0x80);
}

void LCD_Clear()
{
	WriteIns(0x01);
	_delay_ms(2);
	WriteIns(0x80);
	
}

void LCD_WriteNumber_u8(u8 num)//1:9
{
	LCD_Clear();
	LCD_WriteChar('0'+num);
}