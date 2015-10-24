

#ifndef _IO_H_
#define _IO_H_

#define PULSATOR_PIN 11 // PTC11
#define PULSATOR_MASK (1<<PULSATOR_PIN)

#define GREEN_PIN 5 		// PTD5
#define RED_PIN 29			// PTE29
#define BUZZER_PIN 1		// PTE1

#define GREEN_MASK (1UL << GREEN_PIN);
#define RED_MASK (1UL << RED_PIN);
#define BUZZER_MASK (1UL << BUZZER_PIN);


void LED_green_on(void);
void LED_red_on(void);
void LED_green_off(void);
void LED_red_off(void);
void LED_green_toggle(void);
void LED_red_toggle(void);	
void LED_BUZZER_on(void);
void LED_BUZZER_off(void);



void IO_init(void);



#endif