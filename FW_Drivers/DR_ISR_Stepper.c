/*
 * DR_ISR_Stepper.c
 *
 *  Created on: 6/11/2015
 *      Author: Fernando
 */


#include "Aplicacion.h"

extern volatile st_block_t st_manual_block;

/**
 * \fn TIMERn_IRQHandler
 * \brief control de interrupcion del timern
 * \detail cada vez que interrumpe un match bajamos y subimos el pin de Step, para generarl el tren de pulsos
 *
 */
void TIMER0_IRQHandler (void)
{
//	if (sys.state == S_MANUAL){// entra a manual, manda la linea a ejecutarse y vuelve a estado idle
		if( (T0IR & ( 1 << IRMR0 )) && st_manual_block.steps[X_AXIS] > 0 )	///< Si interrumpio Match 0
		{
			T0IR = ( 1 << IRMR0 );	///< Borro flag del Match 0
			SetPIN(XSTEP , 0 ) ;			///< XSTEP ; estado = 1
			st_manual_block.steps[X_AXIS]--;

			if(st_manual_block.direction_bits[X_AXIS] == CW)
				sys.position[X_AXIS]++;
			if(st_manual_block.direction_bits[X_AXIS] == CCW)
				sys.position[X_AXIS]--;
		}
		if( T0IR & ( 1 << IRMR1 ))	///< Si interrumpio Match 1
		{
			T0IR = ( 1 << IRMR1 ); 	///< Borro flag del Match 1
			SetPIN( XSTEP , 1 ) ;			///< XSTEP ; estado = 0
		}
		if(!st_manual_block.steps[X_AXIS])
		{
			T0IR = ( 1 << IRMR0 );		///< Desabilita la interrupcion del MRn
			T0IR = ( 1 << IRMR1 );
		}
	//}
}

void TIMER1_IRQHandler(void){
	//if (sys.state == S_MANUAL){
		if( (T1IR & ( 1 << IRMR0 )) && st_manual_block.steps[Y_AXIS] > 0 )
		{
			T1IR = ( 1 << IRMR0 );
			SetPIN(YSTEP , 0 ) ;
			st_manual_block.steps[Y_AXIS]--;

			if(st_manual_block.direction_bits[Y_AXIS] == CW)
				sys.position[Y_AXIS]++;
			if(st_manual_block.direction_bits[Y_AXIS] == CCW)
				sys.position[Y_AXIS]--;
		}
		if( T1IR & ( 1 << IRMR1 ))
		{
			T1IR = ( 1 << IRMR1 );
			SetPIN( YSTEP , 1 ) ;
		}
		if(!st_manual_block.steps[Y_AXIS])
		{
			T1IR = ( 1 << IRMR0 );
			T1IR = ( 1 << IRMR1 );
		}
	//}
}

void TIMER2_IRQHandler(void){
	//if (sys.state == S_MANUAL){
		if( (T2IR & ( 1 << IRMR0 )) &&  st_manual_block.steps[Z_AXIS] > 0 )
		{
			T2IR = ( 1 << IRMR0 );
			SetPIN(ZSTEP , 0 ) ;
			st_manual_block.steps[Z_AXIS]--;

			if(st_manual_block.direction_bits[Z_AXIS] == CW)
				sys.position[Z_AXIS]++;
			if(st_manual_block.direction_bits[Z_AXIS] == CCW)
				sys.position[Z_AXIS]--;
		}
		if( T2IR & ( 1 << IRMR1 ))
		{
			T2IR = ( 1 << IRMR1 );
			SetPIN( ZSTEP , 1 ) ;
		}
		if(!st_manual_block.steps[Z_AXIS])
		{
			T2IR = ( 1 << IRMR0 );
			T2IR = ( 1 << IRMR1 );
		}
	//}
}






