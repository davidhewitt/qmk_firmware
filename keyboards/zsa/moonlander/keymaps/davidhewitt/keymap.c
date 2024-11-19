#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_uk.h"
#include "keymap_us_international.h"

#include <stdio.h>

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)
#define MOON_LED_LEVEL LED_LEVEL

enum custom_keycodes {
    LCTL_NUM = SAFE_RANGE,
    LALT_NUM,
    RGB_SLD,
    KC_ARRS,
    KCALTTB,
    WIN_1,
    WIN_2,
    WIN_3,
    WIN_4,
    WIN_5,
    WIN_6,
    WIN_7,
    WIN_8,
    WIN_9,
    WIN_10,
    HOST,
    KCTOMAC,
    KCTOWIN,
};

typedef struct {
    bool    is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP, // Send two single taps
    TRIPLE_TAP,
    TRIPLE_HOLD
};

// Tap dance enums
enum {
    X_FN,
    X_FN_MAC,
    X_LCTL,
    X_LGUI,
    X_LALT,
};

uint8_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_on_each_tap(tap_dance_state_t *state, void *user_data);
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);

enum {
    LAYER_BASE,
    LAYER_BASE_MAC,
    LAYER_FN,
    LAYER_FN_MAC,
    LAYER_NUMS,
    LAYER_FN_NUMS,
    LAYER_WINTRAVEL,
    LAYER_MGMT,
    LAYER_LAYERTRAVEL,
};

#undef KC_PIPE
#define KC_PIPE LSFT(KC_NONUS_BACKSLASH)
#undef KC_HASH
#define KC_HASH KC_NONUS_HASH
#define KC_BSLH KC_NONUS_BACKSLASH
#define KC_SPCE KC_SPACE
#define KC_QUOT KC_QUOTE
#undef KC_TILD
#define KC_TILD LSFT(KC_NONUS_HASH)
#define KCPOUND RSFT(KC_3)

#define KC_ORYX WEBUSB_PAIR

#define KC_X_FN TD(X_FN)
#define KC_XALT TD(X_LALT)
#define KC_XCTL TD(X_LCTL)
#define KC_XGUI TD(X_LGUI)
#define NUMBERS MO(LAYER_NUMS)
#define FN_NUMS MO(LAYER_FN_NUMS)
#define WINTRVL MO(LAYER_WINTRAVEL)
#define JUMPKEY OSL(LAYER_LAYERTRAVEL)

// mac specific keycodes
#define KM_HASH LALT(KC_3)
#define KM_PIPE LSFT(KC_NONUS_HASH)
#define KM_TILD LSFT(KC_GRV)
#define KM_X_FN TD(X_FN_MAC)
#define KM_AT S(KC_2)
#define KM_DQUO S(KC_QUOT)

