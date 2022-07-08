# AVR Fuses and the avrdude Utility

AVR microcontrollers allow users to select and to change a number of custom configuration settings.

The settings are stored in non-volatile bytes of memory, called "fuse bytes". Non-volatile means the bytes retain their value in the chip's memory during power-off intervals.

A utility program named "avrdude" can be used to modify the configuration settings by writing carefully structured values into the fuse bytes. It also can be used to read the values of the fuse bytes.

This article describes changing one bit in one of the fuse bytes for an ATtiny2313. The change will make the chip's CPU process instructions at a speed of 8 MHz (eight million cycles per second,) rather than the default speed of 1 MHz.

<!-- the following produces a list of posts -->
{% include post_list.html %}

### The Low Fuse Byte Governs Speed
It might help to refer to Table 67 on page 160 of the [datasheet for the ATtiny2313](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2543-AVR-ATtiny2313_Datasheet.pdf). It explains the Low Fuse Byte as an 8-bit value where each bit means something. We're interested in five of these Bits.

First, footnote 2 under this table tells us that the default settings for Bits 3 through 0 cause an "internal RC oscillator" to run at a rate of 8 MHz. Since that is the rate we want, we go with the default settings for these four bits.

Look at Bit 7, named CKDIV8, described as "Divide Clock by 8." The datasheet tells us that this bit is "programmed" by default.

It means that the oscillator setting of 8 MHz will be divided by 8 to produce the final running speed of the chip, that is, 8 MHz / 8 = 1 MHz. 

We don't want this slow speed. We want 8 MHz. We need to "unprogram" the CKDIV8 bit, to make it stop dividing the oscillator by 8.

All we have to do is to write a new 8-bit value to the Low Fuse Byte.  Let's calculate the new value.

| |Binary|Hex|
|---|---|---|
|Old Value|0b01100100|0x64|
|New value|0b11100100|0xE4|

So: we need to write 0xE4 to the Low Fuse byte.

### AVRDUDE

Arduino IDE installs (and uses) a handy command-line tool for reading and writing the memory of an AVR microcontroller. Its name is "avrdude". It resides in the "installation folder" of the Arduino IDE. On my Mac, the installation folder is the "Arduino15" folder inside my user account's Library.

Here is a link to [a fairly complete reference for avrdude](https://www.nongnu.org/avrdude/user-manual/avrdude_3.html).

The following spells out how I got avrdude to work in 2022, having Arduino IDE 1.8.15 installed on a Mac, OS version 11.6.2 Big Sur. 

Launching avrdude involves typing a string of parameters on the command line in a terminal window. I like to prepare the command in a text editor.

Begin with the full path to the avrdude executable file.

```/Users/<account_name>/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/avrdude```

Add the -C option followed by the full path to the avrdude.conf configuration file.

```-C/Users/<account_name>/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf```

Then I like to include the "verbose output" option.

```-v```

The "-p" option specifies the type of AVR chip. This can be looked up in the avrdude.conf file, or in the reference linked to above. For ATtiny2313 it is "t2313".

```-pt2313```

The type of programmer being used must be specified with the "-c" option. I am using an "Arduino as ISP" as explained in [a tutorial hosted on on the arduino.cc web site](https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP). For Arduino as ISP, the avrdude specifier is:

```-cstk500v1```

The next two parameters relate to the serial port being used by the programmer, in this case an Arduino Uno board. First, the "-P" option identifies which serial port is being used, like this: ```-P<your_programmer's_actual_serial_port>```.  On my machine it was:

```-P/dev/cu.usbmodem14201```

Finally, the "-b" option sets the baud rate for data communications. Using Arduino as ISP, this setting apparently needs to be 19200.

```-b19200```

Putting it all together in the text editor gives a long string to copy and paste onto the command line of a terminal window. The following string will *read* the memory of an ATtiny2313 and print out useful information in the terminal window.

```/Users/<account_name>/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/avrdude -C/Users/<account_name>/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf -v -pt2313 -cstk500v1 -P/dev/cu.usbmodem14201 -b19200```

Writing a value with avrdude involves stringing several fields together in a colon-delimited string. I list the fields here: -Ulfuse:w:0xe4:m

|Field|What it means|
|---|---|
|-U| specifies the memory to access |
|lfuse| which memory to write, in this case the low fuse byte |
|w| means to write to the specified memory |
|0xe4| the byte value to write |
|m| means "immediate mode"; write the byte given on the command line |

The fields come together, with their delimiting colon characters, as: ```-Ulfuse:w:0xe4:m```. The complete avrdude command line string for writing "0xe4" to the low byte of the ATtiny2313 is:

```/Users/<account_name>/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/avrdude -C/Users/<account_name>/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf -v -pt2313 -cstk500v1 -P/dev/cu.usbmodem14201 -b19200 -Ulfuse:w:0xe4:m```