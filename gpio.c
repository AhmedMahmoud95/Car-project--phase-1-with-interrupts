#include "gpio.h"

/*===========================PORT Control===============================*/
/**
 * Description: set port direction (which is DDR register)
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @param direction: set the port direction and takes the following values
 * 				- 0x00 -> Input
 * 				- 0xff -> Output
 */
void gpioPortDirection(uint8 port, uint8 direction)
{
	switch (port)
	{
		case GPIOA:
		PORTA_DIR = direction;
		break;
		case GPIOB:
		PORTB_DIR = direction;
		break;
		case GPIOC:
		PORTC_DIR = direction;
		break;
		case GPIOD:
		PORTD_DIR = direction;
		break;
		default:
		break;
	}
}

/**
 * Description: set the port value (which is PORT register)
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param value: set the port value and takes the following values
 * 				- 0x00 -> Low
 * 				- 0xff -> High
 */
void gpioPortWrite(uint8 port, uint8 value)
{
	switch (port)
	{
		case 0:
		PORTA_DATA = value;
		break;
		case 1:
		PORTB_DATA = value;
		break;
		case 2:
		PORTC_DATA = value;
		break;
		case 3:
		PORTD_DATA = value;
		break;
		default:
		break;
	}
}

/**
 * Description: toggle the port value (which is PORT register)
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 */

void gpioPortToggle(uint8 port)
{
	switch (port)
	{
		case 0:
		PORTA_DATA =  PORTA_DATA ^ 0xFF;
		break;
		case 1:
		PORTB_DATA = PORTB_DATA ^ 0xFF;
		break;
		case 2:
		PORTC_DATA = PORTC_DATA ^ 0xFF;
		break;
		case 3:
		PORTD_DATA = PORTD_DATA ^ 0xFF;
		break;
		default:
		break;
	}
}

/**
 * Description: read the current port value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @return
 */
uint8 gpioPortRead(uint8 port)
{
	switch (port)
	{
		case GPIOA:
		return (PORTA_PIN);
		case GPIOB:
		return (PORTB_PIN);
		case GPIOC:
		return (PORTC_PIN);
		case GPIOD:
		return (PORTD_PIN);
	}
	return 0; // Unreached
}

/*===========================PIN Control===============================*/
/**
 * Description: set selected pins (more than one pin [ORed]) direction
 *
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pins the user need to set its direction and takes
 * 				any member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 *
 * @param direction: set the pins direction and takes the following values
 * 				- 0x00 -> Input
 * 				- 0xff -> Output
 */
void gpioPinDirection(uint8 port, uint8 pins, uint8 direction)
{
	switch (port)
	{
		case GPIOA:
		if (direction == 0xff)
		{
			PORTA_DIR |= pins;
		}
		else
		{
			pins ^= 0xFF;
			PORTA_DIR &= pins;
		}
		break;

		case GPIOB:
		if (direction == 0xff)
		{
			PORTB_DIR |= pins;
		}
		else
		{
			pins ^= 0xFF;
			PORTB_DIR &= pins;
		}
		break;

		case GPIOC:
		if (direction == 0xff)
		{
			PORTC_DIR |= pins;
		}
		else
		{
			pins ^= 0xFF;
			PORTC_DIR &= pins;
		}
		break;

		case GPIOD:
		if (direction == 0xff)
		{
			PORTD_DIR |= pins;
		}
		else
		{
			pins ^= 0xFF;
			PORTD_DIR &= pins;
		}
		break;

		default:
		break;
	}
}

/**
 * Description: set selected pins (more than one pin [ORed]) values
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pins the user need to write its values and takes
 * 				any member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 * @param value
 */
void gpioPinWrite(uint8 port, uint8 pins, uint8 value)
{
	switch (port)
	{
		case GPIOA:
		if (value == 0xff)
		{
			PORTA_DATA |= pins;
		}
		else
		{
			pins ^= 0xFF;
			PORTA_DATA &= pins;
		}
		break;

		case GPIOB:
		if (value == 0xff)
		{
			PORTB_DATA |= pins;
		}
		else
		{
			pins ^= 0xFF;
			PORTB_DATA &= pins;
		}
		break;

		case GPIOC:
		if (value == 0xff)
		{
			PORTC_DATA |= pins;
		}
		else
		{
			pins ^= 0xFF;
			PORTC_DATA &= pins;
		}
		break;

		case GPIOD:
		if (value == 0xff)
		{
			PORTD_DATA |= pins;
		}
		else
		{
			pins ^= 0xFF;
			PORTD_DATA &= pins;
		}
		break;

		default:
		break;
	}
}

