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

 
 
 
 
 void Drive_steer_extreme ( uint8_t rl );
 void Drive_steer_cnt ( void );
 void Drive_angle_per ( uint8_t per );
 
 
 #endif