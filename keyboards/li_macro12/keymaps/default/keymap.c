
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_MUTE,    KC_MPRV , KC_MPLY   ,    KC_MNXT,
        KC_NO,      KC_ESC  , KC_MINS   ,      MO(1),
        KC_NO,      KC_F2   , KC_SLASH  ,    C(KC_R),
        KC_NO,      KC_Z    , KC_X      ,      KC_C
    ),

    [1] = LAYOUT(
        KC_MUTE, KC_PSCR, C(KC_PSCR), S(KC_PSCR),
        KC_NO,  KC_TRNS, RESET, KC_TRNS,
        KC_NO,  KC_PGDN, KC_UP , KC_PGUP,
        KC_NO,  KC_LEFT, KC_DOWN, KC_RGHT
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {

    switch(biton32(layer_state)){
        case 1:
            if (clockwise) {
                tap_code16(C(KC_Z));
            } else {
                tap_code16(C(KC_Y));
            }
            break;
        default:
            if (clockwise){
                tap_code(KC_VOLD);
            } else{
                tap_code(KC_VOLU);
            }
    }
} 

