/**********************************************************
 * FILE NAME : timer.h
 *
 * DISCRIBTION : timer0 driver
 *
 * AUTHOR : Kyrillos Phelopos Sawiris
 *
 **********************************************************/



#ifndef TIMER_H_
#define TIMER_H_

#include"std_types.h"

/******************************************************
 *             CONFIGRATION PARAMETERS
 ****************************************************/
typedef enum
{
	COMPARE_MOOD,OVERFLOW_MOOD
}mood;

typedef enum
{
	F_CPU_CLOCK=1,F_CPU_8=2,F_CPU_64=3,F_CPU_256=4,F_CPU_1024=5
}prescaler;

typedef enum
{
	POLLING,INTERRUPT
}interfacing_type;

typedef struct
{
mood TIMER_MOOD;
prescaler TIMER_PRESCALER;
interfacing_type type;
uint8 compareValue;
}TIMER_config;



/************************************************
 *                    FUNCTIONS DIFINATIONS
 ***********************************************/


/*
 * function that initialize the timer
 */
void TIMER_init(const TIMER_config*);

/*
 * function to de-initialize the timer
 */
void TIMER_deInit();

/*
 * setting call back function
 */
void TIMER_setCallBack(void(*a_ptr)(void));

#endif /* TIMER_H_ */
