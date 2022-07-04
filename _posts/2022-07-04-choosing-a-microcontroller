# Choosing a Microcontroller
There are literally thousands of choices.

Microchip manufactures the microcontroller units (MCUs) used on Arduinos. Its web store lists 827 different models having 8-bit CPUs. They also sell many 32-bit models which we ignore here.

Each model may come in a variety of packages. For example, the ATmega328P used on Arduino Uno and Nano boards comes in a dozen different shapes and configurations.

So: many models multiplied by many packages per model = many, many different MCUs.

<!-- the following produces a list of posts -->
{% include post_list.html %}

#### The Choice
I considered just five devices for this project. 

##### ATmega328P
I could have simply pried one of these off of an Uno. It has plenty of capacity: 20 I/O pins, 32K of flash memory, 2K of RAM.

##### ATmega168
This one is the same physical size and shape as a 328P. The difference is less memory: 16K of flash and 1K of RAM, still plenty.

##### ATtiny85
It's physically the smallest model I considered, having just five I/O pins. Flash memory is 8K and RAM is 512 bytes, still plenty. This project uses only four I/O pins, which means this chip could handle it.

##### ATtiny84
Here we find the same flash and RAM capacity as the ATtiny85, but in a larger package having eleven I/O pins.

##### ATtiny2313
Old and feeble &mdash; like me! First released in 2003, they have a mere 2K of flash memory for program storage and just 128 bytes of RAM. Could my project's code shrink down to fit in there? That would be fun to try. I/O pins would be no problem; the chip exposes 17 of them. OK, then, choice made.

#### Buying the chips
I grew weary of shopping for these things through online resellers. Too many problems. 

How happy I was to discover that Microchip would sell them to little, old me. They will sell in any quantity, even just a single chip. 

Their web site can be a challenge to navigate. Try a shortcut. 

Use a search engine to fetch links for "microchip" and the chip model that interests you. 

For example, "microchip 2313" brings up a link to the ATtiny2313. The "Purchase Options" link on the product page lists every different package, its price and availability. 

In this era of chip shortages they often say the chip you want is out of stock. Keep checking. Once in a while I've found they had some on hand. They use reputable express services to deliver. Things arrive quickly, even from halfway around the world.

Even after paying for shipping, per-chip acquisition cost can be less this way compared to some online resellers who claim "free" shipping.

It won't surprise anyone who knows me that I wound up with an inventory of all the different chip models mentioned above.

#### Programming a Bare Chip
The MCUs mentioned in this article share a common programming framework.
* The memory addresses usesd to control their operations have a more or less consistent set of names, and
* they accept uploads via In-Circuit Serial Programming (ICSP).

The Arduino IDE can be configured to compile code for these different chips. One has to install a "core" that defines the particular chip. For ATtiny2313 I used Spence Konde's [ATTinyCore repository on Github](https://github.com/SpenceKonde/ATTinyCore). Installation and usage instructions are provided in the README file of that repository.

ICSP programming requires a dedicated exernal ISP programmer. I use an Arduino Uno as ISP, as explained on an [official Arduino Docs web page](https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP).

Mount the chip on a breadboard, straddling the middle gutter to keep the pins electrically isolated from each other. Connect jumper wires from Uno to ATtiny2313 as listed in the table below. Arduino pin numbers are as marked on the Arduino board. ATtiny2313 pin numbers are as shown on page 2 of its [data sheet](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2543-AVR-ATtiny2313_Datasheet.pdf).

|Arduino pin|ATtiny2313 pin|Signal|
|---|---|---|
|5V|20|Vcc|
|Gnd|10|Ground|
|10|1|Control / Reset|
|11|17|COPI, f.k.a. MOSI|
|12|18|CIPO, f.k.a. MISO|
|13|19|SCK|

It took me a while to get comfortable using ICSP to upload programs. That's another topic for another post.

