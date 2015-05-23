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
 
 #define MOTOR_MIN_E5 30   // Range for typical SERVO in 1/E5
 #define MOTOR_MAX_E5 1150
 
 #define MOTOR_SPEED_MAX 50   // Absolutely maximum speed %
 #define MOTOR_SPEED_MIN 3    // For SLOW function
 
 void Drive_steer_extreme ( uint8_t rl );
 void Drive_steer_cnt ( void );
 void Drive_angle_per ( uint8_t per );
 void Drive_motor_stop ( void );
 void Drive_motor_per ( uint8_t per );
 void Drive_motor_slow ( void );
 
 
 
 #endif