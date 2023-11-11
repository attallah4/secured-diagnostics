#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "TIMER0_Interface.h"
#include "UART_Interface.h"
#include "UART_Services.h"
#include "Sec_Dia.h"


u32 rand=0;
u32 enc=0;
u32 rot=0;


void SecDia_Init(void)
{
	DIO_Init();
	LCD_Init();
	UART_Init();
	TIMER0_Init(TIMER0_NORMAL_MODE);
	TIMER0_Start(TIMER0_SCALER_8);
}


void SecDia_Runnable(void)
{
	u8 *p=(u8*)&rand;

	u32 sid_sec=0;

	u32 sid_enc=0;

	u32 sid_rot=0;

	u32 decrypt_num=0;

	u8 flag_security=0;

	LCD_Clear();
	LCD_WriteString("secure diagnostics");
	flag_security=0;

	sid_sec=0;

	sid_enc=0;

	sid_rot=0;

	enc=0;

	rot=0;

	decrypt_num=0;

	if(flag_security==0)
	{
		
		
		sid_sec=UART_Receive_SidSec();

		if (sid_sec==0x27010000&&!flag_security)
		{
			LCD_Clear();
			LCD_WriteString("67 01    ");
			rand=random_num();
			
			for (u8 i=3;i!=255;i--)
			{
				LCD_WriteHex(p[i]);
			}
			
			LCD_GoTo(3,0);
			LCD_WriteString("Access Done");
			
			decrypt_num=dec_num();
			flag_security=1;
		}
		else
		{
			LCD_Clear();
			LCD_WriteString("NRC 7F ");
			sid_sec>>=16;
			p=(u8*) &sid_sec;
			for (u8 i=1;i!=255;i--)
			{
				LCD_WriteHex(p[i]);
			}
			LCD_WriteString(" 35");
			LCD_GoTo(3,0);
			LCD_WriteString("Access Denied");
		}
	}
	if(flag_security==1)
	{
		sid_enc=UART_Receive_SidEnc();
		if ((sid_enc==0x27020000)&&(enc==decrypt_num)&&(flag_security==1))
		{
			LCD_Clear();
			LCD_WriteString("67 02 ");
			LCD_GoTo(3,0);
			LCD_WriteString("Access Done");
			flag_security=2;
		}
		else
		{
			LCD_Clear();
			LCD_WriteString("NRC 7F ");
			sid_sec>>=16;
			p=(u8*)&sid_enc;
			for (u8 i=1;i!=255;i--)
			{
				LCD_WriteHex(p[i]);
			}
			LCD_WriteString(" 35");
			LCD_GoTo(3,0);
			LCD_WriteString("Access Denied");
		}
	}
	if(flag_security==2)
	{
		
		
		sid_rot=UART_Receive_SidRot();
		if ((sid_rot==0x31010000)&&(rot==0xaa00)&&flag_security==2)
		{
			led_on();
			LCD_Clear();
			LCD_WriteString("7701 ");
			LCD_GoTo(3,0);
			LCD_WriteString("Task Done");
			LCD_GoTo(4,0);
			LCD_WriteString("led is turned on");
			_delay_ms(1500);
		}
		else
		{
			LCD_Clear();
			LCD_WriteString("NRC 7F ");
			sid_sec>>=16;
			p=(u8*)&sid_rot;
			for (u8 i=1;i!=255;i--)
			{
				LCD_WriteHex(p[i]);
			}
			LCD_WriteString(" 35");
			LCD_GoTo(3,0);
			LCD_WriteString("Task Undefined");
		}
	}
	
			_delay_ms(1500); // to display the diagnostics before the second task

}

void led_on(void)
{
	DIO_WritePin(PINA6,HIGH);
}

u32 UART_Receive_SidSec(void)
{
	u32 num;
	
	u8 n1,n2,n3,n4;
	n1=UART_Receive();
	n1-='0';
	n2=UART_Receive();
	n2-='0';
	n3=UART_Receive();
	n3-='0';
	n4=UART_Receive();
	n4-='0';
	
	num=((u32)n1<<28)|((u32)n2<<24)|((u32)n3<<20)|((u32)n4<<16);
	n1=UART_Receive();
	n1=UART_Receive();
	return num;
	
}


u32 UART_Receive_SidEnc(void)
{
	u32 num;
	u8 n1,n2,n3,n4;
	n1=UART_Receive();
	n1-='0';
	n2=UART_Receive();
	n2-='0';
	n3=UART_Receive();
	n3-='0';
	n4=UART_Receive();
	n4-='0';
	enc=UART_Receive_enc();
	
	num=((u32)n1<<28)|((u32)n2<<24)|((u32)n3<<20)|((u32)n4<<16);
	num&=0xffff0000;
	
	
	
	return num;
	
}

u32 UART_Receive_SidRot(void)
{
	u32 num;
	rot=0;
	u8 n1,n2,n3,n4;
	n1=UART_Receive();
	n1-='0';
	n2=UART_Receive();
	n2-='0';
	n3=UART_Receive();
	n3-='0';
	n4=UART_Receive();
	n4-='0';
	rot=UART_Receive_rot();
	
	num=((u32)n1<<28)|((u32)n2<<24)|((u32)n3<<20)|((u32)n4<<16);
	
	
	return num;
	
}

u32 UART_Receive_enc(void)
{
	u32 num=0;
	
	u8 n1=0;
	for(u8 i=0;i<8;i++)
	{
		n1=UART_Receive();
		if (n1<='9'&&n1>='0')
		n1-='0';
		else
		n1=n1-'A'+10;
		
		n1&=0x0f;
		num=(num<<4)|n1;
	}
	
	n1=UART_Receive();
	n1=UART_Receive();
	return num;
}


u32 UART_Receive_rot(void)
{
	u32 num=0;
	
	u8 n1=0;
	for(u8 i=0;i<4;i++)
	{
		n1=UART_Receive();
		if (n1<='9'&&n1>='0')
		n1-='0';
		else
		n1=n1-'A'+10;
		
		n1&=0x0f;
		num=(num<<4)|n1;
	}
	n1=UART_Receive();
	n1=UART_Receive();
	return num;
}

u32 random_num(void)
{
	u32 num;
	u8 n1,n2,n3,n4;
	n1=TCNT0;
	_delay_us(30);
	n2=TCNT0;
	_delay_us(30);
	n3=TCNT0;
	_delay_us(30);
	n4=TCNT0;
	num=((u32)n1<<24)|((u32)n2<<16)|((u32)n3<<8)|(n4);
	return num;
}

u32 dec_num(void)
{
	u32 num=0;
	u8 *p1=(u8*)&rand;
	u8 *p2=(u8*)&num;
	for (u8 i=0;i<4;i++)
	{
		p2[i]=p1[i]^5;
	}
	return num;
}





