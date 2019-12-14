#include "timers.h"
#include "led.h"
#include "MotorDC.h"
#include "interrupt.h"
/*===========================Timer0 Control===============================*/
/**
 * Description:
 * @param control
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */



uint16 gu16_initialValue, gu16_offTime;
uint8 turningOff;


/*
// for timer 1
typedef enum En_timer1Mode_t{
	T1_NORMAL_MODE=0x0000,T1_COMP_MODE_OCR1A_TOP=0x0008, T1_COMP_MODE_ICR1_TOP = 0x0018

}En_timer1Mode_t;
typedef enum En_timer1OC_t{
	T1_OC0_DIS=0,T1_OC1A_TOGGLE=0x4000,T1_OC1B_TOGGLE=0x1000,T1_OC1A_CLEAR=0x8000,T1_OC1B_CLEAR=0x2000,T1_OC1A_SET=0xC000,T1_OC1B_SET=0x3000
}En_timer1OC_t;

typedef enum En_timer1perscaler_t{
	T1_NO_CLOCK=0x0000,T1_PRESCALER_NO=0x0001,T1_PRESCALER_8=0x0002,T1_PRESCALER_64=0x0003,T1_PRESCALER_256=0x0004,T1_PRESCALER_1024=0x0005
}En_timer1perscaler_t;

typedef enum En_timer1Interrupt_t{
	T1_POLLING=0,T1_INTERRUPT_NORMAL=0x04,T0_INTERRUPT_CMP_1B=0x08, T1_INTERRUPT_CMP_1A=0x10, T1_INTERRUPT_ICAPTURE = 0x20
}En_timer1Interrupt_t;

*/
 /*========================Timer static global variables===================*/
 static En_timer0perscaler_t gen_timer0prescaler;
 static En_timer1perscaler_t gen_timer1prescaler;
 static En_timer1perscaler_t gen_timer2prescaler;
 /*========================================================================*/

void timer0Init(En_timer0Mode_t mode,En_timer0OC_t OC0,En_timer0perscaler_t prescal, uint8 initialValue, uint8 outputCompare, En_timer0Interrupt_t interruptMask)
{
    TCCR0 = mode | OC0 | prescal ;

    if (interruptMask == T0_POLLING)
    {
        ASSIGN_BIT(TIMSK, BIT6, 0x00);
        ASSIGN_BIT(TIMSK, BIT7, 0x00);
    }
    else if (interruptMask == T0_INTERRUPT_CMP)
    {
        ASSIGN_BIT(TIMSK, BIT6, 0xFF);
        ASSIGN_BIT(TIMSK, BIT7, 0x00);
    }
    else if (interruptMask == T0_INTERRUPT_NORMAL)
    {
        ASSIGN_BIT(TIMSK, BIT6, 0x00);
        ASSIGN_BIT(TIMSK, BIT7, 0xFF);
    }
    TCNT0 = initialValue;
    OCR0 = outputCompare;
    gen_timer0prescaler = prescal ;
}

/**
 * Description:
 * @param value
 */
void timer0Set(uint8 value)
{
    TCNT0 = value;
}

/**
 * Description:
 * @return
 */
uint8 timer0Read(void)
{
    return TCNT0;
}

/**
 * Description:
 */
void timer0Start(void)
{
    TCCR0 |= gen_timer0prescaler;
}

/**
 * Description:
 */
void timer0Stop(void)
{
    TCCR0 &= 0xF8;
}

/**
 * Description:
 * @param delay
 */
void timer0Delay_ms(uint16 delay)
{
    uint8 au_max_count_for_millisecond = 125;
    uint8 au_timer0InitialValue = 0;
    timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64, au_timer0InitialValue, 5, T0_POLLING);

    while (delay--)
    {
        while (TCNT0<au_max_count_for_millisecond);
        timer0Set(0);
    }
}

/*===========================Timer1 Control===============================*/
/**
 * Description:
 * @param controlA
 * @param controlB
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void timer1Init(En_timer1Mode_t mode,En_timer1OC_t OC,En_timer1perscaler_t prescal, uint16 initialValue, uint16 outputCompareA, uint16 outputCompareB,uint16 inputCapture, En_timer1Interrupt_t interruptMask)
{
	TCCR1 = mode | OC | prescal;
	TCNT1 = initialValue;
	OCR1A = outputCompareA;
	OCR1B = outputCompareB;
	ICR1  = inputCapture;
	/*for ( i = 4; i<=32; i*=2)
	{
		ASSIGN_BIT(TIMSK, i, GET_BIT(interruptMask, i));
	}
	*/
	TIMSK |= interruptMask;
	gen_timer1prescaler = prescal;
}

/**
 * Description:
 * @param value
 */
void timer1Set(uint16 value)
{
	TCNT1 = value;
}

/**
 * Description:
 * @return
 */
uint16 timer1Read(void)
{
	return TCNT1;
}

/**
 * Description:
 */
void timer1Start(void)
{
	TCCR1 |= gen_timer1prescaler;
}

/**
 * Description:
 */
void timer1Stop(void)
{
	TCCR1 &= 0xFFF8;
}

/**
 * Description:
 * @param delay
 */
void timer1Delay_ms(uint16 delay)
{
	uint16 au16_initialValueForMillisecond = 64536;
	timer1Init(T1_NORMAL_MODE,T1_OC1_DIS,T1_PRESCALER_8, au16_initialValueForMillisecond,0,0,0,T1_INTERRUPT_NORMAL);
	while (delay--)
	{
		while (GET_BIT(TIFR,BIT2)==0);
		SET_BIT(TIFR,BIT2);
		timer1Set(au16_initialValueForMillisecond);
	}
}

