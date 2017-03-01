#include "I2C_Config.h"

void I2C_Init( void ){			/*  Initialize the I2C Protocol				  */
	TWBR = 0x26;			/*  Set Bit Rate as 00100110 in TWBR Register		  */
	TWSR |= (1 << TWPS0);		/*  Set PreScaler to Register to 01| PreScaler value is 4 */
	TWSR &=~(1 << TWPS1);		/*  Set PreScaler to Register to 01| PreScaler value is 4 */
	TWCR |= (1 << TWEN);		/*  Enable The I2C Register				  */
}

void I2C_Start_Condition ( void ){	/*  Set the START condition			*/
	TWCR &=~(1 << TWEN);		/*  Enable Interrupt Register Flag to one	*/
	TWCR |= (1 << TWSTA);		/*  Set >>Start<< Condition flag register	*/
	TWCR |= (1 << TWINT);		/*  Enable Interrupt Register Flag to one	*/
	TWCR |= (1 << TWEN);		/*  Enable the I2C Register to one		*/
	while ((TWCR & 0x80) == 0);	/*  Wait until Send Start Condition		*/
}

void I2C_Stop_Condition ( void ){	/*  Set the STOP condition			*/
	TWCR |= (1 << TWINT);		/*  Enable Interrupt Register Flag to one	*/
	TWCR |= (1 << TWEN);		/*  Enable the I2C Register to one		*/
	TWCR |= (1 << TWSTO);		/*  Set >>STOP<< Condition flag register	*/
}

void I2C_Restart( void ){
	TWCR &=~(1 << TWEN);
}

void I2C_Address_Set(unsigned char Address){
	TWAR = Address;			/*  To assign the address of Slave	*/
}

unsigned char I2C_Status(){
	return (TWSR & 0xF8);		/*  Make & with last 5 bits in TWSR Register (TWS7 ~ TWS3), and return its value	*/
}

void I2C_WriteTo_Address ( u8 Address ){
	TWDR = Address+0;			/*  Send Address of slave in WRITE mode		*/
	TWCR |= (1 << TWINT);			/*  Enable Interrupt Register Flag to one	*/
	TWCR |= (1 << TWEN);			/*  Enable the I2C Register to one		*/
	while ((TWCR & 0x80) == 0);		/*  Wait until Send Data			*/
}

void I2C_ReadFROM_Address ( u8 Address ){
	TWDR = (Address+1);			/*  Send Address of slave in READ mode		*/
	TWCR |= (1 << TWINT);			/*  Enable Interrupt Register Flag to one	*/
	TWCR |= (1 << TWEN);			/*  Enable the I2C Register to one		*/
	while ((TWCR & 0x80) == 0);		/*  Wait until Send Data			*/
}

unsigned char I2C_Read ( void ){
	TWCR |= (1 << TWINT);			/*  Enable Interrupt Register Flag to one	*/
	TWCR |= (1 << TWEN);			/*  Enable the I2C Register to one		*/
	while((TWCR & 0x80) == 0);		/*  Wait until receiving data complete		*/
	return TWDR;				/*  Return the received data from Master	*/
}

unsigned char I2C_Read_With_ACK ( u8 ACK ){
	TWCR |= (1 << TWINT);			/*  Enable Interrupt Register Flag to one			*/
	TWCR |= (1 << TWEN);			/*  Enable the I2C Register to one				*/
	TWCR |= (ACK << TWEA);			/*  Activate ACK option to send ACK to transmitter Master	*/
	while((TWCR & 0x80) == 0);		/*  Wait until receiving data complete				*/
	return TWDR;				/*  Return the received data from Master			*/
}

void I2C_Write ( u8 Data ){
	TWDR = Data;				/*  Put the data byte in TWDR Data Register	*/
	TWCR |= (1 << TWINT);			/*  Enable Interrupt Register Flag to one	*/
	TWCR |= (1 << TWEN);			/*  Enable the I2C Register to one		*/
	while ((TWCR & 0x80) == 0);		/*  Wait until Send Data			*/
}
