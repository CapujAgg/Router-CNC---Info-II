//Documentacion de un archivo
/**
 	\file TestMotot
 	\brief Mover un motor generando pulsos con timer
 	\details
 	\author
 	\date 2015.09
*/
//Documentacion de una funcion
/**
	\fn  int NombreFuncion( int val )
	\brief Descripcion general de NombreFuncion
 	\details Descripción detallada de la NombreFuncion
 	\author Ing. Marcelo Trujillo
 	\date 2015.09
 	\param [in] val Valor para …...
	\return Retorna el resultado de ……..


 *	@fn  void TimerStart ( uint8_t  , timer_t   )
 *	@brief Dispara el temporizador n_ev  durante t tiempo
 *  @details Portable
 *	@param [in] n_ev numero de tempotizador
 *	@param [in] t tiempo de duracion
 *  @return void

*/
//Documentacion de una variable
/**
	\var char estado
	\brief Descripción breve de la variable.
	\details Descripción detallada de la variable.
*/

#include "Aplicacion.h"
#include "stdio.h"

//** Descripcion del programa ***************************************************************************
// en esta version manejamos los motores con el timer 0
// controlamos la velocidad y distanciaores
// voy a tratar de mover dos motores
//***************************************************************************************************

//** Buffers del sistema ***************************************************************************
volatile unsigned char key = NO_KEY ;			//!< Buffer de teclado
volatile unsigned char Flagkey = 0 ;			//!< Buffer de teclado
unsigned char TxStart;
system_t sys;
//***************************************************************************************************

void(* arrayFunciones[])(void) = {funcion_S_INI,funcion_S_ALARM,funcion_S_IDLE,funcion_S_MANUAL,funcion_S_AUTO,funcion_S_SETTINGS,funcion_S_HOMING};
int main(void)
{

//declaración de variables
int condicion = 1;

//inicialización de perifericos

Inicializar_Perifericos();

	while(condicion)
	{

		state_machine();

	}
	return 0 ;
}




void debugPrint(char* s){
	printf("	%s \n",s);
}








