#include "Aplicacion.h"



void settings_restore_global_settings() {

	  settings.steps_per_mm[X_AXIS] = DEFAULT_X_STEPS_PER_MM;
	  settings.steps_per_mm[Y_AXIS] = DEFAULT_Y_STEPS_PER_MM;
	  settings.steps_per_mm[Z_AXIS] = DEFAULT_Z_STEPS_PER_MM;
	  settings.max_feed_rate[X_AXIS] = DEFAULT_X_MAX_RATE;
	  settings.max_feed_rate[Y_AXIS] = DEFAULT_Y_MAX_RATE;
	  settings.max_feed_rate[Z_AXIS] = DEFAULT_Z_MAX_RATE;
	  settings.max_travel_steps[X_AXIS] = DEFAULT_X_MAX_TRAVEL;
	  settings.max_travel_steps[Y_AXIS] = DEFAULT_Y_MAX_TRAVEL;
	  settings.max_travel_steps[Z_AXIS] = DEFAULT_Z_MAX_TRAVEL;
	  settings.work_plane = DEFAULT_PLANE;
	  settings.units = DEFAULT_UNITS;
	  settings.def_feed_rate[X_AXIS]= DEFAULT_FEEDRATE_XY; // mm/seg
	  settings.def_feed_rate[Y_AXIS]= DEFAULT_FEEDRATE_XY;
	  settings.def_feed_rate[Z_AXIS]= DEFAULT_FEEDRATE_Z;
	  settings.manual_steps[X_AXIS] = DEFAULT_MANUAL_STEPS_XY; // mm
	  settings.manual_steps[Y_AXIS] = DEFAULT_MANUAL_STEPS_XY;
	  settings.manual_steps[Z_AXIS] = DEFAULT_MANUAL_STEPS_Z;
}
