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
 
   int i = 0;
   int t = 0; 
    

    
   PWM_init();
   PWM_set_pro ( MOTOR_CH, 49);
    
    
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
   */ 
    
  
 
   while(1){
      
   for ( i = 490; i < 800; i++ ) {
          
      for ( t = 0; t < 30000; t ++ ){}
      PWM_set_E5 ( STEER_CH, i);
   
 
   }
   for ( i = 800; i > 499; i-- ) {
          
      for ( t = 0; t < 30000; t ++ ){}
      PWM_set_E5 ( STEER_CH, i);   
 
   }
 
 }
 
 }