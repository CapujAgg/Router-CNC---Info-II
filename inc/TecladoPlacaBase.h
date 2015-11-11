/**
 * @author Catedra Info II
 */
#ifndef TECLADOPLACBASE_H_
#define TECLADOPLACBASE_H_

#define		REBOTES			3					//!< Cantidad de lecturas estables del cambio de estadpara darlo por bueno
#define		NO_KEY			( (uint8_t) 0xff )	//!< Codigo de tecla para indicar buffer vacio

//!< PROTOTIPOS -----------------------------------------------------------------------------------------------------------
//!< Drivers
void InicializarTeclado( void );
void DriverTecladoSW ( void );
unsigned char DriverTecladoHW( void );

/* ----- se comunican a traves del buffer key ----- */

//!< Primitivas
uint8_t Teclado( void );

#endif /* TECLADOPLACBASE_H_ */
