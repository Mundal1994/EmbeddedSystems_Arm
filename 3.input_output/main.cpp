// Solution to mbed MOOC Module 3 project

#include "mbed.h"

/*  initialize input and output    */
DigitalIn start(p5);
DigitalIn stop(p6);
DigitalIn guard(p7);
DigitalIn temp(p8);
DigitalOut ready(p9);
DigitalOut running(p10);
DigitalOut error(p11);
DigitalOut exces(p12);

void ControlLED_DigitalIO()
{
    if (guard)
        error = guard;
    else
        error = 0;
    if (temp)
        exces = temp;
    else
        exces = 0;
    if (!stop && !guard && !temp)
    {
        if (start)
        {
            ready = 0b0000;
            if (!running)
                running = start;
            printf("motor start\n");
        }
        if (!running)
        {
            if (!ready)
                ready = 1;
            else
                ready = 0;
        }
    }
    else
    {
        if (running)
        {
            running = 0;
            if (guard)
            {
                printf("motor stopped due to machine stop sensor\n");
                wait (0.5);
            }
            else if (temp)
            {
                printf("motor stopped due to guarderature sensor\n");
                wait (0.5);
            }
            else
                printf("motor stop\n");
        }
        
    }
}

int main(void)
{
    while (1)
    {
        ControlLED_DigitalIO();
        wait (0.25);
    }
}
