# monitor_system

Using the mbed simulator to generate sound, using analog I/O and PWM(pulse width modulation)

The assignments are made with Mbed online compiler and Mbed simulator

## ASSIGMENT

Develop a monitoring (but not control) system for a heating tank in an industrial process. There are two sensors in the tank, one for temperature and the other for level. Four output states must be detected, each triggering a different audible status tone: 

            Tank is full, temperature too high (upper third of temperature range) : two-tone  
            Tank is full, temperature is good (middle third of temperature range): steady continuous tone 
            Tank is full, temperature too low (lower third of temperature range): single beeping tone 
            Tank level is too low (tank less than three quarters full), any temperature: frequency-modulated “warble”  tone, flashing LED

Sensors must be tested at least once every two seconds. 

Use potentiometers for tank level and temperature, and the Pwm speaker to generate the audible status signals.
