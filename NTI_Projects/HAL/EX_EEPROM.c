
#include "StdTypes.h"
#include "Utils.h"
#include "I2C_Interface.h"
#include "EX_EEPROM_Interface.h"

EEPROM_STATE_T EEPROM_WriteChar(u8 addres_eeprom,u16 eeprom_mem,u8 data)
{
	I2C_Error_State error=I2C_OK;
	error=I2C_Master_enuSendStartCond();
	if(error==I2C_SC_ERROR)
	return EEMPROM_W_NOK;
	error=I2C_Master_enuSendSlaveAddressWithWrite(addres_eeprom);
	if(error==I2C_MT_SLA_W_ERROR)
	return EEMPROM_W_NOK;
 	error=I2C_Master_enuSendu8Data(eeprom_mem);
 	if(error==I2C_MT_DATA_ERROR)
 	return EEMPROM_W_NOK;
	error=I2C_Master_enuSendu8Data(data);
	if(error==I2C_MT_DATA_ERROR)
	return EEMPROM_W_NOK;
	I2C_Master_enuSendStopCond();
	return EEMPROM_W_OK;
}



EEPROM_STATE_T EEPROM_ReadChar(u8 addres_eeprom,u16 eeprom_mem,u8* data)
{
	I2C_Error_State error=I2C_OK;
	error=I2C_Master_enuSendStartCond();
	if(error==I2C_SC_ERROR)
	return EEMPROM_R_NOK;
	error=I2C_Master_enuSendSlaveAddressWithWrite(addres_eeprom);
	if(error==I2C_MT_SLA_W_ERROR)
	return EEMPROM_R_NOK;
	error=I2C_Master_enuSendu8Data(eeprom_mem);
	if(error==I2C_MT_DATA_ERROR)
	return EEMPROM_R_NOK;
	error=I2C_Master_enuSendRepeatedStartCond();
	if(error==I2C_RSC_ERROR)
	return EEMPROM_R_NOK;
	error=I2C_Master_enuSendSlaveAddressWithRead(addres_eeprom);
	if(error==I2C_MT_SLA_R_ERROR)
	return EEMPROM_R_NOK;
	
	error=I2C_Master_enuReadu8Data(data);
	if(error==I2C_MR_DATA_ERROR)
	return EEMPROM_R_NOK;
	
	I2C_Master_enuSendStopCond();
	return EEMPROM_R_OK;
}