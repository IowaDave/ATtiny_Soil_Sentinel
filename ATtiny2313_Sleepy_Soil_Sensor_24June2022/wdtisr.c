#include <inttypes.h>
#include <avr/io.h>


#define TEST_PREP_DELAY 4 // 1 seconds
#define TEST_WAIT_MOIST 3600 // 15 minutes
#define TEST_WAIT_DRY 60 // 15 seconds
#define LED_ON_MOIST 4 // 1 seconds
#define LED_OFF_MOIST 36 // 9 seconds
#define LED_ON_DRY 1 // 1/4 second
#define LED_OFF_DRY 3 // 1/4 seconds
#define LED_DELAY_TESTING 0 // 1/4 second
#define CALIBRATION_INTERVAL 240 // first 60 seconds after startup


ISR (WDT_OVERFLOW_vect) {

// ==================
// local declarations
// ==================

static uint8_t calibrationCountdown = CALIBRATION_INTERVAL;

static enum {
  MOIST_ON,
  MOIST_OFF,
  DRY_ON,
  DRY_OFF,
  TESTING,
  PUMPING,
  INACTIVE
} ledState = MOIST_OFF;

static uint16_t ledDelay; 

static enum {
  PREPARE,
  TEST,
  WAIT_MOIST,
  WAIT_DRY
} testState = PREPARE;

static uint16_t testDelay;
// ==================================
// The action takes place here, below
// ==================================
  
  // clear the sleep enable bit immediately after waking up
  MCUCR &= ~(1<<SE);

  // are we still in the initial startup minute?
  if (calibrationCountdown > 0) {
    // has the sensor stabilized?
    if (calibrationCountdown < 236) {
      // sense the soil
      if (ACSR & (1<<ACO) ) {
        // soil is dry, toggle LED on pin PB5
        PINB |= (1<<PINB5);
      } else {
        // soil is moist, turn off the LED on pin PB5
        PORTB &= ~(1<<PORTB5);
      }
    }
    // decrement calibration time remaining
    calibrationCountdown -= 1; // decrement calibration time remaining
    testDelay = ledDelay = 1; // prevent entering the state machines
  }

  // check the test delay counter
  if (testDelay == 0) { // enter the testing state machine
    switch (testState) {
      case PREPARE:
        // enable analog comparator (clear the ACD bit)
        // but disable analog comparator interrupt (clear the ACIE bit)
        ACSR &= ~( (1<<ACD) | (1<<ACIE) );
        PORTB |= (1<<PORTB2); // energize sensor on pin PB2
        testDelay = TEST_PREP_DELAY; // allow sensor to stabilize...
        testState = TEST; // ...then do the test
        ledDelay = 0;
        break;
      case TEST:
        if (ACSR & (1<<ACO)) {
          // soil is dry
          testState = WAIT_DRY;
        } else {
          // soil is moist
          testState = WAIT_MOIST;
        }
        // set analog comparator disable bit
        ACSR |= (1<<ACD);
        // turn off the sensor on pin PB2
        PORTB &= ~(1<<PORTB2);
        ledState = INACTIVE;        
        break;
      case WAIT_MOIST:
        testDelay = TEST_WAIT_MOIST;
        testState = PREPARE;
        ledState = MOIST_ON;
        break;
      case WAIT_DRY:
        testDelay = TEST_WAIT_DRY;
        testState = PREPARE;
        ledState = DRY_ON;
        break;
      default:
        testState = PREPARE;
    }
  }

  // check the LED delay counter
  if (ledDelay == 0) { // enter the LED state machine
    switch (ledState) {
      case MOIST_ON:
        ledDelay = LED_ON_MOIST;
        PORTB |= (1<<PORTB5); // energize LED
        ledState = MOIST_OFF;
        break;
      case MOIST_OFF:
        ledDelay = LED_OFF_MOIST;
        PORTB &= ~(1<<PORTB5); // turn LED off
        ledState = MOIST_ON;
        break;
      case DRY_ON:
        ledDelay = LED_ON_DRY;
        PORTB |= (1<<PORTB5); // energize LED
        ledState = DRY_OFF;        
        break;
      case DRY_OFF:
        ledDelay = LED_OFF_DRY;
        PORTB &= ~(1<<PORTB5); // turn LED off
        ledState = DRY_ON;
        break;
      case TESTING:
        ledDelay = LED_DELAY_TESTING;
        PINB |= (1<<PINB5); // toggle LED 
        break;
      case PUMPING:
      case INACTIVE:
      default:
        PORTB &= ~(1<<PORTB5); // turn LED off
    }
  }

  // decrement the two delay counters
  if (testDelay > 0) testDelay -= 1;
  if (ledDelay > 0) ledDelay -= 1;
  
} // end WDT_OVERFLOW ISR
