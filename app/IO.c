



#include "Common.H"
#include "IO.h"
#include "Drive.h"


void LED_green_on(void){PTD->PCOR = GREEN_MASK;}

void LED_red_on(void){PTE->PCOR = RED_MASK;}

void LED_green_off(void){PTD->PSOR = GREEN_MASK;}

void LED_red_off(void){PTE->PSOR = RED_MASK;}

void LED_green_toggle(void){PTD->PTOR = GREEN_MASK;}

void LED_red_toggle(void){PTE->PTOR = RED_MASK;}

void LED_BUZZER_on(void){PTE->PCOR = BUZZER_MASK;}

void LED_BUZZER_off(void){PTE->PSOR = BUZZER_MASK;}


//************************************************************************************
void IO_init(void){

SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; //SW1+SW2
SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; // GREEN LED
SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK; //RED LED
	
PORTC->PCR[PULSATOR_PIN] |= PORT_PCR_MUX(1);
	
PTC->PDDR &= PULSATOR_MASK; //->input (PDDR is default cleared...)

	
PORTC->PCR[PULSATOR_PIN] |=   PORT_PCR_PS_MASK//Pull res selected as pullup
													 |  PORT_PCR_IRQC(10);//IRQ on falling

	

	
PORTD->PCR[GREEN_PIN] |= PORT_PCR_MUX(1);	//Purpose as GPIO
PORTE->PCR[RED_PIN] |= PORT_PCR_MUX(1);
PORTE->PCR[BUZZER_PIN] |= PORT_PCR_MUX(1); // BUZZER!


PTD->PDDR |= GREEN_MASK; //Direction of transmittion -> output
PTE->PDDR |= RED_MASK;
PTE->PDDR |= BUZZER_MASK;

//		
PTE->PSOR |= RED_MASK;	//Initial status od RED is cleared (bit set)
PTD->PSOR |= GREEN_MASK;
PTD->PSOR |= BUZZER_MASK;	
	
	
//NVIC
NVIC_ClearPendingIRQ(PORTC_PORTD_IRQn);
NVIC_EnableIRQ(PORTC_PORTD_IRQn);
NVIC_SetPriority(PORTC_PORTD_IRQn, 2);

}

//************************************************************************************



//************************************************************************************	
void PORTC_PORTD_IRQHandler(void){	
	
	if((PORTC->PCR[PULSATOR_PIN]&PORT_PCR_ISF_MASK) != 0){
		
		
		//Drive_pulse ();
		LED_red_toggle();
				
		PORTC->PCR[PULSATOR_PIN] |= PORT_PCR_ISF_MASK  ; 	 
	
	}

}





