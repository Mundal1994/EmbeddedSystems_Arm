#include "mbed.h"

#define SPEAKER p21
#define AIN1 p15
#define AIN2 p16

// Define the PWM speaker output
PwmOut speaker(SPEAKER);

// Define analog inputs
AnalogIn ain1(AIN1);
AnalogIn ain2(AIN2);

// Define interrupt inputs
InterruptIn saw(p5);
InterruptIn triangle(p6);
InterruptIn start(p7);
InterruptIn stop(p8);

//Define variables
float val1;
float val2;
float i;
volatile unsigned int is_saw;
volatile unsigned int is_start;

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
        //speaker.period(0.003125-(0.002*val1));
        speaker = i * 0.05 * val2;
    }
    for (i = 1; i > 0; i -= 0.025)
    {
        //speaker.period(0.003125-(0.002*val1));
        speaker = i * 0.05 * val2;
    }
}

void    saw_handler()
{
    if (!is_saw)
    {
        printf("switching to saw_tooth wave\n");
        is_saw = 1;   
    }
}

void    triangle_handler()
{
    if (is_saw)
    {
        printf("switching to triangle wave\n");
        is_saw = 0;
    }
}

void    start_handler()
{
    if (!is_start)
    {
        printf("play\n");
        is_start = 1;   
    }
}

void    stop_handler()
{
    if (is_start)
    {
        printf("paused\n");
        is_start = 0;   
    }
}

int main(){
    printf("playing saw_tooth wave\n");
    is_saw = 1;
    is_start = 1;

    // Interrupt handlers
    saw.rise(&saw_handler);
    triangle.rise(&triangle_handler);
    start.rise(&start_handler);
    stop.rise(&stop_handler);

    while(1){
        val1 = ain1.read();
        val2 = ain2.read();

        if (is_saw && is_start)
        {
            // Create a saw-tooth sound wave
            // the period and volume are adjustable using the potentiometers
            saw_tooth_wave();
        }
        else if (!is_saw && is_start)
        {
            // create a triangle sound wave
            triangle_wave();
        }
        wait_ms(100);
    }
}
