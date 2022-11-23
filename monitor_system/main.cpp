#include "mbed.h"

#define SPEAKER p21
#define AIN1 p15
#define AIN2 p16

// Define the PWM speaker output
PwmOut speaker(SPEAKER);

// Define analog inputs
AnalogIn level(AIN1);
AnalogIn temperature(AIN2);

//Define variables
float val_level;
float val_temp;
float i;

void    status_tone()
{
    float lower;
    float upper;
    
    lower = 1.0 / 3.0;
    upper = 2.0 / 3.0;
    printf("check temperature %f and tank level %f %f\n", val_temp, val_level, lower);
    if (val_level < lower)
    {
        printf("tank level %f too low\n", val_level);
        //flashing LED, frequency modulated
    }
    else if (val_temp < lower)
    {
        printf("temp %f too low\n", val_temp);
        // single beeping tone
    }
    else if (val_temp > upper)
    {
        printf("temp %f too high\n", val_temp);
        //two-tone
    }
    else
    {
        printf("OK\n");
        // steady continuous tone
    }
    /*
    if temperature is too low
        flashing LED, frequency modulated
    else if tank full and temp too high(upper third of temperature range)
        two-tone
    else if tank full and temp is good (middle third of temperature range)
        steady continuous tone
    else
        single beeping tone
    */
}

int main(){
    int i;

    i = 0;
    while(1){
        // only read every two seconds?
        if (!i)
        {
            printf("check temperature and tank level\n");
            val_level = level.read();
            val_temp = temperature.read();
        }

        status_tone();
        wait_ms(100);
        if (i < 20)
            i++;
        else
            i = 0;
    }
}
