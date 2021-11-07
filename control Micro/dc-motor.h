 /******************************************************************************
 *
 * Module: dc-motor
 *
 * File Name: dc-motor.h
 *
 * Description: DC MOTOR deriver
 *
 *Author: Kyrillos Phelopos
 *******************************************************************************/
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include"gpio.h"


/****************************************************************
 * configrations
 *****************************************************************/
#define MOTOR_PORT_ID       PORTC_ID
#define MOTOR_PIN0_ID       PIN5_ID
#define MOTOR_PIN1_ID       PIN6_ID

/*
 * State enum
 */
typedef enum
{
STOP,CLOCK_WISE,ANTI_CLOCK_WISE
}DcMotor_State;


void DcMotor_Init(void);

void DcMotor_Rotate(DcMotor_State state);


#endif /* DC_MOTOR_H_ */
