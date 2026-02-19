/*
 * ws2812.h
 *
 *  Created on: Feb 5, 2026
 *      Author: Користувач
 */

#ifndef INC_WS2812_H_
#define INC_WS2812_H_
#include "main.h"
void logic_0();
void logic_1();
void send_byte(uint8_t b);
void set_color(uint8_t r, uint8_t g, uint8_t b);
void mode1(); //lava
void red(uint8_t pwm_val);
void green(uint8_t pwm_val);
void blue(uint8_t pwm_val);
void no_color();
void reset();
void led_position(uint8_t position, uint8_t number_leds, uint8_t r,uint8_t g,uint8_t b);
void leds_range(uint8_t start, uint8_t stop, uint8_t number_leds, uint8_t r,uint8_t g,uint8_t b);
void bizucha_stroka_2(uint8_t delay, uint8_t r, uint8_t g, uint8_t b);
void set_color_null_to_index(uint8_t index, uint8_t r,uint8_t g,uint8_t b);
void gradient_peach();
void gradient1();
#endif /* INC_WS2812_H_ */
