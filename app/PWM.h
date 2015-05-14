/*
 *	PWM.h
 *
 *
 */
 
 #ifndef _PWM_H_
 #define _PWM_H_
 
 #include "MKL46Z4.h"
 #include <stdbool.h>
 
 #define STEER_PIN 1  // PTC1
 #define MOTOR_PIN 2  // PTC2
 
 #define STEER_CH 0   // Channel 0, TPM0
 #define MOTOR_CH 1   // Channel 1, TPM0
 
 #define STEER_MASK  ( 1UL<<STEER_PIN )
 #define MOTOR_MASK  ( 1UL<<MOTOR_PIN )
 
 
 void PWM_init ( void );
 
 
 #endif