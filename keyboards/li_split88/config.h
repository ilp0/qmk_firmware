#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Ilpo Loikkanen
#define PRODUCT         li-split88
#define DESCRIPTION     Split Keyboard
#define SOFT_SERIAL_PIN D3
// CUSTOM STUFF

#define MASTER_LEFT 


/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 11

/* key matrix pins */
#define MATRIX_ROW_PINS { D0, D2, D4, C6, D7 }
#define MATRIX_COL_PINS { B5, B6, B2, B3, B1, F7, F6, F4, F5, D3, D2}

#define MATRIX_ROW_PINS_RIGHT { F5, D2, D4, D7, C6 }
//A2, 0, 4, 6, 5, 

#define MATRIX_COL_PINS_RIGHT { E6, B4, B5, B6, B2, B3, B1, F6, F7}

//A0, A1, 15, 14, 16, 10, 9, 8, 7
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PINl
#define BACKLIGHT_LEVELS 0
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* reduce polling rate to 1000hz */
#define USB_POLLING_INTERVAL_MS 1

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

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