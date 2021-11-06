#ifndef tracky72_H
#define tracky72_H

#include "quantum.h"

#define KEYMAP_DEFAULT( \
		K00, 	K01, 	K02, 	K03, 	K04, 	K05, 	K06, 			K100, 	     	K102,	K103,	K104, K105, K106, 	K107, \
		K10, 	K11, 	K12, 	K13, 	K14, 	K15, 	     			K110, 	     	K112,	K113,	K114, K115, K116, 	K117, \
		K20, 	K21, 	K22, 	K23, 	K24, 	K25, 	K26,			K120, 	K121, 	K122, 	K123,	K124, K125, K126, 	K127, \
		K30, 	K31, 	K32, 	K33, 	K34, 	K35, 	K36, 			K130, 	     	K132, 	K133,	K134, K135, K136, 	K137, \
		K40, 	K41, 	K42, 	K43, 	K44, 	K45, 	K46,    		K140, 	K141, 	K142, 	K143,	K144, K145,      	K147  \
) { \
	{ 	K00,   	K01,   	K02,   	K03,   	K04,   	K05,   	K06,   	KC_NO }, \
	{ 	K10,   	K11,   	K12,   	K13,   	K14,   	K15,   	KC_NO,  KC_NO }, \
	{ 	K20,   	K21,   	K22,   	K23,   	K24,   	K25,   	K26,   	KC_NO }, \
	{ 	K30,   	K31,   	K32,   	K33,   	K34,   	K35,   	K36,   	KC_NO }, \
	{ 	K40,   	K41,   	K42,   	K43,   	K44,   	K45,   	K46,   	KC_NO },  \
	{ 	K100,   KC_NO, 	K102,	K103,	K104,	K105,   K106,   K107 }, \
	{ 	K110,   KC_NO, 	K112,	K113,	K114,	K115,   K116,   K117 }, \
	{ 	K120,   K121,  	K122,	K123,	K124,	K125,   K126,   K127 }, \
	{ 	K130,   KC_NO, 	K132,	K133,	K134,	K135,   K136,   K137 }, \
	{ 	K140,   K141,  	K142,	K143,	K144,	K145,   KC_NO,  K147 }  \
}

#endif