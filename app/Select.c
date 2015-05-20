/*
 *	Select.c
 *
 *
 */
 
 #include "Select.h"
 
 uint8_t resp = 0xF0;
 
 void Select_main ( cmd_frame_t* cmd ){
 
   switch( cmd->OpCode ){
   
      case 0x10:
         Drive_steer_extreme ( cmd->Param[0] );
         //UART_data_send ( &resp, 1 );
         break;
   
   
   }
 
 
 }