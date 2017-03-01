
#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "Function_Prototypes.h"
#include "DataTypes.h"
#include <avr/io.h>


void I2C_Init( void );
void I2C_Start_Condition ( void );
void I2C_Stop_Condition  ( void );

u8   I2C_Status( void );
void I2C_Address_Set( u8 Address );

void I2C_WriteTo_Address ( u8 Address );
void I2C_Write ( u8 );

void I2C_ReadFROM_Address ( u8 Address );
u8   I2C_Read ( void );
u8   I2C_Read_With_ACK ( u8 ACK );   

















#endif /* I2C_CONFIG_H_ */