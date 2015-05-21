/*
 *	main.c
 *
 *
 */
 
 
 /* Servo min promil: 15
    Servo max promil: 117
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
      
   
   UART_data_send( dupa, 4 );   
      
   //TPM1_OneShot ( test_f, 500 );
   
  while(1){}
    
    
 }
 
