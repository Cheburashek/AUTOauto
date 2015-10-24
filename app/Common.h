/*
 *	Common.h
 *
 *
 */
 
 
 #ifndef _COMMON_H_
 #define _COMMON_H_
 
 #include "MKL46Z4.h"
 #include <stdbool.h>
 
 #include "core_cm0plus.h"
 #define UART_BUFF_SIZE 16

 
typedef struct cmd_frame {

   uint8_t OpCode;
   uint8_t Len;
   uint8_t Param[UART_BUFF_SIZE-3];
   
}cmd_frame_t;



typedef void(*cmd_cb_t)( cmd_frame_t* );     // Pointer for setting callback -> UART-Select
 
 
 #endif