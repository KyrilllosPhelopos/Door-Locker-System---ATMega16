/*
 * FILE NAME : HMI_ECU.c
 *
 * DISCRIBTION : RESPONSIBLE FOR INTERFACING WITH THE USER
 *
 * AUTHOR : Kyrillos Phelopos Sawiris
 */

/*******************************************************
 *            INCLUDE LIBRARIES
 *******************************************************/
#include"lcd.h"
#include"keypad.h"
#include<util/delay.h>
#include"password.h"
#include"uart.h"

/*********************************************************
 *             MAIN FUNCTION
 **********************************************************/
int main()
{
	/**********************************************************
	 *              LIBRARIES CONFIGRATIONS
	 **********************************************************/
	UART_config UART_Config = {BIT_8,EVEN_PARITY,BIT_1,9600};


	/*********************************
	 * INITIALIZING USED FUNCTIONS
	 ******************************/
	LCD_init();

	UART_init(&UART_Config);

	PASSWORD_setPassword();
	/*
	 * declearing some variables to be used
	 */
	uint16 pass;
	uint8 temp;

	while(1)
	{
		/******************************************
		 * DISPLAYING MAIN OPITIONS
		 *****************************************/
		LCD_clearScreen();
		LCD_moveCursor(0, 0);
		LCD_displayString("+ : OPen Door");
		LCD_moveCursor(1, 0);
		LCD_displayString("- : Change Pass");
		temp = KEYPAD_getPressedKey(); // get the option from the user
		_delay_ms(2500);

		UART_sendByte(temp); //sending the operation to the controlling MC

		switch(temp)
		{
		/****************************************
		 *               RESET THE PASSWORD
		 **************************************/
		case '-':
			do{
				/*
				 * checking the old password
				 */
				pass = PASSWORD_getPassword();
				UART_sendByte((uint8)(pass));
				UART_sendByte((uint8)(pass>>8));
				temp = UART_recieveByte(); // if he entered a wrong password
				if(temp == WRONG)
				{
					UART_sendByte(WRONG);
					LCD_clearScreen();
					LCD_moveCursor(0, 0);
					LCD_displayString("STOP a THIEF....");
					while(UART_recieveByte()!=DONE){}
				}
				else
					UART_sendByte(RIGHT);
			}while(temp==WRONG);

			/*
			 * when he enter the write old password he will managed to set a new one
			 */

			PASSWORD_setPassword();
			break;


		case '+':
			/**********************************************************
			 *                 OPENNING THE DOOR
			 **********************************************************/
			do{
				/*
				 * checking the old password
				 */
				pass = PASSWORD_getPassword();
				UART_sendByte((uint8)(pass));
				UART_sendByte((uint8)(pass>>8));

				temp = UART_recieveByte();
				if(temp == WRONG)
				{
					UART_sendByte(WRONG);
					LCD_clearScreen();
					LCD_moveCursor(0, 0);
					LCD_displayString("STOP a THIEF....");
					while(UART_recieveByte()!=DONE){}
				}
				else
					UART_sendByte(RIGHT);
			}while(temp==WRONG);

			/*
			 * when he enter the write old password he will managed to open the door
			 */

			UART_sendByte(OPEN);

			LCD_clearScreen();
			LCD_moveCursor(0, 0);
			LCD_displayString("OPENNING..."); // displaying the state of the door

			while(UART_recieveByte()!=OPENED){}

			LCD_clearScreen();
			LCD_moveCursor(0, 0);
			LCD_displayString("DOOR OPENED --)");

			while(UART_recieveByte()!=CLOSE){}

			LCD_clearScreen();
			LCD_moveCursor(0, 0);
			LCD_displayString("CLOSING...");


			while(UART_recieveByte()!=DONE){}

			break;
		}

	}
}
