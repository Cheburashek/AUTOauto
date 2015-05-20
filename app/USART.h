/*
 *	USART.h
 *
 *
 */


#ifndef _USART_H_
#define _USART_H_

#include "Common.h"
#include "ring_buffer.h"
#include "PWM.h"

//************************************************************************
#define RX_PIN 17 // PTE17
#define TX_PIN 16 // PTE16

#define RX_MASK (1UL << RX_PIN)
#define TX_MASK (1UL << TX_PIN)

#define CMD_PREFIX 0xEE


//************************************************************************
// MACROS:

#define UART2_TIE_ON() (UART2->C2 |= UART_C2_TIE_MASK)
#define UART2_TIE_OFF() (UART2->C2 &= ~UART_C2_TIE_MASK)



//************************************************************************
// Functions defs:

void UART_parser_cb ( cmd_cb_t );
void UART_parser ( void );
void UART_init( void );
void UART_data_send ( const uint8_t* data, uint8_t len );




#endif
