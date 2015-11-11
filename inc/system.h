/*
  system.h - Header for system level commands and real-time processes
  Part of Grbl

  Copyright (c) 2014-2015 Sungeun K. Jeon  

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef system_h
#define system_h

/***********************************************************************************************/
/**
 * Eje XY
 * pasos_por_mm = (pasos_por_vuelta_del_motor * micropasos_del_driver_del_motor ) / (paso_entre_dientes_de_la_polea * numero_dientes_polea)
 * pasos_por_mm = (200 * 32) / (16 * 2)
 *
 * Eje Z
 * Varilla 5/16 18 hilos
 * pasos_por_mm = (pasos_por_vuelta_del_motor * micropasos_del_driver_del_motor) / paso_varilla
 * (200 * 32) / (25,4/18)
 */
///< Aqui van las macros, prototipos , etc. de la aplicacion

#define		RIGHT			1
#define		LEFT			0
#define		E_ON			1
#define		E_OFF			0

#define		CW				0
#define		CCW				1
#define		X_AXIS			0
#define		Y_AXIS			1
#define		Z_AXIS			2

#define		UN_MM_SEG			1
#define		DOS_MM_SEG			2
#define		CINCO_MM_SEG		5
#define		DIEZ_MM_SEG			10
#define		VEINTE_MM_SEG		20
#define		CINCUENTA_MM_SEG	50
#define		CIEN_MM_SEG			100 //Velocidad maxima ?



#define 	MM_SEG			125000
#define 	PASOSXY_MM		(200 * 32) / (16 * 2)
#define		PASOSZ_MM		(int)(200 * 32) / (25.4/18)


#define		PC_CONNECTION				"gil el que lee"

//Macros teclas
#define		 key_XR			K0
#define		 key_XL			K1
#define		 key_YR			K2
#define		 key_YL			K3
#define		 key_ZU			K4
#define		 key_ZD			K5
#define		 key_MENU		K6
#define		 key_HOME		K7

//Declaracion de estados
#define 	TRUE  		1
#define 	FALSE  		0
#define 	S_INI		0
#define 	S_ALARM		1
#define 	S_IDLE		2
#define 	S_MANUAL	3
#define 	S_AUTO		4
#define 	S_SETTINGS	5
#define 	S_HOMING	6

#define START_HOMING	1
#define START_AUTO		2
#define SET_SETTINGS	3
#define START_MANUAL	4
#define DONE			6
#define UNDONE			0


// Define global system variables
typedef struct {
  uint8_t abort;                 // System abort flag. Forces exit back to main loop for reset.
  uint8_t state;                 // Tracks the current state of Grbl.
  uint8_t suspend;               // System suspend flag. Allows only realtime commands. Used primarily for holds.

  volatile uint8_t rt_exec_state;  // Global realtime executor bitflag variable for state management. See EXEC bitmasks.
  volatile uint8_t alarm;  // Global realtime executor bitflag variable for setting various alarms.

  volatile uint32_t position[N_AXIS];      // Posicion de la maquina en tiempo real, en pasos
  volatile uint32_t new_Home_Ref[N_AXIS];  // nuevo Home si fue seteado
  volatile int planner_position[N_AXIS];

  uint8_t firstHome;       // Locks axes when limits engage. Used as an axis motion mask in the stepper ISR.
  uint8_t manual_key;
  uint8_t sAuto;
  uint8_t endstop_rached;  // Flag final de carrera alcanzado

} system_t;
extern system_t sys;




void state_machine(void);
//Prototipos de funciones para la maquina
void funcion_S_INI (void);
void funcion_S_ALARM (void);
void funcion_S_IDLE (void);
void funcion_S_MANUAL (void);
void funcion_S_AUTO (void);
void funcion_S_SETTINGS (void);
void funcion_S_HOMING (void);

//Prototipos de los eventos
int Inicializar_Sys(void);
int serialEvent(void);
int keyEvent(void);
int alarmEvent(void);
int	setSettings(void);

//Prototipos de las acciones

void init_system_var (void);

 /*********************************************************************************************





// Define system executor bit map. Used internally by realtime protocol as realtime command flags, 
// which notifies the main program to execute the specified realtime command asynchronously.
// NOTE: The system executor uses an unsigned 8-bit volatile variable (8 flag limit.) The default
// flags are always false, so the realtime protocol only needs to check for a non-zero value to 
// know when there is a realtime command to execute.
#define EXEC_STATUS_REPORT  bit(0) // bitmask 00000001
#define EXEC_CYCLE_START    bit(1) // bitmask 00000010
#define EXEC_CYCLE_STOP     bit(2) // bitmask 00000100
#define EXEC_FEED_HOLD      bit(3) // bitmask 00001000
#define EXEC_RESET          bit(4) // bitmask 00010000

// Alarm executor bit map.
// NOTE: EXEC_CRITICAL_EVENT is an optional flag that must be set with an alarm flag. When enabled,
// this halts Grbl into an infinite loop until the user aknowledges the problem and issues a soft-
// reset command. For example, a hard limit event needs this type of halt and aknowledgement.
#define EXEC_CRITICAL_EVENT     bit(0) // bitmask 00000001 (SPECIAL FLAG. See NOTE:)
#define EXEC_ALARM_HARD_LIMIT   bit(1) // bitmask 00000010
#define EXEC_ALARM_SOFT_LIMIT   bit(2) // bitmask 00000100
#define EXEC_ALARM_ABORT_CYCLE  bit(3) // bitmask 00001000
#define EXEC_ALARM_HOMING_FAIL  bit(4) // bitmask 00010000


// Define system suspend states.
#define SUSPEND_DISABLE       0      // Must be zero.
#define SUSPEND_ENABLE_HOLD   bit(0) // Enabled. Indicates the cycle is active and currently undergoing a hold.
#define SUSPEND_ENABLE_READY  bit(1) // Ready to resume with a cycle start command.
#define SUSPEND_ENERGIZE      bit(2) // Re-energizes output before resume.
#define SUSPEND_MOTION_CANCEL bit(3) // Cancels resume motion. Used by probing routine.





// Initialize the serial protocol
void system_init();


// Executes an internal system command, defined as a string starting with a '$'
uint8_t system_execute_line(char *line);


// Returns machine position of axis 'idx'. Must be sent a 'step' array.
float system_convert_axis_steps_to_mpos(uint32_t *steps, uint8_t idx);

// Updates a machine 'position' array based on the 'step' array sent.
void system_convert_array_steps_to_mpos(float *position, uint32_t *steps);

*/

#endif
