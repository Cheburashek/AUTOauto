/*
 *	main.c
 *
 *
 */
 
 
 /* Servo abs min E5: 250
    Servo abs max E5: 1150
 */
 
 
 #include "main.h"
 
 
 int main ( void ){
   
	 
   // Initialization:
   sLCD_init();
   PWM_init();
   TPM2_init();
   //Drive_horn_init();
   UART_init();  
	 
	 sLCD_init();
	Trig_init();
	Echo_init();
	 
   UART_parser_cb ( Select_main );        // CBfor parsing
   UART_SATimeout_cb ( Drive_SATimeout ); // CB for Still Alive timeout
      
   // Default settings:
   Drive_steer_LCR ( 0x01 );  // Center
   Drive_dir_set ( 0x00 );    // Forward   
//   
//	 while(1)
//	 {
//		for ( i = 0; i < 50000; i++ ){;}
//		 UART_data_send ( "Dupa", 4 );
//	 }
	 
	 
	 
   // Infinity loop
   while(1){;}    
    
 }
 