/**
 * Description: toggle selected pin (only one pin) direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pin the user need to toggle it's value and takes
 * 				only one member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 */

void gpioPinToggle(uint8 port, uint8 pins)
{
	switch (port)
	{
		case GPIOA:
		PORTA_DATA ^= pins;
		break;

		case GPIOB:
		PORTB_DATA ^= pins;
		break;

		case GPIOC:
		PORTC_DATA ^= pins;
		break;

		case GPIOD:
		PORTD_DATA ^= pins;
		break;
	}

}

/**
 * Description: read selected pin (only one pin) direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @param pin: the selected pin the user need to read it's value and takes
 * 				only one member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 * @return
 */
uint8 gpioPinRead(uint8 port, uint8 pin)
{
	switch (port)
	{
		case GPIOA:
		return (GET_BIT(PORTA_PIN,pin));
		case GPIOB:
		return (GET_BIT(PORTB_PIN,pin));
		case GPIOC:
		return (GET_BIT(PORTC_PIN,pin));
		case GPIOD:
		return (GET_BIT(PORTD_PIN,pin));
	}
	return FALSE ;
}

/*===========================Upper Nibble Control===============================*/
/**
 * Description: set the upper nibble direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param direction
 */
void gpioUpperNibbleDirection(uint8 port, uint8 direction)
{
	switch (port)
	{
		case GPIOA:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTA_DATA, i, value);
		}
		*/
		if (direction == HIGH)
            PORTA_DIR |= 0xF0;
		else
            PORTA_DIR &= 0x0F;
		case GPIOB:
		/*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTB_DATA, i, value);
		}
		*/
		if (direction == HIGH)
            PORTB_DIR |= 0xF0;
		else
            PORTB_DIR &= 0x0F;
		case GPIOC:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTC_DATA, i, value);
		}
		*/
		if (direction == HIGH)
            PORTC_DIR |= 0xF0;
		else
            PORTC_DIR &= 0x0F;
		case GPIOD:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTD_DATA, i, value);
		}
		*/
		if (direction == HIGH)
            PORTD_DIR |= 0xF0;
		else
            PORTD_DIR &= 0x0F;
	}
}

/**
 * Description: write the upper nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param value
 */
void gpioUpperNibbleWrite(uint8 port, uint8 value)
{
	switch (port)
	{
		case GPIOA:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTA_DATA, i, value);
		}
		*/
		if (value == HIGH)
            PORTA_DATA |= 0xF0;
		else
            PORTA_DATA &= 0x0F;
		case GPIOB:
		/*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTB_DATA, i, value);
		}
		*/
		if (value == HIGH)
            PORTB_DATA |= 0xF0;
		else
            PORTB_DATA &= 0x0F;
		case GPIOC:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTC_DATA, i, value);
		}
		*/
		if (value == HIGH)
            PORTC_DATA |= 0xF0;
		else
            PORTC_DATA &= 0x0F;
		case GPIOD:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTD_DATA, i, value);
		}
		*/
		if (value == HIGH)
            PORTD_DATA |= 0xF0;
		else
            PORTD_DATA &= 0x0F;
	}
}

/**
 * Description: toggle the upper nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 */

void gpioUpperNibbleToggle(uint8 port)
{
	switch (port)
	{
		case GPIOA:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			TOGGLE_BIT(PORTA_DATA,i);
		}
		*/
		PORTA_DATA ^= 0xF0;
		case GPIOB:
        PORTB_DATA ^= 0xF0;
        /*
		for (uint8 i = 4; i<8; i++)
		{
			TOGGLE_BIT(PORTB_DATA,i);
		}
		*/
		case GPIOC:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			TOGGLE_BIT(PORTC_DATA,i);
		}
		*/
		PORTC_DATA ^= 0xF0;
		case GPIOD:
		/*
		for (uint8 i = 4; i<8; i++)
		{
			TOGGLE_BIT(PORTD_DATA,i);
		}
		*/
		PORTD_DATA ^= 0xF0;
	}
}

