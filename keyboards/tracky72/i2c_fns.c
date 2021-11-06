#include "i2c_fns.h"
#include "IQS5xx.h"
#include "defs.h"
#include "quantum.h"
#include "print.h"

uint16_t 	ui16Timeout = 100;  // Timeout on i2c in ms
uint8_t 	ui8Success;
uint32_t 	ui32StartTime;
//
// Function prototypes
//
uint8_t I2C_Write2(uint16_t ui16RegisterAddress, uint8_t *pData, uint8_t ui8NoOfBytes);
uint8_t I2C_Read2(uint16_t ui16RegisterAddress, uint8_t *pData, uint8_t ui8NoOfBytes);

//#############################################################################
//! Public functions
//#############################################################################


//*****************************************************************************
//
//! Setup I2C
//!
//!
//! \param None
//!
//! \return None
//
//*****************************************************************************
void I2C_Setup(void)
{
	// Set SDA and SCL to inputs
	//
	#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega328P__)
		SetBit(PORTC, 4);
		SetBit(PORTC, 5);
	#else
		SetBit(PORTD, 0);
		SetBit(PORTD, 1);
	#endif
	//
	// Set prescaler and clock frequency
	//
	ClearBit(TWSR, TWPS0);
	ClearBit(TWSR, TWPS1);
	TWBR = ((8000000 / 100000) - 16) / 2;
	//
	// Enable module, and set to ACK
	//
	SetBit(TWCR, TWEA);
	SetBit(TWCR, TWEN); 
}
 
//*****************************************************************************
//
//! I2C write function
//!
//! This function writes the provided data to the address specified.  If  
//! anything in the write process is not successful, then it will be repeated
//! up till four more times.  If still not successful, it will write an error
//! message on the serial terminal.
//!
//! \param ui16RegisterAddress is the 16-bit memory map address on the IQS5xx
//! \param pData is a pointer to the first byte of a block of data to write
//! \param ui8NoOfBytes indicates how many bytes of data to write
//!
//! \return Boolean indicating success/fail of write attempt
//
//*****************************************************************************
uint8_t I2C_Write(uint16_t ui16RegisterAddress, uint8_t *pData, uint8_t ui8NoOfBytes)
{
	uint8_t ui8Retry = 4;
	
	ui8Success = I2C_Write2(ui16RegisterAddress, pData, ui8NoOfBytes);
	//
	// If comms was not successful, retry 4 more times
	//
	while((!ui8Success) && (ui8Retry != 0))
	{
		ui8Success = I2C_Write2(ui16RegisterAddress, pData, ui8NoOfBytes);
		ui8Retry--;
	}
	
	if(ui8Success)
	{
		return(TRUE);
	}
	else
	{
		print("\nComms write error");
		return(FALSE);
	}
}

//*****************************************************************************
//
//! I2C read function
//!
//! This function reads data from the address specified and stores this data
//! in the area provided by the pointer.  If anything in the read process is 
//! not successful, then it will be repeated up till four more times.  
//! If still not successful, it will write an error message on the serial 
//! terminal.
//!
//! \param ui16RegisterAddress is the 16-bit memory map address on the IQS5xx
//! \param pData is a pointer to where the read data must be stored
//! \param ui8NoOfBytes indicates how many bytes of data to read
//!
//! \return Boolean indicating success/fail of read attempt
//
//*****************************************************************************
uint8_t I2C_Read(uint16_t ui16RegisterAddress, uint8_t *pData, uint8_t ui8NoOfBytes)
{
	uint8_t ui8Retry = 4;
	
	ui8Success = I2C_Read2(ui16RegisterAddress, pData, ui8NoOfBytes);
	//
	// If comms was not successful, retry 4 more times
	//
	while((!ui8Success) && (ui8Retry != 0))
	{
		ui8Success = I2C_Read2(ui16RegisterAddress, pData, ui8NoOfBytes);
		ui8Retry--;
	}
	
	if(ui8Success)
	{
		return(TRUE);
	}
	else
	{
		print("\nComms read error");
		return(FALSE);
	}
}

//*****************************************************************************
//
//! Wait for a communication window
//!                            
//! This function waits for the RDY window to be available. RDY I/O indicates 
//! when the communication window is available.  
//!			                         
//! \param None
//!                                             
//! \return None
//                                                      
//*****************************************************************************
//void RDY_wait() 
//{
//	while(readPin(RDY_PIN) == 0)
//	{
//		__asm__("nop\n\t");
//	}
//
//}

//*****************************************************************************
//
//! Terminate communication window
//!                            
//! The IQS5xx B000 does not close the communication window on the reception of 
//!	the STOP bit; therefore this function sends the END COMMUNICATION WINDOW 
//!	COMMAND (Please see datasheet for more information). RDY will go low after 
//!	receiving any write to 0xEEEE followed by a STOP. 
//!			                         
//! \param None
//!                                           
//! \return None
//                                                      
//*****************************************************************************
void Close_Comms() 
{
  uint8_t ui8DataBuffer[1];
  
  I2C_Write(END_WINDOW, &ui8DataBuffer[0], 1);
}


//#############################################################################
//! Private Functions
//#############################################################################

void I2C_Reset(void)
{
	// Release SCL and SDA lines and re-enable module
	//
	TWCR = 0;
	SetBit(TWCR, TWEA);
	SetBit(TWCR, TWEN);
}

