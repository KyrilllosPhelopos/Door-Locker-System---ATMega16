#include"password.h"
#include"keypad.h"
#include<util/delay.h>
#include"uart.h"
#include"std_types.h"



uint16 PASSWORD_getPassword()
{
	uint8 i , temp ;
	uint16 pass=0;

	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("Enter Password:");

	LCD_moveCursor(1, 0);
	for(i=0;i<4;i++)
	{
		temp= KEYPAD_getPressedKey();
		_delay_ms(1500);
		if(temp>=0 && temp<=9)
		{
			LCD_displayCharacter('*');
			pass= pass * 10 +temp;
		}
	}
	_delay_ms(1000);
	return pass;
}

static uint16 PASSWORD_checkPassword()
{
	uint8 i , temp ;
	uint16 pass=0;

	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("Re-Enter Pass:");

	LCD_moveCursor(1, 0);

	for(i=0;i<4;i++)
	{
		temp= KEYPAD_getPressedKey();
		_delay_ms(1500);
		if(temp>=0&&temp<=9)
		{
			LCD_displayCharacter('*');
			pass= pass * 10 +temp;
		}
	}
	_delay_ms(1000);
	return pass;

}

void  PASSWORD_setPassword()
{
	uint8 valid=TRUE;
	uint16 pass1=0, pass2=0 ;

	while(valid)
	{
		pass1 = PASSWORD_getPassword();
		pass2 = PASSWORD_checkPassword();

		if(pass1==pass2)
			valid=FALSE;

		else
		{
			LCD_clearScreen();
			LCD_moveCursor(0, 0);
			LCD_displayString("NOT MATCHED PASS");
			_delay_ms(2000);
			valid = TRUE;
		}
	}
	UART_sendByte((uint8)(pass1));
	UART_sendByte((uint8)(pass1>>8));

	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("SUCCESSFULL..!");
	_delay_ms(2000);
}

