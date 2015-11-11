/* lcd.c
 *
 *  Created on: 02/09/2015
 *      Author: Usuario
 */
#include "Aplicacion.h"

void Display_lcd( char *msg , char renglon , char posicion )
{
	unsigned char i ;

#ifdef LCD_16x2
	if( renglon )
		posicion = posicion + 0xc0 ;
	else
		posicion = posicion + 0x80 ;
#endif

#ifdef LCD_20x4
	switch( renglon )
	{
		case RENGLON0:
			posicion = posicion + 0x80 ;
			break;
		case RENGLON1:
			posicion = posicion + 0xc0 ;
			break;
		case RENGLON2:
			posicion = posicion + 0x94 ;
			break;
		case RENGLON3:
			posicion = posicion + 0xd4 ;
			break;
	}
#endif

	Dato_LCD( posicion , LCD_CONTROL );
	for( i = 0 ; msg[ i ] != '\0' ; i++ )
		Dato_LCD( msg[ i ] , LCD_DATA );

}

void Deb_Disp (char* s){

	static uint8_t i=0;
	if(i == 4)
		Dato_LCD(LCD_CLEARDISPLAY ,LCD_CONTROL);
	i%=4;
	Display_lcd(s,i,0);
	i++;
}







