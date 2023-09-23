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

//  Aliases for readability
#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q          ,  KC_W          ,  KC_E          ,  KC_R             ,  KC_T               ,              KC_Y      ,  KC_U                 ,  KC_I          ,  KC_O            ,  KC_P,
        LGUI_T(KC_A)  ,  LALT_T(KC_S)  ,  LCTL_T(KC_D)  ,  LSFT_T(KC_F)     ,  KC_G               ,              KC_H      ,  LSFT_T(KC_J)         ,  LCTL_T(KC_K)  ,  LALT_T(KC_L)    ,  LGUI_T(KC_QUOTE),
        KC_Z          ,  RALT_T(KC_X)  ,  KC_C          ,  KC_V             ,  KC_B               ,              KC_N      ,  KC_M                 ,  KC_COMMA      ,  RALT_T(KC_DOT)  ,  KC_SLASH,
                                    LT(NUM, KC_ESCAPE)  ,  LT(SYM, KC_TAB)  ,  LT(NAV, KC_SPACE)  ,              KC_ENTER  ,  MEH_T(KC_BACKSPACE)  ,  LT(FUN, KC_DELETE)
    ),

    [NUM] = LAYOUT_split_3x5_3(
        XXXXXXX  ,  XXXXXXX  ,  XXXXXXX  ,  XXXXXXX  ,  XXXXXXX  ,              KC_BSLS   ,  KC_7  ,  KC_8  ,  KC_9  ,  KC_EQUAL,
        KC_LGUI  ,  KC_LALT  ,  KC_LCTL  ,  KC_LSFT  ,  XXXXXXX  ,              KC_GRAVE  ,  KC_4  ,  KC_5  ,  KC_6  ,  KC_SCLN,
        XXXXXXX  ,  KC_RALT  ,  XXXXXXX  ,  XXXXXXX  ,  XXXXXXX  ,              KC_LBRC   ,  KC_1  ,  KC_2  ,  KC_3  ,  KC_RBRC,
                                _______  ,  XXXXXXX  ,  XXXXXXX  ,              KC_MINUS  ,  KC_0  ,  KC_DOT
    ),

    [SYM] = LAYOUT_split_3x5_3(
        XXXXXXX  ,  XXXXXXX  ,  XXXXXXX  ,  XXXXXXX  ,  XXXXXXX  ,              KC_PIPE  ,  KC_AMPR  ,  KC_ASTR  ,  KC_LPRN  ,  KC_RPRN,
        KC_LGUI  ,  KC_LALT  ,  KC_LCTL  ,  KC_LSFT  ,  XXXXXXX  ,              KC_TILD  ,  KC_DLR   ,  KC_PERC  ,  KC_CIRC  ,  KC_COLN,
        XXXXXXX  ,  KC_RALT  ,  XXXXXXX  ,  XXXXXXX  ,  XXXXXXX  ,              KC_LCBR  ,  KC_EXLM  ,  KC_AT    ,  KC_HASH  ,  KC_RCBR,
                                XXXXXXX  ,  _______  ,  XXXXXXX  ,              KC_PLUS  ,  XXXXXXX  ,  XXXXXXX
    ),

    [NAV] = LAYOUT_split_3x5_3(
        XXXXXXX      ,  XXXXXXX     ,  XXXXXXX      ,  XXXXXXX       ,  XXXXXXX            ,              LSFT(KC_MAC_UNDO)  ,  KC_MAC_PASTE  ,  KC_MAC_COPY  ,  KC_MAC_CUT  ,  KC_MAC_UNDO,
        KC_LGUI      ,  KC_LALT     ,  KC_LCTL      ,  KC_LSFT       ,  XXXXXXX            ,              KC_LEFT            ,  KC_DOWN       ,  KC_UP        ,  KC_RIGHT    ,  CW_TOGG,
        KC_MAC_UNDO  ,  KC_MAC_CUT  ,  KC_MAC_COPY  ,  KC_MAC_PASTE  ,  LSFT(KC_MAC_UNDO)  ,              KC_HOME            ,  KC_PGDN       ,  KC_PGUP      ,  KC_END      ,  KC_INSERT,
                                           XXXXXXX  ,  XXXXXXX       ,  _______            ,              KC_ENTER           ,  KC_BACKSPACE  ,  KC_DELETE
    ),

    [FUN] = LAYOUT_split_3x5_3(
        KC_F1   ,  KC_F2   ,  KC_F3    ,  KC_F4    ,  KC_F5    ,              XXXXXXX              ,  XXXXXXX            ,  XXXXXXX          ,  XXXXXXX              ,  XXXXXXX,
        KC_F6   ,  KC_F7   ,  KC_F8    ,  KC_F9    ,  KC_F10   ,              KC_MEDIA_PREV_TRACK  ,  KC_AUDIO_VOL_DOWN  ,  KC_AUDIO_VOL_UP  ,  KC_MEDIA_NEXT_TRACK  ,  KC_MEDIA_PLAY_PAUSE,
        KC_F11  ,  KC_F12  ,  XXXXXXX  ,  XXXXXXX  ,  XXXXXXX  ,              XXXXXXX              ,  XXXXXXX            ,  XXXXXXX          ,  XXXXXXX              ,  XXXXXXX,
                               KC_F18  ,  XXXXXXX  ,  XXXXXXX  ,              XXXXXXX              ,  XXXXXXX            ,  _______
    ),
};

/*
 * Layer template
 *
 * ,----------------------------------.                ,----------------------------------.
 * |      |      |      |      |      |                |      |      |      |      |      |
 * |------+------+------+------+------|                |------+------+------+------+------|
 * |      |      |      |      |      |                |      |      |      |      |      |
 * |------+------+------+------+------+                +------+------+------+------+------|
 * |      |      |      |      |      |                |      |      |      |      |      |
 * `-------------+------+------+------+------.  ,------+------+------+------+-------------'
 *                      |      |      |      |  |      |      |      |      |
 *                      |      |      |      |  |      |      |      |      |
 *                      `--------------------'  `---------------------------'
 *
    [_LAYERINDEX] = LAYOUT_split_3x5_3(
      _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______,
                                 _______, _______, _______,                   _______, _______, _______
    ),
*/
