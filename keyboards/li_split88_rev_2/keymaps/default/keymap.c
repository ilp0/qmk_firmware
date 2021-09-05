#include "li_split88.h"

enum layers {
    _QWERTY,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_QWERTY] = KEYMAP(
		KC_NLCK, 	KC_PSLS, KC_PAST, KC_PMNS, 	KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, 		KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BSPC, KC_INS, 
					KC_P7, KC_P8, KC_P9,  		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, 					KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, KC_ENT, KC_DEL,
		KC_PPLS, 	KC_P4, KC_P5, KC_P6, 		MO(1), KC_A, KC_S, KC_D, KC_F, KC_G, 					KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOT, KC_NONUS_HASH, 
					KC_P1, KC_P2, KC_P3, 		KC_LSFT, KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B, 				KC_N, KC_M, KC_COMM, KC_DOT, KC_SLASH, KC_RSFT, KC_PGUP, KC_UP, KC_PGDN, 
		KC_PENT, 	KC_PDOT, 	KC_P0,			KC_LCTL, KC_LGUI, KC_LALT, KC_LSFT, KC_BSPC, 		KC_SPC, KC_RALT, KC_RCTL, MO(1), KC_LEFT, KC_DOWN, KC_RGHT),

	[_FN] = KEYMAP(
		KC_TRNS, KC_PSCR, KC_TRNS, KC_TRNS, KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, RESET, 
		KC_F17, KC_F18, KC_F19, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_F14, KC_F15, KC_F16, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_F11, KC_F12, KC_F13, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_AUDIO_VOL_UP, KC_MEDIA_PLAY_PAUSE, 
		KC_F10, RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MEDIA_PREV_TRACK, KC_AUDIO_VOL_DOWN, KC_MEDIA_NEXT_TRACK),
};

void matrix_init_user(void) {
}


void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void led_set_user(uint8_t usb_led) {
	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_KANA)) {
		
	} else {
		
	}

}