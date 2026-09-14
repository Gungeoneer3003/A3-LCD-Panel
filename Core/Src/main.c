/*
Assignment:	A3
Names: 		Chris Amey & Alan Kusparmakov
Professor: 	Dr. John Oliver 
Date: 		September 13th, 2026
Class: 		CPE-3160
*/

#include "main.h"

#include "stdbool.h"
#include "stm32l476xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_gpio.h"
#include <stdint.h>


#define INSTRUCTION_DISPLAY_CLEAR 0b1
#define INSTRUCTION_CURSOR_HOME 0b10
#define INSTRUCTION_ENTRY_MODE_SET 0b100
#define INSTRUCTION_DISPLAY_OFF 0b1000
#define INSTRUCTION_CURSOR_SHIFT 0b10000


/* PC1-8 = DB0-7 */
void DB_set(uint8_t val) {
	GPIOC->ODR &= ~(0b11111111 << GPIO_ODR_OD1_Pos);
	GPIOC->ODR |= (val << GPIO_ODR_OD1_Pos);
}

void RS_set(bool val) {
	GPIOC->ODR &= ~GPIO_ODR_OD0_Msk;
	GPIOC->ODR |= (val << GPIO_ODR_OD0_Pos);
}

void send_instruction(uint8_t val) {
	RS_set(false);
	DB_set(val);
}

void send_data(uint8_t val) {
	RS_set(true);
	DB_set(val);
}

void bus_init() {
	RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN);
}

void gpio_init() {
	bus_init();

	//Set PC0-9 as input mode
	GPIOC->MODER &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1 | GPIO_MODER_MODE2 | GPIO_MODER_MODE3);
	GPIOC->MODER &= ~(GPIO_MODER_MODE4 | GPIO_MODER_MODE5 | GPIO_MODER_MODE6);
	GPIOC->MODER &= ~(GPIO_MODER_MODE7 | GPIO_MODER_MODE8 | GPIO_MODER_MODE9);

	GPIOC->MODER |= (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0 | GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0);
	GPIOC->MODER |= (GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0);
	GPIOC->MODER |= (GPIO_MODER_MODE7_0 | GPIO_MODER_MODE8_0 | GPIO_MODER_MODE9_0);

	return;
}

int main() {
	gpio_init();
	
	return 0;
}
