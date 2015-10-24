#ifndef TRIG_H
#define TRIG_H

#include "MKL46Z4.h"

void Trig_init(void);

#define TRIGGER_PIN  21	// PE
#define TRIGGER_MASK (1UL << TRIGGER_PIN);


#endif