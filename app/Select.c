/*
 *	Select.c
 *
 *
 */

 #include "Select.h"

 
  
 extern bool  motorRewFlag;
 extern bool  motorPermFlag;
 
 uint8_t resp = 0xF0;
 
 void Select_main ( cmd_frame_t* cmd ){
 
   switch( cmd->OpCode ){
   
      case STEER_RL:      
         Drive_steer_LCR ( cmd->Param[0] );         
         break;
         
      case STEER_PER:
         Drive_steer_per ( cmd->Param[0] );
         break;
      
      case MOTOR_STOP:
         Drive_motor_init();
         break; 
			         
      case MOTOR_SLOW:
				if ( motorPermFlag && !motorRewFlag )
				{
         Drive_motor_slow();
				}
         break;
         
      case MOTOR_PER:
				if (  motorPermFlag && !motorRewFlag )
				{
         Drive_motor_per ( cmd->Param[0] );
				}
         break;
      
      case MOTOR_DIR:
         Drive_dir_set ( cmd->Param[0] );
         break;
         
      case HORN_BEEP:
       Drive_horn_beep ( cmd->Param[0] );
			 //Drive_horn_signal ( );

         break;
   
      case PING:
         ;// TODO: special ping response
         break;
         
      default:
         ;
         break;
   }
 
 
 }