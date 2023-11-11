/*
 * UART_Services.h
 *
 * Created: 18/08/2023 06:14:07
 *  Author: Alahram
 */ 


#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

void UART_SendString(c8 *str);

void UART_ReceiveString(u8*str);

void UART_SendNumber(u32 num);

u32 UART_ReceiveNumber(void);

u8 endian_check(void);

u16 endian_convert_u16(u16 num);

u32 endian_convert_u32(u32 num)  ;

void UART_SendStringAsynch(u8*str);

u8 UART_REC_PushStack (void);

u8 UART_REC_PopStack (u8 *pdata);



#endif /* UART_SERVICES_H_ */