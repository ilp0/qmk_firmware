#include "tracky72.h"

enum layers { _QWERTY, _FN };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,                         KC_7,       KC_8,   KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSPC, 
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                               KC_Y,       KC_U,   KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC, 
    MO(1), KC_A, KC_S, KC_D, KC_F, KC_G, KC__MUTE,                      KC_H,       KC_J,   KC_K,       KC_L,       KC_SCLN,    KC_QUOT,    KC_HASH,  KC_ENT, 
    KC_LSFT, KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B,                     KC_B,       KC_N,   KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT, 
    KC_LCTL, KC_LGUI, KC_LALT, MO(1), KC_BSPC, KC_SPC, KC_ENT,           KC_MUTE,    KC_SPC, KC_RALT,    KC_RGUI,   KC_RCTL,    KC_APP,     MO(1)
),

    [_FN] = LAYOUT(
    KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                   KC_F7,   KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, 
    KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, OUT_AUTO,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP,     KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, OUT_BT, OUT_USB,       RESET,   KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT,   KC_TRNS
    ),
};

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

#ifdef OLED_ENABLE
void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("FN\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}
#endif