static bool is_macos = false;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_moonlander(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KCTOMAC,               _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    HOST,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______,               KC_MEH,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
    WINTRVL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_ESC,                _______, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_LALT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LGUI, KC_XALT, _______, JUMPKEY,          NUMBERS,               KC_ARRS,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCTL,
                                        KC_BSPC, KC_X_FN, KC_XCTL,               KC_ENT,  KC_RSFT, KC_SPCE
  ),
  [LAYER_BASE_MAC] = LAYOUT_moonlander(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KCTOWIN,               _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    HOST,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______,               KC_MEH,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
    WINTRVL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_ESC,                _______, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_LALT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LGUI, KC_XALT, _______, JUMPKEY,          NUMBERS,               KC_ARRS,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCTL,
                                        KC_BSPC, KM_X_FN, KC_XGUI,               KC_ENT,  KC_RSFT, KC_SPCE
  ),
  [LAYER_FN] = LAYOUT_moonlander(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   TO(0),                 _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, KC_EXLM, UK_AT,   KC_LCBR, KC_RCBR, KC_QUOT, _______,               _______, KC_QUOT, KC_EQL,  KC_PLUS, KC_DLR,  KCPOUND, KC_F12,
    _______, KC_HASH, KC_PERC, KC_LPRN, KC_RPRN, KC_GRV,  _______,               _______, KC_AT,   KC_MINS, KC_UNDS, KC_TILD, KC_COLN, _______,
    _______, KC_PIPE, KC_CIRC, KC_LBRC, KC_RBRC, KC_BSLH,                        KC_AMPR, KC_ASTR, KC_LABK, KC_RABK, KC_QUES, _______,
    _______, KC_APP,  _______, _______, _______,          _______,               _______,          KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
                                        KC_DEL,  _______, _______,               _______, _______, _______
  ),
  [LAYER_FN_MAC] = LAYOUT_moonlander(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   TO(0),                 _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, KC_EXLM, KM_AT,   KC_LCBR, KC_RCBR, KC_QUOT, _______,               _______, KC_QUOT, KC_EQL,  KC_PLUS, KC_DLR,  KCPOUND, KC_F12,
    _______, KM_HASH, KC_PERC, KC_LPRN, KC_RPRN, KC_GRV,  _______,               _______, KM_DQUO, KC_MINS, KC_UNDS, KM_TILD,  KC_COLN, _______,
    _______, KM_PIPE, KC_CIRC, KC_LBRC, KC_RBRC, KC_BSLH,                        KC_AMPR, KC_ASTR, KC_LABK, KC_RABK, KC_QUES, _______,
    _______, KC_APP,  _______, _______, _______,          _______,               _______,          KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
                                        KC_DEL,  _______, _______,               _______, _______, _______
  ),
  [LAYER_NUMS] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, TO(0),                 _______, _______, _______, _______, _______, _______, _______,
    KCALTTB, _______, KC_1,    KC_2,    KC_3,    KC_0,    _______,               _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_4,    KC_5,    KC_6,    _______, _______,               _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_7,    KC_8,    KC_9,    _______,                                 _______, _______, _______, _______, _______, _______,
    _______, _______, _______, KC_0,    _______,          _______,               _______,          _______, _______, _______, _______, _______,
                                        _______, _______, _______,               _______, _______, _______
  ),
  [LAYER_FN_NUMS] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, TO(0),                 _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F10,  _______,               _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______,               _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F12,                                  _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,          _______,               _______,          _______, _______, _______, _______, _______,
                                        _______, _______, _______,               _______, _______, _______
  ),
  [LAYER_WINTRAVEL] = LAYOUT_moonlander(
    _______, WIN_1,   WIN_2,   WIN_3,   WIN_4,   WIN_5,   _______,               _______, WIN_6,   WIN_7,   WIN_8,   WIN_9,   WIN_10,  _______,
    _______, _______, WIN_1,   WIN_2,   WIN_3,   WIN_10,  _______,               _______, _______, _______, _______, _______, _______, _______,
    _______, _______, WIN_4,   WIN_5,   WIN_6,   _______, _______,               _______, _______, _______, _______, _______, _______, _______,
    _______, _______, WIN_7,   WIN_8,   WIN_9,   _______,                                 _______, _______, _______, _______, _______, _______,
    _______, _______, _______, WIN_10,  _______,          _______,               _______,          _______, _______, _______, _______, _______,
                                        _______, _______, _______,               _______, _______, _______
  ),
  [LAYER_MGMT] = LAYOUT_moonlander(
    AU_TOGG,  _______, _______, _______, _______, _______, TO(0),                 _______, _______, _______, _______, _______, _______, _______,
    MU_TOGG,  _______, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______, _______,
    MU_NEXT,  _______, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______, KC_MEDIA_PLAY_PAUSE,
    _______, _______, _______, _______, _______, _______,                                 _______, KC_AUDIO_MUTE, _______, _______, _______, _______,
    _______, KC_ORYX, _______, _______, _______,          RGB_MOD,               RGB_TOG, KC_MEDIA_PREV_TRACK, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_MEDIA_NEXT_TRACK, _______,
                                        RGB_VAD, RGB_VAI, TOGGLE_LAYER_COLOR,    RGB_SLD, RGB_HUD, RGB_HUI
  ),
  [LAYER_LAYERTRAVEL] = LAYOUT_moonlander(
    TO(0),  TO(1),    TO(2),   _______, _______, TO(5),   TO(6),                 _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                                 _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,          _______,               TO(0),            _______, _______, _______, _______, _______,
                                        _______, _______, _______,               _______, _______, _______
  ),
};
// clang-format on

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
}

// Sticky arrows
//
// The idea here is that if you start arrow navigation, you don't need
// to keep the numbers layer activated to keep navigating the home row.
//
// Pressing any key (except for a few blessed ones) will immediately
// end arrow navigation.

