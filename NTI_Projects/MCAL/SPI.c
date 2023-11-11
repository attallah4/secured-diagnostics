
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "SPI_Interface.h"

static void(* SPI_Fptr)(void)=NULL_PTR;


void SPI_voidMasterInit(void)
{
	SET_BIT(SPCR,MSTR);
	SET_BIT(SPCR,SPE);
	
}

void SPI_voidSlaveInit(void)
{
	CLR_BIT(SPCR,MSTR);
	SET_BIT(SPCR,SPE);
}

u8 SPI_u8Transfer(u8 Copy_Data)
{
	// write puffer
	SPDR=Copy_Data;
	while(!READ_BIT(SPSR,SPIF));
	//READ PUFFER
	return SPDR;
}

void SPI_voidSetCallBack( void (*local_fptr) (void) )
{
	SPI_Fptr=local_fptr;
}

u8 SPI_u8ReadDataISR(void)
{
	return SPDR;
}

void SPI_voidSendData(u8 Copy_Data)
{
	SPDR=Copy_Data;
	while(!READ_BIT(SPSR,SPIF));
}
void SPI_voidSendDataISR(u8 Copy_Data)
{
	SPDR=Copy_Data;
}

void SPI_InterruptEnable(void)
{
	SET_BIT(SPCR,SPIE);
}

void SPI_InterruptDisable(void)
{
	CLR_BIT(SPCR,SPIE);
}

ISR(SPI_STC_vect)
{
	if (SPI_Fptr!=NULL_PTR)
	{
		SPI_Fptr();
		
	}
}