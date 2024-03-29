
 /******************************************************************************
 *
 * Module: dc-motor
 *
 * File Name: dc-motor.c
 *
 * Description: DC MOTOR deriver
 *
 *Author: Kyrillos Phelopos
 *******************************************************************************/


#include"dc-motor.h"
/****************************************
 * FUNCTION DECLARATIONS
 ***************************************/

void DcMotor_Init(void)
{
GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_PIN0_ID, PIN_OUTPUT);
GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_PIN1_ID, PIN_OUTPUT);
GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN0_ID , 0);
GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN1_ID , 0);
}

void DcMotor_Rotate(DcMotor_State state)
{
if(state == STOP)
{
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN0_ID , 0);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN1_ID , 0);
}
else if (state == CLOCK_WISE)
{
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN0_ID , 1);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN1_ID , 0);
}
else if (state==ANTI_CLOCK_WISE)
{
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN0_ID , 0);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN1_ID , 1);
}
}

