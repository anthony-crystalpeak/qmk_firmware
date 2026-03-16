// Copyright 2022 Mark Stosberg (@markstos)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    FUNC,
    BACKLIT,
    MACRO_COPY,
    MACRO_PASTE,
    VIM_WRITE,
};


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _FUNC,
};

// For _RAISE layer
#define CTL_ESC  LCTL_T(KC_ESC)

enum combos {
    ENT,
    ESC,
    FUNC_LAYER,
    OPEN_PAREN,
    CLOSE_PAREN,
    OPEN_BRACE,
    CLOSE_BRACE,
    OPEN_BRACKET,
    CLOSE_BRACKET,
};

const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM er_combo[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM mcomm_combo[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM rt_combo[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM yu_combo[] = {KC_Y, KC_U, COMBO_END};


combo_t key_combos[] = {
    [ENT]        = COMBO(df_combo, KC_ENT),
    [ESC]        = COMBO(jk_combo, KC_ESC),
    [FUNC_LAYER]        = COMBO(sd_combo, MO(_FUNC)),
    [OPEN_PAREN] = COMBO(er_combo, KC_LPRN),
    [CLOSE_PAREN] = COMBO(ui_combo, KC_RPRN),
    [OPEN_BRACE] = COMBO(cv_combo, KC_LCBR),
    [CLOSE_BRACE] = COMBO(mcomm_combo, KC_RCBR),
    [OPEN_BRACKET] = COMBO(rt_combo, KC_LBRC),
    [CLOSE_BRACKET] = COMBO(yu_combo, KC_RBRC),
};




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MACRO_COPY:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_C);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_C);
            }
            break;
        case MACRO_PASTE:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_V);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_V);
            }
            break;

        case VIM_WRITE:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_SEMICOLON);
                unregister_code(KC_LSFT);
                register_code(KC_W);
                register_code(KC_ENT);
            } else {
                unregister_code(KC_SEMICOLON);
                unregister_code(KC_W);
                unregister_code(KC_ENT);
            }
            break;
    }

    return true;

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
            //,-----------------------------------------------------.                                       ,-----------------------------------------------------.
                KC_UNDS,    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                               KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_PLUS,
            //|--------+--------+--------+--------+--------+--------|                                       |--------+--------+--------+--------+--------+--------|
MT(MOD_LSFT, KC_MINUS),     KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                               KC_H,   KC_J,   KC_K,   KC_L,   KC_SEMICOLON,  KC_QUOT,
            //|--------+--------+--------+--------+--------+--------|                                       |--------+--------+--------+--------+--------+--------|
        MT(MOD_LCTL, KC_DEL),    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                                               KC_N,   KC_M,   KC_COMM, KC_DOT,    KC_SLSH,  KC_BSLS,
            //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
                        MT(MOD_LALT, KC_TAB) , LT(_RAISE, KC_BSPC), MT(MOD_LSFT, KC_EQL),           MT(MOD_LCTL, KC_ENT), LT(_LOWER, KC_SPC), MT(MOD_LALT, KC_DEL)
            //`--------------------------'  `--------------------------'
 ),
    [_LOWER] = LAYOUT_split_3x6_3(
            //,-----------------------------------------------------.                                        ,-----------------------------------------------------.
                KC_TRNS, KC_EXLM,   KC_AT,  KC_HASH,    KC_DLR, KC_PERC,                                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
            //|--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------|
                KC_TRNS, KC_1,      KC_2,   KC_3,       KC_4,   KC_5,                                           KC_6,   KC_7,       KC_8,   KC_9,   KC_0,   KC_TRNS ,
            //|--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------|
                KC_TRNS, CW_TOGG , KC_TILD, KC_LBRC, KC_RBRC,KC_GRV,                                             KC_TRNS, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_TRNS ,
            //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
                                                        KC_TRNS, KC_BSPC, KC_TRNS,        KC_TRNS, KC_SPC, KC_DEL
        ),


    [_RAISE] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                                        ,-----------------------------------------------------.
            KC_TRNS,  KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_PIPE,                                            KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_PIPE,    KC_TRNS,
    //|--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------|
            KC_TRNS,  KC_MINS, KC_EQL, KC_LCBR, KC_RCBR, KC_BSLS,                                            KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_BSLS,     KC_TRNS,
    //|--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------|
            KC_TRNS, MACRO_COPY, MACRO_PASTE, KC_COPY, KC_PSTE, KC_PSCR,                                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
    //|--------+--------+--------+--------+--------+--------+--------|                      |--------+--------+--------+--------+--------+--------+--------|
                                                        KC_TRNS, KC_BSPC, KC_TRNS,        KC_TRNS, KC_SPC, KC_DEL
    ),

    [_FUNC] = LAYOUT_split_3x6_3(
            //,-----------------------------------------------------.                                                        ,-----------------------------------------------------.
            KC_TRNS, KC_F1, KC_F2, KC_F3, KC_MS_ACCEL0, KC_F4 ,                                                             KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT,  XXXXXXX, KC_TRNS ,
            //|--------+--------+--------+--------+--------+--------|                                                        |--------+--------+--------+--------+--------+--------|
            KC_TRNS, KC_F5, XXXXXXX, XXXXXXX, KC_MS_ACCEL1, KC_F7 ,                                                         KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT,  XXXXXXX, KC_TRNS,
            //|--------+--------+--------+--------+--------+--------|                                                        |--------+--------+--------+--------+--------+--------|
            KC_TRNS, XXXXXXX,XXXXXXX,XXXXXXX, KC_MS_ACCEL2, XXXXXXX,                                                           KC_F8, KC_F9, KC_F10, KC_F11, QK_BOOT, KC_TRNS,
            //|--------+--------+--------+--------+--------+--------+--------|                                  |--------+--------+--------+--------+--------+--------+--------|
                                                            KC_MS_BTN4, KC_MS_BTN1, KC_TRNS,        KC_MS_BTN3, KC_MS_BTN2, KC_MS_BTN5
    )
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
        switch (keycode) {
            case LT(_RAISE, KC_BSPC):
                        return TAPPING_TERM_THUMB;
            case LT(_LOWER, KC_TAB):
                        return TAPPING_TERM_THUMB;
            default:
                        return TAPPING_TERM;
        }
}


