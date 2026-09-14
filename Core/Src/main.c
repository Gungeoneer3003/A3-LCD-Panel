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
#include <string.h> // For strlen();

#define INSTRUCTION_DISPLAY_CLEAR_Pos 0
#define INSTRUCTION_CURSOR_HOME_Pos 1
#define INSTRUCTION_ENTRY_MODE_SET_Pos 2
#define INSTRUCTION_DISPLAY_OFF_Pos 3
#define INSTRUCTION_CURSOR_SHIFT_Pos 4
#define INSTRUCTION_FUNCTION_SET_Pos 5

#define DISPLAY_DELAY 3000

/* PC1-8 = DB0-7 */
void DB_set(uint8_t val)
{
	GPIOC->ODR &= ~(0b11111111 << GPIO_ODR_OD1_Pos);
	GPIOC->ODR |= (val << GPIO_ODR_OD1_Pos);
}

void RS_set(bool val)
{
	GPIOC->ODR &= ~GPIO_ODR_OD0_Msk;
	GPIOC->ODR |= (val << GPIO_ODR_OD0_Pos);
}

void instruction_send(uint8_t val)
{
	RS_set(false);
	DB_set(val);
}

void data_send(uint8_t val)
{
	RS_set(true);
	DB_set(val);
}

uint8_t instruction_mask_create(uint8_t offset, uint8_t argument_count, bool *arguments)
{
	uint8_t mask = 0;
	mask |= (1 << offset);

	for (uint8_t i = 0; i < argument_count; i++) {
		uint8_t argument_offset = offset - 1 - i;
		mask |= (arguments[i] << argument_offset);
	}

	return mask;
}

void entry_mode_set(bool increment, bool display_shift_on)
{
}


// TODO: need to have display ON/OFF configured
void LCD_write_char(uint8_t letter) {
	data_send(letter);
}


void LCD_print(const char* message, uint8_t line) {
	// Check if the string can fit in the line
	size_t length = strlen(message);
	if (length > 20) {
		LCD_print("BAD STR", line);
		return;
	}

	for(int i = 0; i < length; i++) {
		LCD_write_char(message[i]);
	}

	return;
}

void bus_init() {
	RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN);
}

void gpio_init()
{
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

int main()
{
	gpio_init();
	//LCD_init();

	int displayFlag = 0;

	while (1) {
		if (displayFlag) {
	LCD_print("m", 1);
	return 0;



	while(1) {
		if(displayFlag) {
			lcd_clear();
			lcd_print("Greetings from", 0);
			lcd_print("Alan and Chris", 1);
		} else {
			lcd_clear();
			lcd_print("Hello World", 0);
			lcd_print("Assignment 3", 1);
		}

		displayFlag ^= 1;
		HAL_DELAY(DISPLAY_DELAY);
	}

	return 0;
}
