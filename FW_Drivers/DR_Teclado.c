/**
 * @author Catedra Info II
 */

#include "Aplicacion.h"

extern volatile unsigned char key ;		//!< Buffer de teclado
//extern volatile unsigned char Flagkey ;

/** @fn void InicializarTeclado( void )
 * @brief Inicializacion del teclado de 4x1 de la placa BASE Infotronic
 * @details No portable
 * 		<ul>
 *		<li> KEY0..3: puerto y pin de cada tecla
 * 		<li> FUNCION_GPIO: Funcion GPIO del pin del micro
 * 		<li> ENTRADA: Configura a la GPIO como entrada
 * 		<li> PINMODE_PULLUP: aplica a la entrada un pullup interno
 * 		</ul>
 * @param 	void.
 * @return 	void.
 */
void InicializarTeclado( void )
{
	SetPINSEL ( KEY0 , FUNCION_GPIO );
	SetPINSEL ( KEY1 , FUNCION_GPIO );
	SetPINSEL ( KEY2 , FUNCION_GPIO );
	SetPINSEL ( KEY3 , FUNCION_GPIO );
	SetPINSEL ( KEY4 , FUNCION_GPIO );


	SetDIR ( KEY0 , ENTRADA );
	SetDIR ( KEY1 , ENTRADA );
	SetDIR ( KEY2 , ENTRADA );
	SetDIR ( KEY3 , ENTRADA );
	SetDIR ( KEY4 , ENTRADA );


	SetPINMODE ( KEY0 , PINMODE_PULLUP );
	SetPINMODE ( KEY1 , PINMODE_PULLUP );
	SetPINMODE ( KEY2 , PINMODE_PULLUP );
	SetPINMODE ( KEY3 , PINMODE_PULLUP );
	SetPINMODE ( KEY4 , PINMODE_PULLUP );
}

/** @fn void DriverTecladoSW (  void )
 * @brief Elimina el rebote de la tecla pulsada
 * @details Portable
 * @details Caracteristicas de las macros utilizadas
 * 		<ul>
 * 		<li> REBOTES: Cantidad de veces que se cuenta un cambio de estado para darlo por valido
 * 		<li> NO_KEY: No hay tecla pulsada
 * 		</ul>
 * @param 	void.
 * @return	void.
 */
void DriverTecladoSW (  void )
{
	static unsigned char CodigoAnterior = NO_KEY;	//!< Conserva el valor del codigo de la tecla  ante el primer cambio de estado
	static unsigned char EstadosEstables;			//!< Contador de estados estables consecutivos
	unsigned char CodigoActual;						//!< Nueva lectura del las GPIO de teclado

	CodigoActual = DriverTecladoHW(  );

	if( CodigoActual == NO_KEY )
	{
		CodigoAnterior = NO_KEY;
		EstadosEstables = 0;
		return;
	}

	if( EstadosEstables == 0 )
	{
		CodigoAnterior = CodigoActual;
		EstadosEstables = 1;
		return;
	}

	if( CodigoActual != CodigoAnterior )
	{
		CodigoAnterior = NO_KEY;
		EstadosEstables = 0;
		return;
	}

	if( EstadosEstables == REBOTES )
	{
		key = CodigoActual;
//		Flagkey = 1;
		EstadosEstables++;

		return;
	}

	if( EstadosEstables == REBOTES + 1 )
		return;

	EstadosEstables ++;

	return;
}

/** @fn unsigned char DriverTecladoHW( void )
 * @brief Lectura de las GPIO asignadas a las teclas
 * @details No Portable
 * @details Caracteristicas de las macros utilizadas
 * 		<ul>
 * 		<li> NO_KEY: No hay tecla pulsada
 * 		<li> KEY0..3: puerto y pin de cada tecla
 * 		<li> ACTIVO_ALTO: Configuracion del  puerto como activo alto
 * 		</ul>
 * @param 	void.
 * @return 	codigo asignado a la tecla leida.
 */
unsigned char DriverTecladoHW( void )
{

	if ( ! GetPIN ( KEY0 , ACTIVO_ALTO ) )
		return K0;

	if ( ! GetPIN ( KEY1 , ACTIVO_ALTO ) )
		return K1;

	if ( ! GetPIN ( KEY2 , ACTIVO_ALTO ) )
		return K2;

	if ( ! GetPIN ( KEY3 , ACTIVO_ALTO ) )
		return K3;

	if ( ! GetPIN ( KEY3 , ACTIVO_ALTO ) )
		return K4;

	return NO_KEY;
}
