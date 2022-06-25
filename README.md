# ATtiny_Soil_Sentinel
Building a battery-operated, long-lived, soil moisture monitor on a tiny chip.

It was time to cut the cord. Sons must leave their mothers. Likewise tinkerers, their Arduinos.

The project presented here takes an old, familiar Arduino demonstration in new directions, including:
* no Arduino &ndash; just a tiny microchip;
* no "Arduino language" &ndash; control the chip directly;
* no ```delay()``` &ndash; sleep instead.

The project also presents useful techniques for:
* waterproofing the sensor, and
* soldering the project onto perfboard.

For my friends who have received one my perfboard models, I provide instructions for [hooking it up and calibrating it](https://github.com/IowaDave/ATtiny_Soil_Sentinel/edit/main/README.md#connecting-and-calibrating), below.

A breadboard version will be built first, because it's traditional.

## Materials

### AVR microcontroller
The build illustrated here used an ATtiny2313V. It boasts a meagre 2K of flash memory for program code and a mere 128 bytes of RAM. Yet, careful code writing easily fits a useful application in there.  You can use almost any AVR chip, including an ATmega328P pried loose from an Arduino Uno. An ATtiny85 would be a good choice. But I'll demonstrate only the tiny2313 here.

### Components
* capacitor, 0.1 &mu;F
* resistors, 10K&Omega; (3)
* resistor, 330&Omega; (1)
* LED (1)
* potentiometer, 10K&Omega; or greater (1)
* capacitive soil moisture sensor
    * [example at Amazon](https://www.amazon.com/dp/B07SYBSHGX?psc=1&ref=ppx_yo2ov_dt_b_product_details)
* battery holder, 3 x AA, and batteries
    * [example at Amazon](https://www.amazon.com/dp/B07M7WYZ32?psc=1&ref=ppx_yo2ov_dt_b_product_details)
* breadboard and hookup wire
* optional
    * perfboard
    * screw terminal block, two- and three-point (1 each)
        * [example at Amazon](https://www.amazon.com/dp/B07YK4QM9C?psc=1&ref=ppx_yo2ov_dt_b_product_details)
    * DIP socket for the AVR chip 

### Tools
* A programming environment, such as Arduino IDE.
* Code library for the AVR chip being used.
    * [example for the ATtiny2313](https://github.com/SpenceKonde/ATTinyCore): see the "Installation" link in the READMe file there.
* An ISP programmer
    * example: [Arduino as ISP](https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP)
* A copy of the datasheet for the AVR chip being used.
    * example: [ATtiny2313 datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2543-AVR-ATtiny2313_Datasheet.pdf)

### Code
The code for this project is contained in the folder, "ATtine_Soil_Sentinel". It comprises four code modules:
* [ATtiny_Soil_Sentinel.ino](https://github.com/IowaDave/ATtiny_Soil_Sentinel/blob/main/ATtiny_Soil_Sentinel/ATtiny_Soil_Sentinel.ino) performs one-time setup operations. Then, in the loop() section, all it does is to put the AVR chip into power-down sleep.
* [utilities.h](https://github.com/IowaDave/ATtiny_Soil_Sentinel/blob/main/ATtiny_Soil_Sentinel/utilities.h) declares certain global values and function prototypes.
* [utilities.cpp](https://github.com/IowaDave/ATtiny_Soil_Sentinel/blob/main/ATtiny_Soil_Sentinel/utilities.cpp) implements functions declared in utilities.h.
* [wdtisr.c](https://github.com/IowaDave/ATtiny_Soil_Sentinel/blob/main/ATtiny_Soil_Sentinel/wdtisr.c) is the heart of the application. It defines an interrupt service routine (ISR) that runs at 1/4-second intervals of time, i.e., each time the Watchdog Timer overflows. 
    * The Watchdog Timer wakes up the chip from sleep. 
    * The ISR evaluates certain variables and performs corresponding operations.
    * At the conclusion of the ISR, program execution returns to the main loop() which puts the AVR chip back to sleep.

Combining power-down sleep with the Watchdog Timer and its ISR replaces the  ```delay()``` statement familiar from "Arduino language." Why bother? Because ```delay()``` keeps the AVR chip running while time passes, wasting battery power. By contrast, during sleep the chip consumes almost no power at all, and this code keeps the chip asleep almost all of the time. Result: batteries last much longer this way compared to Arduino &mdash; weeks or even months, rather than a few hours or days.

The ISR code appears lengthy at first glance. However, most of the code gets skipped over during any, single pass through the procedure. This is because it is organized into two so-called Finite State Machines, implemented as ```switch()``` statements. State machines are very fast ways to select which portion of a code listing will be processed. Further, these state machines are entirely skipped over most of the time; they run only when the value of a countdown timer reaches zero. As a result, each pass through the ISR may involve as many as nine or ten instructions, or as few as four.

### Connecting and Calibrating
