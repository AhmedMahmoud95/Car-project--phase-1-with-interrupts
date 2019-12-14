#include "pushButton.h"
#include "led.h"


static En_buttonStatus_t Btn_0_Status;
static En_buttonStatus_t Btn_1_Status;
static En_buttonStatus_t Btn_2_Status;
static En_buttonStatus_t Btn_3_Status;

/**
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the enum (En_buttonId) parameters
 *
 */
void pushButton_Init(En_buttonId btn_id)
{
	switch (btn_id)
	{
		case BTN_0:
            gpioPinDirection(BTN_0_GPIO, BTN_0_BIT, 0x00);
		case BTN_1:
            gpioPinDirection(BTN_1_GPIO, BTN_1_BIT, 0x00);
        case BTN_2:
            gpioPinDirection(BTN_2_GPIO, BTN_2_BIT, 0x00);
        case BTN_3:
            gpioPinDirection(BTN_3_GPIO, BTN_3_BIT, 0x00);
	}
}

/**
 * Description: read all BTN_x (where x 0, 1, 2, 3) states and store it in the program
 *
 * @note : this function must be called in the system tick handler or in the super loop handler
 */
void pushButton_Update(void)
{
    // The function reads the button continuously until it reads 10 similar readings in a row
    uint8 limit = 10, count = 0, stable_reading = FALSE;
    En_buttonStatus_t initial_Status, current_status;

    /*                  for button 0                    */

    initial_Status = (gpioPinRead(BTN_0_GPIO, BTN_0_BIT)) ? Pressed:Released;
    stable_reading = FALSE;
    while (stable_reading == FALSE)
    {
        current_status = (gpioPinRead(BTN_0_GPIO, BTN_0_BIT))? Pressed:Released;
        if (initial_Status == current_status)
        {
            count ++;
            if (count > limit)
            {
                Btn_0_Status = current_status;
                stable_reading = 1;
            }
        }
        else
        {
            initial_Status = current_status;
            count = 0;
        }

    }
/*                  for button 1                    */

    count =0;
    initial_Status = (gpioPinRead(BTN_1_GPIO, BTN_1_BIT)) ? Pressed:Released;
    stable_reading = FALSE;
    while (stable_reading == FALSE)
    {
        current_status = (gpioPinRead(BTN_1_GPIO, BTN_1_BIT)) ? Pressed:Released;
        if (initial_Status == current_status)
        {
            count ++;
            if (count > limit)
            {
                Btn_1_Status = current_status;
                stable_reading = 1;
            }
        }
        else
        {
            initial_Status = current_status;
            count = 0;
        }

}
    /*                  for button 2                    */

    count =0;
    initial_Status = (gpioPinRead(BTN_2_GPIO, BTN_2_BIT)) ? Pressed:Released;
    stable_reading = FALSE;
    while (stable_reading == FALSE)
    {
        current_status = (gpioPinRead(BTN_2_GPIO, BTN_2_BIT)) ? Pressed:Released;
        if (initial_Status == current_status)
        {
            count ++;
            if (count > limit)
            {
                Btn_2_Status = current_status;
                stable_reading = 1;
            }
        }
        else
        {
            initial_Status = current_status;
            count = 0;
        }

}
    /*                  for button 3                    */
    count =0;
    initial_Status = (gpioPinRead(BTN_3_GPIO, BTN_3_BIT)) ? Pressed:Released;
    stable_reading = FALSE;
    while (stable_reading == FALSE)
    {
        current_status = gpioPinRead(BTN_3_GPIO, BTN_3_BIT);
        if (initial_Status == current_status)
        {
            count ++;
            if (count > limit)
            {
                Btn_3_Status = current_status;
                stable_reading = 1;
            }
        }
        else
        {
            initial_Status = current_status;
            count = 0;
        }

    }

}


/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */

En_buttonStatus_t pushButton_GetStatus(En_buttonId btn_id)
{
    pushButton_Update();
    switch (btn_id)
    {
    case BTN_0:
        return Btn_0_Status;
    case BTN_1:
        return Btn_1_Status;
    case BTN_2:
        return Btn_2_Status;
    case BTN_3:
        return Btn_3_Status;
    }
    return FALSE;
}

