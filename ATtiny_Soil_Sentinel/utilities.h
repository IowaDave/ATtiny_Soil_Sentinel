
#include <arduino.h>

#ifndef UTILITIES_H
#define UTILITIES_H

// make sure of the system clock frequency
#ifdef F_CPU
#undef F_CPU
#define F_CPU 8000000
#endif



void configurePins();
void resetWDR ();
void sleepNow ();
void configureAnaComp ();
void configureWDT ();
void doAllTheWork ();

#endif
