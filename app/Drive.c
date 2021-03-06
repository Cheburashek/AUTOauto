/*
 *	Drive.c
 *
 *
 */
 
 #include "Drive.h"
 #include "IO.h"
 #include "Echo.h"
 #include "USART.h"
 
 #define STOP_DIST  800
 
 
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
 
 
 // Externs:
bool motorPermFlag = true;
bool motorRewFlag = false;		// Rewerse
 
 // Steering and motor structures ( in 1/E5 ):
 
 static Steer_t Steer = { STEER_MIN_E5, STEER_MAX_E5, STEER_CNT_E5, 0 };
 static Motor_t Motor = { MOTOR_MIN_E5, MOTOR_MAX_E5, 0 };
 static Steer_t Head =  { HEAD_MIN_E5, HEAD_MAX_E5, HEAD_CNT_E5, 0 };

 
 
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
		  motorRewFlag = false;
   }
   else if ( 1 == dir ){
      PWM_set_E5 ( DIRECT_CH, DIRECT_REV_E5 );
		  motorRewFlag = true;
   } 
 }
 

 
 //****************************************************************
 void Drive_horn_beep ( uint8_t stat )
 {
	if ( !stat )
	{
		LED_BUZZER_on();	
	}
	else
  {
		LED_BUZZER_off(); 
  }	
 }
  
 
 
//****************************************************************
 
void Drive_pulse ( void )
{

	static uint8_t cnt;	
	cnt++;
	
} 
 

//****************************************************************
void Drive_measure_end ( uint16_t dist )
{
		static uint8_t cnt;
		
	if ( dist < STOP_DIST )		// STOP
	{
		Drive_motor_init ( );	
		motorPermFlag = false;
		Drive_horn_beep ( 0x01 );
	}
	else
	{
		motorPermFlag = true;
		Drive_horn_beep ( 0x00 );
	}
	
	cnt ++;	
	
	if ( cnt == 10 )
	{
		uint8_t data[] = { CMD_PREFIX, 0x10, 0x02, (uint8_t)(dist>>8), (uint8_t)dist };
		
		UART_data_send ( data, sizeof ( data ) );
		cnt = 0;	
	}
}
 
 
 