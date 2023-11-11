

#ifndef UTILS_H_
#define UTILS_H_

#define READ_BIT(reg,bit) ((reg>>bit)&1)
#define CLR_BIT(reg,bit) (reg=reg &(~(1<<bit)))
#define SET_BIT(reg,bit) (reg=reg |(1<<bit))
#define TGL_BIT(reg,bit) (reg=reg ^(1<<bit))

/****************inside interrupt driver************************/ //enabling & disabling  global interrupt flag
#define GIE_voidEnable sei

#define GIE_voidDisable cli
/*************************************************************/
/*******************ASSEMBLY FUNCS***************************/

# define sei()  __asm__ __volatile__ ("sei" ::)// enable the global int register
# define cli()  __asm__ __volatile__ ("cli" ::)//disable the global int register
# define reti() __asm__ __volatile__ ("reti" ::)//return with enabling the global int register
# define ret()  __asm__ __volatile__ ("ret" ::)// return
/**********************************************************/

//timers utils
#define SET_TCTNT0(x) (TCNT0=(x))

#define GET_TCTNT0()  TCNT0

#define SET_OCR0(x) (OCR0=(x))
/*************************************************/

#define F_CPU 16000000
#include <util/delay.h>




#endif /* UTILS_H_ */