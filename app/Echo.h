#ifndef ECHO_H
#define ECHO_H

#include "MKL46Z4.h"
#include "sLCD.h"


#define ECHO_PIN 20	// PE
#define ECHO_MASK (1UL << ECHO_PIN);


void Echo_init(void);


#endif