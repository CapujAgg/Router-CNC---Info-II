/**
*	\file funciones.c
*	\brief 
*	\details Descripcion detallada del archivo
*	\author Bustamante, Capuj, Romero, Pizzani
*	\date 06-11-2015 09:48:39
*/



#include "Aplicacion.h"




extern void(* arrayFunciones[])(void);
extern system_t sys;



//funciones para la maquina

//comienzo

		
void funcion_S_INI (void){
	//Deb_Disp("S_INI");
	if((Inicializar_Sys()==TRUE) )	{
		 sys.state = S_ALARM ;
	}
}

void funcion_S_ALARM (void){
	//Deb_Disp("S_ALARM");
	if((alarmEvent()==FALSE) ){
		 sys.state = S_IDLE ;
	}
	else{
		report_alarm();
		sys.alarm = NO_ALARM;
		sys.state = S_INI;//apagar motores, analizar error, tomas las medidas necesarias
	}
}

void funcion_S_IDLE (void)
{
	if((keyEvent()==START_HOMING)|| (serialEvent()==START_HOMING) || sys.firstHome){
		sys.firstHome = 0;
		sys.state = S_HOMING ;
	}

	if(serialEvent()==SET_SETTINGS ){
		 sys.state = S_SETTINGS ;
	}

	if((keyEvent()==START_MANUAL)|| (serialEvent()==START_MANUAL) ){
		 sys.state = S_MANUAL ;
	}

	if((serialEvent()==START_AUTO) ){
		 sys.state = S_AUTO ;
	}
}

void funcion_S_MANUAL (void){
	//Deb_Disp("S_MANUAL");
	if((alarmEvent()==TRUE) ){
		 sys.state = S_ALARM ;
	}

	if((alarmEvent()==FALSE) && (plan_move_manual()==DONE) ){
		 sys.state = S_IDLE ;
	}
}

void funcion_S_AUTO (void)
{
	Deb_Disp("S_AUTO");
	if((alarmEvent()==TRUE) ){
		 sys.state = S_ALARM ;

	}
	if((alarmEvent()==FALSE)&& (sys.sAuto==DONE) ){
		 sys.state = S_IDLE ;
	}
}

void funcion_S_SETTINGS (void)
{
	Deb_Disp("S_SETTINGS");
	if(setSettings()==DONE)
	{
		 sys.state = S_IDLE ;

	}

}
void funcion_S_HOMING (void)
{

	//Deb_Disp("S_HOMING");
	if((alarmEvent()==TRUE) ){
		 sys.state = S_ALARM ;
	}

	if((alarmEvent()==FALSE)&& (goHome()==DONE) ){
		 sys.state = S_IDLE ;
	}
}


//Maquina de estado mediante vector de ptr a funcion

/**
*	\fn void maquina_estado()
*	\brief Resumen
*	\details Detalles
*	\author Bustamante, Capuj, Romero, Pizzani
*	\date 06-11-2015 09:48:39
*/
void state_machine()
{
	//sys.state = S_INI;


	if(sys.state > S_HOMING )
	{
		sys.state = S_INI;
		return;
	}

	arrayFunciones[sys.state]();
}











