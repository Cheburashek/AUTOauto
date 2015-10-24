/*
 *	PWM.h
 *
 *
 */
 
 #ifndef _PWM_H_
 #define _PWM_H_
 

 #include "Common.h" 
 
 // Macros:
 #define STEER_PIN 1  // PTC1
 #define MOTOR_PIN 2  // PTC2
 #define DIRECT_PIN 3 // PTE30
 #define HEAD_PIN 4	  // PTD4
 
 #define STEER_CH 0   // Channel 0, TPM0
 #define MOTOR_CH 1   // Channel 1, TPM0
 #define DIRECT_CH 3  // Channel 3, TPM0 
 #define HEAD_CH 4	  // Channel 4, TPM0 
 
 #define STEER_MASK  ( 1UL<<STEER_PIN )
 #define MOTOR_MASK  ( 1UL<<MOTOR_PIN )
 #define DIRECT_MASK ( 1UL<<DIRECT_PIN )
 #define HEAD_MASK 	 ( 1UL<<HEAD_PIN )  
  
 #define PWM_MOD_50HZ   0x99C0   // for 50Hz PWM
 
 // Typedefs: 
 typedef  void(*cb_t)(void);
 
 // Functions definitions:
 void PWM_init ( void );
 void PWM_set_pro ( uint8_t ch, uint16_t promile );
 void PWM_set_E5 ( uint8_t ch, uint16_t E5 );
 
 void TPM2_OneShot ( cb_t cb, uint16_t ms );
 void TPM2_init ( void );
 
 #endif
 
 
  