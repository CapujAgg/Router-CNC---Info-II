/*
 * DR_InitLCD.c
 *
 *  Created on: 22/10/2015
 *      Author: admin
 */

#include "Aplicacion.h"

void InitLCD ( void )
{
	unsigned int i,j;

	//1.- Selecciono los bits del puerto como GPIOs y los direcciono:
//	PINSEL0 |= FUNCION_GPIO << 10;
//	DIRECCION(LCD_D4_PORT,LCD_D4_PIN,SALIDA);
	SetPIN(LCD_D4,FUNCION_GPIO);
	SetDIR(LCD_D4,SALIDA);

//	PINSEL0 |= FUNCION_GPIO << 20;
//	DIRECCION(LCD_D5_PORT,LCD_D5_PIN,SALIDA);
	SetPIN(LCD_D5,FUNCION_GPIO);
	SetDIR(LCD_D5,SALIDA);


//	PINSEL4 |= FUNCION_GPIO << 8;
//	DIRECCION(LCD_D6_PORT,LCD_D6_PIN,SALIDA);
	SetPIN(LCD_D6,FUNCION_GPIO);
	SetDIR(LCD_D6,SALIDA);

//	PINSEL4 |= FUNCION_GPIO << 10;
//	DIRECCION(LCD_D7_PORT,LCD_D7_PIN,SALIDA);
	SetPIN(LCD_D7,FUNCION_GPIO);
	SetDIR(LCD_D7,SALIDA);

//	PINSEL4 |= FUNCION_GPIO << 12;
//	DIRECCION(LCD_RS_PORT,LCD_RS_PIN,SALIDA);
	SetPIN(LCD_RS,FUNCION_GPIO);
	SetDIR(LCD_RS,SALIDA);

//	PINSEL3 |= FUNCION_GPIO << 24;
//	DIRECCION(LCD_BF_PORT,LCD_BF_PIN,ENTRADA);
	SetPIN(LCD_BF,FUNCION_GPIO);
	SetDIR(LCD_BF,ENTRADA);


//	PINSEL0 |= FUNCION_GPIO << 8;
//	DIRECCION(LCD_E_PORT,LCD_E_PIN,SALIDA);

	SetPIN(LCD_E,FUNCION_GPIO);
	SetDIR(LCD_E,SALIDA);

	for( i = 0 ; i < 3 ; i++ )
	{
		LCD_E_OFF;
		for ( j = 0 ; j < 500000 ; j++ ); // 300000
		LCD_DATO(1,1,0,0);

		LCD_RS_OFF;
		LCD_E_ON;

		for( j = 0 ; j < 10000 ; j++ );//4500

		LCD_E_OFF;
	}

	LCD_E_OFF;

	for ( j = 0 ; j < 500000 ; j++ ); // 300000

	LCD_DATO(0,1,0,0);

	LCD_RS_OFF;
	LCD_E_ON;

	for( j = 0 ; j < 10000 ; j++ );//4500

	LCD_E_OFF;

	// A partir de aca pasa a 4 bits
	Dato_LCD( 0x28 , LCD_CONTROL );
	Dato_LCD( 0x08 , LCD_CONTROL);	// display OFF
	Dato_LCD( 0x01 , LCD_CONTROL);	// clear display
	for( j = 0 ; j < 10000 ; j++ );	//delay por la instruccion clear display
	Dato_LCD( 0x06 , LCD_CONTROL);	// programo el LCD para mis necesidades
	Dato_LCD( 0x0C , LCD_CONTROL);	// display ON,sin cursor y blinking OFF del cursor

}