/**
 * Description: read the upper nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @return
 */
uint8 gpioUpperNibbleRead(uint8 port)
{
		switch (port)
	{
		case GPIOA:
		return (PORTA_PIN & 0xF0);
		case GPIOB:
		return (PORTB_PIN & 0xF0);
		case GPIOC:
		return (PORTC_PIN & 0xF0);
		case GPIOD:
		return (PORTD_PIN& 0xF0);
	}
	return FALSE;
}

/*===========================Lower Nibble Control===============================*/
/**
 * Description: set the lower nibble direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @param direction
 */
void gpioLowerNibbleDirection(uint8 port, uint8 direction)
{
	switch (port)
	{
		case GPIOA:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTA_DATA, i, value);
		}
		*/
		if (direction == HIGH)
            PORTA_DIR |= 0x0F;
		else
            PORTA_DIR &= 0xF0;
		case GPIOB:
		/*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTB_DATA, i, value);
		}
		*/
		if (direction == HIGH)
            PORTB_DIR |= 0x0F;
		else
            PORTB_DIR &= 0xF0;
		case GPIOC:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTC_DATA, i, value);
		}
		*/
		if (direction == HIGH)
            PORTC_DIR |= 0x0F;
		else
            PORTC_DIR &= 0xF0;
		case GPIOD:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTD_DATA, i, value);
		}
		*/
		if (direction == HIGH)
            PORTD_DIR |= 0x0F;
		else
            PORTD_DIR &= 0xF0;
	}
}

/**
 * Description: write the lower nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param value
 */
void gpioLowerNibbleWrite(uint8 port, uint8 value)
{
	switch (port)
	{
		case GPIOA:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTA_DATA, i, value);
		}
		*/
		if (value == HIGH)
            PORTA_DATA |= 0x0F;
		else
            PORTA_DATA &= 0xF0;
		case GPIOB:
		/*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTB_DATA, i, value);
		}
		*/
		if (value == HIGH)
            PORTB_DATA |= 0x0F;
		else
            PORTB_DATA &= 0xF0;
		case GPIOC:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTC_DATA, i, value);
		}
		*/
		if (value == HIGH)
            PORTC_DATA |= 0x0F;
		else
            PORTC_DATA &= 0xF0;
		case GPIOD:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			ASSIGN_BIT(PORTD_DATA, i, value);
		}
		*/
		if (value == HIGH)
            PORTD_DATA |= 0x0F;
		else
            PORTD_DATA &= 0xF0;
	}
}

/**
 * Description: toggle the lower nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 */
void gpioLowerNibbleToggle(uint8 port)
{
	switch (port)
	{
		case GPIOA:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			TOGGLE_BIT(PORTA_DATA,i);
		}
		*/
		PORTA_DATA ^= 0x0F;
		case GPIOB:
        PORTB_DATA ^= 0x0F;
        /*
		for (uint8 i = 4; i<8; i++)
		{
			TOGGLE_BIT(PORTB_DATA,i);
		}
		*/
		case GPIOC:
        /*
		for (uint8 i = 4; i<8; i++)
		{
			TOGGLE_BIT(PORTC_DATA,i);
		}
		*/
		PORTC_DATA ^= 0x0F;
		case GPIOD:
		/*
		for (uint8 i = 4; i<8; i++)
		{
			TOGGLE_BIT(PORTD_DATA,i);
		}
		*/
		PORTD_DATA ^= 0x0F;
	}
}

/**
 * Description: read the lower nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @return
 */
uint8 gpioLowerNibbleRead(uint8 port)
{
		switch (port)
	{
		case GPIOA:
		return (PORTA_PIN & 0x0F);
		case GPIOB:
		return (PORTB_PIN & 0x0F);
		case GPIOC:
		return (PORTC_PIN & 0x0F);
		case GPIOD:
		return (PORTD_PIN & 0x0F);
	}
	return FALSE;
}
