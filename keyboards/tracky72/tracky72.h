#ifndef tracky72_H
#define tracky72_H

#include "quantum.h"

#define KEYMAP_DEFAULT( \
	     K01, K02, K03, K04, K05, K06, K07,      \
	K10, K11, K12, K13, K14, K15, K16, K17,      \
	     K21, K22, K23, K24, K25, K26, K27,      \
	K30, K31, K32, K33, K34, K35,      K37,      \
	     K41,      K43, K44, K45, K46, K47  \
) { \
	{ KC_NO, K01,   K02,   K03,   K04,   K05,   K06,   K07,   KC_NO }, \
	{ K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   KC_NO }, \
	{ KC_NO, K21,   K22,   K23,   K24,   K25,   K26,   K27,   KC_NO }, \
	{ K30,   K31,   K32,   K33,   K34,   K35,   KC_NO, K37,   KC_NO }, \
	{ KC_NO, K41,   KC_NO, K43,   K44,   K45,   K46,   K47,   KC_NO }  \
}

#endif
