#include "utilities.h"

void setup() {
  // configure to minimize power use during sleep
  // See pages 31-32 of the datasheet
  
  // I/O pins
  configurePins ();

  // Analog Comparator (AnaComp)
  configureAnaComp ();
  
  // Brown-out Detector
  // fuses are set to disable Brown-out Detector

  // Internal Voltage Reference
  // will not draw power
  // unless it is selected for use by the ACO, 
  // which it will not be. Nothing to do here.

  // Watchdog Timer (WDT) will be used. Configure it.
  configureWDT ();   

  // select SM[1:0] = 01 for power-down sleep mode
  // and clear the sleep enable (SE) bit for now
  MCUCR = (MCUCR & 0b10001111) | (1<<SM0);

  // energize pin PB2 at startup
  // to power-up the sensor for calibration
  PORTB |= (1<<PORTB2);
  
}

void loop() {
  // enable the watchdog interrupt
  WDTCSR |= (1<<WDIE);
  // put the device to sleep
  // set the SE bit to 1
  MCUCR |= (1<<SE);
  sleepNow ();

  // all of the action takes place in the WDT ISR, ihncluded below
  
}

#include "wdtisr.c"
