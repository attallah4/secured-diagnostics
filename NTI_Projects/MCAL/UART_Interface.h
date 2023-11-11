

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


#define  STACK_SIZE  10

typedef enum {
	
	STACK_FULL,
	STACK_EMPTY,
	STACK_DONE
	
}STACK_State;


typedef enum {
	PARITY_DISABLE,
	PARITY_ODD,
	PARITY_EVEN
	
}PARITY_Status_type;

typedef enum {
	ONE_STOP,
	TWO_STOP
	
}STOP_Bit_Status_type;


STACK_State UART_Stack_Push(u8 data);
STACK_State UART_Stack_Pop(u8 *data);




void UART_Init(void);

void UART_Send(u8 data);

u8 UART_Receive(void);

u8 UART_ReceivePerodic(u8*pdata);

void UART_SendNoBlock(u8 data);

u8 UART_ReceiveNoBlock(void);

void UART_RX_InterruptEnable(void);

void UART_RX_InterruptDisable(void);

void UART_TX_InterruptEnable(void);

void UART_TX_InterruptDisable(void);

void UART_RX_SetCallBack(void (*LocalFptr)(void));

void UART_TX_SetCallBack(void (*LocalFptr)(void));


#endif /* UART_INTERFACE_H_ */