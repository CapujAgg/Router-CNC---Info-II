/*
 * Settings.h
 *
 *  Created on: 29/10/2015
 *      Author: Julieta
 */

#ifndef INC_SETTINGS_H_
#define INC_SETTINGS_H_

typedef struct {
  // Axis settings
  float steps_per_mm[N_AXIS];
  float max_feed_rate[N_AXIS];
  float max_travel_steps[N_AXIS];
  uint8_t work_plane;
  uint8_t units;
  float def_feed_rate[N_AXIS];
  float manual_steps[N_AXIS];

} settings_t;
extern settings_t settings;

void settings_restore_global_settings();


// Grbl generic default settings. Should work across different machines.
#define DEFAULT_X_STEPS_PER_MM 	PASOSXY_MM
#define DEFAULT_Y_STEPS_PER_MM 	PASOSXY_MM
#define DEFAULT_Z_STEPS_PER_MM 	PASOSZ_MM
#define DEFAULT_X_MAX_RATE 500.0 // mm/min
#define DEFAULT_Y_MAX_RATE 500.0 // mm/min
#define DEFAULT_Z_MAX_RATE 500.0 // mm/min
#define DEFAULT_X_MAX_TRAVEL 100 * PASOSXY_MM	// pasos !!!NO DEFINITIVO
#define DEFAULT_Y_MAX_TRAVEL 100 * PASOSXY_MM 	// pasos !!!NO DEFINITIVO
#define DEFAULT_Z_MAX_TRAVEL 100 * PASOSZ_MM	// pasos !!!NO DEFINITIVO
#define DEFAULT_PLANE PLANE_SELECT_XY
#define DEFAULT_UNITS UNITS_MODE_MM
#define	DEFAULT_FEEDRATE_XY		2*DIEZ_MM_SEG
#define	DEFAULT_FEEDRATE_Z		VEINTE_MM_SEG
#define DEFAULT_MANUAL_STEPS_XY	10*PASOSXY_MM
#define DEFAULT_MANUAL_STEPS_Z	10*PASOSZ_MM

#endif /* INC_SETTINGS_H_ */
