/*
 * Stepper.h
 *
 *  Created on: 8/11/2015
 *      Author: Julieta
 */

#ifndef INC_STEPPER_H_
#define INC_STEPPER_H_


typedef struct {
  uint8_t direction_bits[N_AXIS];
  uint32_t steps[N_AXIS];
  uint32_t step_event_count;
} st_block_t;


//***************************************************************
//Initialize and setup the stepper motor subsystem
void stepper_init(void);
// Immediately disables steppers
void stepper_stop(void);

uint8_t st_move_line ( uint8_t, uint8_t, uint32_t, uint16_t);
void st_setdir(uint8_t,uint8_t);




//***************************************************************



// Enable steppers, but cycle does not start unless called by motion control or realtime command.
void st_wake_up();



// Generate the step and direction port invert masks.
void st_generate_step_dir_invert_masks();

// Reset the stepper subsystem variables
void st_reset();

// Reloads step segment buffer. Called continuously by realtime execution system.
void st_prep_buffer();

// Called by planner_recalculate() when the executing block is updated by the new plan.
void st_update_plan_block_parameters();


#endif /* INC_STEPPER_H_ */
