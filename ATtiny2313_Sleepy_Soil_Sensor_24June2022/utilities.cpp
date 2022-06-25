#include "utilities.h"

void configurePins() {
  // input buffers will be disabled during sleep,
  // thus only need to set unused pins to INPUT PULL-UP
  // First set all pins to INPUT 
  DDRA = 0;
  DDRB = 0;
  DDRD = 0;
  // Pull-up all I/O pins not used for digital output or the analog comparator
  PORTA = 0b00000111; 
  PORTB = 0b11011000; // leave pins PB0, PB1, PB2 and PB5 LOW
  PORTD = 0b01111111; 
  // Set the digital output pins to OUTPUT
  DDRB |= (1<<DDB2) | (1<<DDB5); // PB2 and PB5
}

void resetWDR () {
  asm volatile (
    "wdr \n\t" :::
  );
}

void sleepNow () {
  asm volatile (
    "sleep \n\t" :::
  );
}

void  configureAnaComp () {
  // disable digital input on pins PB0 and PB1,
  // the pins used by the Analog Cmparator
  DIDR = ( (1<<AIN1D) | (1<<AIN0D) );
  // clear analog comparator disable bit,
  // the analog comparator interrupt enable bit,
  // and the bandgap select bit
  ACSR &= ~( (1<<ACD) | (1<<ACIE) | (1<<ACBG) );
  
}

void configureWDT () {
  cli(); // disable interrupts  
  resetWDR(); // reset the Watchdog Counter to zero
  MCUSR &= ~(1<<WDRF); // clear the watchdog reset flag
  
  /*
   * Quoting from the datasheet, page 39...
   * alterations to the Watchdog set-up 
   * (registers MCUSR and WDTCSR)
   * must follow timed sequences. 
   * The sequence for clearing WDE 
   * and changing time-out configuration is as follows:
   * 1. In the same operation, write a logic one 
   * to the Watchdog change enable bit (WDCE) and WDE. 
   * A logic one must be written to WDE 
   * regardless of the previous value of the WDE bit.
   * 2. Within the next four clock cycles, 
   * write the WDE and Watchdog prescaler bits 
   * (WDP) as desired, but with the WDCE bit cleared. 
   * This must be done in one operation.
   */
   // Start the timed sequence.
   WDTCSR |= ( (1<<WDCE) | (1<<WDE) );
   // Write values to WDTCSR as desired in a single step:
   //   WDP[3:0] = 0100 sets overflow cycles 32K = 0.25 seconds
   //   WDIE = 0 disables the WD Interrupt, for the time being
   //   WDE = 0 disables the WD Reset behavior permanently
   //   WDIF = 1 clears the WD Interrupt Flag, just in case
   //   and WDCE = 0 is required in this step
   WDTCSR = ( (1<<WDIF) | (1<<WDP2) );
   sei(); // enable interrupts
}
