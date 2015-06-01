/*
 *	PWM.c
 *
 *
 */
 
 #include "PWM.h"
 
 
 static cb_t cb_TPM1;
 
 
 //***********************************************************************
 // PWM initialization
 void PWM_init ( void ){

   
   SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
   SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
   SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
   
   SIM->SOPT2 |= SIM_SOPT2_TPMSRC( 3u ); // MCGIRCLK clock as a source 
    
   MCG->C1 |= MCG_C1_IRCLKEN_MASK;  // MCGIRCLK enabled
   MCG->C2 |= MCG_C2_IRCS_MASK;     // Fast IRC 4MHz
    
   // Alernatives:	
   PORTC->PCR[ STEER_PIN ] |= PORT_PCR_MUX( 4u );
	PORTC->PCR[ MOTOR_PIN ] |= PORT_PCR_MUX( 4u );
   PORTE->PCR[ DIRECT_PIN ] |= PORT_PCR_MUX( 3u );
   
   // Center-aligned PWM, LOW-true, both channels:
   TPM0->CONTROLS[ STEER_CH ].CnSC |= TPM_CnSC_MSB_MASK
                                 |  TPM_CnSC_ELSA_MASK; 
   
   TPM0->CONTROLS[ STEER_CH ].CnSC &= ~(TPM_CnSC_MSA_MASK
                                    | TPM_CnSC_ELSB_MASK);
   
   TPM0->CONTROLS[ MOTOR_CH ].CnSC |= TPM_CnSC_MSB_MASK
                                   |  TPM_CnSC_ELSA_MASK; 
   
   TPM0->CONTROLS[ MOTOR_CH ].CnSC &= ~(TPM_CnSC_MSA_MASK
                                    | TPM_CnSC_ELSB_MASK); 
     
   TPM0->CONTROLS[ DIRECT_CH ].CnSC |= TPM_CnSC_MSB_MASK
                                    |  TPM_CnSC_ELSA_MASK; 
   
   TPM0->CONTROLS[ DIRECT_CH ].CnSC &= ~(TPM_CnSC_MSA_MASK
                                    | TPM_CnSC_ELSB_MASK);   
                                    
   // PWM frequency:                                                                              
   
   
   TPM0->MOD = TPM_MOD_MOD( PWM_MOD_50HZ ); // For 50Hz PWM    

   TPM0->SC |= TPM_SC_PS( 0u );    // Divided by 1 -> 4MHz 
   TPM0->SC |= TPM_SC_CMOD( 1u );    // TPM enabled             
         
 }

 //***********************************************************************
 // Setting PWM duty in promiles 
 void PWM_set_pro ( uint8_t ch, uint16_t promile ){
   
    uint16_t temp = 0;
    
    if ( promile != 1000 ){
       temp = ( PWM_MOD_50HZ * promile ) / 1000;      
    }
    else{          
       temp = PWM_MOD_50HZ + 1; // For 100% PWM duty
    }
    
    TPM0->CONTROLS[ ch ].CnV = TPM_CnV_VAL( temp );  
 }
//***********************************************************************
// Setting PWM duty in 1/10000
 void PWM_set_E5 ( uint8_t ch, uint16_t E5 ){
   
    uint16_t temp = 0;
    
    if ( 10000!= E5 ){
       
       temp = ( PWM_MOD_50HZ * E5 ) / 10000;      
    }
    else{          
       temp = PWM_MOD_50HZ + 1; // For 100% PWM duty
    }
    
    TPM0->CONTROLS[ ch ].CnV = TPM_CnV_VAL( temp );  
    
 }
 
 
 
 //************************************************************************
 // TPM1 general purpose timer initialization
 void TPM1_init ( void ){ 
 
   SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
   SIM->SOPT2 |= SIM_SOPT2_TPMSRC( 3u ); // MCGIRCLK clock as a source 
    
   MCG->C1 |= MCG_C1_IRCLKEN_MASK;  // MCGIRCLK enabled
   MCG->C2 |= MCG_C2_IRCS_MASK;     // Fast IRC 4MHz
     
   TPM1->SC |= TPM_SC_PS( 7u );    // Divided by 128 -> ~16kHz 
 
 	NVIC_ClearPendingIRQ(TPM1_IRQn);
	NVIC_EnableIRQ(TPM1_IRQn);
	NVIC_SetPriority(TPM1_IRQn, 1);  // Lower priority
   
 }
 
 
 //************************************************************************
 // TPM1 general purpose timer for callbacks   
 void TPM1_OneShot ( cb_t cb, uint16_t ms ){
 
   TPM1->CNT = TPM_CNT_COUNT( 0u );   // Clearing TPM
 
   // for ~16kHz ( max 4s ): 
   if ( ms <= 4000 ){
      TPM1->MOD = TPM_MOD_MOD( (16*ms) ); 
   }
   else{
      TPM1->MOD = TPM_MOD_MOD( 64000 );
   }
   
   TPM1->SC |= TPM_SC_TOIE_MASK; // Interrupt enabled
   
   cb_TPM1 = cb;  // Callback set
   
   TPM1->SC |= TPM_SC_CMOD( 1u );    // TPM enabled   
   
 }
 
  
 //************************************************************************
 // TPM1 IRC handler:
 
 void TPM1_IRQHandler ( void ){
 
   // Timer overflow:
   if ( TPM1->SC & TPM_SC_TOF_MASK ){  
   
      TPM1->SC |= TPM_SC_TOF_MASK;    // Clearing TOF
      TPM1->SC &= ~TPM_SC_TOIE_MASK;  // Interrupt disabled
      TPM1->SC &= ~TPM_SC_CMOD_MASK; // TPM disabled  -> Firstly disable interrupts!
      TPM1->MOD = TPM_MOD_MOD( 0u );
      
      cb_TPM1();    // Callback invoke 
      
   }
   
 }
 