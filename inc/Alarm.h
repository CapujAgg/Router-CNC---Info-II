/*
 * Alarm.h
 *
 *  Created on: 8/11/2015
 *      Author: Julieta
 */

#ifndef INC_ALARM_H_
#define INC_ALARM_H_

void report_alarm (void);
uint8_t soft_check_limit ( uint8_t axis, uint8_t dir, uint32_t steps);
uint8_t get_dir (uint8_t t);

#define		NO_ALARM					0
#define		SOFT_LIMIT_ERROR			1
#define		CONNECTION_ESTABLISHED		2
#define		NO_PC_CONNECTION			3


#endif /* INC_ALARM_H_ */
