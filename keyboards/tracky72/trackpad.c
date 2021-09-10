#include "pointing_device.h"
#include "i2c_fns.h"
#include "defs.h"
#include "IQS5xx.h"
#include "trackpad.h"
#include "print.h"
#include "quantum.h"
#include "outputselect.h"

uint8_t 	Data_Buff[44];
uint8_t     activeRefreshRate[2] = {0, TRACKPAD_RATE};
uint8_t     idleRefreshRate[2] = {0,20};


uint16_t	ui16SnapStatus[15], ui16PrevSnap[15];

void pointing_device_init(void) { 
    print("\ntrackpad setup start\n");
	// Configure RDY pin
	//
	setPinInputHigh(RDY_PIN);
	
	I2C_Setup();
	//
	// Clear the reset indication bit, so that from here on a reset can be 
	// detected if the bit becomes set
	//
	IQS5xx_AcknowledgeReset();
	//
	// Read the version and display on the serial terminal
	//
	IQS5xx_CheckVersion();


    I2C_Write(ActiveRR_adr, &activeRefreshRate[0], 2);
    I2C_Write(IdleRR_adr, &idleRefreshRate[0], 2);
    I2C_Write(IdleTouchRR_adr, &idleRefreshRate[0], 2);
    I2C_Write(LP1RR_adr, &idleRefreshRate[0], 2);
    I2C_Write(LP2RR_adr, &idleRefreshRate[0], 2);

	//
	// End the communication window
	//
	Close_Comms();

	set_output(OUTPUT_USB);

}


void pointing_device_task(void) {
    uint8_t		ui8TempData[30], i;

	RDY_wait();
	
	I2C_Read(GestureEvents0_adr, &Data_Buff[0], 44);

	if((Data_Buff[3] & SNAP_TOGGLE) != 0)
	{
		// If there was a change in a snap status, then read the snap status 
		// bytes additionally. Keep previous valus to identify a state change
		//
		I2C_Read(SnapStatus_adr, &ui8TempData[0], 30);
		for(i = 0; i < 15; i++)
		{
			ui16PrevSnap[i] = ui16SnapStatus[i];
			ui16SnapStatus[i] = ((uint16_t)(ui8TempData[2*i])<<8) + 
								 (uint16_t)ui8TempData[(2*i)+1];
		}
	}
	//
	// Terminate the communication session, so that the IQS5xx can continue 
	// with sensing and processing
	//
	Close_Comms();
	//
	// Process received data 
	//
	Process_XY();

}
