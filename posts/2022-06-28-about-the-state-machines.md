# About the State Machines
How the code knows what to do the next time the MCU wakes up

## Articles in This Series

## State Machines in the Code
The watchdog timer wakes the MPU up at 1/4-second intervals. This event is due to a phenomenon built into the silicon of the chip: an interrupt. Each time the interrupt "fires", code execution jumps to an interrupt service routine, or ISR.

The concepts of watchdog timer and ISRs belong in an article of their own and will not be discussed much more here. The main things to know about them are:

1. the **watchdog timer** is always counting up from 0 to 255. 
2. Each time it hits 255 it starts over again at zero. This event is called **overflow**.
3. You can set how long it takes the watchdog timer to overflow. This project sets it to 1/4 of a second. 
4. The **watchdog timer interrupt** happens *in hardware* each time the timer overflows, such as every 1/4 of a second.
5. A watchdog timer interrupt can **wake up the MPU** from even the deepest, most energy-saving, "power down" level of sleep.
6. The **watchdog overflow ISR** is a subroutine that runs automatically each time the watchdog timer interrupt wakes up the chip.
  
So, every 1/4 of a second our chip is going to wake up and execute the code in its watchdog timer interrupt service routine.

ISRs should be brief and execute fast. Most of the time, the ISR will go something like this:

1. Is it time to check the sensor?
    * No, so don't check it.
2. Is it time to do something with the LED?
    * No, so don't change it.
3. Decrement the time remaining on the sensor and the LED.

Those instructions boil down to about 10 lines of assembly language code, which execute in about 10 CPU clock cycles, or 1/800,000th of a second. That's pretty quick.

Eventually the one of the countdowns will reach zero. Then, the ISR must execute one of its Finite State Machines. Sounds wicked, right?

The one for the LED gives a simple example. Think about it. An LED can be either:
<ol type="a">
  <li>On, waiting to be turned off, or</li>
  <li>Off, waiting to be turned on.</li>
</ol>

Now think again. We have two different flashing intervals, depending on whether the soil is moist or dry. So, we actually have four, different combinations of soil moisture + LED status:
1. moist + waiting to be turned on,
2. moist + waiting to be turned off,
3. dry + waiting to be turned on, and
4. dry + waiting to be turned off.

A code writing technique called Finite State Machine suits this type of situation well. It has two parts:
* an *enum* having a member named for each one of the different states, and
* a *switch* statement that defines *case* code for each member of the enum.

Switch statements act like a series of *if-then* statements, but can be more efficient because *switch* boils down to a jump table. If you don't know what that means, you can look it up, or just take my word for it.

Each time the ISR enters the state machine, it runs only the case code corresponding to the value of the enum. For example, MOIST_ON is one of the named states for the LED in this project. In that case, the ISR does just three things. It:
1. turns the LED on,
2. sets the time remaining on the LED to one second,
3. and changes the LED state to MOIST_OFF.

One second later, the ISR enters the LED state machine again. This time it jumps to the MOIST_OFF code, which:
1. turns the LED off,
2. sets the time remaining on the LED to 9 seconds,
3. and changes the LED state to MOIST_ON.

Again, these instructions take almost no time to complete. Yet, the result is an LED that shines for 1 second every ten seconds. 

The LED state machine in the project implements two additional states: TESTING, which toggles the LED every time through the ISR; and INACTIVE, which simply turns the LED off.

The other state machine in this project regulates the operation of the sensor. It defines four states:
1. PREPARE = energize the sensor and allow time for it to stabilize
2. TEST = read the sensor, then power it down; finally, set the appropriate WAIT_ state
3. WAIT_MOIST = set a delay of 15 minutes before the next sensor operation, put the LED into the MOIST_ON state, put the sensor into PREPARE state
4. WAIT_DRY = set a delay of 15 seconds before the next sensor operation, put the LED into the DRY_ON state, put the sensor into PREPARE state

Listing the different cases in the two *switch* statements makes the ISR look lengthy. Look again.

Two things stand out. First, the amount of code that actually gets run is very short, usually just a few lines, because the *switch* statements jumps to the right *case*. Second, the code in each *case* is always telling the ISR what to do *the next time* it enters the state machine.

A more complete illustration of the ISR goes something like this:

1. Is it time to check the sensor?
    * No, so don't check it; or
    * Yes, enter the sensor state machine
        * What state am I in?
        * Jump to the code for that case. 
2. Is it time to do something with the LED?
    * No, so don't change it; or
    * Yes, enter the LED state machine
        * What state am I in?
        * Jump to the code for that case. 
3. Decrement the time remaining on the sensor and the LED.

Conclusion: most often there will still be time remaining on the sensor or the LED. The answers to "Is it time?" will be "No", and the ISR concludes rapidly. 

However, now and then the countdown reaches zero and answer will be "Yes". In those cases, the ISR executes the relevant *case*. Code in that *case* peforms the actions defined for the current state, establishes the next state, then restarts the countdown. 

Finite State Machines do a nice job of organizing and self-documenting the code to handle a list of different situations that can come up, when all of the situations are known and can be be defined in advance.