void ResetTimeout(void)
{
	// Mark the current time, to start the i2c timeout counter from
	//
	//ui32StartTime = millis();
}

uint8_t I2CTimeout(void)
{
	//return((millis() - ui32StartTime) >= ui16Timeout);
	return FALSE;
}

uint8_t I2C_start(void)
{
	ResetTimeout();

	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)))
	{
		if(I2CTimeout())
		{
			I2C_Reset();
			return(FALSE);
		} 
	}
	if((TWI_STATUS == START) || (TWI_STATUS == REPEATED_START))
	{
		return(TRUE);
	}
	if(TWI_STATUS == LOST_ARBTRTN)
	{
		I2C_Reset();
	}
	return(FALSE);
}

uint8_t I2C_stop(void)
{
	ResetTimeout();
	
	TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
	while((TWCR & (1<<TWSTO)))
	{
		if(I2CTimeout())
		{
			I2C_Reset();
			return(FALSE);
		}
	}
	return(TRUE);
}

uint8_t I2C_sendAddress(uint8_t ui8Address)
{
	TWDR = ui8Address;
	ResetTimeout();
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)))
	{
		if(I2CTimeout())
		{
			I2C_Reset();
			return(FALSE);
		}  
	}
	if((TWI_STATUS == MT_SLA_ACK) || (TWI_STATUS == MR_SLA_ACK))
	{
		return(TRUE);
	}

	if((TWI_STATUS == MT_SLA_NACK) || (TWI_STATUS == MR_SLA_NACK))
	{
		I2C_stop();
	}
	else
	{
		I2C_Reset();
	} 
	return(FALSE);
}

uint8_t I2C_sendByte(uint8_t ui8Data)
{
	TWDR = ui8Data;
	ResetTimeout();
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)))
	{
		if(I2CTimeout())
		{
			I2C_Reset();
			return(FALSE);
		}
	}
	if(TWI_STATUS == MT_DATA_ACK)
	{
		return(TRUE);
	}
	if(TWI_STATUS == MT_DATA_NACK)
	{
		I2C_stop();
	}
	else
	{
		I2C_Reset();
	} 
	return(FALSE);
}

uint8_t I2C_receiveByte(uint8_t ack)
{
	ResetTimeout();

	if(ack)
	{
		TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	}
	else
	{
		TWCR = (1<<TWINT) | (1<<TWEN);
	}
	while(!(TWCR & (1<<TWINT)))
	{
		if(I2CTimeout())
		{
			I2C_Reset();
			return(FALSE);
		}
	}
	if(TWI_STATUS == LOST_ARBTRTN)
	{
		I2C_Reset();
		return(FALSE);
	}

	if(((TWI_STATUS == MR_DATA_NACK) && (!ack)) ||
	 ((TWI_STATUS == MR_DATA_ACK) && (ack)))
	{
		return(TRUE);
	}
	else
	{
		return(FALSE);
	}
}

uint8_t I2C_Write2(uint16_t ui16RegisterAddress, uint8_t *pData, uint8_t ui8NoOfBytes)
{
	uint8_t	i;
	
	if(I2C_start() == FALSE)
	{
		return(FALSE);
	}

	if(I2C_sendAddress(IQS5xx_ADDR<<1) == FALSE)
	{
		return(FALSE);
	}
	
	if(I2C_sendByte((uint8_t)(ui16RegisterAddress>>8)) == FALSE)
	{
		return(FALSE);
	}
	
	if(I2C_sendByte((uint8_t)ui16RegisterAddress) == FALSE)
	{
		return(FALSE);
	}
	
	for(i = 0; i < ui8NoOfBytes; i++)
	{
		if(I2C_sendByte(*pData) == FALSE)
		{
			return(FALSE);
		}
		pData++;
	}

	if(I2C_stop() == FALSE)
	{
		return(FALSE);
	}
	return(TRUE);
}

uint8_t I2C_Read2(uint16_t ui16RegisterAddress, uint8_t *pData, uint8_t ui8NoOfBytes)
{
	uint8_t	i;
		
	if(ui8NoOfBytes == 0)
	{
		ui8NoOfBytes++;
	}

	if(I2C_start() == FALSE)
	{
		return(FALSE);
	}

	if(I2C_sendAddress(IQS5xx_ADDR<<1) == FALSE)
	{
		return(FALSE);
	}

	if(I2C_sendByte((uint8_t)(ui16RegisterAddress>>8)) == FALSE)
	{
		return(FALSE);
	}

	if(I2C_sendByte((uint8_t)ui16RegisterAddress) == FALSE)
	{
		return(FALSE);
	}

	if(I2C_start() == FALSE)
	{
		return(FALSE);
	}

	if(I2C_sendAddress((IQS5xx_ADDR<<1) + 0x01) == FALSE)
	{
		return(FALSE);
	}
	
	for(i = 0; i < ui8NoOfBytes; i++)
	{
		if(i == (ui8NoOfBytes - 1))
		{
			if(I2C_receiveByte(0) == FALSE)
			{
				return(FALSE);
			}
		}
		else
		{
			if(I2C_receiveByte(1) == FALSE)
			{
				return(FALSE);
			}
		}
		*pData = TWDR;
		pData++;
	}
	if(I2C_stop() == FALSE)
	{
		return(FALSE);
	}
	return(TRUE);
}