/*
 *	Drive.c
 *
 *
 */
 
 #include "Drive.h"
 
 // Steering:
 Steer_s Steer = {1,  2,  3, 4};
 
 
 // Min/max angle:
 //****************************************************************
 
 void Drive_steer_extreme ( bool rl ){

   if ( rl ){   
      PWM_set_pro ( STEER_CH, Steer.max_p );   
   }
   else{
      PWM_set_pro ( STEER_CH, Steer.min_p );   
   } 
 }

 //****************************************************************
 // Center angle:
 void Drive_steer_cnt ( void ){
 
   PWM_set_pro ( STEER_CH, Steer.cnt_p ); 
 }
 
 //****************************************************************
 // Percent of max angle scope ( 50% -> center):
 void Drive_angle_per ( uint8_t per ){
 
   uint8_t temp = 0;
    
   if ( per < 50 ){      
      temp = (( Steer.cnt_p - Steer.min_p )*per ) / 100; 
   }
   else{
      temp = (( Steer.max_p - Steer.cnt_p )*per ) / 100;
   }
 
   PWM_set_pro ( STEER_CH, temp ); 
 }