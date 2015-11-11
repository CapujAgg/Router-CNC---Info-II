/*
 * Sys_Event.c
 *
 *  Created on: 8/11/2015
 *      Author: Julieta
 */

#include "Aplicacion.h"

extern system_t sys;

//Funciones asociadas a los eventos

/**
 *	\fn int Inicializar(void)
 *	\brief Resumen
 *	\details Detalles
 *	\author Bustamante, Capuj, Romero, Pizzani
 *	\date 06-11-2015 09:48:39
 */
int Inicializar_Sys(void)
{

	settings_restore_global_settings();
	init_system_var();
	//uint8_t c;
	/*
	 * reset estructuras y buffers, planner, stepper, serial,
	 * cargar deafult settigs ( sin home )
	 *
	 * establecer conexion con la pc, si falla ir a Alarm (mensaje en lcd)
	 * conexion ok, mensaje de bienvenida ( lcd, entorno ..)
	 *
	 *
	 * go idle
	 */
//	sendSerialString(PC_CONNECTION); //ver si hace falta meter un delay
//	c = serialRead();
//	if(c!=CONNECTION_ESTABLISHED)
//		sys.alarm = NO_PC_CONNECTION;
//	else
//	{

//	}
	return TRUE;
}

/**
 *	\fn int serialEvent(void)
 *	\brief Resumen
 *	\details Detalles
 *	\author Bustamante, Capuj, Romero, Pizzani
 *	\date 06-11-2015 09:48:39
 */
int serialEvent(void)
{
	int res = 0 ;

	//Codigo propio de la funci?n


	return res;

}

/**
 *	\fn int keyEvent(void)
 *	\brief Resumen
 *	\details Detalles
 *	\author Bustamante, Capuj, Romero, Pizzani
 *	\date 06-11-2015 09:48:39
 */
int keyEvent(void)
{
	int def = 7 ; //REVISAR valor tecla no valida
	uint8_t c;
	c = Teclado();

	switch(c)
	{
	case key_XR: case key_XL: case key_YR: case key_YL: case key_ZU: case key_ZD:
		sys.manual_key=c;
		return START_MANUAL;
	case key_HOME:
		return START_HOMING;
	case key_MENU:
		return SET_SETTINGS;
	}
	return def;
}

/**
 *	\fn int alarmEvent(void)
 *	\brief Resumen
 *	\details Detalles
 *	\author Bustamante, Capuj, Romero, Pizzani
 *	\date 06-11-2015 09:48:39
 */
int alarmEvent(void)
{

	if(sys.alarm == NO_ALARM)
		return FALSE;
	else{
		return TRUE;
	}
	/*
	 * hay que chequear sys.alarm y
	 * enviarlo por pc, lcd
	 *
	 */
}

int	setSettings(void){

	return DONE;
}

void init_system_var (void){

	sys.state = S_INI;
	sys.alarm = NO_ALARM;
	sys.firstHome = FALSE;
	sys.abort = FALSE;
	sys.endstop_rached = FALSE;
	sys.manual_key = NO_KEY;
	sys.rt_exec_state = FALSE;
	sys.sAuto = FALSE;
	sys.suspend = FALSE;
	memset(&sys.position, 0, sizeof(sys.position));
	memset(&sys.new_Home_Ref, 0 ,sizeof(sys.new_Home_Ref));
	init_planblock();

}




















