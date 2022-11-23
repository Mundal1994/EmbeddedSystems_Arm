#include "mbed.h"

#define SPEAKER p21
#define AIN1 p15
#define AIN2 p16

// Define the PWM speaker output
PwmOut speaker(SPEAKER);

// Define analog inputs
AnalogIn ain1(AIN1);
AnalogIN ain2(AIN2);

//Define variables
float val1;
float val2;
float i;

/*  saw tooth wave calculation   */
void    saw_tooth_wave()
{
    for (i = 0; i < 1; i += 0.05)
    {
        speaker.period(0.003125-(0.002*val1));
        speaker = i * 0.05 * val2;
    }
}

/*  triangle wave calculation   */
void    triangle_wave()
{
    for (i = 0; i < 1; i += 0.05)
    {
        speaker.period(0.003125-(0.002*val1));
        speaker = i * 0.05 * val2;
    }
    for (i = 1; i > 0; i -= 0.025)
    {
        speaker.period(0.003125-(0.002*val1));
        speaker = i * 0.05 * val2;
    }
}

int main(){
    while(1){
        val1 = ain1.read();
        val2 = ain2.read();

        // Create a saw-tooth sound wave
        // the period and volume are adjustable using the potentiometers
        saw_tooth_wave();

        // create a triangle sound wave
        // triangle_wave();
        wait_ms(100);
    }
}

/*
to create a saw-tooth wave we could do
for(i = 0; i < 1; i += 0.05)
    out = i;
    
to create a traingle wave use two for loops:

for (i = 0; i < 1; i += 0.05)
    out = i;
for (i = 1; i > 0; i -= 0.025)
    out = i;


*/
