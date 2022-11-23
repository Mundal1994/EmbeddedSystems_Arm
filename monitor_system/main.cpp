#include "mbed.h"

#define SPEAKER p21
#define AIN1 p15
#define AIN2 p16

// Define the PWM speaker output
PwmOut speaker(SPEAKER);

// Define analog inputs
AnalogIn level(AIN1);
AnalogIn temperature(AIN2);
DigitalOut blink(p5);

//Define variables
float val_level;
float val_temp;

void    stop_blik()
{
    if (blink)
        blink = !blink;
}

void    play(float hival, float loval)
{
    speaker.period (hival); 
    wait_ms (500); 
    speaker.period (loval); 
    wait_ms (500); 
}

void    check_temperature(float upper)
{
    float lower;
    
    lower = 1.0 / 3.0;
    if (val_temp < lower)
    {
        stop_blik();
        printf("temp %f too low\n", val_temp);
        // single beeping tone
        play(0.005, 1);
    }
    else if (val_temp > upper)
    {
        stop_blik();
        printf("temp %f too high\n", val_temp);
        // two-tone
        play(0.001, 0.005);
    }
    else
    {
        stop_blik();
        printf("tank level and temp OK!\n");
        // steady continuous tone
        play(0.002, 0.002);
    }
}

void    status_tone()
{
    float upper;
    
    upper = 2.0 / 3.0;
    if (val_level < upper)
    {
        printf("tank level %f too low\n", val_level);
        blink = !blink;
        // "warble" tone - low to high value
        for (float i = 0; i < 1; i += 0.05)
        {
            speaker.period(0.010 - (0.008 * i));
            wait_ms (50);
        }
    }
    else
        check_temperature(upper);
}

int main(){
    int check;

    blink = 0;
    check = 0;
    speaker = 0.5;
    while(1){
        if (!check)
        {
            // check tank level values
            val_level = level.read();
            val_temp = temperature.read();
        }
        status_tone();
        if (check < 1)
            check++;
        else
            check = 0;
    }
}
