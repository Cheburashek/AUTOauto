/*
 *	Select.c
 *
 *
 */
 
 #include "Select.h"
 
 uint8_t resp = 0xF0;
 
 void Select_main ( cmd_frame_t* cmd ){
 
   switch( cmd->OpCode ){
   
      case STEER_RL:      
         Drive_steer_extreme ( cmd->Param[0] );         
         break;
         
      case STEER_PER:
         //TODO
         break;
      
      case MOTOR_STOP:
         Drive_motor_stop();
         break;
         
      case MOTOR_SLOW:
         Drive_motor_slow();
         break;
         
      case MOTOR_PER:
         Drive_motor_per ( cmd->Param[0] );
         break;
   
   }
 
 
 }