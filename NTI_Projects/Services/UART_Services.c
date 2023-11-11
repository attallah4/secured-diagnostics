#include "StdTypes.h"
#include "UART_Interface.h"
#include "UART_Services.h"




static void tx_func(void);
static void RX_STACK_FUNC(void);
void UART_SendString(c8 *str)
{
	for (u8 i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
	
}

void UART_ReceiveString(u8*str)
{
	u8 i=0;
	str[0]=UART_Receive();
	for (;str[i]!=0x0d;)
	{
		i++;
		str[i]=UART_Receive();
	}
	str[i]=0;
	str[i+1]=UART_Receive();
	
}

void UART_SendNumber(u32 num)
{
	u8*p=(u8*)&num;
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);
}

u32 UART_ReceiveNumber(void)
{
	u8*p;
	u32 num;
	p=(u8 *)&num;
	p[0]=UART_Receive();
	p[1]=UART_Receive();
	p[2]=UART_Receive();
	p[3]=UART_Receive();
	
	return num;
	
}



u8 endian_check(void)
{
	u32 num=1;
	u8*p=(u8 *)&num;
	if(*p==1)
	{
		return 1;
	}
	else
	{
		return 2;
	}
	
}

u16 endian_convert_u16(u16 num)
{
	return num>>8|num<<8;
}

u32 endian_convert_u32(u32 num)  
{
	
	
	u32 num2;
	
	num2=num>>24|num<<24|((num>>8) & 0x0000ff00)|((num<<8) & 0x00ff0000);
	return num2;
}

void UART_SendStringCheckSum(u8*str){	u8 i,l;	u16 sum=0;	for(l=0;str[l];l++)	{		sum+=str[l];	}	UART_Send(l);	for (i=0;str[i];i++)	{		UART_Send(str[i]);	}	UART_Send((u8)sum);	UART_Send((u8)(sum>>8));	}u8 UART_ReceiveStringCheckSum(u8*str){	u8 i=0,l =UART_Receive();	u16 sum_calc=0,sum_rec=0;	for (;i<l;i++)	{		str[i]=UART_Receive();		sum_calc+=str[i];	}	sum_rec=UART_Receive();	sum_rec=(UART_Receive()<<8)|sum_rec;		if (sum_calc==sum_rec)	{		return 1;	}	return 0;}
	static u8 i;
	static volatile u8*Str_TX[20];
void UART_SendStringAsynch(u8*str)
{

	UART_Send(str[0]);
	Str_TX[i]=str;
	i++;
	if (i==20)
	{
		i=0;
	}
	UART_TX_InterruptEnable();
	UART_TX_SetCallBack(tx_func);
	
}

static void tx_func(void)
{
	static u8 j=1;
	if (Str_TX[i][j]!=0)
	{
		UART_SendNoBlock(Str_TX[i][j]);
		j++;
	}
	else
	{
		j=1;
		
		
	}
	
}

static u8 UART_STACk[STACK_SIZE];
static u8 SP = 0;
static u8 INT_data=0;
u8 RX_flag=0;
static void RX_STACK_FUNC(void)
{
	INT_data =UART_ReceiveNoBlock();
	RX_flag=1;
}

u8 UART_REC_PushStack (void)
{
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(RX_STACK_FUNC);
	
	if (RX_flag==1)
	{
		RX_flag=0;
		if (UART_Stack_Push(INT_data)==STACK_DONE)
		{
			return 1;
		}
		return 0;
	}
	
	return 2;
	
}

STACK_State UART_Stack_Push(u8 data)
{
	if (SP == STACK_SIZE )
	{
		return STACK_FULL;
	}
	else
	{
		UART_STACk[SP] = data;
		SP++;
	}
	return STACK_DONE;
}


u8 UART_REC_PopStack (u8 *pdata)
{
	if (UART_Stack_Pop(pdata)==STACK_DONE)
	{
		return 1;
	}
	return 0;
}

STACK_State UART_Stack_Pop(u8 *pdata)
{
	if (SP == 0 )
	{
		return STACK_EMPTY;
	}
	else
	{
		SP--;
		*pdata = UART_STACk[SP];
	}
	return STACK_DONE;
}