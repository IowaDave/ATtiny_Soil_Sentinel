# Why Not Use an Arduino?
I saw four reasons to use an AVR microcontroller, rather than full-featured Arduino development board.
1. **Cost**. A microcontroller chip typically costs less to buy compared to an Arduino.
2. **Size**. A chip takes up less space than an Arduino. Some AVR chips are *really* tiny, yet do the job.
3. **Energy savings**. Power-down sleep can cut a chip's battery drain almost to zero. An Arduino will continue to draw significant power even while the chip onboard of it is sleeping.
4. **Try something new**. Because I'm not getting any younger!

## Articles in this Series
[Home Page](https://iowadave.github.io/ATtiny_Soil_Sentinel/)
Why Not Use an Arduino? **<< You are Here**

## Why Not, Part One
Arduino is much more than just a microcontroller chip. The chip is also known as a microprocessing unit, or MPU, and is just one component among many that crowd the surface of an Arduino.

MPU chips contain many components inside their tiny, plastic packages. You code can access and control the components by reading values from or writing to certain memory locations in the MPU. You can look up details about an MPU chip in its datasheet. These are available to download as PDF files. Datasheets can be anywhere from a few hundred pages to well over a thousand pages long.

Or you can save yourself the trouble, and just use "Arduino language" statements such as ```digitalRead()``` or ```Serial.print()```. The advantage of Arduino language is that you do never have to know how the MPU chip works. The disadvantage is that you never learn how the MPU chip works, either.

There, in a nutshell, is why I chose not to use an Arduino. I wanted to learn how an MPU chip works, then use one all by itself in a project.

## Why Not, Part Two
Face facts. Rarely does an Arduino project use all of the I/O pins on the board. Many Internet-of-Things (IoT) devices require very few I/O pins. The ATmega328P MPU on the Arduino Uno and Nano boards have 20 or more I/O pins

## Good Books

