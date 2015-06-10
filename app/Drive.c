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
 
 static Steer_t Steer = { STEER_MIN_E5, STEER_MAX_E5, STEER_CNT_E5, 0 };
 static Motor_t Motor = { MOTOR_MIN_E5, MOTOR_MAX_E5, 0 };
 
 //****************************************************************
 // Still Alive timeout routine:
 
 void Drive_SATimeout ( void ){
 
   Drive_steer_cnt();
   Drive_motor_init();
   
 }
 
 
 // Min/max angle:
 //****************************************************************
 
 void Drive_steer_LCR ( uint8_t lcr ){

   switch ( lcr ){   
   
      case 0x00:   
         PWM_set_E5 ( STEER_CH, Steer.max );   
         break;
      case 0x01:
         PWM_set_E5 ( STEER_CH, Steer.cnt );   
         break;
      case 0x02:
         PWM_set_E5 ( STEER_CH, Steer.min );   
         break;                  
   }
 }

 //****************************************************************
 // Center angle:
 void Drive_steer_cnt ( void ){
 
   PWM_set_E5( STEER_CH, Steer.cnt ); 
 }
 
 //****************************************************************
 // Percent of max angle scope ( 50% -> center):
 void Drive_steer_per ( uint8_t per ){
 
   uint16_t temp = 0;
    
   if ( per < 50 ){      
      temp = ((( Steer.cnt - Steer.min )*per ) / 50) + Steer.min; 
   }
   else{
      temp = ((( Steer.max - Steer.cnt )*(per-50) ) / 50) + Steer.cnt;
   }
 
   PWM_set_E5 ( STEER_CH, temp ); 
 }
 
 
 //****************************************************************
 // Stops motor (or initialization): 
 void Drive_motor_init ( void ){
 
   PWM_set_E5 ( MOTOR_CH, MOTOR_INIT_E5 ); 
 }
 
 
 //****************************************************************
 // Sets motor speed in percent: 
 void Drive_motor_per ( uint8_t per ){

   uint16_t E5 = 0;
   
   if ( per > MOTOR_SPEED_MAX ){
      per = MOTOR_SPEED_MAX; 
   }      
   
   E5 = (((Motor.max - Motor.min) * per) / 100) + Motor.min; 
 
   PWM_set_E5 ( MOTOR_CH, E5 );

 }
 
 //****************************************************************
 // Sets motor speed - maximum speed in % defined in Drive.h: 
 void Drive_motor_slow ( void ){
 
   Drive_motor_per ( MOTOR_SPEED_SLOW );
 }
 
 
 //****************************************************************
 // Sets direction:
 void Drive_dir_set ( uint8_t dir ){
 
   if ( 0 == dir ) {
      PWM_set_E5 ( DIRECT_CH, DIRECT_FOR_E5 );
   }
   else if ( 1 == dir ){
      PWM_set_E5 ( DIRECT_CH, DIRECT_REV_E5 );
   } 
 }
 
 
 //****************************************************************
 // Horn beep:
 void Drive_horn_beep ( uint8_t stat ){
 
   if ( 0 == stat ){
      HORN_PIT_OFF();
      HORN_PIN_LO();
   }
   else if (1 == stat ){
      HORN_PIT_ON();      
   }
 }
 
 //****************************************************************
 // Horn init ( PIT ):
 
 void Drive_horn_init ( void ){
 
   SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
   SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
   
   
   PORTB->PCR[ HORN_PIN ] |= PORT_PCR_MUX ( 1u );
   
   PTB-> PDDR |= GPIO_PDDR_PDD( HORN_MASK ); // Output
   
   NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_EnableIRQ(PIT_IRQn);
	NVIC_SetPriority(PIT_IRQn, 1);  // Lower priority
   
   PIT->MCR &= ~PIT_MCR_MDIS_MASK;     // Enabling PIT 
   PIT->CHANNEL[ HORN_PIT_CH ].TCTRL |= PIT_TCTRL_TIE_MASK;   // Enabling ints
   
   // 48000 -> 1ms, 1kHz
   PIT->CHANNEL[ HORN_PIT_CH ].LDVAL = 48000;
 }
 
 
 //****************************************************************
 // PIT handler:
 
 void PIT_IRQHandler ( void ){

      HORN_PIN_TOGGLE(); 
      PIT->CHANNEL[ HORN_PIT_CH ].TFLG |= PIT_TFLG_TIF_MASK;   // Clearing TIF
 }
 
 
