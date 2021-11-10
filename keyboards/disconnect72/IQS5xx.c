#include "config.h"
#include "IQS5xx.h"
#include "print.h"
#include "pointing_device.h"
#include "quantum.h"
#include "mousekey.h"
#include "adafruit_ble.h"
#include "outputselect.h"

extern uint8_t Data_Buff[44];

__attribute__((weak)) void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y) {
    mouse_report->x = x;
    mouse_report->y = y;
}

bool holdingMouse1 = FALSE;

void Process_XY(void) {
#ifdef BLUETOOTH
    bool release = FALSE;
#endif
    bool sendMovement = TRUE;
    // bool holdingMouse2 = FALSE;
    // uint8_t 	i;
    static uint8_t ui8FirstTouch = 0;
    uint8_t        ui8NoOfFingers;
    // uint8_t        ui8SystemFlags[2];
    int16_t i16RelX[6];
    int16_t i16RelY[6];
    uint8_t buttons = 0;
    // int8_t         mouseWheel   = 0;
    uint8_t        output       = get_output();
    report_mouse_t mouse_report = {};

    // these could be useable
    // int8_t         mousePan = 0;
    // uint16_t ui16TouchStrength[6];
    // uint8_t  	ui8Area[6];
    ui8NoOfFingers    = Data_Buff[4];

    if (output == OUTPUT_USB) mouse_report = pointing_device_get_report();
    // single click
    if ((Data_Buff[0]) == SINGLE_TAP) {
        sendMovement = FALSE;
        if (output == OUTPUT_USB) {
            tap_code(KC_BTN1);
        }
        if (holdingMouse1) {
            holdingMouse1 = FALSE;
        }
        buttons = 1;
        uprintf("%u tap\n", buttons);
#ifdef BLUETOOTH
        release = TRUE;
#endif

    }
    // double click
    else if ((Data_Buff[1]) == TWO_FINGER_TAP) {
        if (output == OUTPUT_USB) {
            tap_code(KC_BTN2);
        }
        buttons = 2;
        uprintf("%u tap\n", buttons);
#ifdef BLUETOOTH
        release = TRUE;
#endif
        sendMovement = FALSE;
    }

    i16RelX[1] = ((Data_Buff[5] << 8) | (Data_Buff[6]));
    i16RelY[1] = ((Data_Buff[7] << 8) | (Data_Buff[8]));
    // uprintf("%d x \n", Data_Buff[5]);

    // first finger touch strength
    // ui16TouchStrength[1] = ((Data_Buff[13] << 8) | (Data_Buff[14])); //13-20-27-34-11/14-21-28-35-42

    // uprintf("\ntouch strength %u", ui16TouchStrength[1]);

    if (ui8NoOfFingers != 0 || buttons) {
        if (!(ui8FirstTouch)) {
            print("Data:\n");
            ui8FirstTouch = 1;
        }

        switch (Data_Buff[0]) {
            case TAP_AND_HOLD:
                print("tap n hold");
                if (!holdingMouse1) {
                    buttons       = 1;
                    holdingMouse1 = TRUE;
#ifdef BLUETOOTH
                    release = FALSE;
#endif
                } else {
                    holdingMouse1 = TRUE;
#ifdef BLUETOOTH
                    release = FALSE;
#endif
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
                    if (i16RelY[1] < 0) {
                        // mouseWheel = MOUSEWHEEL_SENSITIVITY;
                        tap_code(KC_MS_WH_DOWN);
                        wait_ms(5);

                    } else {
                        // mouseWheel = MOUSEWHEEL_SENSITIVITY * -1;
                        tap_code(KC_MS_WH_UP);
                        wait_ms(5);
                    }
                    sendMovement = FALSE;
                    if (output == OUTPUT_BLUETOOTH) {
                        wait_ms(MOUSEKEY_WHEEL_DELAY);
                    }
                    break;
                }

            case ZOOM:
                if (ZOOM_ENABLED) {
                    if (i16RelX[1] > 0) {
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
        if (i16RelX[1] < -120) i16RelX[1] = 0;
        if (i16RelX[1] > 120) i16RelX[1] = 0;
        if (i16RelY[1] < -120) i16RelY[1] = 0;
        if (i16RelY[1] > 120) i16RelY[1] = 0;

        uprintf("x %d y %d\n", i16RelX[1], i16RelY[1]);

        if (output == OUTPUT_BLUETOOTH) {
#ifdef BLUETOOTH
            if ((sendMovement && buttons == 0) || (sendMovement && holdingMouse1) || release != 0) {
                adafruit_ble_send_mouse_move((int8_t)i16RelX[1], (int8_t)i16RelY[1], mouseWheel, 0, buttons, release);

            } else {
                adafruit_ble_send_mouse_move(0, 0, mouseWheel, 0, buttons, release);
            }
#endif
        } else if (output == OUTPUT_USB) {
            if (sendMovement) {
                process_mouse_user(&mouse_report, (int16_t)i16RelX[1] * -1, (int16_t)i16RelY[1] * -1);
                pointing_device_set_report(mouse_report);
                pointing_device_send();
            } else {
                process_mouse_user(&mouse_report, 0, 0);
                pointing_device_set_report(mouse_report);
                pointing_device_send();
            }
        } else {
            print("unknown output");
        }
#ifdef BLUETOOTH
        release = FALSE;
#endif
    } else {
        ui8FirstTouch = 0;
    }
}