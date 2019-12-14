//#include <avr/interrupt.h>
//#include <avr/io.h>
#include "std_types.h"
#include "gpio.h"
#include "timers.h"
#include "led.h"
#include "registers.h"
#include "interrupt.h"
#include "MotorDC.h"
//#include <avr/iom32.h>


void fromZeroToMAxInSec (uint16 seconds)
{
    /*
    * For one second, Timer0 makes 30 overflows from zero to 255
    * To update PWM every loop max Duty cycle (100)  by count divided by total number of overflows
    *           (seconds * 30)          100
    *               X                   Duty cycle
    */
    /*
    timer0Init(T0_NORMAL_MODE, T0_OC0_DIS, T0_PRESCALER_256,0 , 0, T0_INTERRUPT_NORMAL);
    uint16 au16_overFlowCount = 0;
    timer1SwPWM(0, 10);
    while (au16_overFlowCount < (5 * seconds))
    {
        timer0Set(0);
        while (timer0Read() < 255)
        {
//            continuous_pwm();
        }

        //timer2Delay_ms(1);
        au16_overFlowCount++;
        uint16 au16_newPWM = (100 * au16_overFlowCount) / (5 * seconds );
        timer1SwPWM(au16_newPWM, 10);
    }
    */
    uint16 counter = 0;
    uint16 newPwm =0;
//    timer1SwPWM(newPwm, 2);
//    timer0Delay_ms(2000);
//    newPwm = 0;
/*
*   This algorithm is used to accelerate from 0 to max in any period of time
*   Let's assume that we will accelerate in five seconds
*   therefore, we have 5000 milliseconds -> 5000/100(Max duty cycle) = 50
*   Therefore, we should increment the duty cycle by one every 50 milliseconds
*/
    timer1SwPWM(newPwm, 2);
    while (counter < 1000 * seconds)
    {
        counter ++;
        timer0Delay_ms(1);
        if (!(counter % (10 * seconds)))
        {
            timer1SwPWM(newPwm++, 2);
        }

    }
//    timer0Delay_ms(2000);
}
void fromMaxToZeroInSec (uint16 seconds)
{
    /*
    * For one second, Timer0 makes 30 overflows from zero to 255
    * To update PWM every loop max Duty cycle (100)  by count divided by total number of overflows
    *           (seconds * 30)          100
    *               X                   Duty cycle
    */
    /*
    timer0Init(T0_NORMAL_MODE, T0_OC0_DIS, T0_PRESCALER_256,0 , 0, T0_INTERRUPT_NORMAL);
    uint16 au16_overFlowCount = 2;
    uint16 au16_newPWM = 99;
    timer1SwPWM(au16_overFlowCount, 10);
    while (au16_newPWM < 100)
    {
        timer0Set(0);
        while (timer0Read() < 255)
        {
//            continuous_pwm();
        }

        //timer2Delay_ms(1);
        au16_overFlowCount++;
        au16_newPWM = (100 * au16_overFlowCount) / (5 * seconds );
        timer1SwPWM(100 - au16_newPWM, 10);
    }
    */

/*
*   This algorithm is used to accelerate from 0 to max in any period of time
*   Let's assume that we will accelerate in five seconds
*   therefore, we have 5000 milliseconds -> 5000/100(Max duty cycle) = 50
*   Therefore, we should increment the duty cycle by one every 50 milliseconds
*/
    uint16 counter = 1000 * seconds;
    uint16 newPwm =100;
    timer1SwPWM(newPwm, 2);
    while (newPwm > 1)
    {
        counter --;
        timer0Delay_ms(1);
        if (!(counter % (10 * seconds)))
        {
            timer1SwPWM(newPwm--, 2);
        }

    }
}

void rotate()
{
    MotorDC_Dir(MOT_1, FORWARD);
    MotorDC_Dir(MOT_2, BACKWARD);
    fromZeroToMAxInSec(1);
    fromMaxToZeroInSec(1);
}
int main(void)
{

    // Insert code
    gpioPortDirection(GPIOB, 0xFF);
    gpioPortWrite(GPIOB, LOW);
    MotorDC_Init(MOT_1);
    MotorDC_Init(MOT_2);
    MotorDC_Dir(MOT_1, FORWARD);
    MotorDC_Dir(MOT_2, FORWARD);
    sei();
    //MotorDC_Init(MOT_1);
    fromZeroToMAxInSec(5);
    fromMaxToZeroInSec(5);
    rotate();
    timer1Stop();
    gpioPortWrite(GPIOB, HIGH);

    while(1)
    {
        //Led_On()
        //continuous_pwm();

        //gpioPortToggle(GPIOB);
        //timer0Delay_ms(1000);
    }

    return 0;
}
/*
void continuous_pwm(void)
{
    timer1Set(gu16_initialValue);
	while (GET_BIT(TIFR, BIT2)== 0)
    {
        gpioPinWrite(LED_1_GPIO, LED_1_BIT, HIGH);
        gpioPinWrite(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, HIGH);
    }
	SET_BIT(TIFR, BIT2);
	timer1Set(0xFFFF - gu16_offTime);
	while (GET_BIT(TIFR, BIT2)== 0)
    {
        gpioPinWrite(LED_1_GPIO, LED_1_BIT, LOW);
        gpioPinWrite(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, LOW);
    }
	SET_BIT(TIFR, BIT2);

}
*/
