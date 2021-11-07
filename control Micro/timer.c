/**********************************************************
 * FILE NAME : timer.c
 *
 * DISCRIBTION : timer0 driver
 *
 * AUTHOR : Kyrillos Phelopos Sawiris
 *
 **********************************************************/

/*******************************************************
 *            INCLUDE LIBRARIES
 *******************************************************/
#include "timer.h"
#include "common_macros.h"
#include <avr/io.h>
#include<avr/interrupt.h>

/*
 * defination of the callBack function
 */

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*
 * ISR in case of OVERFLOW mood
 */
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*
 * ISR in case of COMPARE mood
 */

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*
 * function that initialize the timer
 */
void TIMER_init(const TIMER_config* config_ptr)
{
	TCNT0=0;             // set 0 to be initial value
	TCCR0|=(1<<FOC0);    // as it isnot PWM


/*
 * setting if the timer will be in compare mood
 * and if it will be polling or interrupt
 */
	if(config_ptr->TIMER_MOOD==COMPARE_MOOD)
	{
		OCR0  = config_ptr->compareValue; // Set Compare Value
		TCCR0 |=(1<<WGM01);
		if (config_ptr->type == INTERRUPT)
		{

			TIMSK |= (1<<OCIE0); // Enable Timer0 Compare Interrupt
		}

	}
	/*
	 * settings if the timer will be in overflow and operate in interrupt
	 */
	else if (config_ptr->TIMER_MOOD==OVERFLOW_MOOD &&config_ptr->type == INTERRUPT)
	{
		TIMSK |= (1<<TOIE0); // Enable Timer0 Overflow Interrupt
	}

/*
 * setting the disared prescaler
 */
	TCCR0 = (TCCR0&0xf8)|(config_ptr->TIMER_PRESCALER);

	/*
	 * setting the POLLING MOODE and INTERRUPT MOOD
	 */
	if (config_ptr->type == POLLING)
	{
		if(config_ptr->TIMER_MOOD==OVERFLOW_MOOD)//if it was overflow
		{
			while(!(TIFR & (1<<TOV0))); // Wait until the Timer0 Overflow occurs (wait until TOV0 = 1)
		}
		else if (config_ptr->TIMER_MOOD==COMPARE_MOOD)// if it was compare
		{
			while(!(TIFR & (1<<OCF0))); // Wait until the Timer0 compare match occurs (wait until OCF0 = 1)
		}
		TIMER_deInit();
	}




}
/*
 * function to de-initialize the timer
 */
void TIMER_deInit()
{

	SET_BIT(TIFR,TOV0); // Clear TOV0 bit by set its value

	TCCR0 = 0; // Stop Timer0 by clear the Clock bits (CS00, CS01 and CS02)


}
/*
 * setting call back function
 */
void TIMER_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}


