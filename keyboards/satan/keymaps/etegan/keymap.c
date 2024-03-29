
#include "satan.h"
// TODO: replace your ugly german brckets with #defines

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DEF 0
#define _SPC 1
#define _TAB 2
#define _SFX 3

/* #define AF(N) ACTION_FUNCTION(N) */

// dual-role shortcuts
#define TABDUAL   LT(_TAB, KC_TAB)
#define CAPSDUAL  CTL_T(KC_ESC)
#define SPACEDUAL LT(_SPC, KC_SPACE)
#define ENTERDUAL CTL_T(KC_ENT)
// arrow cluster duality bottom right corner
#define ARRLEFT  ALT_T(KC_LEFT)
#define ARRDOWN  GUI_T(KC_DOWN)
#define ARRUP    SFT_T(KC_UP)
#define ARRRIGHT CTL_T(KC_RIGHT)
// Swedish brackets
#define SWE_CUR_L RALT(KC_7)    // {
#define SWE_CUR_R RALT(KC_0)    // }
#define SWE_PAR_L LSFT(KC_8)    // (
#define SWE_PAR_R LSFT(KC_9)    // )
#define SWE_ANG_L KC_NUBS       // <
#define SWE_ANG_R LSFT(KC_NUBS) // >
#define SWE_BRC_L RALT(KC_8)    // [
#define SWE_BRC_R RALT(KC_9)    // ]

// increase readability 
#define _______ KC_TRNS
#define XXXXXXX KC_NO

enum action_codes {
    RGB_TOGG = SAFE_RANGE,
    RGBLED_STEP_MODE,
    RGBLED_INCREASE_HUE,
    RGBLED_DECREASE_HUE,
    RGBLED_INCREASE_SAT,
    RGBLED_DECREASE_SAT,
    RGBLED_INCREASE_VAL,
    RGBLED_DECREASE_VAL,
};

  
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _DEF: Default Layer
     * ,-----------------------------------------------------------.
     * |Grv|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   \ | Tab is Fn1
     * |-----------------------------------------------------------|
     * |Ctrl   | A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '| Return |
     * |-----------------------------------------------------------|
     * |Sft | < |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn2| RShift is UP
     * |-----------------------------------------------------------|
     * |Ctrl|Win |Alt |      Space/Fn0         |Alt |Win |Menu|RCtl| Gui Menu, RCtrl is 
     * `-----------------------------------------------------------'   LEFT DWN RIGHT
     */
    [_DEF] = KEYMAP_ISO_SPLITRSHIFT(
        KC_GRV,   KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   \
        TABDUAL,  KC_Q,    KC_W,    KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   \
        CAPSDUAL, KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, ENTERDUAL, \
        KC_LSFT,  KC_NUBS, KC_Z,    KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, ARRUP,   TG(_SFX),      \
        KC_LCTL,  KC_LGUI, KC_LALT,             SPACEDUAL,                       KC_RALT, ARRLEFT, ARRDOWN, ARRRIGHT),


    /* Keymap 2: Tab Layer w/ vim pageup, modified with Tab (by holding tab)
     * ,-----------------------------------------------------------.
     * |WAKE|   |   |   |   |   |   |   |   |   |   |   |   |Insert|  TAB+GRC = WAKE
     * |-----------------------------------------------------------|
     * |     |   |   |   |   |   |   |   | { | } |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |   |   |   |   |   |Pos1|PgDn|PgUp|End|  |   |Retrn |
     * |-----------------------------------------------------------|
     * |    |   |   |   |   |   |   |AF2|   |   |   |   | PgUp |   |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |Alt |Pos1|PgDn|End |
     * `-----------------------------------------------------------'
     */
    [_TAB] = KEYMAP_ISO_SPLITRSHIFT(
        KC_WAKE, _______, _______, _______, _______, _______, _______, _______,    _______,  _______, _______, _______, _______, KC_INS,  \
        _______, _______, _______, _______, _______, _______, _______, SWE_CUR_L, SWE_CUR_R, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN,    KC_PGUP,  KC_END,  _______, _______, _______, KC_ENT,  \
        _______, _______, _______, _______, _______, _______, _______, M(1),       _______,  _______, _______, _______, KC_PGUP, _______, \
        _______, _______, _______,                            _______,                                _______, KC_HOME, KC_PGDN, KC_END),

    /* Keymap 3: Split right shift Numpad toggle Layer (by tapping the split rshift key)
     * ,-----------------------------------------------------------.
     * |RSET|  |   |   |   |   |   |  7|  8|  9|   |   |   |Backsp |
     * |-----------------------------------------------------------|
     * |     |   |   |   |   |   |   | 4 | 5 | 6 |   |   |   |   \ |
     * |-----------------------------------------------------------|
     * |    | L | L | L | L |F(11)|   | 1 | 2 | 3 |   |   | Return |
     * |-----------------------------------------------------------|
     * |    |   | L | L | L | L | L | L |   | 0 |   |  /|  Up  |   | All "L"s represent
     * |-----------------------------------------------------------| LED controlling
     * |Ctrl|Win |Alt |                        |Alt |Left|Down|Right|
     * `-----------------------------------------------------------'
     */
    [_SPC] = KEYMAP_ISO_SPLITRSHIFT(
        RESET,   _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9, _______, _______, _______, KC_BSPC, \
        _______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6, _______, _______, _______, KC_BSLS, \
        _______, RGB_TOGG,    F(3),    BL_DEC, BL_INC, F(11), _______, KC_1,    KC_2,    KC_3, _______, _______, XXXXXXX, KC_ENT, \
        _______, F(4),    F(5),    F(6),    F(7),    F(8),    F(9),    _______, _______, KC_0, _______, KC_SLSH, KC_UP,   _______, \
        _______, _______, _______,                            _______,                         _______, KC_LEFT, KC_DOWN, KC_RGHT),
};

