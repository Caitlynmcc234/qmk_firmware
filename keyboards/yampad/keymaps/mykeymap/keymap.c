/* MIT License

Copyright (c) 2019 Mattia Dal Ben

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
    _DEF,
    _NAV
};

enum custom_keycodes {
    KC_DBL0 = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap _BL: (Base Layer) Default Layer
 * ,-------------------.
 * | Nav| /  | *  |Bspc|
 * |----|----|----|----|
 * | 7  | 8  | 9  |    |
 * |----|----|----| +  |
 * | 4  | 5  | 6  |    |
 * |----|----|----|----|
 * | 1  | 2  | 3  |    |
 * |----|----|----| En |
 * | 0  | 00 | .  |    |
 * `-------------------'
 */
  [_DEF] = LAYOUT(
    TG(_NAV),  KC_PSLS,  KC_PAST,   KC_BSPC,
    KC_P7,    KC_P8,    KC_P9,
    KC_P4,    KC_P5,    KC_P6,     KC_PPLS,
    KC_P1,    KC_P2,    KC_P3,
    KC_P0,    KC_DBL0,  KC_PDOT,   KC_PENT
  ),

/* Keymap _NV: Navigation layer
 * ,-------------------.
 * |INS |HOME|PGUP| Def|
 * |----|----|----|----|
 * |DEL |END |PGDN|    |
 * |----|----|----|    |
 * |    |    |    |    |
 * |----|----|----|----|
 * |    | UP |    |    |
 * |----|----|----|    |
 * |LEFT|DOWN|RIGH|    |
 * `-------------------'
 */
  [_NAV] = LAYOUT(
    KC_INS,   KC_HOME,  KC_PGUP,   TG(_DEF),
    KC_DEL,   KC_END,   KC_PGDN,
    XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,
    XXXXXXX,  KC_UP,    XXXXXXX,
    KC_LEFT,  KC_DOWN,  KC_RGHT,   XXXXXXX
  )
};

bool led_update_user(led_t led_state) {
    if (led_state.num_lock == false) {
        SEND_STRING(SS_TAP(X_NUM));
    }
    return true;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_DBL0:
      if (record->event.pressed) {
        SEND_STRING("00");
      } else {
        // when keycode KC_DBL0 is released
      }
      break;

  }
  return true;
};

#ifdef OLED_ENABLE

// Animation parameters
#define FRAME_DURATION 500 // How long each frame lasts in milliseconds

// Animation variables

uint32_t timer = 0;
uint8_t current_frame = 0;

static void render_animation(void) {
    // Frame 1
    static const char epd_bitmap_frame_1_delay_0 [] PROGMEM = {
        // 'BongoCat1', 32x32px
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x80, 0x40, 0x40, 0x80, 0x80, 0x40, 0x20, 0x10, 0x10, 0x08, 0x06, 0x01, 0x02, 0x04,
        0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x40, 0x20, 0x10, 0xf0, 0x00,
        0x10, 0x1f, 0x10, 0x26, 0x23, 0x20, 0x23, 0x40, 0x40, 0x40, 0x40, 0x86, 0x80, 0x80, 0x8c, 0x18,
        0x10, 0x10, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x83, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x01, 0x01, 0x01, 0x02, 0x0e, 0x12, 0x21, 0x20, 0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x0b, 0x1c
    };

    // Frame 2
    static const char epd_bitmap_frame_0_delay_0 [] PROGMEM = {
        // 'BongoCat2', 32x32px
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x10, 0x08, 0x06, 0x01, 0x02, 0x04,
        0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x40, 0x20, 0x10, 0xf0, 0x00,
        0x30, 0x48, 0x84, 0x82, 0x81, 0x41, 0x40, 0x40, 0x40, 0x40, 0x40, 0x86, 0x80, 0x80, 0x8c, 0x18,
        0x10, 0x10, 0x00, 0x00, 0x30, 0x00, 0xe0, 0x10, 0xc8, 0x68, 0x10, 0x60, 0x00, 0x7c, 0x83, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x03, 0x04, 0x04, 0x04, 0x04, 0x08, 0x08, 0x08, 0x0b, 0x1c
    };

    // Animation frames array
    const char* epd_bitmap_allArray [] = {
        epd_bitmap_frame_0_delay_0,
        epd_bitmap_frame_1_delay_0
    };

    // Frame sizes array
    uint16_t frame_sizes[2] = {
        sizeof(epd_bitmap_frame_0_delay_0),
        sizeof(epd_bitmap_frame_1_delay_0)
    };

    // Run animation
    if (timer_elapsed(timer) > FRAME_DURATION) {
        // Set timer to updated time
        timer = timer_read();

        // Increment frame
        current_frame = (current_frame + 1) % (sizeof(epd_bitmap_allArray) / sizeof(epd_bitmap_allArray[0]));

        // Draw frame to OLED
        oled_write_raw_P(epd_bitmap_allArray[current_frame], frame_sizes[current_frame]);
    }
}

bool oled_task_user(void) {
    if (last_input_activity_elapsed() > 30000) {
        oled_off();
    } else {
        oled_on();
        oled_write_P(PSTR("LAYER"), false);
        switch (get_highest_layer(layer_state)) {
            case _DEF :
                oled_write_P(PSTR(" DEF\n"), false);
                break;
            case _NAV :
                oled_write_P(PSTR(" NAV\n"), false);
                break;
        }
        oled_advance_page(true);
        oled_write_P(PSTR("CAPS\n"), host_keyboard_led_state().caps_lock);
        oled_advance_page(true);
        oled_advance_page(true);
        oled_advance_page(true);
        oled_advance_page(true);
        oled_advance_page(true);
        oled_advance_page(true);
        oled_advance_page(true);
        render_animation();
    }
    return false;
}

#endif
