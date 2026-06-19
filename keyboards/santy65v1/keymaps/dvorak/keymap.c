// Copyright 2023-2026 Santiago Garcia (@santy81855)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _DVORAK,
    _GAMING,
    _SHIFT,
    _FN,
    _NUMBER,
    _ARROW,
};

enum custom_keycodes {
    GMAIL = SAFE_RANGE,
    WORK_EMAIL,
    DRAG_SCROLL,
    DRAG_SCROLL_V,
    DRAG_SCROLL_H,
    SB,
    CB,
};

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 15.0
#define SCROLL_DIVISOR_V 40.0

// variable used in the drag scroll functionality
bool set_scrolling = false;
bool set_scrolling_v = false;
bool set_scrolling_h = false;
// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v -= (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    // Check if drag scrolling vertical is active
    if (set_scrolling_v) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_v -= (float)mouse_report.y / SCROLL_DIVISOR_V;
        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.v = (int8_t)scroll_accumulated_v;
        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;
        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    // Check if drag scrolling horizontal is active
    if (set_scrolling_h) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;        
        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GMAIL:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("santyg81855@gmail.com");
            }
            break;
        case WORK_EMAIL:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("santyg818552@gmail.com");
            }
            break;
        case SB:
            if (record->event.pressed) {
                SEND_STRING("[]"SS_TAP(X_LEFT));
            }
            break;
        case CB:
            if (record->event.pressed) {
                SEND_STRING("{}"SS_TAP(X_LEFT));
            }
            break;
        case DRAG_SCROLL:
            set_scrolling = record->event.pressed;
            break;
        case DRAG_SCROLL_V:
            set_scrolling_v = record->event.pressed;
            break;
        case DRAG_SCROLL_H:
            set_scrolling_h = record->event.pressed;
            break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DVORAK] = LAYOUT(
    A(KC_F5), KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, G(KC_BSLS), A(KC_END), GMAIL, 
    A(KC_F3), KC_TAB, KC_SCLN, KC_COMMA, KC_DOT, KC_P, KC_Y, 		 		   		KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSLS, KC_LBRC, KC_RBRC, WORK_EMAIL, 
    A(KC_F2), KC_BSPC, KC_A, KC_O, KC_E, KC_U, KC_I, 		 						KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, KC_ENT, UG_TOGG, 
    A(KC_F1), MO(_SHIFT), KC_QUOTE, KC_Q, KC_J, KC_K, KC_X, 						KC_B, KC_M, KC_W, KC_V, KC_Z, MO(_SHIFT), KC_UP, 
    TO(_GAMING), KC_LCTL, KC_LGUI, KC_LALT, MO(_FN), MO(_NUMBER), KC_TRNS,		KC_SPACE, MO(_ARROW), KC_MPLY, KC_VOLD, KC_VOLU, KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    [_GAMING] = LAYOUT(
    KC_F7, KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, 						 	KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, MS_BTN1, 
    KC_F8, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, 		 		   						KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, KC_LBRC, KC_RBRC, MS_BTN2, 
    KC_F9, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, 		 								KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOTE, KC_ENT, KC_TRNS, 
    KC_F10, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, 										KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, KC_RSFT, KC_UP, 
    TO(_DVORAK), KC_LCTL, KC_LGUI, KC_LALT, KC_F11, KC_SPACE, KC_TRNS,					KC_SPACE, KC_SPACE, KC_MPLY, KC_VOLD, KC_VOLU, KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    [_SHIFT] = LAYOUT(
    KC_TRNS, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 					KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TILD,
    KC_TRNS, S(KC_TAB), KC_COLN, S(KC_COMM), S(KC_DOT), S(KC_P), S(KC_Y), 	S(KC_F), S(KC_G), S(KC_C), S(KC_R), S(KC_L), S(KC_BSLS), S(KC_LBRC), S(KC_RBRC), KC_GRV,
    KC_TRNS, C(KC_BSPC), S(KC_A), S(KC_O), S(KC_E), S(KC_U), S(KC_I),     S(KC_D), S(KC_H), S(KC_T), S(KC_N), S(KC_S), KC_UNDS, S(KC_ENT), KC_TRNS,
    KC_TRNS, KC_SLASH, KC_DQUO, S(KC_Q), S(KC_J), S(KC_K), S(KC_X), 			S(KC_B), S(KC_M), S(KC_W), S(KC_V), S(KC_Z), KC_EQL, KC_TRNS,
    TO(_GAMING), KC_LCTL, KC_LGUI, KC_LALT, MO(_FN), MO(_NUMBER), KC_TRNS,			 		KC_SPACE, KC_LGUI, KC_MPLY, KC_VOLD, KC_VOLU, KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    [_FN] = LAYOUT(
    KC_TRNS, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 					 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, A(KC_END), KC_TRNS,
    KC_TRNS, KC_TRNS, KC_SCLN, CB, SB, KC_TRNS, C(KC_L), 		 		 	 C(KC_F), KC_PGUP, KC_UP, C(KC_T), C(KC_N), C(S(KC_N)), UG_TOGG, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_BSPC, C(KC_A), C(KC_X), C(KC_C), KC_LSFT, C(KC_V), 				 KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, C(KC_S), KC_END, C(KC_GRV), KC_TRNS,
    KC_TRNS, KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_LALT, KC_LALT, 						  	 KC_TRNS, KC_PGDN, C(KC_W), C(S(KC_T)), KC_DEL, KC_LGUI, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LALT, KC_TRNS,			 				 KC_LCTL, KC_LCTL, KC_TRNS, KC_TRNS, KC_TRNS, G(C(KC_LEFT)), KC_TRNS, G(C(KC_RIGHT))
    ),

    [_NUMBER] = LAYOUT(
    KC_TRNS, KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 					KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, 		 	KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_BSPC, KC_1, KC_2, KC_3, KC_4, KC_5, 		 								KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_ENTER, KC_TRNS,
    KC_TRNS, KC_QUES, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 					KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_TRNS, KC_PLUS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,			 				KC_SPACE, MO(_ARROW), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_ARROW] = LAYOUT(
    KC_TRNS, KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, 							                KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, LSG(KC_S), KC_TRNS,
    KC_TRNS, KC_TRNS, LALT(KC_F13), LALT(KC_F14), LALT(KC_F15), LALT(KC_F16), LALT(KC_F22), 		 		   		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, LALT(KC_F17), LALT(KC_F18), LALT(KC_F19), LALT(KC_F20), LALT(KC_F21), 		 				                C(MS_BTN1), MS_BTN1, MS_BTN2, DRAG_SCROLL_V, DRAG_SCROLL_H, KC_TRNS, LCA(KC_O), KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LALT(KC_F23), LALT(KC_F24), KC_TRNS, 						                C(MS_BTN1), C(MS_BTN1), KC_TRNS, KC_TRNS, KC_TRNS, KC_LGUI, UG_TOGG,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCTL, KC_LSFT, KC_TRNS,			 			                LALT(KC_F6), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_DVORAK] = {
        ENCODER_CCW_CW(C(KC_PGUP), C(KC_PGDN)),
        ENCODER_CCW_CW(UG_PREV, UG_NEXT)
    },
    [_GAMING] = {
        ENCODER_CCW_CW(MS_WHLU, MS_WHLD),
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
    },
    [_SHIFT] = {
        ENCODER_CCW_CW(MS_WHLU, MS_WHLD),
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
    },
    [_FN] = {
        ENCODER_CCW_CW(MS_WHLU, MS_WHLD),
        ENCODER_CCW_CW(UG_VALD, UG_VALU)
    },
    [_NUMBER] = {
        ENCODER_CCW_CW(MS_WHLU, MS_WHLD),
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
    },
    [_ARROW] = {
        ENCODER_CCW_CW(MS_WHLU, MS_WHLD),
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
    },
};
#endif