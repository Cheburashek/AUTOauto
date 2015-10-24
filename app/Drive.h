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
 #define MOTOR_SPEED_SLOW 5   // For SLOW function
 
 #define DIRECT_FOR_E5 750
 #define DIRECT_REV_E5 650
 
 #define HEAD_MIN_E5 280   
 #define HEAD_CNT_E5 ((HEAD_MIN_E5+HEAD_MAX_E5)/2)
 #define HEAD_MAX_E5 1300
 
 
 #define HORN_PIN 0    // PTB0
 #define HORN_MASK ( 1UL<<HORN_PIN )
 #define HORN_PIT_CH 0
 
 #define HORN_PIT_ON()    PIT->CHANNEL[ HORN_PIT_CH ].TCTRL |= PIT_TCTRL_TEN_MASK  // Enabling timer channel
 #define HORN_PIT_OFF()   PIT->CHANNEL[ HORN_PIT_CH ].TCTRL &= ~PIT_TCTRL_TEN_MASK   // Disabling timer channel
 #define HORN_PIN_HI()    PTB-> PTOR |= GPIO_PSOR_PTSO( HORN_MASK )
 #define HORN_PIN_LO()    PTB-> PTOR |= GPIO_PCOR_PTCO( HORN_MASK )
 #define HORN_PIN_TOGGLE()    PTB-> PTOR |= GPIO_PTOR_PTTO( HORN_MASK )



 void Drive_SATimeout ( void );
 void Drive_steer_LCR ( uint8_t lcr );
 void Drive_steer_cnt ( void );
 void Drive_steer_per ( uint8_t per );
 void Drive_motor_init ( void );
 void Drive_motor_per ( uint8_t per );
 void Drive_motor_slow ( void );
 void Drive_dir_set ( uint8_t dir );
 void Drive_horn_beep ( uint8_t stat );
 void Drive_horn_init ( void );
 void Drive_head_per ( uint8_t per );

 
 
 #endif