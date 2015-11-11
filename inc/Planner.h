/*
 * Planner.h
 *
 *  Created on: 25/10/2015
 *      Author: Julieta
 */

#ifndef INC_PLANNER_H_
#define INC_PLANNER_H_


typedef struct {
  uint8_t direction_bits[N_AXIS];
  uint32_t steps[N_AXIS];    			// Step count along each axis
  uint32_t step_event_count; 			// The maximum step axis count and number of steps required to complete this block.
} plan_block_t;

#define		PL_BUFF_TAM		80

uint8_t plan_move_manual(void);
uint8_t goHome(void);

void plan_reset(void);
void plan_buffer_line(float *target, float feed_rate, uint8_t invert_feed_rate) ;
void init_planblock (void);

#endif /* INC_PLANNER_H_ */
