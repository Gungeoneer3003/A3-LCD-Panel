/*
Assignment:	A2
Names: 		Chris Amey & Alan Kusparmakov
Professor: 	Dr. John Oliver 
Date: 		September 9th, 2026
Class: 		CPE-3160
*/

#include "main.h"

#include "stdbool.h"
#include "stm32l476xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_gpio.h"
#include <stdint.h>

/* PC1-8 = DB0-7 */
void DB_set(uint8_t command) {
	GPIOC->ODR &= ~(0b11111111 << GPIO_ODR_OD1_Pos);
	GPIOC->ODR |= (command << GPIO_ODR_OD1_Pos);
}

void RS_set(bool val) {
	GPIOC->ODR &= ~GPIO_ODR_OD0_Msk;
	GPIOC->ODR |= (val << GPIO_ODR_OD0_Pos);
}

void gpio_init() {
	return;
}

int main() {

	return 0;
}
