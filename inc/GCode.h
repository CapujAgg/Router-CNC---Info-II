/*
 * GCode.h
 *
 *  Created on: 23/10/2015
 *      Author: Julieta
 */

#ifndef INC_GCODE_H_
#define INC_GCODE_H_

//******** Gcode***********************************************************
#define LINE_BUFFER_SIZE		80
#define SERIAL_NO_DATA			0xff
#define FAIL(status)		 return (status);

//********COMANDOS NO MODALES********************************
// Modal Group G0: Non-modal actions
#define NON_MODAL_NO_ACTION 0 // (Default: Must be zero)
#define NON_MODAL_DWELL 1 // G4
#define NON_MODAL_SET_COORDINATE_DATA 2 // G10
#define NON_MODAL_GO_HOME 3 // G28
#define NON_MODAL_ABSOLUTE_OVERRIDE 4 // G53
#define NON_MODAL_SET_COORDINATE_OFFSET 5 // G92
#define NON_MODAL_RESET_COORDINATE_OFFSET 6//G92.1

//********COMANDOS MODALES********************************
// Motion Group 1
#define MOTION_MODE_SEEK 0 // G0 (Default: Must be zero)
#define MOTION_MODE_LINEAR 1 // G1
#define MOTION_MODE_CW_ARC 2  // G2
#define MOTION_MODE_CCW_ARC 3  // G3
#define MOTION_MODE_NONE 4 // G80

// Plane select
#define PLANE_SELECT_XY 0 // G17 (Default: Must be zero)
#define PLANE_SELECT_ZX 1 // G18
#define PLANE_SELECT_YZ 2 // G19

// Distance mode
#define DISTANCE_MODE_ABSOLUTE 0 // G90 (Default: Must be zero)
#define DISTANCE_MODE_INCREMENTAL 1 // G91

//Arc IJK distance mode (???????????????????????)
#define DISTANCE_ARC_MODE_INCREMENTAL 0 // G91.1 (Default: Must be zero)

// Program flow
#define PROGRAM_FLOW_RUNNING 0 // (Default: Must be zero)
#define PROGRAM_FLOW_PAUSED 1 // M0, M1
#define PROGRAM_FLOW_COMPLETED 2 // M2, M30

// Feed rate mode
#define FEED_RATE_MODE_UNITS_PER_MIN 0 // G94 (Default: Must be zero)
#define FEED_RATE_MODE_INVERSE_TIME 1 // G93

// Units mode
#define UNITS_MODE_MM 0 // G21 (Default: Must be zero)
#define UNITS_MODE_INCHES 1 // G20

// Modal Group G7: Cutter radius compensation mode
#define CUTTER_COMP_DISABLE 0 // G40 (Default: Must be zero)

// Modal Group M7: Spindle control
#define SPINDLE_DISABLE 0 // M5 (Default: Must be zero)
#define SPINDLE_ENABLE 1// M3 // M4

//********************todo modificar**************************
#define MAX_CHAR 180
#define MAX_INT_DIGITS  3
#define NEGATIVO 0
#define POSITIVO 1


typedef struct {
  uint8_t motion;          // {G0,G1,G2,G3,G38.2,G80}
  uint8_t feed_rate;       // {G93,G94}
  uint8_t units;           // {G20,G21}
  uint8_t distance;        // {G90,G91}
  uint8_t plane_select;    // {G17,G18,G19}
  uint8_t program_flow;    // {M0,M1,M2,M30}
  uint8_t spindle;         // {M3,M4,M5}
} gcode_modal_t;

typedef struct {
  float f;         // Feed
  float ijk[3];    // I,J,K Axis arc offsets
  uint32_t n;       // Line number
  float p;         // G10 or dwell parameters
  float r;         // Arc radius
  float s;		   // Spindle Speed
  float xyz[3];    // X,Y,Z Translational axes
} gcode_values_t;

typedef struct {
  gcode_modal_t modal;

  float spindle_speed;          // RPM
  float feed_rate;              // Millimeters/min
  uint32_t line_number;          // Last line number sent
  float position[3];       // Where the interpreter considers the tool to be at this point in the code
} parser_state_t;

typedef struct {
  uint8_t non_modal_command;
  gcode_modal_t modal;
  gcode_values_t values;

} parser_block_t;

uint8_t tokenizer (char*);
void read_float (char* , float*, char*);
uint8_t gcode_parser (char*);
void gc_init(void);


#endif /* INC_GCODE_H_ */
