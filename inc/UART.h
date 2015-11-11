/*
 * UART.h
 *
 *  Created on: 17/9/2015
 *      Author: Fernando
 */

#ifndef INC_UART_H_
#define INC_UART_H_


#define TAM_BUF_RX	20
#define TAM_BUF_TX	40
#define FLAG_TX     U1LSR & 0x20
#define REG_SAL_TX  U1THR

void InitUART1 ( void );

/**
 * Funciones UART
 */
void sendSerialString ( char *);
void push_RX(unsigned char);
int pop_TX(void);
int serialRead(void);
void push_TX(unsigned char);

#endif /* INC_UART_H_ */
