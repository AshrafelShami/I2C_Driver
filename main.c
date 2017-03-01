#include "I2C_Config.h"

int main(void){
	DDRB = 0xFF;
	u8 i;
	
	I2C_Init();
	I2C_Start_Condition();
	I2C_WriteTo_Address(0x70);
	
	for (i = 0 ; i < 32 ; i++)
		I2C_Write(i);
	
	I2C_Stop_Condition();
	_delay_ms(500);
	
	I2C_Start_Condition();
	I2C_WriteTo_Address(0x78);
	for (i=0; i<32; i++){
		I2C_Write(i);
	}
	I2C_Stop_Condition();
	return 0;
}