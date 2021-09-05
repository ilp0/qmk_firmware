

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0012
#define DEVICE_VER      0x0001
#define MANUFACTURER    Ilpo Loikkanen
#define PRODUCT         li-macro12
#define DESCRIPTION     4x3 Macropad with a Rotary Encoder

/* key matrix size */
#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

/* Keyboard Matrix Assignments */ 

#define MATRIX_ROW_PINS {B6,B5,B4,E6}
#define MATRIX_COL_PINS {D1,B1,F7,B3}

#define ENCODERS_PAD_A { D0 }
#define ENCODERS_PAD_B { D4 }


/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
