#pragma once

#define START           0x08
#define REPEATED_START  0x10
#define MT_SLA_ACK		0x18
#define MT_SLA_NACK		0x20
#define MT_DATA_ACK     0x28
#define MT_DATA_NACK    0x30
#define MR_SLA_ACK		0x40
#define MR_SLA_NACK		0x48
#define MR_DATA_ACK     0x50
#define MR_DATA_NACK    0x58
#define LOST_ARBTRTN    0x38
#define TWI_STATUS      (TWSR & 0xF8)
	

void I2C_Setup(void);
uint8_t I2C_Write(uint16_t registerAddress, uint8_t *data, uint8_t numberBytes);
uint8_t I2C_Read(uint16_t registerAddress, uint8_t *data, uint8_t numberBytes);
void RDY_wait(void);
void Close_Comms(void);
