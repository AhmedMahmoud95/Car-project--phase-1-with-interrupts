#include "led.h"

/**
 * Description: Initialize the LED_x (where x 0, 1, 2, 3) as output
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_Init(En_LedNumber_t led_id)
{
		switch (led_id)
		{
			case LED_0:
			gpioPinDirection(LED_0_GPIO, LED_0_BIT, 0xFF);
			break;
			case LED_1:
			gpioPinDirection(LED_1_GPIO, LED_1_BIT, 0xFF);
			break;
			case LED_2:
			gpioPinDirection(LED_2_GPIO, LED_2_BIT, 0xFF);
			break;
			case LED_3:
			gpioPinDirection(LED_3_GPIO, LED_3_BIT, 0xFF);
			break;
		}
}

/**
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be on
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_On(En_LedNumber_t led_id)
{
	switch (led_id)
	{
		case LED_0:
		gpioPinDirection(LED_0_GPIO, LED_0_BIT, 0xFF);
		gpioPinWrite(LED_0_GPIO, LED_0_BIT, HIGH);
		break;
		case LED_1:
		gpioPinDirection(LED_1_GPIO, LED_1_BIT, 0xFF);
        gpioPinWrite(GPIOB, LED_1_BIT, HIGH);
		break;
		case LED_2:
		gpioPinDirection(LED_2_GPIO, LED_2_BIT, 0xFF);
		gpioPinWrite(LED_2_GPIO, LED_2_BIT, HIGH);
		break;
		case LED_3:
		gpioPinDirection(LED_3_GPIO, LED_3_BIT, 0xFF);
		gpioPinWrite(LED_3_GPIO, LED_3_BIT, HIGH);
		break;
	}
}

/**
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be off
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_Off(En_LedNumber_t led_id)
{
	switch (led_id)
	{
		case LED_0:
		gpioPinDirection(LED_0_GPIO, LED_0_BIT, 0xFF);
		gpioPinWrite(LED_0_GPIO, LED_0_BIT, LOW);
		break;
		case LED_1:
		gpioPinDirection(LED_1_GPIO, LED_1_BIT, 0xFF);
        gpioPinWrite(GPIOB, LED_1_BIT, LOW);
		break;
		case LED_2:
		gpioPinDirection(LED_2_GPIO, LED_2_BIT, 0xFF);
		gpioPinWrite(LED_2_GPIO, LED_2_BIT, LOW);
		break;
		case LED_3:
		gpioPinDirection(LED_3_GPIO, LED_3_BIT, 0xFF);
		gpioPinWrite(LED_3_GPIO, LED_3_BIT, LOW);
		break;
	}
}

/**
 * Description: Toggle the LED_x state (where x 0, 1, 2, 3)
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_Toggle(En_LedNumber_t led_id)
{
	switch (led_id)
	{
		case LED_0:
		gpioPinDirection(LED_0_GPIO, LED_0_BIT, 0xFF);
		gpioPinToggle(LED_0_GPIO, LED_0_BIT);
		break;
		case LED_1:
		gpioPinDirection(LED_1_GPIO, LED_1_BIT, 0xFF);
		gpioPinToggle(LED_1_GPIO, LED_1_BIT);
		break;
		case LED_2:
		gpioPinDirection(LED_2_GPIO, LED_2_BIT, 0xFF);
		gpioPinToggle(LED_2_GPIO, LED_2_BIT);
		break;
		case LED_3:
		gpioPinDirection(LED_3_GPIO, LED_3_BIT, 0xFF);
		gpioPinToggle(LED_3_GPIO, LED_3_BIT);
		break;
	}
}