/**
 * Description:
 * @param dutyCycle
 * Assume freq in in KHZ
 */
void timer1SwPWM(uint8 dutyCycle,uint8 freq)
{
	uint16 au16_realFreq = 8000000/ ((uint16)freq * 1000);
	uint16 au16_onTime = au16_realFreq * (float)dutyCycle/100;
    gu16_offTime = au16_realFreq - au16_onTime;
    gu16_initialValue = 0xFFFF - (au16_onTime + gu16_offTime);
    timer1Init(T1_NORMAL_MODE, T1_OC1_DIS, T1_PRESCALER_NO, gu16_initialValue, (gu16_initialValue + au16_onTime), 0, 0,(T1_INTERRUPT_NORMAL | T1_INTERRUPT_CMP_1A));
	/*
	while (1)
	{

	    gpioPinDirection(GPIOD, BIT5, 0xFF);
		timer1Init(T1_COMP_MODE_OCR1A_TOP,T1_OC1A_CLEAR, T1_PRESCALER_NO, au16_initialValue,au16_onTime,0,0,T1_INTERRUPT_NORMAL);
		while (GET_BIT(TIFR, BIT4)== 0)
        {
            Led_Off(LED_1);
        }
		SET_BIT(TIFR, BIT4);
		timer1Init(T1_COMP_MODE_OCR1A_TOP,T1_OC1A_SET,T1_PRESCALER_NO, au16_onTime,au16_offTime,0,0,T1_INTERRUPT_NORMAL);
		while (GET_BIT(TIFR, BIT4) == 0 )
            Led_On(LED_1);
		SET_BIT(TIFR, BIT4);
		*/
		/*
		timer1Set(au16_initialValue);
		while (GET_BIT(TIFR, BIT2)== 0)
        {
            Led_On(LED_1);
        }
		SET_BIT(TIFR, BIT2);
		timer1Set(0xFFFF - au16_offTime);
		while (GET_BIT(TIFR, BIT2)== 0)
        {
            Led_Off(LED_1);
        }
		SET_BIT(TIFR, BIT2);

	}
*/

}

/*===========================Timer2 Control===============================*/
/**
 * Description:
 * @param control
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void timer2Init(En_timer2Mode_t mode,En_timer2OC_t OC,En_timer2perscaler_t prescal, uint8 initialValue, uint8 outputCompare, uint8 assynchronous, En_timer2Interrupt_t interruptMask)
{
	TCCR2 = mode | OC | prescal;
	TCNT2 = initialValue;
	OCR2  = outputCompare;
	uint8 i;
	for ( i = 6; i<=7; i++)
	{
		ASSIGN_BIT(TIMSK, i, GET_BIT(interruptMask, i));
	}
	gen_timer2prescaler = prescal;
}

/**
 * Description:
 * @param value
 */
void timer2Set(uint8 value)
{
    TCNT2 = value;
}

/**
 * Description:
 * @return
 */
uint8 timer2Read(void)
{
    return TCNT2;
}

/**
 * Description:
 */
void timer2Start(void)
{
	TCCR2 |= gen_timer2prescaler;
}

/**
 * Description:
 */
void timer2Stop(void)
{
    TCCR2 &= 0xF8;
}


/**
 * Description:
 * @param delay
 */
void timer2Delay_ms(uint8 delay)
{
	uint8 au8_initialValueForMillisecond = 125;
    timer2Init(T2_NORMAL_MODE, T2_OC2_DIS, T2_PRESCALER_64, au8_initialValueForMillisecond, 0, 0, T2_INTERRUPT_NORMAL);

	while (delay--)
	{
		while (GET_BIT(TIFR,BIT6)==0);
		SET_BIT(TIFR,BIT6);
		timer1Set(au8_initialValueForMillisecond);
	}
}

/*
 * user defined
 */
void timer2Delay_us(uint32 delay)
{
	uint8 au8_initialValueForMicrosecond = 255 - 2;
    timer2Init(T2_NORMAL_MODE, T2_OC2_DIS, T2_PRESCALER_NO, au8_initialValueForMicrosecond, 0, 0, T2_INTERRUPT_NORMAL);

	while (delay--)
	{
		while (GET_BIT(TIFR,BIT6)==0);
		SET_BIT(TIFR,BIT6);
       //timer1Set(au8_initialValueForMicrosecond);
	}
}

/*=========================== Timer1 Interrupt ===============================*/

ISR (TIMER1_OVF_vect)
{
	timer1Set(gu16_initialValue);
    //gpioPinWrite(LED_1_GPIO, LED_1_BIT, HIGH);
    gpioPinWrite(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, HIGH);
    gpioPinWrite(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, HIGH);
    gpioPortWrite(GPIOB, HIGH);
}

ISR (TIMER1_COMPA_vect)
{
    //gpioPinWrite(LED_1_GPIO, LED_1_BIT, LOW);
    gpioPinWrite(MOTOR_EN_1_GPIO, MOTOR_EN_1_BIT, LOW);
    gpioPinWrite(MOTOR_EN_2_GPIO, MOTOR_EN_2_BIT, LOW);
    gpioPortWrite(GPIOB, LOW);
}

/*
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

*/
