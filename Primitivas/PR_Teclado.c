/**
 * @author Catedra Info II
 */
#include "Aplicacion.h"

extern volatile unsigned char key ;			// Buffer de teclado
//extern volatile unsigned char Flagkey ;

/**
 *	@fn  unsigned char Teclado( void )
 *	@brief lectura del bufer de teclado, si hay codigo lo retorna y borra el buffer
 *  @details Portable
 * 	@param [in]
 *	@return Exito: Codigo de tecla, No Exito NO_KEY
*/
uint8_t Teclado( void )
{
	uint8_t Key = NO_KEY;
//	if (Flagkey){
	Key = key;
	key = NO_KEY;
//	Flagkey;
//	}
	return Key;
}
