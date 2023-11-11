

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_



#define     I2C_SLAVE         0
#define     I2C_MASTER        1

#define     ENABLE            0
#define     DISABLE           1


/*        I2C Physical Pins */
#define       I2C_SCL          PINC0
#define       I2C_SDA          PINC1

/*
#define       I2C_SC_ACK        0x08
#define       I2C_RSC_ACK       0x10
#define       I2C_MT_SLA_R_ACK  0x40
#define       I2C_MT_SLA_W_ACK  0x18
#define       I2C_MT_DATA_ACK   0x28
#define       I2C_MR_DATA_ACK   0x48
#define       I2C_SR_DATA_ACK   0x80
#define		  I2C_SR_ADD_ACK	0x60
*/

#define START_STATE               0x08 // start has been sent
#define REP_START_STATE           0x10 // repeated start
#define SLA_W_ACK_STATE           0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define SLA_W_NACK_STATE          0x20
#define SLA_R_ACK_STATE           0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define SLA_R_NACK_STATE          0x48
#define DATA_WRITE_ACK_STATE      0x28 // Master transmit data and ACK has been received from Slave.
#define DATA_WRITE_NACK_STATE     0x30
#define DATA_READ_ACK_STATE       0x50 // Master received data and send ACK to slave
#define DATA_READ_NACK_STATE      0x58 // Master received data but doesn't send ACK to slave
#define DATA_SL_R_ACK			  0x80
#define	SLA_W_ACK           	  0x60




#endif /* I2C_PRIVATE_H_ */