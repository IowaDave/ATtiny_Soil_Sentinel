# Building the ATtiny Soil Sensor
An "Arduino" project without the Arduino!

The web serves up many examples where an Arduino is used to check a soil moisture sensor and flash an LED when things get too dry. 

I wondered: how much could I learn to do the same project with only a &ldquo;bare&rdquo; microcontroller, such as an ATmega328P pried loose from an Arduino Uno? Better yet, with one of the ATtiny chips instead! A lot, as it turned out. 

Now I'm writing it up. You can read the following articles in any order you choose:

## Articles in this Series
<ul>
  <li><h3>Home **<< you are here**</h3></li>  
  {% for post in site.posts %}
    <li>
      <!-- <h3><a href="{{site.baseurl}}{{ post.url }}">{{ post.title }}</a></h3> -->
      <h3>[{{ post.title }}]({{site.baseurl}}{{ post.url }})</h3>
    </li>
  {% endfor %}
</ul>

[Why Not Use an Arduino?](https://iowadave.github.io/ATtiny_Soil_Sentinel/posts/2022-06-25-why-not-use-an-arduino)

[About the State Machines](https://iowadave.github.io/ATtiny_Soil_Sentinel/posts/2022-06-28-about-the-state-machines)
