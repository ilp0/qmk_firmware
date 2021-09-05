#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x8888
#define PRODUCT_ID      0x7272
#define DEVICE_VER      0x0001
#define MANUFACTURER    Ilpo Loikkanen
#define PRODUCT         tracky72
#define DESCRIPTION     Split Keyboard

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

#define AdafruitBleResetPin D4
#define AdafruitBleCSPin B4
#define AdafruitBleIRQPin E6

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 9

/* key matrix pins 
#define MATRIX_ROW_PINS { B0, B1, B2, B3, C6 }
#define MATRIX_COL_PINS { B5, B6, B7, C0, C1, C2, C3, C4, C5 }*/

#define MATRIX_ROW_PINS { NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN}
#define MATRIX_COL_PINS { NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN }

#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 0
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 1

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

#define MOUSEKEY_INTERVAL           20
#define MOUSEKEY_DELAY              0
#define MOUSEKEY_TIME_TO_MAX        60
#define MOUSEKEY_MAX_SPEED          7
#define MOUSEKEY_WHEEL_DELAY        400

