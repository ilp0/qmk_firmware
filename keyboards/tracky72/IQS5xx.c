#include "defs.h"
#include "i2c_fns.h"
#include "IQS5xx.h"
#include "print.h"
#include "pointing_device.h"
#include "quantum.h"
#include "mousekey.h"

extern uint8_t  Data_Buff[44];
extern uint16_t ui16SnapStatus[15], ui16PrevSnap[15];

//*****************************************************************************
//
//! Acknowledge the reset flag
//!
//! This function simply sets the ACK_RESET bit found in the SYSTEM_CONTROL_0
//! register.  By setting this bit the SHOW_RESET flag is cleared in the
//! SYSTEM_INFO_0 register.  During normal operation, the SHOW_RESET bit can be
//! monitored and if it becomes set, then an unexpected reset has occurred.
//! If any device configuration is needed, it must then be repeated.
//!
//! \param None
//!
//! \return None
//
//*****************************************************************************
void IQS5xx_AcknowledgeReset(void) {
    static uint8_t System_ctrl_0 = ACK_RESET;

    I2C_Write(SystemControl0_adr, &System_ctrl_0, 1);
}

//*****************************************************************************
//
//! Read and display version
//!
//! This function reads the version details from the IQS5xx and sends this to
//! the display port.
//!
//! \param None
//!
//! \return None
//
//*****************************************************************************
void IQS5xx_CheckVersion(void) {
    uint8_t ui8DataBuffer[6];
    //
    // Dont wait for RDY here, since the device could be in EventMode, and then
    // there will be no communication window to complete this.  Rather do a
    // forced communication, where clock stretching will be done on the IQS5xx
    // until an appropriate time to complete the i2c.
    //
    I2C_Read(ProductNumber_adr, &ui8DataBuffer[0], 6);

    print("Product ");
    uprintf("%u", (ui8DataBuffer[0] << 8) + ui8DataBuffer[1]);
    print("  Project ");
    uprintf("%u", (ui8DataBuffer[2] << 8) + ui8DataBuffer[3]);
    print("  Version ");
    uprintf("%u", ui8DataBuffer[4]);
    print(".");
    uprintf("\n%u", ui8DataBuffer[5]);
}

//*****************************************************************************
//
//! Display a snap state change
//!
//! If the state of any snap output has changed, then this function can be used
//!	to display which Rx/Tx channel has changed status.
//!
//! \param None
//!
//! \return None
//
//*****************************************************************************
void DisplaySnap(void) {
    uint8_t  ui8Tx, ui8Rx;
    uint16_t ui16ToggledBits;

    for (ui8Tx = 0; ui8Tx < 15; ui8Tx++) {
        ui16ToggledBits = ui16PrevSnap[ui8Tx] ^ ui16SnapStatus[ui8Tx];

        for (ui8Rx = 0; ui8Rx < 10; ui8Rx++) {
            if (BitIsSet(ui16ToggledBits, ui8Rx)) {
                if (BitIsSet(ui16SnapStatus[ui8Tx], ui8Rx)) {
                    print("Snap set on Rx");
                } else {
                    print("Snap released on Rx");
                }
                uprintf("%u", ui8Rx);
                print("/Tx");
                uprintf("%u", ui8Tx);
                uprintf("\n channel    ");
            }
        }
    }
}

__attribute__((weak)) void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y, bool release, uint8_t buttons) {
    if (x < -127) x = -127;
    if (x > 127) x = 127;
    if (y < -127) y = -127;
    if (y > 127) y = 127;
    mouse_report->release = release;
    mouse_report->x       = x;
    mouse_report->y       = y;
    mouse_report->buttons = buttons;
}

bool holdingMouse1 = FALSE;
bool holdingMouse2 = FALSE;

