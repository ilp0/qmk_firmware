#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6061
#define DEVICE_VER      0x0001
#define MANUFACTURER    Ilpo Loikkanen
#define PRODUCT         li-split88-rev2
#define DESCRIPTION     Split Keyboard
// CUSTOM STUFF

#define MASTER_LEFT 
#define SOFT_SERIAL_PIN D0


/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 11


/* key matrix pins */
#define MATRIX_ROW_PINS { B4, E6, D7, C6, D4 }
#define MATRIX_COL_PINS { B5, B6, B2, B3, B1, F7, F6, F5, F4, D3, D2}

#define MATRIX_ROW_PINS_RIGHT { B4, E6, D7, C6, D4 }
//A2, 0, 4, 6, 5, 

#define MATRIX_COL_PINS_RIGHT { D2, B5, B6, B2, B3, B1, F7, F6, F5}

//A0, A1, 15, 14, 16, 10, 9, 8, 7
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PINl
#define BACKLIGHT_LEVELS 0
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 1

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