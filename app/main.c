/*
 *	main.c
 *
 *
 */
 
 
 /* Servo abs min E5: 250
    Servo abs max E5: 1150
 */
 
 
 #include "main.h"
 #include "IO.h"
 
 int main ( void ){
   
	 
   // Initialization:
   sLCD_init();
   PWM_init();
   TPM2_init();
   UART_init();  
	 
	 sLCD_init();
	 Trig_init();
	 Echo_init();
	 IO_init();
	 
   UART_parser_cb ( Select_main );        // CBfor parsing
   UART_SATimeout_cb ( Drive_SATimeout ); // CB for Still Alive timeout
      
   // Default settings:
   Drive_steer_LCR ( 0x01 );  // Center
   Drive_dir_set ( 0x00 );    // Forward 
	 //Drive_head_per ( 50 );

	 Drive_motor_init();	
	 Drive_motor_per ( 50) ;
   // Infinity loop
	 LED_green_on();
   while(1){;}    
    
 }
 
