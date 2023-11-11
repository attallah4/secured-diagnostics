


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_


void KEYPAD_Init(void);

u8 KEYPAD_GetKey(void);
s32 KEYPAD_GetNum(u8 k,u8* k2);

u8 KEYPAD_GETBinary(void);
u8 KEYPAD_GETHex(void);


#endif /* KEYPAD_INTERFACE_H_ */