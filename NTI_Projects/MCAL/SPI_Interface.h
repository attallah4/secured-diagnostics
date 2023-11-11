

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_






u8 SPI_Receive(void);


void SPI_voidMasterInit(void);

void SPI_voidSlaveInit(void);

u8 SPI_u8Transfer(u8 Copy_Data);

void SPI_voidSetCallBack( void (*PtrToFunc) (void) );

u8 SPI_u8ReadDataISR(void);

void SPI_voidSendDataISR(u8 Copy_Data);

void SPI_InterruptEnable(void);

void SPI_InterruptDisable(void);

void SPI_voidSendDataISR(u8 Copy_Data);

#endif /* SPI_INTERFACE_H_ */