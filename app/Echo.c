#include "Echo.h"
#include "USART.h"

// TPM1 for ECHO

uint8_t flag = 0;
uint32_t temp_cnv = 0;



void Echo_init(void){

	// PORTE 20 CONFIG (TPM1 Channel 0)
	
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	PORTE->PCR[ECHO_PIN] |= PORT_PCR_MUX(0x03);											 
											 		
											 

	

	
//***************************************************************
	
// TPM1 CONFIG

	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3);	   // MCGIRC 
       
	MCG->C1 |= MCG_C1_IRCLKEN_MASK; 		   // MCGIRCLK active.
	MCG->C2 |= MCG_C2_IRCS_MASK;										// External FAST (4MHz) reference clock is selected.
	
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;

	TPM1->SC |= TPM_SC_PS(1)            // Divide by 2  (1MHz)
		   | TPM_SC_CMOD(0x01);	  	// Enabling TPM1 

	NVIC_ClearPendingIRQ(TPM1_IRQn);					
	NVIC_EnableIRQ(TPM1_IRQn);
	NVIC_SetPriority(TPM1_IRQn, 1);
	
	TPM1->CONTROLS[0].CnSC |= TPM_CnSC_ELSA_MASK		// Input capture -> every edge
				     | TPM_CnSC_ELSB_MASK
				     | TPM_CnSC_CHIE_MASK;			// Channel int. enabled
										 
}

//***************************************************************

void TPM1_IRQHandler(void){

	TPM1->CONTROLS[0].CnSC |= TPM_CnSC_CHF_MASK;	// Clearing Ch0 int

	if(flag == 0){
		temp_cnv = (TPM1->CONTROLS[0].CnV & TPM_CnV_VAL_MASK);
		flag = 1;
	}
	else if(flag == 1){
		temp_cnv = (TPM1->CONTROLS[0].CnV & TPM_CnV_VAL_MASK) - temp_cnv;
		temp_cnv *= 10;
		temp_cnv /= 58; 	// value in mm
		
		if(temp_cnv > 9999){temp_cnv = 9999;}
		
		sLCD_dec(temp_cnv);
		Drive_measure_end ( temp_cnv );		
		temp_cnv = 0;
		TPM1->CNT = 0;
		flag = 0;	
	}
				
}
		
