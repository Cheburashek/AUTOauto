/*
 *	PWM.c
 *
 *
 */
 
 #include "PWM.h"
 
 
 static cb_t cb_TPM2;
 
 
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
   PORTC->PCR[ DIRECT_PIN ] |= PORT_PCR_MUX( 4u );
	 PORTD->PCR[ HEAD_PIN ] |= PORT_PCR_MUX( 4u );

   
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
																		  
   TPM0->CONTROLS[ HEAD_CH ].CnSC |= TPM_CnSC_MSB_MASK
                                    |  TPM_CnSC_ELSA_MASK; 
   
   TPM0->CONTROLS[ HEAD_CH ].CnSC &= ~(TPM_CnSC_MSA_MASK
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
 // TPM2 general purpose timer initialization
 void TPM2_init ( void ){ 
 
   SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
   SIM->SOPT2 |= SIM_SOPT2_TPMSRC( 3u ); // MCGIRCLK clock as a source 
    
   MCG->C1 |= MCG_C1_IRCLKEN_MASK;  // MCGIRCLK enabled
   MCG->C2 |= MCG_C2_IRCS_MASK;     // Fast IRC 4MHz
     
   TPM2->SC |= TPM_SC_PS( 7u );    // Divided by 128 -> ~16kHz 
 
 	NVIC_ClearPendingIRQ(TPM2_IRQn);
	NVIC_EnableIRQ(TPM2_IRQn);
	NVIC_SetPriority(TPM2_IRQn, 1);  // Lower priority
   
 }
 
 
 
 //************************************************************************
 // TPM2 general purpose timer for callbacks   
 void TPM2_OneShot ( cb_t cb, uint16_t ms ){
 
   TPM2->CNT = TPM_CNT_COUNT( 0u );   // Clearing TPM
 
   // for ~16kHz ( max 4s ): 
   if ( ms <= 4000 ){
      TPM2->MOD = TPM_MOD_MOD( (16*ms) ); 
   }
   else{
      TPM2->MOD = TPM_MOD_MOD( 64000 );
   }
   
   TPM2->SC |= TPM_SC_TOIE_MASK; // Interrupt enabled
   
   cb_TPM2 = cb;  // Callback set
   
   TPM2->SC |= TPM_SC_CMOD( 1u );    // TPM enabled   
   
 }
 
  
 //************************************************************************
 // TPM2 IRC handler:
 
 void TPM2_IRQHandler ( void ){
 
   // Timer overflow:
   if ( TPM2->SC & TPM_SC_TOF_MASK ){  
   
      TPM2->SC |= TPM_SC_TOF_MASK;    // Clearing TOF
      TPM2->SC &= ~TPM_SC_TOIE_MASK;  // Interrupt disabled
      TPM2->SC &= ~TPM_SC_CMOD_MASK; // TPM disabled  -> Firstly disable interrupts!
      TPM2->MOD = TPM_MOD_MOD( 0u );
      
      cb_TPM2();    // Callback invoke 
      
   }
   
 }
 