// Defaults to break processing keycode after switch-case. Return true to continue processing.

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case SPACEDUAL:
    if (record->event.pressed) {
      rgblight_mode(1);
      rgblight_sethsv(72, 50, 70);
      rgblight_setrgb_at(255, 0, 0, 0);
    }else{
      rgblight_sethsv(0, 0, 0);
    }
    break;
  case RGB_TOGG:
    //led operations
    if (record->event.pressed) {
      rgblight_toggle();
    }
    return false;
  case RGBLED_INCREASE_HUE:
    if (record->event.pressed) {
      rgblight_increase_hue();
    }
    return false;
  case RGBLED_DECREASE_HUE:
    if (record->event.pressed) {
      rgblight_decrease_hue();
    }
    return false;
  case RGBLED_INCREASE_SAT:
    if (record->event.pressed) {
      rgblight_increase_sat();
    }
    return false;
  case RGBLED_DECREASE_SAT:
    if (record->event.pressed) {
      rgblight_decrease_sat();
    }
    return false;
  case RGBLED_INCREASE_VAL:
    if (record->event.pressed) {
      rgblight_increase_val();
    }
    return false;
  case RGBLED_DECREASE_VAL:
    if (record->event.pressed) {
      rgblight_decrease_val();
    }
    return false;
  case RGBLED_STEP_MODE:
    if (record->event.pressed) {
      rgblight_step();
    }
    return false;
  }
  return true;
}
/* const uint16_t PROGMEM fn_actions[] = { */
/*     [1]  = ACTION_FUNCTION(LAUNCH), */
/*     [2]  = ACTION_FUNCTION(RGBLED_TOGGLE), */
/*     [3]  = ACTION_FUNCTION(RGBLED_STEP_MODE), */
/*     [4]  = ACTION_FUNCTION(RGBLED_INCREASE_HUE), */
/*     [5]  = ACTION_FUNCTION(RGBLED_DECREASE_HUE), */
/*     [6]  = ACTION_FUNCTION(RGBLED_INCREASE_SAT), */
/*     [7]  = ACTION_FUNCTION(RGBLED_DECREASE_SAT), */
/*     [8]  = ACTION_FUNCTION(RGBLED_INCREASE_VAL), */
/*     [9]  = ACTION_FUNCTION(RGBLED_DECREASE_VAL), */
/*     [10] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ENT), */
/* }; */

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    switch(id) {
        case 0:
            return (record->event.pressed ? 
                    MACRO( D(RALT), T(SPC), U(RALT), END )
                    :MACRO( END ));
            break;
        case 1:
            return (record->event.pressed ? 
                    MACRO( D(LALT), T(F2), U(LALT), END )
                    :MACRO( END ));
            break;
    }
    return MACRO_NONE;
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id) {
    }
}
