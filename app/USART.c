/*
 *	USART.c
 *
 *
 */

#include "USART.h"
#include "sLCD.h"



// UART transmit buffer descriptor
static RingBuffer UART_RingBuffer_Tx;
// UART transmit buffer memory pool
//static char RingBufferData_Tx[100];

// UART receive buffer descriptor
static RingBuffer UART_RingBuffer_Rx;
// UART receive buffer memory pool
//static char RingBufferData_Rx[100];


//************************************************************************
// Data sending:


void UART2_data_send ( const char* data, uint8_t len ){

   while ( len ){

      RingBuffer_PutChar ( &UART_RingBuffer_Tx, *data );
      len--;
      data++;
   }
   
   // Enabling TIE:
   UART2_TIE_ON();
}




//************************************************************************
// UART2 HANDLER:
void UART2_IRQHandler(void){

   char temp = 0;
   
   //Transmitting ( until Tx ring buffer is empty ):
   if ( UART2->S1 & UART_S1_TDRE_MASK ){
      
      if ( RingBuffer_GetChar( &UART_RingBuffer_Tx, &temp ) ){
      
         UART2->D = temp;
      }
      else{
      
         UART2_TIE_OFF();
      }   
   }
   
   // Receiving:
   
   if ( UART2->S1 & UART_S1_RDRF_MASK ){
   
      RingBuffer_PutChar( &UART_RingBuffer_Rx, UART2->D );
      
      
      
   }
   
   
   
}



//************************************************************************
// USART2 initialization:
void UART2_init(void){
			

	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
   SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

		
	PORTE->PCR[RX_PIN] = PORT_PCR_MUX(3u);		// PTE17 as UART2RX
	PORTE->PCR[TX_PIN] = PORT_PCR_MUX(3u);		// PTE16 as UART2TX

					
	UART2->C2 &= ~UART_C2_RE_MASK; 			
	UART2->C2 &= ~UART_C2_TE_MASK;			// RE, TE disabled
	
	UART2->C1 &= ~UART_C1_M_MASK; 			// Normal - start + 8 data bits (lsb first) + stop.   
	UART2->C1 &= ~UART_C1_PE_MASK;			// No hardware parity generation or checking.
	
	UART2->BDH &= ~UART_BDH_SBNS_MASK; 			// One stop bit	
 
	UART2->BDH |= UART_BDH_SBR(0);		   	// 5 older bits (clock divider)		for BR = 9600 - > SBR = 156			
	UART2->BDL = UART_BDL_SBR(156);			// 8 younger bits (clock divider)																	

	// INT 
	
	NVIC_ClearPendingIRQ(UART2_IRQn);
	NVIC_EnableIRQ(UART2_IRQn);
	NVIC_SetPriority(UART2_IRQn, 3);
	
	UART2->C2 |= UART_C2_RIE_MASK;			 // Receiver Interrupt Enable for RDRF

	// ~INT

	UART2->C2 |= UART_C2_RE_MASK 				 // RE, TE enabled
		    |  UART_C2_TE_MASK;
	
   // Ring Buffers initialization with length defined in ring_buffer.h
   RingBuffer_Init( &UART_RingBuffer_Tx );
   RingBuffer_Init( &UART_RingBuffer_Rx );
 
   
} 




