#include "Aplicacion.h"

settings_t settings;
plan_block_t plan_block_buffer[PL_BUFF_TAM];

uint8_t plan_move_manual(void){

	char str[20];
	// uint8_t ok;
	// actualizar posiciones globales ?
	// TODO hay que tener una variable posiscion para el planner, que no sea en tiempo real

	switch(sys.manual_key){
	case key_XR:
		if(st_move_line( X_AXIS, CW, settings.manual_steps[X_AXIS], settings.def_feed_rate[X_AXIS]))
			sys.planner_position[X_AXIS]+=settings.manual_steps[X_AXIS];
		else return UNDONE;
		break;
	case key_XL:
		if(st_move_line( X_AXIS, CCW, settings.manual_steps[X_AXIS], settings.def_feed_rate[X_AXIS]))
			sys.planner_position[X_AXIS]-=settings.manual_steps[X_AXIS];
		else return UNDONE;
		break;
	case key_YR:
		if(st_move_line( Y_AXIS, CW, settings.manual_steps[Y_AXIS], settings.def_feed_rate[Y_AXIS]))
			sys.planner_position[Y_AXIS]+=settings.manual_steps[Y_AXIS];
		else return UNDONE;
		break;
	case key_YL:
		if(st_move_line( Y_AXIS, CCW, settings.manual_steps[Y_AXIS], settings.def_feed_rate[Y_AXIS]))
			sys.planner_position[Y_AXIS]-=settings.manual_steps[Y_AXIS];
		else return UNDONE;
		break;
	case key_ZU:
		if(st_move_line( Z_AXIS, CW, settings.manual_steps[Z_AXIS], settings.def_feed_rate[Z_AXIS]))
			sys.planner_position[Z_AXIS]+=settings.manual_steps[Z_AXIS];
		else return UNDONE;
		break;
	case key_ZD:
		if(st_move_line( Z_AXIS, CCW, settings.manual_steps[Z_AXIS], settings.def_feed_rate[Z_AXIS]))
			sys.planner_position[Z_AXIS]-=settings.manual_steps[Z_AXIS];
		else return UNDONE;
		break;
	}
	Dato_LCD(LCD_CLEARDISPLAY ,LCD_CONTROL);
	sprintf(str, "Xp:%d", sys.planner_position[X_AXIS]);
	Display_lcd(str,RENGLON1,(char)7);
	sprintf(str, "Yp:%d", sys.planner_position[Y_AXIS]);
	Display_lcd(str,RENGLON2,(char)7);
	return DONE;
}


void plan_buffer_line(float *target, float feed_rate, uint8_t invert_feed_rate){

	// llenar plan_block_buffer[PL_BUFF_TAM];

}

uint8_t goHome(void)
{
	/*
	 * Esta funcion debe mover los ejes de a uno hasta llegar a los finales de correra de cada uno
	 * una vez alcanzados los tres limites, setea el 0,0,0 y retorna DONE
	 */
	memset (&sys.position,0,sizeof(sys.position));
	sys.alarm = NO_ALARM;
	return DONE;
}

void init_planblock (){

	memset(&plan_block_buffer,0,sizeof(plan_block_buffer));
}

void mc_line ( float *target, float feed_rate, uint8_t invert_feed_rate){

	/*
	 * if ( sys.state == PROCESANDO CODIGO G) { return }
	 *
	 * do { chequear si el buffer esta lleno
	 * 		si esta vacio break;
	 * 	  } while(1)
	 */
	//if (soft_check_limit(target)){

	plan_buffer_line(target, feed_rate, invert_feed_rate);
	//}
}


void mc_arc( float *position, float *target, float *ijk, float r, float feed_rate,
		uint8_t invert_feed_rate, uint8_t axis_0, uint8_t axis_1, uint8_t axis_linear, uint8_t is_clockwise_arc){

	/*
	 * cos phi = (CP*CT) / (|CP|*|CT|) ; producto vectorial
	 * |CP| = |CT| = r^2
	 */
	float SEG_CT_X, SEG_CT_Y, SEG_CP_X, SEG_CP_Y,numerator, denominator, travel_angle, delta_angle, phi, pointB[N_AXIS];

	SEG_CT_X = target[axis_0]-ijk[axis_0];
	SEG_CT_Y = target[axis_1]-ijk[axis_1];

	SEG_CP_X = position[axis_0]-ijk[axis_0];
	SEG_CP_Y = position[axis_1]-ijk[axis_1];

	numerator = ( (SEG_CT_X * SEG_CP_X) + (SEG_CT_Y * SEG_CP_Y));
	denominator = r*r;

	travel_angle = acos ( numerator/ denominator );

	delta_angle = 1;

	for ( phi = delta_angle ; phi <= travel_angle ; phi += delta_angle){

		pointB[axis_0] = r * sin (phi);
		pointB[axis_1] = r * cos (phi);

		mc_line ( pointB, feed_rate, invert_feed_rate );
	}
	//if (sys.abort) { return; }
}

















