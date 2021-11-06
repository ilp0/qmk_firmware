#include "tracky72.h"

enum layers { _QWERTY, _MO1 };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = KEYMAP_DEFAULT(
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,                         KC_7,       KC_8,   KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSPC, 
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                               KC_Y,       KC_U,   KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC, 
    MO(1), KC_A, KC_S, KC_D, KC_F, KC_G, KC__MUTE,                      KC_H,       KC_J,   KC_K,       KC_L,       KC_SCLN,    KC_QUOT,    KC_HASH,  KC_ENT, 
    KC_LSFT, KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B,                     KC_B,       KC_N,   KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT, 
    KC_LCTL, KC_LGUI, KC_LALT, MO(1), KC_BSPC, KC_SPC, KC_ENT,           KC_MUTE,    KC_SPC, KC_RALT,    KC_RGUI,    MO(1),      KC_APP, KC_RCTL
),

    [_MO1] = KEYMAP_DEFAULT(
    KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                   KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, 
    KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, OUT_AUTO,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, OUT_BT, OUT_USB,        RESET, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS
    ),
};

/*
    [_QWERTY] = KEYMAP_DEFAULT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,
        MO(1), KC_A, KC_S, KC_D, KC_F, KC_G, KC__MUTE,
        KC_LSFT, KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B,
        KC_LCTL, KC_LGUI, KC_LALT, MO(1), KC_BSPC, KC_SPC, KC_ENT),

    [_MO1] = KEYMAP_DEFAULT(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
        KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, OUT_AUTO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, OUT_BT, OUT_USB),
        */
void matrix_init_user(void) {}

void matrix_scan_user(void) {}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
   uprintf("KL: kc: 0x%04X, col: %u, row: %u\n", keycode, record->event.key.col, record->event.key.row);
#endif
    return true;
}
/*
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (!clockwise) {
        tap_code(KC_VOLD);
    } else {
        tap_code(KC_VOLU);
    }
    return true;
}*/

// OLED STUFF STARTS HERE
// based on https://github.com/qmk/qmk_firmware/blob/master/keyboards/kyria/keymaps/j-inc/keymap.c

// In your rules.mk make sure you have:
// OLED_DRIVER_ENABLE = yes
// WPM_ENABLE = yes

#ifdef OLED_ENABLE
// WPM-responsive animation stuff here

// Used to draw on to the oled screen
void oled_task_user(void) {

    oled_set_cursor(0, 0);                        // sets cursor to (row, column) using charactar spacing (5 rows on 128x32 screen, anything more will overflow back to the top)
    led_t led_state = host_keyboard_led_state();  // caps lock stuff, prints CAPS on new line if caps led is on
    oled_set_cursor(0, 1);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS") : PSTR("       "), false);
}
#endif