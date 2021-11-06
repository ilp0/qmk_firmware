#pragma once

//enable or disable gestures here
#define ZOOM_ENABLED            FALSE
#define SCROLL_ENABLED          TRUE

#define IQS5xx_ADDR          	0x74
//#define RDY_PIN              	B7
#define	END_WINDOW				(uint16_t)0xEEEE

#define BitIsSet(VAR,Index)		(VAR & (1<<Index)) != 0
#define BitIsNotSet(VAR,Index)	(VAR & (1<<Index)) == 0

#define SetBit(VAR,Index)		VAR |= (1<<Index)
#define ClearBit(VAR,Index)		VAR &= (uint8_t)(~(1<<Index))

#define FALSE 					0
#define	TRUE 					!FALSE

#define MOUSEWHEEL_SENSITIVITY 1

void Process_XY(void);