// clang-format off
const uint16_t PROGMEM LAYER_ARROWS[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_moonlander(
_______, _______, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______, _______,               _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
_______, _______, _______, _______, _______, _______,                                 _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______,          _______,               _______,          _______, _______, _______, _______, _______,
                                    _______, _______, _______,               _______, _______, _______
);
const uint16_t PROGMEM LAYER_FN_ARROWS[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_moonlander(
_______, _______, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______, _______,               _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
_______, _______, _______, _______, _______, _______,                                 _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______,          _______,               _______,          _______, _______, _______, _______, _______,
                                    _______, _______, _______,               _______, _______, _______
);
// clang-format on

bool handle_sticky_modifiers(uint16_t keycode, keyrecord_t *record) {
    static uint8_t sticky_mods = 0;
    switch (keycode) {
        case KCALTTB:
            if (record->event.pressed) {
                sticky_mods |= MOD_BIT(is_macos ? KC_LGUI : KC_LALT);
                add_mods(sticky_mods);
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return false;

        case WIN_1:
        case WIN_2:
        case WIN_3:
        case WIN_4:
        case WIN_5:
        case WIN_6:
        case WIN_7:
        case WIN_8:
        case WIN_9:
        case WIN_10:
            const uint16_t number_keycode = KC_1 + (keycode - WIN_1);
            if (record->event.pressed) {
                sticky_mods |= MOD_BIT(KC_LGUI);
                add_mods(sticky_mods);
                register_code(number_keycode);
            } else {
                unregister_code(number_keycode);
            }
            return false;

        case KC_LSFT:
            // special case for traversing list
            break;

        default:
            unregister_mods(sticky_mods);
            sticky_mods = 0;
            break;
    }
    return true;
}

bool handle_sticky_arrows(uint16_t keycode, keyrecord_t *record) {
    static bool arrows_on = false;
    // static bool sticky_arrows = false;

    if (keycode == KC_ARRS) {
        if (record->event.pressed) {
            arrows_on = true;
        } else {
            arrows_on = false;
        }
        return false;
    }

    if (arrows_on && (keycode == KC_X_FN || keycode == KM_X_FN)) {
        // If swapping between layers, clear all arrows
        if (record->event.pressed) {
            unregister_code(KC_LEFT);
            unregister_code(KC_DOWN);
            unregister_code(KC_UP);
            unregister_code(KC_RGHT);
        } else {
            unregister_code(KC_HOME);
            unregister_code(KC_PGDN);
            unregister_code(KC_PGUP);
            unregister_code(KC_END);
        }
        return true;
    }

    const uint16_t arrow_code = (IS_LAYER_ON(LAYER_FN) || IS_LAYER_ON(LAYER_FN_MAC)) ? LAYER_FN_ARROWS[record->event.key.row][record->event.key.col] : LAYER_ARROWS[record->event.key.row][record->event.key.col];

    if (arrow_code != _______) {
        // always clear both codes when lifting the key; this helps
        // avoid the case where KC_ARRS has been released but the arrow
        // hasn't, or when the original key is down before the arrows.
        if (!record->event.pressed) {
            unregister_code(arrow_code);
            unregister_code(keycode);
        }

        // otherwise if we're in arrow mode, this is the correct key to
        // handle
        // if (arrows_on || sticky_arrows) {
        if (arrows_on) {
            // for keydown, register the arrow code
            if (record->event.pressed) {
                // We love alt-up and alt-down for moving lines around in
                // code, so put this specially on the thumb activator.
                if (IS_LAYER_ON(LAYER_NUMS)) {
                    add_oneshot_mods(MOD_BIT(KC_LALT));
                }

                // macos: alt-left and alt-right function like ctrl-left and
                // ctrl-right, so we make override cmd-left and cmd-right to
                // alt-left and alt-right
                int gui_mods = 0;
                if (is_macos && (gui_mods = (get_mods() & MOD_MASK_GUI)) && (arrow_code == KC_LEFT || arrow_code == KC_RIGHT)) {
                    del_mods(MOD_MASK_GUI);
                    add_oneshot_mods(MOD_BIT(KC_LALT));
                }

                // whatever modifier madness we've done, we now send the code
                register_code(arrow_code);

                // restore any mods we've messed with
                if (gui_mods) {
                    add_mods(gui_mods);
                }
            }
            // and report that no more handling needed
            return false;
        }
    }

    return true;
}

bool handle_host_switch(uint16_t keycode, keyrecord_t *record) {
    if (keycode == HOST) {
        int os = is_macos ? KC_M : KC_W;
        if (record->event.pressed) {
            register_code(os);
        } else {
            unregister_code(os);
        }
        return false;
    }

    if (keycode == KCTOMAC) {
        set_single_persistent_default_layer(LAYER_BASE_MAC);
        is_macos = true;
        return false;
    }

    if (keycode == KCTOWIN) {
        set_single_persistent_default_layer(LAYER_BASE);
        is_macos = false;
        return false;
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!handle_sticky_modifiers(keycode, record)) {
        return false;
    }
    if (!handle_sticky_arrows(keycode, record)) {
        return false;
    }
    if (!handle_host_switch(keycode, record)) {
        return false;
    }
    return true;
}

// clang-format off
const uint16_t x_modifiers[][2] = {
    [X_FN] = {MO(LAYER_FN), MO(LAYER_FN_NUMS)},
    [X_FN_MAC] = {MO(LAYER_FN_MAC), MO(LAYER_FN_NUMS)},
    [X_LCTL] = {KC_LCTL, LCTL_NUM},
    [X_LGUI] = {KC_LGUI, LCTL_NUM},
    [X_LALT] = {KC_LALT, LALT_NUM},
};
// clang-format on

void set_modifier(const uint16_t keycode) {
    switch (keycode) {
        case LCTL_NUM:
            layer_on(LAYER_NUMS);
            register_code(KC_LCTL);
            break;

        case LALT_NUM:
            layer_on(LAYER_NUMS);
            register_code(KC_LALT);
            break;

        default:
            if ((keycode & QK_MOMENTARY) == QK_MOMENTARY) {
                layer_on(keycode ^ QK_MOMENTARY);
            } else {
                register_code(keycode);
            }
            break;
    }
}

void unset_modifier(const uint16_t keycode) {
    switch (keycode) {
        case LCTL_NUM:
            layer_off(LAYER_NUMS);
            unregister_code(KC_LCTL);
            break;

        case LALT_NUM:
            layer_off(LAYER_NUMS);
            unregister_code(KC_LALT);
            break;

        default:
            if ((keycode & QK_MOMENTARY) == QK_MOMENTARY) {
                layer_off(keycode ^ QK_MOMENTARY);
            } else {
                unregister_code(keycode);
            }
            break;
    }
}

// clang-format off
tap_dance_action_t tap_dance_actions[] = {
    [X_FN] = ACTION_TAP_DANCE_FN_ADVANCED(x_on_each_tap, NULL, x_reset),
    [X_FN_MAC] = ACTION_TAP_DANCE_FN_ADVANCED(x_on_each_tap, NULL, x_reset),
    [X_LCTL] = ACTION_TAP_DANCE_FN_ADVANCED(x_on_each_tap, NULL, x_reset),
    [X_LGUI] = ACTION_TAP_DANCE_FN_ADVANCED(x_on_each_tap, NULL, x_reset),
    [X_LALT] = ACTION_TAP_DANCE_FN_ADVANCED(x_on_each_tap, NULL, x_reset),
};
// clang-format on

void x_on_each_tap(tap_dance_state_t *state, void *user_data) {
    const uint16_t tap_dance_code = TAP_DANCE_KEYCODE(state) ^ QK_TAP_DANCE;
    const uint8_t  modifier       = (state->count - 1) % 2;

    if (state->count >= 2) {
        const uint8_t last_modifier = (state->count - 2) % 2;
        unset_modifier(x_modifiers[tap_dance_code][last_modifier]);
    }

    set_modifier(x_modifiers[tap_dance_code][modifier]);
}

void x_reset(tap_dance_state_t *state, void *user_data) {
    const uint16_t tap_dance_code = TAP_DANCE_KEYCODE(state) ^ QK_TAP_DANCE;
    const uint8_t  modifier       = (state->count - 1) % 2;
    unset_modifier(x_modifiers[tap_dance_code][modifier]);
}

bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
            set_single_persistent_default_layer(LAYER_BASE_MAC);
            is_macos = true;
            break;
        case OS_IOS:
        case OS_WINDOWS:
        case OS_LINUX:
        case OS_UNSURE:
            set_single_persistent_default_layer(LAYER_BASE);
            is_macos = false;
            break;
    }

    return false;
}
