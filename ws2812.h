#ifndef INC_WS2812_H_
#define INC_WS2812_H_
#include "main.h"

void full_black();
void reset();
void led_position(uint8_t position, uint8_t r,uint8_t g,uint8_t b);
void leds_range(uint8_t start, uint8_t stop, uint8_t number_leds, uint8_t r,uint8_t g,uint8_t b);
void shift_led(uint8_t delay, uint8_t r, uint8_t g, uint8_t b);
void set_color_null_to_index(uint8_t index, uint8_t r,uint8_t g,uint8_t b);

#endif /* INC_WS2812_H_ */

