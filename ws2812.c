/*
 * ws2812.c
 *
 *  Created on: Feb 5, 2026
 *      Author: Користувач
 */
#include<ws2812.h>
extern SPI_HandleTypeDef hspi1;
uint8_t leds[180][3];
void logic_0(){
	uint8_t logic0_ws2812=0b00000100;
	GPIOA->BSRR=1<<19;
	HAL_SPI_Transmit(&hspi1, &logic0_ws2812, 1, 5);
	GPIOA->BSRR=1<<3;
}
void logic_1(){
	uint8_t logic1_ws2812=0b00000110;
	GPIOA->BSRR=1<<19;
	HAL_SPI_Transmit(&hspi1, &logic1_ws2812, 1, 5);
	GPIOA->BSRR=1<<3;
}
void send_byte(uint8_t b){
	for(uint8_t n=0; n<8; n++){
		if(b & (1<<(7-n))){
			logic_1();
		}
		else {
			logic_0();
		}
	}
}
void set_color(uint8_t r, uint8_t g, uint8_t b){
	send_byte(g);
	send_byte(r);
	send_byte(b);
}
void mode1(){ //lava
	for(uint8_t i=0; i<180; i++){
		if(i<140){
			leds[i][0]=0xFF;
			leds[i][1]=i;
			leds[i][2]=0x00;
		}
		leds[i][0]=0xFF;
		leds[i][1]=i*2;
		leds[i][2]=0x00;
	}
	for(uint8_t i=0; i<180; i++){
		set_color(leds[i][0], leds[i][1], leds[i][2]);
	}
}
void red(uint8_t pwm_val){
	send_byte(0x00);
	send_byte(pwm_val);
	send_byte(0x00);
}
void green(uint8_t pwm_val){
	send_byte(pwm_val);
	send_byte(0x00);
	send_byte(0x00);
}
void blue(uint8_t pwm_val){
	send_byte(0x00);
	send_byte(0x00);
	send_byte(pwm_val);
}
void no_color(){ //one led
	send_byte(0x00);
	send_byte(0x00);
	send_byte(0x00);
}
void reset(){
	uint8_t byte_reset=0b00000000;
	GPIOA->BSRR=1<<19;
	HAL_SPI_Transmit(&hspi1, &byte_reset, 18, 5);
	GPIOA->BSRR=1<<3;
}
void led_position(uint8_t position, uint8_t number_leds, uint8_t r,uint8_t g,uint8_t b){
	if(position<number_leds){
		for(uint8_t n=0; n<position; n++){ //clear (0 to led)
			no_color();
		}
		set_color(r, g, b);
		for(uint8_t i=position+1; i<number_leds; i++){ //clear (led to end strip)
			no_color();
		}
	}
	else{
		for(uint8_t n=0; n<180;n++){
			set_color(r, g, b);
		}
	}
}
void leds_range(uint8_t start, uint8_t stop, uint8_t number_leds, uint8_t r,uint8_t g,uint8_t b){
	for(uint8_t k=0; k<start; k++){
		no_color();
	}
	for(uint8_t i=start; i<stop; i ++){
		set_color(r, g, b);
	}
	for(uint8_t i=stop+1; i<number_leds; i ++){
		no_color();
	}
}

void bizucha_stroka_2(uint8_t delay, uint8_t r, uint8_t g, uint8_t b){
	for(uint8_t n=0; n<180; n++){
		led_position(n, 180, r, g, b);
		HAL_Delay(delay);
	}
}
void set_color_null_to_index(uint8_t index, uint8_t r,uint8_t g,uint8_t b){
	for(uint8_t k=0; k<index; k++){
		set_color(r, g, b);
	}
}
void gradient_peach(){
	for(uint8_t k=0; k<180; k++){

	}
	for(uint8_t i=0; i<80; i++){

	}
}
void gradient1(){
	for(uint8_t k=0; k<20; k++){
		//Dark red
		set_color(0x8B, 0x00, 0x00);
	}
	for(uint8_t k=0; k<20; k++){
			//Red
		set_color(0xFF, 0x00, 0x00);

		}
	for(uint8_t k=0; k<20; k++){
			//Dark red (GRB HEX code - 0x008B00)
			set_color(0xFF,0x63,0x47);
		}
	for(uint8_t k=0; k<20; k++){
			//Dark red (GRB HEX code - 0x008B00)
			set_color(0xFF, 0x45, 0x00);
		}
	for(uint8_t k=0; k<20; k++){
			//Dark red (GRB HEX code - 0x008B00)
			set_color(0xD2,0x69,0x1E);
		}
	for(uint8_t k=0; k<20; k++){
			//Dark red (GRB HEX code - 0x008B00)
			set_color(0xFF, 0x8C, 0x00);
		}
	for(uint8_t k=0; k<20; k++){
			//Dark red (GRB HEX code - 0x008B00)
			set_color(0x80, 0x80, 0x00);
		}
	for(uint8_t k=0; k<20; k++){
			//Dark red (GRB HEX code - 0x008B00)
			set_color(0x7F, 0xFF, 0x00);
		}
	for(uint8_t k=0; k<20; k++){
			//Dark red (GRB HEX code - 0x008B00)
			set_color(0x00,0xFA,0x9A);
		}
}
