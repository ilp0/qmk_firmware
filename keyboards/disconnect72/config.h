#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x8888
#define PRODUCT_ID      0x7272
#define DEVICE_VER      0x0001
#define MANUFACTURER    Ilpo Loikkanen
#define PRODUCT         disconnect72
#define DESCRIPTION     Split Keyboard

//shrink firmware size
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT
#define NO_ACTION_ONESHOT

#define LEFTSIDE

#ifdef LEFTSIDE
#define AdafruitBleResetPin D4
#define AdafruitBleCSPin B4
#define AdafruitBleIRQPin E6
#endif

// CUSTOM STUFF

#define MASTER_LEFT 
#define USE_I2C
#define EE_HANDS

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 8

/* key matrix pins */
#define MATRIX_ROW_PINS { F7, F6, F5, F4, F1 }
#define MATRIX_COL_PINS { F0, B6, C7, D6, B7, D3, C6 }

#define MATRIX_ROW_PINS_RIGHT { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS_RIGHT { D3, B5, B6, B2, B3, B1, F7, F6 }

#define ENCODERS_PAD_A { B5 }
#define ENCODERS_PAD_B { D7 }

#define ENCODERS_PAD_A_RIGHT { F5 }
#define ENCODERS_PAD_B_RIGHT { F4 }

#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 0
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 4

/* reduce polling rate to 1000hz */
#define USB_POLLING_INTERVAL_MS 1

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

#endif

#define FALSE 					0
#define	TRUE 					!FALSE

/**
 * 
 * TRACKPAD STUFF
 * 
 */
#define MOUSEKEY_INTERVAL           8
#define MOUSEKEY_DELAY              0
#define MOUSEKEY_TIME_TO_MAX        60
#define MOUSEKEY_MAX_SPEED          6
#define MOUSEKEY_WHEEL_DELAY        400
#define MOUSEWHEEL_SENSITIVITY      1
#define TRACKPAD_RATE       10
//enable / disable gestures
#define ZOOM_ENABLED            FALSE
#define SCROLL_ENABLED          TRUE

#define IQS5xx_ADDR          	0x74
#define RDY_PIN              	D2
#define	END_WINDOW				(uint16_t)0xEEEE