//*****************************************************************************
//
//! Process the data received
//!
//! This function sorts the read bytes from the IQS5xx and prints relevant data
//! on serial port.
//! REL_X[n]: Relative X Position of the finger n; n is from (1 to 5)
//! REL_Y[n]: Relative X Position of the finger n; n is from (1 to 5)
//! ABS_X[n]: Absolute X Position of the finger n; n is from (1 to 5)
//! ABS_Y[n]: Absolute Y Position of the finger n; n is from (1 to 5)
//! ui16TouchStrength[n]   : Touch strength of finger n; n is from (1 to 5)
//! ui8Area[n]   : Touch area of finger n; this is number of channels under touch
//! for a particular finger;
//! Where 'n' is from (1 to 5)
//!
//! \param None
//!
//! \return None
//
//*****************************************************************************
void Process_XY(void) {
    bool           release      = FALSE;
    static int16_t halfway      = 0;
    bool           sendMovement = TRUE;
    // uint8_t 	i;
    static uint8_t ui8FirstTouch = 0;
    uint8_t        ui8NoOfFingers;
    uint8_t        ui8SystemFlags[2];
    int16_t        i16RelX[6];
    int16_t        i16RelY[6];
    uint8_t        buttons = 0;
    // these could be useable
    // uint16_t ui16TouchStrength[6];
    // uint8_t  	ui8Area[6];

    ui8SystemFlags[0] = Data_Buff[2];
    ui8SystemFlags[1] = Data_Buff[3];
    ui8NoOfFingers    = Data_Buff[4];
    //
    // Re-initialize the device if unexpected RESET detected
    //
    if ((ui8SystemFlags[0] & SHOW_RESET) != 0) {
        print("\nRESET DETECTED");
        IQS5xx_AcknowledgeReset();
        return;
    }

    if ((ui8SystemFlags[1] & SNAP_TOGGLE) != 0) {
        // A snap state has changed, thus indicate which channel
        DisplaySnap();
        return;
    }

    report_mouse_t mouse_report = pointing_device_get_report();

    // single click
    if ((Data_Buff[0]) == SINGLE_TAP) {
        tap_code(KC_BTN1);
        sendMovement=FALSE;
        buttons       = 1;
        if (holdingMouse1) {
            holdingMouse1 = FALSE;
            release       = TRUE;
        }
    }
    // double click
    else if ((Data_Buff[1]) == TWO_FINGER_TAP) {
        tap_code(KC_BTN2);
        sendMovement=FALSE;
        buttons      = 2;
        release      = TRUE;
    }

    i16RelX[1] = ((Data_Buff[5] << 8) | (Data_Buff[6]));
    i16RelY[1] = ((Data_Buff[7] << 8) | (Data_Buff[8]));
    // first finger touch strength
    // ui16TouchStrength[1] = ((Data_Buff[13] << 8) | (Data_Buff[14])); //13-20-27-34-11/14-21-28-35-42

    // uprintf("\ntouch strength %u", ui16TouchStrength[1]);

    if (ui8NoOfFingers != 0) {
        if (!(ui8FirstTouch)) {
            // print("Data:\n");
            ui8FirstTouch = 1;
        }

        switch (Data_Buff[0]) {
            case TAP_AND_HOLD:
                if (!holdingMouse1) {
                    buttons       = 1;
                    holdingMouse1 = TRUE;
                    release       = FALSE;
                } else {
                    holdingMouse1 = TRUE;
                    release       = FALSE;
                }
                break;
                
        }

        switch (Data_Buff[1]) {
            /*case TWO_FINGER_TAP:
                tap_code(KC_BTN2);
                release = TRUE;
                break;*/
            case SCROLL:
                if (SCROLL_ENABLED) {
                    if (i16RelY[1] < halfway) {
                        tap_code(KC_MS_WH_DOWN);
                    } else {
                        tap_code(KC_MS_WH_UP);
                    }
                    sendMovement = FALSE;

                    break;
                }

            case ZOOM:
                if (ZOOM_ENABLED) {
                    if (i16RelX[1] > halfway) {
                        sendMovement = FALSE;
                        tap_code16(LCTL(KC_MINUS));
                        // print("zoom minus\n");

                    } else {
                        // print("zoom plus:\n");
                        tap_code16(LCTL(KC_PLUS));
                    }
                    sendMovement = FALSE;
                }

                break;
        }

        // absolute position for 5 fingers
        /*for (i = 0; i < 5; i++)
        {
            ui16AbsX[i+1] = ((Data_Buff[(7*i)+9] << 8) | (Data_Buff[(7*i)+10])); //9-16-23-30-37//10-17-24-31-38
            ui16AbsY[i+1] = ((Data_Buff[(7*i)+11] << 8) | (Data_Buff[(7*i)+12])); //11-18-25-32-39//12-19-26-33-40
            ui16TouchStrength[i+1] = ((Data_Buff[(7*i)+13] << 8) | (Data_Buff[(7*i)+14])); //13-20-27-34-11/14-21-28-35-42
            ui8Area[i+1] = (Data_Buff[7*i+15]); //15-22-29-36-43
        }*/
        if(sendMovement) {
            process_mouse_user(&mouse_report, (int16_t)i16RelX[1], (int16_t)i16RelY[1], release, buttons);
            pointing_device_set_report(mouse_report);
            pointing_device_send();
        } else if (sendMovement && holdingMouse1) {
            process_mouse_user(&mouse_report, (int16_t)i16RelX[1], (int16_t)i16RelY[1], release, buttons);
            pointing_device_set_report(mouse_report);
            pointing_device_send();
        } else {
            process_mouse_user(&mouse_report, 0, 0, release, buttons);
            pointing_device_set_report(mouse_report);
            pointing_device_send();
        }
        release = FALSE;
    } else {
        ui8FirstTouch = 0;
    }
}