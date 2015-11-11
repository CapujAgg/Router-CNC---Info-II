/**
 * @author Catedra Info II
 */
#ifndef APLICACION_H_
#define APLICACION_H_

#include <string.h>
#include <stdio.h>
#include <math.h>

#include "GPIO.h"
#include "infotronic.h"
#include "LPC1769.h"
#include "Oscilador.h"
#include "TecladoPlacaBase.h"
#include "UART.h"
#include "system.h"
#include "Stepper.h"
#include "Planner.h"
#include "Settings.h"
#include "GCode.h"
#include "Alarm.h"


// VOLAR DE ACA
void debugPrint(char* s);

#endif /* APLICACION_H_ */
