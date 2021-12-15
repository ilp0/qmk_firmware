// Copyright 2021 ilp0 (@ilp0)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    KEY_TIMER = SAFE_RANGE,
};

static uint32_t key_timer    = 0;
static bool     key_trigger  = false;

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_MPRV,            KC_MPLY,            KC_MNXT,            KC_PSCREEN,     MO(_FN),
        KC_WWW_BACK,        KC_WWW_REFRESH,     KC_WWW_FORWARD,     KC_F13,         KC_MUTE 
    ),
    [_FN] = LAYOUT(
        RGB_MODE_FORWARD,   RGB_MODE_PLAIN,  RGB_HUI,       KEY_TIMER,        _______,
        RGB_TOG,            _______,         RGB_VAI,       RGB_VAD,          RESET
    )
};

void matrix_scan_user(void) {
    if (timer_elapsed32(key_timer) > 30000) {  // 30 seconds
        key_timer = timer_read32();            // resets timer
        if (key_trigger) tap_code(KC_BTN1);      // tap if enabled
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KEY_TIMER:
            if (record->event.pressed) {
                if(!key_trigger) rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
                else rgblight_reload_from_eeprom();
                if(key_trigger) key_trigger = false;
                else key_trigger = true;
            }
            break;
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
