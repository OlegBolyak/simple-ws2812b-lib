#include<ws2812.h>

#define QUANTITY_LEDS 180

extern SPI_HandleTypeDef hspi1;

uint8_t buffer_leds[QUANTITY_LEDS][3]={};

static void logic_0(){ //function for generate logic 0 (byte 0b00000100)
	uint8_t logic0_ws2812=0b00000100;
	GPIOA->BSRR=1<<19;
	HAL_SPI_Transmit(&hspi1, &logic0_ws2812, 1, 5);
	GPIOA->BSRR=1<<3;
}
static void logic_1(){ //function for generate logic 1 (byte 0b00000110)
	uint8_t logic1_ws2812=0b00000110;
	GPIOA->BSRR=1<<19;
	HAL_SPI_Transmit(&hspi1, &logic1_ws2812, 1, 5);
	GPIOA->BSRR=1<<3;
}
static void create_byte(uint8_t b){
	for(uint8_t n=0; n<8; n++){
		if(b & (1<<(7-n))){
			logic_1();
		}
		else {
			logic_0();
		}
	}
}
static void set_color(uint8_t Red_byte, uint8_t Green_byte, uint8_t Blue_byte){
	create_byte(Green_byte);
	create_byte(Red_byte);
	create_byte(Blue_byte);
}
void full_black(){
	for(uint8_t i=0; i<QUANTITY_LEDS; i++){
		buffer_leds[i][0]=0x00;
		buffer_leds[i][1]=0x00;
		buffer_leds[i][2]=0x00;
	}
	for(uint8_t i=0; i<QUANTITY_LEDS; i++){
			set_color(buffer_leds[i][0], buffer_leds[i][1], buffer_leds[i][2]);
	}
}
void reset(){
	uint8_t byte_reset=0b00000000;
	GPIOA->BSRR=1<<19;
	HAL_SPI_Transmit(&hspi1, &byte_reset, 18, 5);
	GPIOA->BSRR=1<<3;
}
void led_position(uint8_t position, uint8_t r,uint8_t g,uint8_t b){ //light one LED
	if(position>QUANTITY_LEDS) return;

	for(uint8_t n=0; n<position; n++){ //clear (0 to led)
		buffer_leds[n][0]=0x00;
		buffer_leds[n][1]=0x00;
		buffer_leds[n][2]=0x00;
	}
	buffer_leds[position][0]=r;
	buffer_leds[position][1]=g;
	buffer_leds[position][2]=b;
	for(uint8_t i=position+1; i<QUANTITY_LEDS; i++){ //clear (led to end strip)
		buffer_leds[i][0]=0x00;
		buffer_leds[i][1]=0x00;
		buffer_leds[i][2]=0x00;
	}

	for(uint8_t i=0; i<QUANTITY_LEDS; i++){
		set_color(buffer_leds[i][0], buffer_leds[i][1], buffer_leds[i][2]);
	}
}
void leds_range(uint8_t start, uint8_t stop, uint8_t r,uint8_t g,uint8_t b){ //light some range LEDs
	if(start>stop || start>QUANTITY_LEDS || stop>QUANTITY_LEDS) return;

	for(uint8_t k=0; k<start; k++){
		buffer_leds[k][0]=0x00;
		buffer_leds[k][1]=0x00;
		buffer_leds[k][2]=0x00;
	}
	for(uint8_t i=start; i<stop; i ++){
		buffer_leds[i][0]=r;
		buffer_leds[i][1]=g;
		buffer_leds[i][2]=b;
	}
	for(uint8_t i=stop+1; i<QUANTITY_LEDS; i ++){
		buffer_leds[i][0]=0x00;
		buffer_leds[i][1]=0x00;
		buffer_leds[i][2]=0x00;
	}

}
void shift_led(uint8_t delay, uint8_t r, uint8_t g, uint8_t b){
	for(uint8_t n=0; n<QUANTITY_LEDS; n++){
		led_position(n, r, g, b);
		HAL_Delay(delay);
	}
}
void set_color_null_to_index(uint8_t index, uint8_t r,uint8_t g,uint8_t b){
	for(uint8_t k=0; k<index; k++){
		set_color(r, g, b);
	}
}
