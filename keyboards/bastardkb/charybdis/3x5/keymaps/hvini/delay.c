/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"
#include "delay.h"
#include "quantum.h"

#include "features/oneshot_mod.h"

typedef struct {
    oneshot_mod_state_t lalt;
    oneshot_mod_state_t lctl;
    oneshot_mod_state_t lgui;
    oneshot_mod_state_t lsft;
} osm_state_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Custom oneshot mods handler.
    static osm_state_t osm_state = {
        .lalt = ONESHOT_UP_UNQUEUED,
        .lctl = ONESHOT_UP_UNQUEUED,
        .lgui = ONESHOT_UP_UNQUEUED,
        .lsft = ONESHOT_UP_UNQUEUED,
    };
    oneshot_mod_pre(&osm_state.lalt, KC_LALT, OSM_L_ALT, keycode, record);
    oneshot_mod_pre(&osm_state.lctl, KC_LCTL, OSM_L_CTRL, keycode, record);
    oneshot_mod_pre(&osm_state.lgui, KC_LGUI, OSM_L_GUI, keycode, record);
    oneshot_mod_pre(&osm_state.lsft, KC_LSFT, OSM_L_SHFT, keycode, record);

    const bool result = process_record_user_keymap(keycode, record);

    oneshot_mod_post(&osm_state.lalt, KC_LALT, OSM_L_ALT, keycode, record);
    oneshot_mod_post(&osm_state.lctl, KC_LCTL, OSM_L_CTRL, keycode, record);
    oneshot_mod_post(&osm_state.lgui, KC_LGUI, OSM_L_GUI, keycode, record);
    oneshot_mod_post(&osm_state.lsft, KC_LSFT, OSM_L_SHFT, keycode, record);

    return result;
}

__attribute__((weak)) bool process_record_user_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void matrix_scan_user(void) {
    matrix_scan_user_keymap();
}

__attribute__((weak)) void matrix_scan_user_keymap(void) {}

/** Called on layer change. */
// layer_state_t layer_state_set_user(layer_state_t state) {
//   return layer_state_set_user_keymap(state);
// }

// __attribute__((weak)) layer_state_t layer_state_set_user_keymap(
//     layer_state_t state) {
//   return state;
// }

void keyboard_post_init_user(void) {
    oneshot_enable();
    keyboard_post_init_user_keymap();
}

__attribute__((weak)) void keyboard_post_init_user_keymap(void) {}
