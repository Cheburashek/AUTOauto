/*
 *	USART.c
 *
 *
 */

#include "USART.h"


static RingBuffer UART_RingBuffer_Tx;  // UART transmit buffer descriptor
static RingBuffer UART_RingBuffer_Rx;  // UART receive buffer descriptor

static cmd_frame_t cmd_frame;
static cmd_cb_t cb_pars;   //  For function called after succesfull parsing


 
//************************************************************************
// Data parser:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 

// TODO : Multi-frame parsing does not work

// !!!!!!!!! Addditional byte needed to parse-> when rb is empty parsing is not complete


void UART_parser ( void){

   bool is_data = true;
   uint8_t cnt = 0;
   uint8_t temp = 0;
   uint8_t len = RingBuffer_GetLen ( &UART_RingBuffer_Rx );
   

   while ( is_data ){
   
      is_data =  RingBuffer_GetChar( &UART_RingBuffer_Rx, &temp );
   
      if ( cnt >= 3 ){ 
      
         if ( cnt != (cmd_frame.Len + 3) ){
      
            cmd_frame.Param[cnt - 3] = temp;
            cnt++;
         }
         // End of frame parsing:
         else{         
            
            cnt = 0;
            // Echo for testing:    
            cb_pars( &cmd_frame );            
            UART_data_send ( (uint8_t*)&cmd_frame, cmd_frame.Len + 2 );              
         }
      }   
      else{
         switch ( cnt ){
         
            case 0:
               if ( CMD_PREFIX == temp){                
                  cnt++;
               } 
               else{
                  cnt = 0;
               }
               break;
               
            case 1:
               cmd_frame.OpCode = temp;
               cnt++;
               break;
            
            case 2:
               cmd_frame.Len = temp;
               cnt++;
               break;
               
         }
      }
      
      len--;
   }
}


//************************************************************************
// Callback for end of parsing:

void UART_parser_cb ( cmd_cb_t cb ){

   cb_pars = cb;
}


//************************************************************************
// Data sending:
void UART_data_send ( const uint8_t* data, uint8_t len ){

   while ( len ){

      RingBuffer_PutChar ( &UART_RingBuffer_Tx, *data );
      len--;
      data++;
   }
   
   // Enabling TIE:
  
   UART2_TIE_ON();
}




//************************************************************************
// UART2 HANDLER:    DMA!
void UART2_IRQHandler(void){

   uint8_t temp = 0;
   
   //Transmitting ( until Tx ring buffer is empty ):
   if ( UART2->S1 & UART_S1_TDRE_MASK ){
      
      if ( true == RingBuffer_GetChar( &UART_RingBuffer_Tx, &temp ) ){
      
         UART2->D = temp;
      }
      else{
      
         UART2_TIE_OFF();
      }   
   }
   
   // Receiving:   
   if ( UART2->S1 & UART_S1_RDRF_MASK ){
      
      RingBuffer_PutChar( &UART_RingBuffer_Rx, UART2->D );
      (void)UART2->D;
      TPM1_OneShot ( UART_parser, 3 );   

      
   }  
}



//************************************************************************
// USART2 initialization:
void UART_init(void){
			

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
	NVIC_SetPriority(UART2_IRQn, 2);
	
	UART2->C2 |= UART_C2_RIE_MASK;			 // Receiver Interrupt Enable for RDRF

	// ~INT

	UART2->C2 |= UART_C2_RE_MASK 				 // RE, TE enabled
		    |  UART_C2_TE_MASK;
	
   // Ring Buffers initialization with length defined in ring_buffer.h
   RingBuffer_Init( &UART_RingBuffer_Tx );
   RingBuffer_Init( &UART_RingBuffer_Rx );   
} 




