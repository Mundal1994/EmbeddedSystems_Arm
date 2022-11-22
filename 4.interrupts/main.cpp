#include "mbed.h"

/*  define outputs */
BusOut seats(p15, p14, p13, p12, p11, p10, p9, p8);

/*  define interrupt inputs */
InterruptIn parent(p5);
InterruptIn child(p6);
InterruptIn alarm(p7);

/*  define counters */
volatile unsigned int barber1;
volatile unsigned int barber2;
volatile unsigned int barber3;
volatile unsigned int parent_count;
volatile unsigned int child_count;
volatile unsigned int occupied;

/*  assigns x amount of people to the waiting room  */
void    assign_seat(unsigned int people)
{
    int i;
    
    i = 0;
    while (i < people)
    {
        switch(occupied)
        {
            case 0:
                seats = 0b00000001;
                break;
            case 1:
                seats = 0b00000011;
                break;
            case 2:
                seats = 0b00000111;
                break;
            case 3:
                seats = 0b00001111;
                break;
            case 4:
                seats = 0b00011111;
                break;
            case 5:
                seats = 0b00111111;
                break;
            case 6:
                seats = 0b01111111;
                break;
            case 7:
                seats = 0b11111111;
                break;
        }
        occupied++;
        i++;
    }
}

/*  removes one person from the waiting room    */
void    free_seat()
{
    switch(occupied)
    {
        case 1:
            seats = 0b00000000;
            break;
        case 2:
            seats = 0b00000001;
            break;
        case 3:
            seats = 0b00000011;
            break;
        case 4:
            seats = 0b00000111;
            break;
        case 5:
            seats = 0b00001111;
            break;
        case 6:
            seats = 0b00011111;
            break;
        case 7:
            seats = 0b00111111;
            break;
        case 8:
            seats = 0b01111111;
            break;
    }
    occupied--;
}

/*
if an adult enters the store they will be assigned to
barber1 or barber2 if free or put to wait in the waiting room
*/
void    parent_handler()
{
    if ((!barber1 || !barber2) && !parent_count)
    {
        if (!barber1)
            barber1 = 13;
        else
            barber2 = 13;
    }
    else
    {
        if (occupied < 8)
        {
            parent_count++;
            assign_seat(1);
        }
    }
}

/*
if a child enters the store they will either be assigned
to barber3 if free or put in the waiting room with their parent
*/
void    child_handler()
{
    if (!barber3 && !child_count)
    {
        barber3 = 13;
        assign_seat(1);
    }
    else
    {
        if (occupied < 7)
        {
            child_count++;
            assign_seat(2);
        }
    }
}

/*  resets everything to zero   */
void    everybody_leaves()
{
    seats = 0b00000000;
    barber1 = 0;
    barber2 = 0;
    barber3 = 0;
    parent_count = 0;
    child_count = 0;
    occupied = 0;
}

/* 
if barber is with a costumer their counter will be reduced by 1
each second
*/
void    barber_with_costumer()
{
    if (barber1)
        barber1 = barber1 - 1;
    if (barber2)
        barber2 = barber2 - 1;
    if (barber3)
    {
        barber3 = barber3 - 1;
        if (!barber3)
            free_seat();
    }
}

/*
printing which barbers are available to standard output along with
additional information about the people in the waiting room
*/
void    print_barber()
{
    if (barber1)
        printf("barber1 with costumer - minutes left: %d\n", barber1);
    else
        printf("barber1 available\n");
    if (barber2)
        printf("barber2 with costumer - minutes left: %d\n", barber2);
    else
        printf("barber2 available\n");
    if (barber3)
        printf("barber3 with costumer - minutes left: %d\n", barber3);
    else
        printf("barber3 available\n");
    printf("p: %d, c: %d, o: %d\n", parent_count, child_count, occupied);
}

/*  assigns a barber a new costumer */
void    assign_costumer()
{
    if (!barber1 || !barber2)
    {
        if (parent_count)
        {
            parent_count--;
            free_seat();
            if (!barber1)
                barber1 = 13;
            else
                barber2 = 13;
        }
    }
    else if (!barber3)
    {
        if (child_count)
        {
            child_count--;
            free_seat();
            barber3 = 13;
        }
    }
}

int main()
{
    // Initial turn off all LEDs
    everybody_leaves();

    // Interrupt handlers
    parent.rise(&parent_handler);
    child.rise(&child_handler);
    alarm.rise(&everybody_leaves);

    // wait 100 ms
    while (1)
    {
        barber_with_costumer();
        print_barber();
        while ((parent_count && (!barber1 || !barber2)) || (child_count && !barber3))
            assign_costumer();
        wait_ms(1000);
    }
}
