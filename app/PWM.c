/*
 *	PWM.c
 *
 *
 */
 
 #include "PWM.h"
 
 
 void PWM_init ( void ){

   
   SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
   SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
   SIM->SOPT2 |= SIM_SOPT2_TPMSRC( 3u ); // MCGIRCLK clock as a source 
    
   MCG->C1 |= MCG_C1_IRCLKEN_MASK;  // MCGIRCLK enabled
   MCG->C2 |= MCG_C2_IRCS_MASK;     // Fast IRC 4MHz
    
   // Alernatives:	
   PORTC->PCR[ STEER_PIN ] |= PORT_PCR_MUX( 4u );
	PORTC->PCR[ MOTOR_PIN ] |= PORT_PCR_MUX( 4u );
   
    
   // Center-aligned PWM, Hi-true, both channels:
   TPM0->CONTROLS[STEER_CH].CnSC |= TPM_CnSC_MSB_MASK
                                 |  TPM_CnSC_ELSB_MASK; 
   
   TPM0->CONTROLS[STEER_CH].CnSC &= ~(TPM_CnSC_MSA_MASK
                                    | TPM_CnSC_ELSA_MASK);
   
   TPM0->CONTROLS[MOTOR_CH].CnSC |= TPM_CnSC_MSB_MASK
                                 |  TPM_CnSC_ELSB_MASK; 
   
   TPM0->CONTROLS[MOTOR_CH].CnSC &= ~(TPM_CnSC_MSA_MASK
                                    | TPM_CnSC_ELSA_MASK); 
                       
   // PWM frequency:                                                                              
   
   
   TPM0->MOD = TPM_MOD_MOD(0x99C0); // For 50Hz PWM     TODO: macro

   TPM0->SC |= TPM_SC_PS( 0u );    // Divided by 1 -> 4MHz 
   TPM0->SC |= TPM_SC_CMOD( 1u );    // TPM enabled             
    
   
   TPM0->CONTROLS[STEER_CH].CnV |= TPM_CnV_VAL(512);
   TPM0->CONTROLS[MOTOR_CH].CnV |= TPM_CnV_VAL(4505);

 }

 void PWM_duty_set ( uint8_t ch, uint16_t duty ){
   
 
 
 }
 