/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    NAV,
    NUM,
    SYM,
    FUN,
    // MOUSE,
};

enum td_keycodes {
    // CMD+A when tapped, CMD when hold
    SELALL_LGUI
};

// typedance states
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

static td_state_t td_state;
td_state_t cur_dance(tap_dance_state_t *state);

// for each tapdance keycode
void selallgui_finished(tap_dance_state_t *state, void *user_data);
void selallgui_reset(tap_dance_state_t *state, void *user_data);

//  Aliases for readability
#define KC_CUT LGUI(KC_X)
#define KC_COPY LGUI(KC_C)
#define KC_PASTE LGUI(KC_V)
#define KC_UNDO LGUI(KC_Z)
#define KC_REDO LSFT(KC_UNDO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q          ,  KC_W          ,  KC_E          ,  KC_R         ,  KC_T  ,              KC_Y  ,  KC_U          ,  KC_I          ,  KC_O            ,  KC_P,
        LGUI_T(KC_A)  ,  LALT_T(KC_S)  ,  LCTL_T(KC_D)  ,  LSFT_T(KC_F) ,  KC_G  ,              KC_H  ,  LSFT_T(KC_J)  ,  LCTL_T(KC_K)  ,  LALT_T(KC_L)    ,  LGUI_T(KC_QUOTE),
        KC_Z          ,  RALT_T(KC_X)  ,  KC_C          ,  KC_V         ,  KC_B  ,              KC_N  ,  KC_M          ,  KC_COMMA      ,  RALT_T(KC_DOT)  ,  KC_SLASH,
                            KC_ESCAPE  ,  LT(SYM, KC_TAB)  ,  LT(NAV, KC_SPACE)  ,              MEH_T(KC_ENTER)  ,  LT(NUM, KC_BACKSPACE)  ,  LT(FUN, KC_DELETE)
    ),

    [NUM] = LAYOUT_split_3x5_3(
        KC_1     ,  KC_2     ,  KC_3      ,  KC_4      ,  KC_5     ,              KC_6     ,  KC_7     ,  KC_8     ,  KC_9     ,  KC_0,
        XXXXXXX  ,  XXXXXXX  ,  XXXXXXX   ,  XXXXXXX   ,  XXXXXXX  ,              XXXXXXX  ,  KC_LSFT  ,  KC_LCTL  ,  KC_LALT  ,  KC_LGUI,
        XXXXXXX  ,  XXXXXXX  ,  KC_EQUAL  ,  KC_MINUS  ,  KC_PLUS  ,              XXXXXXX  ,  KC_UNDS  ,  KC_COMMA ,  KC_DOT   ,  XXXXXXX,
                                XXXXXXX   ,  XXXXXXX   ,  XXXXXXX  ,              KC_ENTER ,  _______  ,  KC_DELETE
    ),

    [SYM] = LAYOUT_split_3x5_3(
        KC_EXLM  ,  KC_AT    ,  KC_HASH   ,  KC_DLR    ,  KC_PERC  ,              KC_CIRC   ,  KC_AMPR  ,  KC_ASTR  ,  KC_LPRN  ,  KC_RPRN,
        KC_LGUI  ,  KC_LALT  ,  KC_LCTL   ,  KC_LSFT   ,  XXXXXXX  ,              KC_GRAVE  ,  XXXXXXX  ,  KC_LCBR  ,  KC_RCBR  ,  KC_SCLN,
        XXXXXXX  ,  XXXXXXX  ,  KC_EQUAL  ,  KC_MINUS  ,  KC_PLUS  ,              XXXXXXX   ,  KC_UNDS  ,  KC_LBRC  ,  KC_RBRC  ,  KC_BSLS,
                                XXXXXXX   ,  _______   ,  XXXXXXX  ,              KC_ENTER  ,  KC_BACKSPACE  ,  KC_DELETE
    ),

    [NAV] = LAYOUT_split_3x5_3(
        LGUI(KC_Q)       ,  XXXXXXX  ,  XXXXXXX  ,  XXXXXXX   ,  XXXXXXX  ,              KC_HOME   ,  KC_PGDN   ,  KC_PGUP  ,  KC_END    ,  KC_CAPS,
        TD(SELALL_LGUI)  ,  KC_LALT  ,  KC_LCTL  ,  KC_LSFT   ,  XXXXXXX  ,              KC_LEFT   ,  KC_DOWN   ,  KC_UP    ,  KC_RIGHT  ,  CW_TOGG,
        KC_UNDO          ,  KC_CUT   ,  KC_COPY  ,  KC_PASTE  ,  KC_REDO  ,              KC_REDO   ,  KC_PASTE  ,  KC_COPY  ,  KC_CUT    ,  KC_UNDO,
                                        XXXXXXX  ,  XXXXXXX   ,  _______  ,              KC_ENTER  ,  KC_BACKSPACE  ,  KC_DELETE
    ),

    [FUN] = LAYOUT_split_3x5_3(
        KC_F1   ,  KC_F2   ,  KC_F3    ,  KC_F4    ,  KC_F5    ,                KC_F6                ,  KC_F7              ,  KC_F8            ,  KC_F9                ,  KC_F10,
        KC_F11  ,  KC_F12  ,  KC_F13   ,  KC_F14   ,  KC_F15   ,                KC_MEDIA_PREV_TRACK  ,  KC_AUDIO_VOL_DOWN  ,  KC_AUDIO_VOL_UP  ,  KC_MEDIA_NEXT_TRACK  ,  KC_MEDIA_PLAY_PAUSE,
        KC_F16  ,  KC_F17  ,  KC_F18   ,  KC_F19   ,  KC_F20   ,                XXXXXXX              ,  XXXXXXX            ,  XXXXXXX          ,  XXXXXXX              ,  XXXXXXX,
                              XXXXXXX  ,  XXXXXXX  ,  XXXXXXX  ,                XXXXXXX  ,  XXXXXXX  ,  _______
    ),
};


td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        // if (state->interrupted || !state->pressed) {
        if (!state->pressed) {
            return TD_SINGLE_TAP;
        } else {
            return TD_SINGLE_HOLD;
        }
    }

    if (state->count == 2) {
        return TD_DOUBLE_SINGLE_TAP;
    }

    return TD_UNKNOWN;
}

void selallgui_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_mods(MOD_BIT(KC_LGUI));
            register_code(KC_A);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LGUI));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            // do nothing
            break;
         default:
            break;
    }
}

void selallgui_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_mods(MOD_BIT(KC_LGUI));
            unregister_code(KC_A);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LGUI));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            // do nothing
            break;
        default:
            break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [SELALL_LGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, selallgui_finished, selallgui_reset)
};
