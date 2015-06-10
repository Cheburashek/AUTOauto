/*
 *	main.c
 *
 *
 */
 
 
 /* Servo min E5: 250
    Servo max E5: 1150
 */
 
 
 #include "main.h"
 
 
 int main ( void ){
 
   int i = 0;
   int t = 0;    
   
   sLCD_init();
   PWM_init();
   TPM1_init();
   Drive_horn_init();
   UART_init();  
   UART_parser_cb ( Select_main ); // CBfor parsing
   UART_SATimeout_cb ( Drive_SATimeout ); // CB for Still Alive timeout
      
   Drive_steer_LCR ( 0x01 );  // Center
   Drive_dir_set ( 0x00 );    // Forward   
    //PWM_set_E5 ( MOTOR_CH, 560 );  
   //TPM1_OneShot ( test_f, 500 );
   
  while(1){} 
    
    
 }
 
