

#ifndef SEC_DIA_H_
#define SEC_DIA_H_

void SecDia_Init(void);

void SecDia_Runnable(void);

void led_on(void);

u32 UART_Receive_SidSec(void);

u32 UART_Receive_SidEnc(void);

u32 UART_Receive_SidRot(void);

u32 UART_Receive_enc(void);

u32 UART_Receive_rot(void);

u32 random_num(void);

u32 dec_num(void);



#endif /* SEC_DIA_H_ */