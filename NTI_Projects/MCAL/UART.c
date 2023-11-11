
#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"
#include "UART_Interface.h"
#include "UART_Cfg.h"




static void(*UART_RX_Fptr)(void)=NULL_PTR;
static void(*UART_TX_Fptr)(void)=NULL_PTR;
//static u8 reg=0;


void UART_Init(void)
{
	// setup boud rate >> prescaller full register
	UBRRL =103;  //9600
	
	//normal speed
	CLR_BIT(UCSRA,U2X);
	
	
	// setup the frame(stop  parity  data length) all are initialized with the initial value of (1stop no parity 8data length)
	
	// parity disable :
	//CLR_BIT(UCSRC,UPM0);
	//CLR_BIT(UCSRC,UPM1);
	
	//stop bits number 1or2 :
	//CLR_BIT(UCSRC,USBS); 1stop bit
	
	// data length 8 bits :
	//SET_BIT(UCSRC,UCSZ0);
	//SET_BIT(UCSRC,UCSZ1);
	//CLR_BIT(UCSRB,UCSZ2);
	
	
	
	//Asynchronous Operation : initialized with asynchronous
	
	//CLR_BIT(USCRC,UMSEL)
	
	//ENABLE RX & TX
	
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);

}


/*
void UART_Init(void)
{
	// setup boud rate >> prescaller full register
	UBRRL =103;  //9600
	
	#if MODE_OF_OPERATION == ASYNCHRONOUS
	CLR_BIT(reg,UMSEL);
	#else
	SET_BIT(reg,UMSEL);
	#endif
	
	#if SPEED_OPERATION	==NORMAL_SPEED_MODE
	CLR_BIT(UCSRA,U2X);
	#else 
	SET_BIT(UCSRA,U2X);
	#endif
	
	// setup the frame(stop  parity  data length) all are initialized with the initial value of (1stop no parity 8data length)
	
	// parity disable :
	//CLR_BIT(UCSRC,UPM0);
	#if PARITY_MODE ==DISABLED
	CLR_BIT(reg,UPM1);
	CLR_BIT(reg,UPM0);
	#elif PARITY_MODE ==EVEN
	SET_BIT(reg,UPM1);
	CLR_BIT(reg,UPM0);
	#else
	SET_BIT(reg,UPM1);
	SET_BIT(reg,UPM0);
	#endif
	
	#if STOP_BIT_SELECT == ONE_BIT
	CLR_BIT(reg,USBS); 
	#else 
	SET_BIT(reg,USBS); 
	#endif
	
	// data length 8 bits :
	//SET_BIT(UCSRC,UCSZ0);
	//SET_BIT(UCSRC,UCSZ1);
	//CLR_BIT(UCSRB,UCSZ2);
	
	//ENABLE RX & TX
	UCSRC=reg;
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);

}

*/

void UART_Send(u8 data)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR=data;
}
u8 UART_Receive(void)
{
	while(!READ_BIT(UCSRA,RXC));
	return UDR;
}

u8 UART_ReceivePerodic(u8*pdata)
{
	if (READ_BIT(UCSRA,RXC))
	{
		
		*pdata=UDR;
		return 1;
	}
	return 0;
}

/***********************************************************************/
void UART_SendNoBlock(u8 data)
{
	UDR=data;
}

u8 UART_ReceiveNoBlock(void)
{
	return UDR;
}



void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}

void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}


ISR(UART_RX_vect)
{
	if (UART_RX_Fptr!=NULL_PTR)
	{
		UART_RX_Fptr();
	}
}

ISR(UART_TX_vect)
{
	if (UART_TX_Fptr!=NULL_PTR)
	{
		UART_TX_Fptr();
	}
}