/*
 *	main.c
 *
 *
 */
 
 
 /* Servo min promil: 15
    Servo max promil: 117
 */
 
 
 #include "main.h"
 
 
 // 
 
 char test[] = { 0x01, 0x02, 0x03, 0x04 };
 
 void test_f(void){
 
   UART2_data_send ( test, 4 );
   TPM1_OneShot ( test_f, 500 );
 }
 
 
 int main ( void ){
 
 
   int i = 0;
   int t = 0; 
   

   sLCD_init();
   PWM_init();
   TPM1_init();
   UART2_init();  
      
   TPM1_OneShot ( test_f, 500 );
      
   
  while(1){}
    
    
    
/*    
   while(1){      
       
   for ( i = 0; i <= 100; i++ ) {
          
      for ( t = 0; t < 300000; t ++ ){}
      Drive_angle_per ( i );
   
 
   }
   for ( i = 100; i >= 0; i-- ) {
          
      for ( t = 0; t < 300000; t ++ ){}
      Drive_angle_per ( i );   
 
   }   
    
    }
   
   while(1){
      
   for ( i = 499; i < 800; i++ ) {
          
      for ( t = 0; t < 300000; t ++ ){}
      PWM_set_E5 ( STEER_CH, i);
   
 
   }
   for ( i = 800; i > 499; i-- ) {
          
      for ( t = 0; t < 300000; t ++ ){}
      PWM_set_E5 ( STEER_CH, i);   
 
   }
 
 }
 */ 
 }
 
