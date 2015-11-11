#include "Aplicacion.h"

volatile st_block_t st_manual_block;
extern system_t sys;

uint8_t st_move_line ( uint8_t axis, uint8_t dir, uint32_t steps, uint16_t feed_rate ) {

	if(soft_check_limit(axis, dir, steps)){

		if(axis==X_AXIS){
			st_manual_block.steps[X_AXIS]=steps;
			st_manual_block.direction_bits[X_AXIS]=dir;
			st_setdir(axis,dir);
			T0MR0 = (MM_SEG/2)/feed_rate; 	//Configuro el valor de match 0
			T0MR1 = MM_SEG/feed_rate;   	//Configuro el valor de match 1
			T0TCR = 0x00000001;				//habilita el timer  0
		}
		if(axis==Y_AXIS){
			st_manual_block.steps[Y_AXIS]=steps;
			st_manual_block.direction_bits[Y_AXIS]=dir;
			st_setdir(axis,dir);
			T1MR0 = (MM_SEG/2)/feed_rate;
			T1MR1 = (MM_SEG)/feed_rate;
			T1TCR = 0x00000001;
		}
		if(axis==Z_AXIS){
			st_manual_block.steps[Z_AXIS]=steps;
			st_manual_block.direction_bits[Z_AXIS]=dir;
			st_setdir(axis,dir);
			T2MR0 = (MM_SEG/2)/feed_rate;
			T2MR1 = (MM_SEG)/feed_rate;
			T2TCR = 0x00000001;
		}
		return DONE;
	}
	sys.alarm = SOFT_LIMIT_ERROR;
	return UNDONE;
}

void st_setdir(uint8_t axis,uint8_t dir){
	if (axis == X_AXIS)
		SetPIN(XDIR,dir);
	if (axis == Y_AXIS)
		SetPIN(YDIR,dir);
	if (axis == Z_AXIS)
		SetPIN(ZDIR,dir);
}

void stepper_stop(void)
{
	SetPIN( XSTEP , OFF );
	SetPIN( YSTEP , OFF );
	SetPIN( ZSTEP , OFF );

	T0IR = ( 1 << IRMR0 );
	T0IR = ( 1 << IRMR1 );
	T1IR = ( 1 << IRMR0 );
	T1IR = ( 1 << IRMR1 );
	T2IR = ( 1 << IRMR0 );
	T2IR = ( 1 << IRMR1 );

	T0TCR = 0x00000002;	//Apaga y resetea el temporizador
	T1TCR = 0x00000002;
	T2TCR = 0x00000002;
}




























