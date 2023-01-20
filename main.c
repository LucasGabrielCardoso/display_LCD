/*
 * File:   main.c
 * Author: LucasGabriel
 *
 * Created on December 9, 2022, 9:05 PM
 */


#include <xc.h>
#include "system.h"
#include "screen.h"

#define DEBOUNCE_TIME       20

void main(void) 
{
    __debug_break();
    System_Initializer();
    LCD_Set_Latin_Char();    
    
    uint8_t flag_SELECIONA_MENU             = 0;
    uint8_t flag_ENTER_MENU                 = 0;
    uint8_t flag_RETORNA_MENU               = 0;
    uint8_t flag_STATE_MENU                 = 1;
    uint8_t flag_RETORNA_MENU_state         = 1;
    uint8_t flag_SELECIONA_MENU_state       = 1;
    uint8_t flag_ENTER_MENU_state           = 1;
    
    Tela_Menu();
    Cursor_Select(flag_STATE_MENU);
    
    while(true)
    {
        //Debounce SELECIONA_MENU Button
        if(0 == SELECIONA_MENU)
        {
            __delay_ms(DEBOUNCE_TIME);
            flag_SELECIONA_MENU =   1;
        }
        else if(1 == SELECIONA_MENU)
        {
            __delay_ms(DEBOUNCE_TIME);
            flag_SELECIONA_MENU             =   0;
            flag_SELECIONA_MENU_state       =   1;
        }
        //Debounce ENTER_MENU Button
        if(0 == ENTER_MENU)
        {
            __delay_ms(DEBOUNCE_TIME);
            flag_ENTER_MENU =   1;
        }
        else if(1 == ENTER_MENU)
        {
            __delay_ms(DEBOUNCE_TIME);
            flag_ENTER_MENU         =   0;           
        }
        //Debounce RETORNA_MENU Button
        if(0 == RETORNA_MENU)
        {
            __delay_ms(DEBOUNCE_TIME);
            flag_RETORNA_MENU =   1;
        }
        else if(1 == RETORNA_MENU)
        {
            __delay_ms(DEBOUNCE_TIME);
            flag_RETORNA_MENU       =   0;
            flag_RETORNA_MENU_state =   1;
        }
        
        //APP
        
        if((1 == flag_SELECIONA_MENU)&&(1 == flag_SELECIONA_MENU_state)&&(1 == flag_ENTER_MENU_state))
        {
            1 != flag_STATE_MENU ? (flag_STATE_MENU = 1) : (flag_STATE_MENU = 2); 
            Cursor_Select(flag_STATE_MENU);
            flag_SELECIONA_MENU_state =   0;
        }
        else if((1 == flag_ENTER_MENU)&&(1 == flag_ENTER_MENU_state))
        {
            flag_ENTER_MENU_state =   0;
            if(1 == flag_STATE_MENU)
                Tela_Option_1();
            else if(2 == flag_STATE_MENU)
                Tela_Option_2();
        }  
        else if((1 == flag_RETORNA_MENU)&&(1 == flag_RETORNA_MENU_state))
        {
            Tela_Menu();
            Cursor_Select(flag_STATE_MENU);
            flag_RETORNA_MENU_state = 0;
            flag_ENTER_MENU_state   = 1; 
        }
    }
    return;
}
