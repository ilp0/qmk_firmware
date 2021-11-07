#include "pointing_device.h"
//#include "i2c_fns.h"
#include "defs.h"
#include "IQS5xx.h"
#include "trackpad.h"
#include "print.h"
#include "quantum.h"
#include "outputselect.h"
#include "i2c_master.h"

uint8_t 	Data_Buff[44];
uint8_t     activeRefreshRate[2] = {0, TRACKPAD_RATE};
uint8_t     idleRefreshRate[2] = {0,20};
uint16_t	ui16SnapStatus[15], ui16PrevSnap[15];

void pointing_device_init(void) { 
    print("\ntrackpad setup start\n");
	// Configure RDY pin
	//
	//setPinInputHigh(RDY_PIN);
	
	//I2C_Setup();

    i2c_writeReg16(IQS5xx_ADDR<<1, ActiveRR_adr, &activeRefreshRate[0], 2, 20);
    i2c_writeReg16(IQS5xx_ADDR<<1, IdleRR_adr, &idleRefreshRate[0], 2, 20);
    i2c_writeReg16(IQS5xx_ADDR<<1, IdleTouchRR_adr, &idleRefreshRate[0], 2, 20);
    i2c_writeReg16(IQS5xx_ADDR<<1, LP1RR_adr, &idleRefreshRate[0], 2, 20);
    i2c_writeReg16(IQS5xx_ADDR<<1, LP2RR_adr, &idleRefreshRate[0], 2, 20);
	//
	// End the communication window
	//

	set_output(OUTPUT_USB);

}


void pointing_device_task(void) {
    uint8_t		ui8TempData[30], i;

	//RDY_wait();
	i2c_readReg16(IQS5xx_ADDR<<1, GestureEvents0_adr, &Data_Buff[0], 44, 20);
	if((Data_Buff[3] & SNAP_TOGGLE) != 0)
	{
		// If there was a change in a snap status, then read the snap status 
		// bytes additionally. Keep previous valus to identify a state change
		//
		i2c_readReg16(IQS5xx_ADDR<<1,SnapStatus_adr, &ui8TempData[0], 30, 20);
		for(i = 0; i < 15; i++)
		{
			ui16PrevSnap[i] = ui16SnapStatus[i];
			ui16SnapStatus[i] = ((uint16_t)(ui8TempData[2*i])<<8) + 
								 (uint16_t)ui8TempData[(2*i)+1];
		}
	}
	// Process received data 
	//
	Process_XY();

}
