# ATtiny_Soil_Sentinel
Building a battery-operated, long-lived, soil moisture monitor on a tiny chip.

![Sentinel beta test version in operating mode](https://github.com/IowaDave/ATtiny_Soil_Sentinel/blob/main/images/IMG_2848.jpg)

---

For my friends who have received one my perfboard models, I provide [instructions for hooking it up and calibrating it](#Connecting-and-Calibrating).

---
It was time to cut the cord. Sons must leave their mothers. Likewise tinkerers, their Arduinos.

The project presented here takes an old, familiar Arduino demonstration in new directions, including:
* no Arduino &ndash; just a tiny microchip;
* no "Arduino language" &ndash; control the chip directly;
* no ```delay()``` &ndash; sleep instead.

The project also presents useful techniques for:
* waterproofing the sensor, and
* soldering the project onto perfboard.

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

Note that the ISR code module file name suffix is ".c" rather than ".cpp".  The reason for naming it this way is to invoke the C compiler rather than the C++ compiler for this part. It turns out that "ISR" is a C-style macro that carries special meaning all the way down deep into the Assembler and Linker stages of the Arduino IDE. It will not compile as part of a ".cpp" file. 

Notice also that the ```#include``` directive for this file appears at the end of the ATtiny_Soil_Sentinel.ino listing. For reasons I do not understand, but believe to be true, Arduino IDE prefers to encounter interrupt service routines only at the end of its main ".ino" file rather than higher up where ```#include``` directives normally go. Placing ```#include wdtisr.c``` at the end of the ".ino" file keeps things tidy. It brings the ISR in at the right place while allowing me to write the ISR code in a separate, library file.

### Connecting and Calibrating

#### Connections

![demo board showing connections](https://github.com/IowaDave/ATtiny_Soil_Sentinel/blob/main/images/IMG_2853.jpg)

The above image of the Sentinel shows a beta test version having connections to a power supply and to a sensor.

**Power**

The power supply connections are shown on the screw terminal block located at the upper-left corner of the Sentinel image. The red wire, marked "+", supplies the positive voltage line. The black wire, marked "−", establishes the ground.

I tested the apparatus using three, AA-size alkaline batteries connected in series to supply approximately 4.5 volts. Based on available information regarding the sensor, the positive voltage supplied should be within the range listed below, inclusive:
* Maximum: 5.5 volts
* Minimum: 3.3 volts

**Sensor**

The sensor connects to the screw terminal block at the lower-right corner of the Sentinel image. Match the wire colors from the sensor to the wire colors on the board as follows:

|Sensor|Board|
|------|-----|
|Orange|Orange|
|Blue stripe|Blue stripe|
|Green|Green stripe|

Take note of how the screw terminal blocks operate, as shown in the following images.

![Closeup of terminals](https://github.com/IowaDave/ATtiny_Soil_Sentinel/blob/main/images/IMG_2858.jpg)

The "open" position is obtained by turning the screw counterclockwise. In this position, a wire can be inserted into the terminal block. The "closed" position is obtained by turning the screw clockwise until it feels tight. 

![Sensor wires in place on the terminal block](https://github.com/IowaDave/ATtiny_Soil_Sentinel/blob/main/images/IMG_2859.jpg)

Tightening the screws secures the wires in place against the top of the terminal block.

#### Calibration

Begin with soil that is about as dry as you care to allow for your plant. Insert the sensor into the soil, leaving about an inch of the sensor protruding above the soil surface.

Locate the trim potentiometer, at the lower-left corner of the Sentinel image.

**Step One** 

Energize the Sentinel board. When power is first applied, the device enters Calibration Mode.

Note that the LED might start flashing, or it might remain off. You will observe both behaviors of the LED in the next step.

The Sentinel will remain in Calibration Mode for about sixty seconds. You can start another Calibration any time you desire, by simply turning the power off then back on again.

**Step Two**

With the Sentinel in Calibration Mode, use a small screwdriver to turn the trim potententiometer through its full arc of motion. At one extreme, the LED will flash steadily. At the other extreme, the LED will be turned off. Rotate the potentiometer from the "off" side back to the position where the LED just starts to flash. This position establishes the initial calibration point. In the next step, you will allow the Sentinel to enter Operating Mode. Then you will verify the calibration.

**Step Three**

Allow the LED to continue blinking. Watch for the blink pattern of the LED to change about one minute after powering up the Sentinel. The change occurs about one minute after powering-up the Sentinel.

The change of pattern means that Calibration Mode has concluded and the device has entered Operating Mode. The new pattern is the "dry" indication.  

**Step Four**

Add a small amount of water to the soil: half a cup or so. Plan to wait for a minute or two to gauge the result. The water needs time to soak in. The sensor needs time to detect the new soil moisture level.

In Operating Mode, the sensor checks the soil and indicates its moisture level at two, different intervals, depending on whether the soil was moist or dry the last time it checked.
* Dry: flash every 2 seconds, sense every 15 seconds
* Moist: flash every 10 seconds, sense every 15 minutes

This is the reason for leaving the trim potentiometer slightly to the "dry" side in Step Two: in order to have the sensor check the effect of the added water at 15-second intervals.

After the soil moisture increases enough to give a "moist" reading, the Sentinel's LED will cease flashing rapdily and frequently. Instead, it will flash slowly, at 10-second intervals. If this change happens soon after you add a small amount of water, then the calibration is confirmed.
