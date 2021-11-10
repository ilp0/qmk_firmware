#include "disconnect72.h"
#include <stdio.h>
#include "outputselect.h"

enum layers { _QWERTY, _FN };

#ifdef OLED_ENABLE
char    wpm_str[10];
char    kc_string[10];
uint8_t kc_string_rows = 0;
#endif

enum custom_keycodes {
    KEY_TIMER = SAFE_RANGE,
};

static uint32_t key_timer    = 0;
static uint16_t oled_timer   = 0;
static bool     key_trigger  = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, MO(1), KC_A, KC_S, KC_D, KC_F, KC_G, KC__MUTE, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT, KC_LSFT, KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LCTL, KC_LGUI, KC_LALT, MO(1), KC_BSPC, KC_SPC, KC_ENT, KC_MUTE, KC_SPC, KC_RALT, KC_RGUI, KC_RCTL, KC_APP, MO(1)),

    [_FN] = LAYOUT(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LSFT(KC_INS), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, OUT_AUTO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KEY_TIMER, OUT_BT, OUT_USB, RESET, KC_TRNS, KC_TRNS, KC_DOWN, KC_LEFT, KC_RGHT, KC_TRNS),
};

void matrix_init_user(void) {}

void matrix_scan_user(void) {
    if (timer_elapsed32(key_timer) > 30000) {  // 30 seconds
        key_timer = timer_read32();            // resets timer
        if (key_trigger) tap_code(KC_NO);      // tap if enabled
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u\n", keycode, record->event.key.col, record->event.key.row);
#endif
    switch (keycode) {
        case KEY_TIMER:
            if (record->event.pressed) {
                key_trigger ^= true;
            }
            break;
    }
#ifdef OLED_ENABLE
    if (kc_string_rows > 6) kc_string_rows = 0;
    oled_set_cursor(0, 8 + kc_string_rows);
    sprintf(kc_string, "0x%03X", keycode);
    kc_string[5] = '\0';
    oled_write(kc_string, false);
    kc_string_rows++;
#endif
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (!clockwise) {
        tap_code(KC_VOLD);
    } else {
        tap_code(KC_VOLU);
    }
    return true;
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
            default:
                // Or use the write_ln shortcut over adding '\n' to the end of your string
                oled_write_ln_P(PSTR("Undf\n"), false);
        }
        oled_set_cursor(0, 2);
        if (output == OUTPUT_BLUETOOTH) oled_write_P(PSTR("BLE\n"), false);
        if (output == OUTPUT_USB) oled_write_P(PSTR("USB\n"), false);
        if (output == OUTPUT_AUTO) oled_write_P(PSTR("AUTO\n"), false);
        oled_set_cursor(0, 4);
        oled_write_P(PSTR("Idle:\n"), false);
        oled_set_cursor(0, 5);
        if (key_trigger)
            oled_write_P(PSTR("ON\n"), false);
        else
            oled_write_P(PSTR("OFF\n"), false);
        oled_set_cursor(0, 7);
        sprintf(wpm_str, "%02dKPS\n", (int)((float)get_current_wpm() / 60 * 5));
        oled_write(wpm_str, false);
        oled_set_cursor(0, 8);
    }
}
#endif
