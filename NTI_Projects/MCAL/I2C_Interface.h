

#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

typedef enum
{
	I2C_OK = 0,
	I2C_SC_ERROR,
	I2C_RSC_ERROR,
	I2C_MT_SLA_R_ERROR,
	I2C_MT_SLA_W_ERROR,
	I2C_MT_DATA_ERROR,
	I2C_MR_DATA_ERROR,
	I2C_SR_DATA_ERROR,
	I2C_SR_ADD_ERROR,
	I2C_SEND_NOT_OK
}I2C_Error_State;

void I2C_Master_voidInit(u8 address);										  //init for master
void I2C_Slave_voidInit(u8 I2C_Address);								      //init fo slave
I2C_Error_State   I2C_Master_enuSendStartCond(void);                          //start if bus is idle
I2C_Error_State   I2C_Master_enuSendRepeatedStartCond(void);                  //repeated start if bus is busy

I2C_Error_State   I2C_Master_enuSendSlaveAddressWithRead(u8 I2C_Address);     //Send slave address With R/W bit Read
I2C_Error_State   I2C_Master_enuSendSlaveAddressWithWrite(u8 I2C_Address); 
I2C_Error_State   I2C_slave_avilable(void);									   //Send slave address With R/W bit Write
I2C_Error_State   I2C_Master_enuSendu8Data(u8 I2C_Data);                      //master Sets Data given in argument
I2C_Error_State   I2C_Master_enuReadu8Data(u8* I2C_Data);                     //master Gets Data and saves it in given argument
void I2C_Master_enuSendStopCond(void);                                        //send stop bit
I2C_Error_State   I2C_Slave_enuReadu8Data(u8* I2C_Data);                      //Slave Reads Data saves it in given argument

I2C_Error_State I2C_SendChar(u8 data,u8 address);
I2C_Error_State I2C_ReceiveChar(u8 *data);

#endif /* I2C_INTERFACE_H_ */