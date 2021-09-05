#include "tracky72.h"

enum layers {
    _QWERTY
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_QWERTY] = KEYMAP_DEFAULT(
		KC_7, KC_8, KC_9, KC_0, KC_PLUS, KC_EQL, KC_BSPC, 
		KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_ENT, 
		KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NUHS, 
		KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, 
		KC_SPC, KC_RALT, KC_LGUI, KC_APP, MO(0), KC_LCTL),
};

void matrix_init_user(void) {
}


void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

