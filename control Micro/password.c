#include"password.h"
#include"external_eeprom.h"
#include"uart.h"
#include<util/delay.h>


void PASSWORD_storePass()
{
	uint8 temp1, temp2;
	temp1 = UART_recieveByte();
	temp2 = UART_recieveByte();

	EEPROM_writeByte(0x0, temp1); /* Write temp1 in the external EEPROM */
	_delay_ms(1000);

	EEPROM_writeByte(0x1, temp2); /* Write temp2 in the external EEPROM */
	_delay_ms(1000);

	EEPROM_writeByte(0x2, 0xf);// flag indicates that there are a password
	_delay_ms(1000);

}

void PASSWORD_checkPass()
{
	uint8 temp1, temp2 , ret1,ret2 ;
	temp1 = UART_recieveByte();
	temp2 = UART_recieveByte();
	EEPROM_readByte(0x0, &ret1); /* read temp1 in the external EEPROM */
	EEPROM_readByte(0x1, &ret2); /* read temp2 in the external EEPROM */
	if((ret1 == temp1) && (ret2 ==temp2))
	{
		UART_sendByte(RIGHT);
	}
	else
		UART_sendByte(WRONG);
}
