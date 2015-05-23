/*
 *	Select.h
 *
 *
 */
 
 #ifndef _SELECT_H_
 #define _SELECT_H_
 
 #include "Common.h"
 #include "Drive.h"
 #include "USART.h"
 
 
 typedef enum en {
 
   STEER_RL = 0x01,
   STEER_PER,
   MOTOR_STOP,
   MOTOR_SLOW,
   MOTOR_PER
 
 }eOpCode_t;
 
 void Select_main ( cmd_frame_t* cmd ); 
 
 #endif