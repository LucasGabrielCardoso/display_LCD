/*
 * File:   sistem.c
 * Author: LucasGabriel
 *
 * Created on 10 de Dezembro de 2022, 20:15
 */


#include <xc.h>
#include "system.h"

/******************************************************************************/
/*                     Internal Function Declaration                          */
/******************************************************************************/
void IO_Initializer(void);


/******************************************************************************/
/*                              Function Declaration                         */
/******************************************************************************/
void System_Initializer(void) 
{
    IO_Initializer();
    LCD_Initializer();
    return;
}

void IO_Initializer(void)
{
    //Clearing outputs
    PORTA           =   0x00;
    PORTB           =   0x00;
    PORTC           =   0x00;
    PORTD           =   0x00;
    
    //Clearing outputs
    LATA            =   0x00;
    LATB            =   0x00;
    LATC            =   0x00;
    LATD            =   0x00;
    
    //Setting unused ports in Tri-state mode
    TRISA           =   0xFF;
    TRISB           =   0xFF;
    TRISC           =   0x0F;           //Setting RC4, RC5, RC6 and RC7 like outputs
    TRISD           =   0xF3;           //Setting RD2 and RD3 like output
    
    //Setting internal pull-ups
    INTCON2bits.RBPU    =   0b0;
    
    //Disable unused Peripheral
    CCP1CON             =   0x00;
    CCP2CON             =   0x00;
}

