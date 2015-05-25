/*
 *	Drive.h
 *
 *
 */
 
 
 #ifndef _DRIVE_H_
 #define _DRIVE_H
 
 
 #include "MKL46Z4.h"
 #include "PWM.h"
 
 #define SERVO_MIN_E5 250   // Range for typical SERVO in 1/E5
 #define SERVO_MAX_E5 1150
 
 #define STEER_MIN_E5 500   
 #define STEER_CNT_E5 680
 #define STEER_MAX_E5 840
 
 #define MOTOR_INIT_E5 560  // For initialization
 #define MOTOR_MIN_E5 600   
 #define MOTOR_MAX_E5 800
 
 #define MOTOR_SPEED_MAX 50   // Absolutely maximum speed %
 #define MOTOR_SPEED_SLOW 3    // For SLOW function
 
 void Drive_steer_LCR ( uint8_t lcr );
 void Drive_steer_cnt ( void );
 void Drive_steer_per ( uint8_t per );
 void Drive_motor_init ( void );
 void Drive_motor_per ( uint8_t per );
 void Drive_motor_slow ( void );
 
 
 
 #endif