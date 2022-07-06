# Shrink the Code
...and minimize power consumption, too!

<!-- the following produces a list of posts -->
{% include post_list.html %}

### Say No to Arduino
There is little room for code in an ATtiny2313 microcontroller (MCU): just 2,048 bytes of flash memory. Economy counts!

##### Code Direct
Eliminating unnecessary "Arduino Language" significantly reduced the code size compared to using familiar Arduino statements. This is done partly by reading from and writing to the relevant, internal registers directly instead.

An example I like to offer is turning on an LED attached to, say, pin 7. The pin has to be initialized for output, first. On the DIP package of an ATtiny2313, physical pin 7 connects internally to pin PD3 of the MCU chip. The Arduino statements will look somewhat familiar:

```
pinMode(PD3, OUTPUT);
digitalWrite(PD3, HIGH);
```

The two instructions listed above generate 16 bytes of code. By contrast, direct instructions achieve the same result but generate only 4 bytes:

```
DDRD |= (1<<DDD3);
PORTD |= (1<<PORTD3);
```

The code size is reduced by 12 bytes. The meaning of the "direct" instructions becomes familiar after using them for a while.

##### No delay()
Arduino will install certain functions by default, regardless of whether your code uses them. These include instructions to configure the timers in the chip <span> &mdash; for possible use as PWM generators &mdash;</span> as well as the millis() and delay() functions so often seen in Arduino code examples.

Eliminating those functions appears to take around 170 bytes off the code size. There are two ways to do it for an ATtiny2313.

One way is a method generally available for many different AVR chips: write your own ```main()``` code block, like this:
```
int main() {
  setup();
  while (1) loop();
  return 0;
 }
 ```
 
The other way takes advantage of some unique features in [Spence Konde's core code for ATtiny chips](https://github.com/SpenceKonde/ATTinyCore). It modifies the Tools menu of the Arduino IDE to give you the choice to disable the millis()/micros() code insertion. The delay() function goes away too, as it depends on millis().

##### No text output
The Sentinel communicates by flashing an LED. This decision eliminates the need for space-hungry libraries to output text.

Just for fun, I compiled a "Hello World" program to use the USART (serial) output of the ATtiny2313. Nothing more than:

```Serial.println("Hello World");```

It gobbled up almost the entire memory of the poor little thing.

### Save Power
By the way, the Sentinel certainly does implement long pauses between actions. Rather than delay(), it sleeps. 

The delay() function keeps the MCU running constantly, consuming power, while it counts down a number of milliseconds. Not only does it consume power, it hogs the processor.

Sleep, combined with a timed, recurring interrupt, affords an alternative way to implement pauses between code operations. AVR chips like the 328P and the 2313 provide a number of different timers and sleep modes that can be used that way.

The most economical combination is the Watchdog Timer and the Power-down Sleep mode. The code described below uses that combination.

How it works is a topic for another post.

### Use libraries
Making code smaller has another dimension: keeping code listings short.

I have grown to favor the practice of splitting code into separate modules. This project has four. You can view the code folder by opening the following link in a separate tab or window: [https://github.com/IowaDave/ATtiny_Soil_Sentinel/tree/main/ATtiny_Soil_Sentinel](https://github.com/IowaDave/ATtiny_Soil_Sentinel/tree/main/ATtiny_Soil_Sentinel).

**ATtiny_Soil_Sentinel.ino** is the main code module. It consists mostly of explanatory comments. 
* The ```#include``` directive imports declarations and code from the ```utilities``` module. 
* The setup() block calls some functions defined in that module. 
* It also sets certain bits in a couple of memory locations.
* The loop() function merely puts the MCU to sleep. Over and over again.
* At the very end, the directive to ```#include wdtisr.c``` brings in the watchdog timer interrupt service routine (ISR). 

**utilities.h** is a header file that defines a key environment variable and declares a set of function prototypes.

**utilities.cpp** implements the C++ functions declared in the header file.

Note: the following was edited July 6, 2022 to correct a misunderstanding on my part. Thanks to Tom Almy for pointing my way back onto the path of Truth and Light.

**wdtisr.h** is a header file that defines a number of timing-related constants. It also imports the "Arduino.h" header file, which is necessary for the the watchgog time interrupt service routine (ISR) to compile.

**wdtisr.cpp** implements the ISR. This file imports the wdtisr.h header file, which in turn imports the "Arduino.h" header file, without which the ISR will not compile.

The ISR is discussed more fully in another post.


 
