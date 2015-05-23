/*
 *	Drive.c
 *
 *
 */
 
 #include "Drive.h"
 
 
 typedef struct {
 
   uint16_t min;
   uint16_t max;
   uint16_t cnt;
   uint16_t act;
 
 }Steer_t; 
 
 typedef struct {
 
   uint16_t min;
   uint16_t max;
   uint16_t act;
 
 }Motor_t; 
 
 // Steering and motor structures ( in 1/E5 ):
 
 static Steer_t Steer = { 500, 800, 650, 0 };
 static Motor_t Motor = { MOTOR_MIN_E5, MOTOR_MAX_E5, 0 };
 
 // Min/max angle:
 //****************************************************************
 
 void Drive_steer_extreme ( uint8_t rl ){

   if ( rl ){   
      PWM_set_E5 ( STEER_CH, Steer.max );   
   }
   else{
      PWM_set_E5 ( STEER_CH, Steer.min );   
   } 
 }

 //****************************************************************
 // Center angle:
 void Drive_steer_cnt ( void ){
 
   PWM_set_E5( STEER_CH, Steer.cnt ); 
 }
 
 //****************************************************************
 // Percent of max angle scope ( 50% -> center):
 void Drive_angle_per ( uint8_t per ){
 
   uint8_t temp = 0;
    
   if ( per < 50 ){      
      temp = (( Steer.cnt - Steer.min )*per ) / 100; 
   }
   else{
      temp = (( Steer.max - Steer.cnt )*per ) / 100;
   }
 
   PWM_set_pro ( STEER_CH, temp ); 
 }
 
 
 //****************************************************************
 // Stops motor (or initialization): 
 void Drive_motor_stop ( void ){
 
   PWM_set_pro ( MOTOR_CH, Motor.min ); 
 }
 
 
 //****************************************************************
 // Sets motor speed in percent: 
 void Drive_motor_per ( uint8_t per ){

   uint16_t E5 = 0;
   
   if ( per > 100 ){
      per = 100;
   }
   else if ( per > MOTOR_SPEED_MAX ){
      per = MOTOR_SPEED_MAX; 
   }      
   
   E5 = (((Motor.max - Motor.min) * per) / 100) + Motor.min; 
 
   PWM_set_E5 ( MOTOR_CH, E5 );

 }
 
 //****************************************************************
 // Sets motor speed - maximum speed in % defined in Drive.h: 
 void Drive_motor_slow ( void ){
 
   Drive_motor_per ( MOTOR_SPEED_MIN );
 }
 
 
 
 