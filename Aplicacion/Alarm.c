#include "Aplicacion.h"

extern system_t sys;
void report_alarm (void){
	Dato_LCD(LCD_CLEARDISPLAY ,LCD_CONTROL);
	char str[20];
	switch (sys.alarm){
	case SOFT_LIMIT_ERROR:
		Deb_Disp("SOFT_LIMIT_ERROR");
		break;
	default:
		sprintf(str, " Alarma: %d", sys.alarm);
		Display_lcd(str,RENGLON1,0);
	}
}

/*
 * Si el punto donde va a terminar nuestro movimiento supera el limite fisico
 * de alguno de los ejes retorna FALSO
 * Target esta siempre en coordenadas absolutas y en mm  y positivo???????????????????????????????
 *
 * aca tenemos que tener en cuaenta que nuestras posiciones van a ser siempre positivas
 * si tomamos el 000 con los finales de carrera.
 * !!!!!!Si es seteado un nuevo 000 tenemos que sumarlo o restarlo a traget antes de preguntar
 *
 */

uint8_t soft_check_limit ( uint8_t axis, uint8_t dir, uint32_t steps){

	int aux;
	if(dir == CW){
		aux = (steps + sys.planner_position[axis] + sys.new_Home_Ref[axis]);
		if(aux > settings.max_travel_steps[axis])
			return FALSE;
	}
	if (dir == CCW){
		aux = ( sys.planner_position[axis] + sys.new_Home_Ref[axis] -steps);
		if( aux < 0)
			return FALSE;
	}
	return TRUE;
}

/*
 * Retorna el estado del pin de direccion del eje enviado en t
 * 0->CW; 1->CCW
 */
uint8_t get_dir (uint8_t t){

	if (t==0)
		return (GetPIN(XDIR,TRUE));
	if (t==1)
		return (GetPIN(YDIR,TRUE));
	if (t==2)
		return (GetPIN(ZDIR,TRUE));
	return 0;
}






















