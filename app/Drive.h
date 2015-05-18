/*
 *	Drive.h
 *
 *
 */
 
 
 #ifndef _DRIVE_H_
 #define _DRIVE_H
 
 
 #include "MKL46Z4.h"
 #include "PWM.h"
 
// Structures: 
 typedef struct{
 
   uint16_t min_p;
   uint16_t max_p;
   uint16_t cnt_p;
   uint16_t act_p;
 
 }Steer_s; 
 
 

 
 
 
 void Drive_steer_extreme ( bool rl );
 void Drive_steer_cnt ( void );
 void Drive_angle_per ( uint8_t per );
 
 
 #endif