/*
 * FILE NAME : CONTROL_ECU.c
 * DISCRIBTION : controlling models used in the project
 * AUTHOR : Kyrillos Phelopos Sawiris
 *
 */

/*******************************************************
 *            INCLUDE LIBRARIES
 *******************************************************/

#include"std_types.h"
#include"uart.h"
#include"twi.h"
#include"timer.h"
#include"password.h"
#include"dc-motor.h"
#include"buzzer.h"

/**********************************************************
 *              LIBRARIES CONFIGRATIONS
 **********************************************************/

	TIMER_config config = {OVERFLOW_MOOD ,F_CPU_1024,POLLING,0 };

	UART_config UART_Config = {BIT_8,EVEN_PARITY,BIT_1,9600};

	TWI_config TWI_Config = {0x02,0x01};

	DcMotor_State state;

/**************************************************************
 * delay function
 *************************************************************/
void delay(uint16 counter);

/*********************************************************
 *             MAIN FUNCTION
 **********************************************************/

int main()
{

	/**********************************************
	 * INITIALIZING USED FUNCTIONS
	 ************************************************/

	DcMotor_Init();
	UART_init(&UART_Config);
	TWI_init(&TWI_Config);
	BUZZER_init();

	PASSWORD_storePass();// saving password

	uint8 temp;

	while(1)
	{
		temp = UART_recieveByte();
		switch(temp)
		{
		case '-': // RESETTING PASSWORD
		{
			do
			{
				PASSWORD_checkPass(); //check the old password
				temp = UART_recieveByte(); // receive if the password was wrong or right
				if (temp == WRONG) // if the password was wrong
				{
					BUZZER_on();// TURNNING ON THE BUZZER ALERT
					delay(100);
					BUZZER_off();
					UART_sendByte(DONE);
				}
			}while(temp==WRONG);

			PASSWORD_storePass();//WHEN ENTERIG THE OLD PASSWORD write we will set a new one
			break;
		}
		case '+': // opening the door
			do
			{
				PASSWORD_checkPass(); //check the old password
				temp = UART_recieveByte(); // receive if the password was wrong or right
				if (temp == WRONG) // if the password was wrong
				{
					BUZZER_on();// TURNNING ON THE BUZZER ALERT
					delay(100);
					BUZZER_off();
					UART_sendByte(DONE);
				}
			}while(temp==WRONG);

			if(UART_recieveByte()== OPEN)//WHEN ENTERIG THE OLD PASSWORD right the door will open
			{
				state = ANTI_CLOCK_WISE; // opening the door
				DcMotor_Rotate(state);

				/* the door will spend 10 sec to open
				 * it take 0.032 sec for one overflow and i sec = 30 overflow
				 */
				delay(300);
				UART_sendByte(OPENED); //send that the door was opened

				state = STOP;          // Keep the door opend
				DcMotor_Rotate(state);
				delay(90); // waiting 3 sec

				UART_sendByte(CLOSE); //start closing the door

				state = CLOCK_WISE;
				DcMotor_Rotate(state);
				delay(100);

				state = STOP; // the door is closed
				DcMotor_Rotate(state);

				UART_sendByte(DONE); // sending that the door was closed

			}

		}
	}
}


void delay(uint16 counter)
{
	uint16 tick;
	for(tick =0 ;tick<counter;tick++)

	{
		TIMER_init(&config);
	}

}
