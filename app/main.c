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
 
 uint8_t dupa[] = { 0xFF, 0xEE, 0xCC, 0x90 };
   int i = 0;
   int t = 0;    
   
   sLCD_init();
   PWM_init();
   TPM1_init();
   UART_init();  
   UART_parser_cb ( Select_main ); // Needed for parsing
      
<<<<<<< HEAD
       //PWM_set_E5 ( MOTOR_CH, 1150 );
=======
   
   UART_data_send( dupa, 4 );   
>>>>>>> master
      
   //TPM1_OneShot ( test_f, 500 );
   
  while(1){}
    
    
 }
 
