#include "disconnect72.h"
#include <stdio.h>
#include "outputselect.h"
#include "adafruit_ble.h"

enum layers { _QWERTY, _FN, _ARROW };

#ifdef OLED_ENABLE
char    wpm_str[10];
char    kc_string[10];
uint8_t kc_string_rows = 0;
char    battery_str[10];
static uint16_t oled_timer   = 0;
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
                KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,
                MO(1), KC_A, KC_S, KC_D, KC_F, KC_G, KC__MUTE, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
                KC_LSFT, KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                KC_LCTL, KC_LGUI, KC_LALT, DF(2), KC_BSPC, KC_SPC, KC_ENT, KC_MUTE, KC_SPC, KC_RALT, KC_RGUI, KC_RCTL, KC_APP, MO(1)),

    [_FN] = LAYOUT(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
            KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_INS),
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, OUT_AUTO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, OUT_BT, OUT_USB, RESET, KC_TRNS, KC_TRNS, KC_DOWN, KC_LEFT, KC_RGHT, KC_TRNS),

    [_ARROW] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
            KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,
            MO(1), KC_A, KC_S, KC_D, KC_F, KC_G, KC__MUTE, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
            KC_LSFT, KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, KC_RSFT,
            KC_LCTL, KC_LGUI, KC_LALT, DF(0), KC_BSPC, KC_SPC, KC_ENT, KC_MUTE, KC_SPC, KC_RALT, KC_DOWN, KC_LEFT, KC_RGHT, MO(1)),

};

void matrix_init_user(void) {}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u\n", keycode, record->event.key.col, record->event.key.row);
#endif
#ifdef OLED_ENABLE
    if (kc_string_rows > 4) kc_string_rows = 0;
    oled_set_cursor(0, 9 + kc_string_rows);
    sprintf(kc_string, "0x%03X", keycode);
    kc_string[5] = '\0';
    oled_write(kc_string, false);
    kc_string_rows++;
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
    return false;
}*/

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    return false;
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_90; }

void oled_task_user(void) {
    if (timer_elapsed(oled_timer) > 20) {
        oled_timer = timer_read();
        uint8_t output = get_output();
        // Host Keyboard Layer Status
        switch (get_highest_layer(layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("QWERT\n"), false);
                break;
            case _FN:
                oled_write_P(PSTR("FN\n"), false);
                break;
            case _ARROW:
                oled_write_P(PSTR("ARROW\n"), false);
                break;
            default:
                // Or use the write_ln shortcut over adding '\n' to the end of your string
                oled_write_ln_P(PSTR("Undf\n"), false);
        }
        oled_set_cursor(0, 2);
        if (output == OUTPUT_BLUETOOTH) oled_write_P(PSTR("BLE\n"), false);
        if (output == OUTPUT_USB) oled_write_P(PSTR("USB\n"), false);
        if (output == OUTPUT_AUTO) oled_write_P(PSTR("AUTO\n"), false);
        oled_set_cursor(0, 4);
        oled_write_P(PSTR("WPM\n"), false);
        oled_set_cursor(0, 5);
        sprintf(wpm_str, "%03d\n", get_current_wpm());
        oled_write(wpm_str, false);
        oled_set_cursor(0, 7);
        sprintf(battery_str, "%03d%%\n",adafruit_ble_read_battery_level());
        oled_write(battery_str, false);
    }
}
#endif
