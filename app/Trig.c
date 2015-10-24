#include "Trig.h"

//Trigger on PIT

void Trig_init(void){
	
// Turning on clock for PIT module
	
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	
// NVIC	
	
	NVIC_ClearPendingIRQ(PIT_IRQn);					
	NVIC_EnableIRQ(PIT_IRQn);
	NVIC_SetPriority(PIT_IRQn, 3);

	
// TCTRLn - Timer Control Register
	
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;		// Timer Interrupt Enable
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TIE_MASK;


// LDVAL (clock for PIT = 24MHz)
	
	PIT->CHANNEL[0].LDVAL = 1440000;	// 60ms			   
	PIT->CHANNEL[1].LDVAL = 240; 		// 10us
	
// Enabling PIT
	
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;


// OUTPUT PIN (PTE21)

	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE->PCR[TRIGGER_PIN] |= PORT_PCR_MUX(1u);
	PTE->PDDR |= TRIGGER_MASK;
	
// Enabling channel 0	
	
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;


}


void PIT_IRQHandler(void){

	if(PIT->CHANNEL[0].TFLG == 1){
	
		PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;			// Writing 1 (MASK) clears flag
		PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TEN_MASK;	// Enabling channel 1
		PTE->PSOR |= TRIGGER_MASK;
	
	}

	if(PIT->CHANNEL[1].TFLG == 1){
	
		PIT->CHANNEL[1].TFLG = PIT_TFLG_TIF_MASK;     
		PIT->CHANNEL[1].TCTRL &= ~PIT_TCTRL_TEN_MASK;	// Disabling channel 1
		PTE->PCOR |= TRIGGER_MASK;
	}


}