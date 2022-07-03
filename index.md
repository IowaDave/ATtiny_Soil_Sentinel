# Building the ATtiny Soil Sensor
An "Arduino" project without the Arduino!

The web serves up many examples where an Arduino is used to check a soil moisture sensor and flash an LED when things get too dry. 

I wondered: how much could I learn by doing the same project with only a &ldquo;bare&rdquo; microcontroller, such as an ATmega328P pried loose from an Arduino Uno? Better yet, with one of the ATtiny chips instead! A lot, as it turned out. 

Now I'm writing it up. You can read the following articles in any order you choose:

<!-- Comment-out the following ------------
## Articles in this Series
<ul>
  {% for post in site.posts %}
    <li>
      <h5><a href="{{site.baseurl}}{{ post.url }}">{{ post.date | date: "%Y-%m-%d" }} : {{ post.title }}</a></h5>
    </li>
  {% endfor %}
</ul>
------------------- end comment    -->
Trying this new approach to listing the posts:
{% include post_list.html %}

## Overview
The project combines a microprocessor (MPU) with a capacitive soil sensor, a trim potentiometer and an LED. 

The sensor and the trim pot supply voltage signals to the analog comparator input pins of the MPU. 

Adjusting the trim pot establishes the voltage level that distinguishes moist from dry. 

The MPU compares the voltage from the trim pot with that from the sensor. Different flashing patterns for the LED indicate the results. 

A user can gauge whether soil surrounding the sensor is moist or dry by observing the LED. 

## Low Power for Longer Battery Life
The circuit aims to minimize power consumption. 

Power is supplied to the sensor and to the trim pot from an output pin of the MPU. The pin is turned on only briefly, long enough to take a reading, then turned off again. 

The MPU is kept in power-down sleep most of the time. It uses almost no power then.

A interrupt from the watchdog timer in the MPU wakes the device periodically. The interrupt service routine (ISR) defines operations that toggle the LED and read the sensor.

Power to the LED comes from another output pin of the MPU. When this pin is set HIGH by the ISR, the pin continues to supply current to the LED while the MPU sleeps. 

The ISR limits power consumption of the LED by turning it on for only short lengths of time, then turning it off for longer lengths of time. 

To be clear: putting the MPU into power-down sleep does not alter the states of its I/O pins. Only the firmware can change the pins.
