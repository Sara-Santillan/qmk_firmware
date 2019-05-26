#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_ortho_5x14(
    KC_ESC ,  KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_F1  ,     KC_F2  , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
    KC_TAB ,  KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_LBRC,     KC_RBRC, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_DEL ,
    KC_LCTL,  KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_PGDN,     KC_PGUP, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_HOME,     KC_END , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_F5  ,
    KC_APP ,  KC_MINS, KC_LGUI, KC_LALT, RAISE  , KC_SPC,  KC_ENT ,     KC_ENT, KC_SPC , RAISE   , KC_GRV , KC_BSLS, KC_EQL , KC_PSCR
  ),

  [_LOWER] = LAYOUT_ortho_5x14(
    KC_ESC,  KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,     KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______,
    BL_TOGG, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    BL_STEP, _______, _______, _______, _______, _______, _______,     _______, KC_LEFT, KC_DOWN , KC_UP , KC_RGHT, _______, _______,
    BL_ON  , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    BL_OFF , _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______
  ),

  [_RAISE] = LAYOUT_ortho_5x14(
    KC_ESC,  KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,     KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______,
    KC_TAB , KC_BTN2, KC_MS_U, KC_BTN1, KC_ACL0, KC_ACL1, KC_ACL2,     RGB_SAI, RGB_SAD, RGB_M_P, RGB_M_B, RGB_M_G, RGB_M_R, KC_INS,
    KC_LCTL, KC_MS_L, KC_MS_D, KC_MS_R, KC_VOLU, KC_VOLD, KC_MUTE,     KC_CAPS, KC_LEFT, KC_DOWN , KC_UP , KC_RGHT, _______, _______,
    KC_LSFT, BL_TOGG, BL_STEP, _______, _______, _______, _______,     RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_VAI, RGB_VAD, _______,
    KC_F1  , KC_APP , KC_LGUI, KC_LALT, RAISE  , KC_SPC,  KC_ENT ,     KC_ENT, KC_SPC , RAISE  , KC_F2  , KC_BSLS, KC_GRV , KC_PSCR
  ),

  [_ADJUST] = LAYOUT_ortho_5x14(
    _______, KC_F1  , KC_F2  ,   KC_F3,   KC_F4,   KC_F5,   KC_F6,     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
    _______, _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,     RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, KC_DEL,  _______,
    _______, _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM,     AG_SWAP, QWERTY,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______
  )


};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
