
#include "StdTypes.h"
#include "KeyPad_Interface.h"
#include "KeyPad_Cfg.h"
#include "DIO_Interface.h"
#include "Utils.h"

extern const u8 KeysArr[ROWS][COLS];

void KEYPAD_Init(void)
{
	for (u8 r=0;r<ROWS;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
	}
}

u8 KEYPAD_GetKey(void)
{
	u8 f,r,c,key=NO_KEY;
	for (r=0;r<ROWS;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,LOW);
		f=0;
		
		for(c=0;c<COLS+1;c++)
		{
			if(c!=1)
			{
				
				if (DIO_ReadPin(FIRST_INPUT+c)==LOW)
				{
					key=KeysArr[r][c-f];
					_delay_ms(3);
					while(DIO_ReadPin(FIRST_INPUT+c)==LOW);
					_delay_ms(3);
					
				}
			}
			else
			{
				f=1;
			}
		}
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
	}
	return key;
}

/*s32 KEYPAD_GetNum(u8 k,u8* k2)
{
u16 num=0;
num=num*10+(k-'0');
if (k!='0')
{
LCD_WriteChar(k);
}
k=KEYPAD_GetKey();
while ((k>='0'&&k<='9')||k==NO_KEY)
{
if (k!=NO_KEY)
{
num=num*10+(k-'0');
LCD_WriteChar(k);
}
k=KEYPAD_GetKey();
}
*k2=k;
return num;
}
u8 KEYPAD_GETBinary(void)
{
u8 b=0;
u8 i=0,k;
while(i<8)
{
k=KEYPAD_GetKey();
if(k=='1'||k=='0')
{
if (k=='1')
{
SET_BIT(b,(7-i));
}
LCD_WriteChar(k);
i++;
}
else if (k=='C')
{
LCD_Clear();
return 0;
}
else if (k=='=')
{
return b;
}
}
return b;
}
u8 KEYPAD_GETHex(void)
{
u8 h=0;
u8 i=255,flag=0;
u8 k=KEYPAD_GetKey();
while (k)
{
if (k>='0'&&k<='9')
{
LCD_WriteChar(k);
if(flag)
{
h|=k-'0';
return h;
}
else
{
h=k-'0';
h<<=4;
flag=1;
}

}

else if (k=='+')
{
i++;
if (i==6)
{
i=0;
}
if (flag)
{
LCD_GoTo(0,4);
}
else
{
LCD_GoTo(0,3);
}
LCD_WriteChar('A'+i);
}
else if (k=='-')
{
i--;
if (i==255||i==254)
{
i=5;
}

if (flag)
{
LCD_GoTo(0,4);
}
else
{
LCD_GoTo(0,3);
}
LCD_WriteChar('A'+i);
}


else if (k=='C')
{
LCD_Clear();
return 0;
}
else if (k=='=')
{
if (flag)
{
i+=10;
h|=i;
i=0;
return h;
}
else
{
h=i+10;
h<<=4;
flag=1;
}
}
k=KEYPAD_GetKey();
}
return NO_KEY;
}*/