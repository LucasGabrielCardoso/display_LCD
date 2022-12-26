/*
 * File:   delay.c
 * Author: LucasGabriel
 *
 * Created on December 9, 2022, 10:14 PM
 */


#include <xc.h>
#include "delay.h"
#include "device_config.h"

void Delay_ms(unsigned long int wait_time) 
{
    for(unsigned long int i = 0; i < wait_time; i++)
    {
        __delay_ms(1);
    }
}

void Delay_us(unsigned long int wait_time) 
{
    for(unsigned long int i = 0; i < wait_time; i++)
    {
        __delay_us(1);
    }
}
