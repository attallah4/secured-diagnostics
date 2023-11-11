
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "I2C_Interface.h"
#include "I2C_Private.h"


void I2C_Master_voidInit(u8 address)
{
	TWBR=12; // >>>>  scl for i2c and prescaller =1 >> for 400 Khz  >> TWPS0 & TWPS1 ==0
	
	//ACK enable
	
	//SET_BIT(TWCR,TWEA);
	
	// General call enable
	
	// SET_BIT(TWAR,TWGCE);
	
	//SET ADDRESS
	address<<=1;
	TWAR|=address;
	
	//I2C Enable
	SET_BIT(TWCR,TWEN);

}

void I2C_Slave_voidInit(u8 I2C_Address)
{
	//TWBR=12; // >>>>  scl for i2c and prescaller =1 >> for 400 Khz  >> TWPS0 & TWPS1 ==0
	
	//SET ADDRESS
	I2C_Address<<=1;
	TWAR|=I2C_Address;
	SET_BIT(TWCR,TWEA);
	//I2C Enable
	SET_BIT(TWCR,TWEN);
}

I2C_Error_State   I2C_Master_enuSendStartCond(void)
{
	// set start
	/*SET_BIT(TWCR,TWSTA);
	// I2C ENABLE
	SET_BIT(TWCR,TWEN);
	// INT Claer
	SET_BIT(TWCR,TWINT);
	*/
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!READ_BIT(TWCR,TWINT));
	
	if ((TWSR&0xf8)!=START_STATE )
	{
		return I2C_SC_ERROR;
	}
	return I2C_OK;
}

I2C_Error_State   I2C_Master_enuSendRepeatedStartCond(void)
{
	// set start
	/*SET_BIT(TWCR,TWSTA);
	// I2C ENABLE
	SET_BIT(TWCR,TWEN);
	// INT Claer
	SET_BIT(TWCR,TWINT);
	//*/
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!READ_BIT(TWCR,TWINT));
	
	if ((TWSR&0xf8)!=REP_START_STATE )
	{
	return I2C_RSC_ERROR;
	}
	return I2C_OK;
	}

	I2C_Error_State   I2C_Master_enuSendSlaveAddressWithRead(u8 I2C_Address)
	{
	I2C_Address<<=1;
	TWDR=I2C_Address;
	SET_BIT(TWDR,0);
	// set frame to read
	//SET_BIT(TWDR,0);
	
	/*// I2C ENABLE
	SET_BIT(TWCR,TWEN);
	// INT Claer
	
	SET_BIT(TWCR,TWINT);
	*/CLR_BIT(TWCR,5);
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	
	while (!READ_BIT(TWCR,TWINT));

	if ((TWSR&0xf8)!=SLA_R_ACK_STATE )
	{
		return I2C_MT_SLA_R_ERROR;
	}
	return I2C_OK;
}

I2C_Error_State   I2C_Master_enuSendSlaveAddressWithWrite(u8 I2C_Address)
{
	I2C_Address<<=1;
	TWDR=I2C_Address;
	// set frame to write
	CLR_BIT(TWDR,0);
	
	// I2C ENABLE
	/*SET_BIT(TWCR,TWEN);
	// INT Claer
	SET_BIT(TWCR,TWINT);
	*/
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (!READ_BIT(TWCR,TWINT));
	
	if ((TWSR&0xf8)!=SLA_W_ACK_STATE )
	{
		return I2C_MT_SLA_W_ERROR;
	}
	return I2C_OK;
}

I2C_Error_State I2C_slave_avilable(void)//TO WRITE
{
	//	I2C_Error_State State=I2C_SR_DATA_ERROR;
	TWCR=(1<<TWINT)|(1<<TWEA)|(1<<TWEN);//ACKNOWADG
	/*
	//ENABLE ACK
	SET_BIT(TWCR,TWEA);
	// I2C ENABLE
	SET_BIT(TWCR,TWEN);
	// INT Claer
	SET_BIT(TWCR,TWINT);
	*/
	while (!READ_BIT(TWCR,TWINT));
	if((TWSR & 0xF8) !=  SLA_W_ACK )
	{
		return I2C_SR_ADD_ERROR;//I Cant start now
	}
	return I2C_OK;
	
}

I2C_Error_State   I2C_Master_enuSendu8Data(u8 I2C_Data)
{
	TWDR=I2C_Data;
	/*// I2C ENABLE
	SET_BIT(TWCR,TWEN);
	// INT Claer
	SET_BIT(TWCR,TWINT);
	*/
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (!READ_BIT(TWCR,TWINT));
	
	if ((TWSR&0xf8)!=DATA_WRITE_ACK_STATE )
	{
	return I2C_MT_DATA_ERROR;
	}
	return I2C_OK;
	}

	I2C_Error_State   I2C_Master_enuReadu8Data(u8* I2C_Data)
	{
	// I2C ENABLE
	/*SET_BIT(TWCR,TWEN);
	// INT Claer
	SET_BIT(TWCR,TWINT);
	*/
	TWCR=(1<<TWINT)|(1<<TWEN);
	while (!READ_BIT(TWCR,TWINT));
	
	if ((TWSR&0xf8)!=DATA_READ_NACK_STATE )
	{
	return I2C_MR_DATA_ERROR;
	}
	*I2C_Data=TWDR;
	return I2C_OK;
	}

	void I2C_Master_enuSendStopCond(void)
	{
	// set stop
	/*SET_BIT(TWCR,TWSTO);
	// I2C ENABLE
	SET_BIT(TWCR,TWEN);
	// INT Claer
	SET_BIT(TWCR,TWINT);
	//*/
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	while(READ_BIT(TWCR, TWSTO) == 1);
}

I2C_Error_State   I2C_Slave_enuReadu8Data(u8* I2C_Data)
{
	// I2C ENABLE
	/*SET_BIT(TWCR,TWEN);
	// INT Claer
	SET_BIT(TWCR,TWINT);
	//ENABLE ACK
	SET_BIT(TWCR,TWEA);
	*/
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while (!READ_BIT(TWCR,TWINT));
	if ((TWSR&0xf8)!=DATA_SL_R_ACK )
	{
		return I2C_SR_DATA_ERROR;
	}
	*I2C_Data=TWDR;
	
	return I2C_OK;
}

I2C_Error_State I2C_SendChar(u8 data,u8 address)
{
	I2C_Error_State error=I2C_OK;
	error=I2C_Master_enuSendStartCond();
	if(error==I2C_SC_ERROR)
	return error;
	error=I2C_Master_enuSendSlaveAddressWithWrite(address);
	if(error==I2C_MT_SLA_W_ERROR)
	return error;
// 	error=I2C_Master_enuSendu8Data(reg);
// 	if(error==I2C_MT_DATA_ERROR)
// 	return error;
	error=I2C_Master_enuSendu8Data(data);
	if(error==I2C_MT_DATA_ERROR)
	return error;
	I2C_Master_enuSendStopCond();
	return error;
}


I2C_Error_State I2C_ReceiveChar(u8 *data)
{
	I2C_Error_State error=I2C_OK;
	error=I2C_slave_avilable();
	if(error==I2C_SR_ADD_ERROR)
	return error;
	error=I2C_Slave_enuReadu8Data(data);
	if(error==I2C_SR_DATA_ERROR)
	return error;
	
	return error;
}

