/*
 * File:   screen.c
 * Author: LucasGabriel
 *
 * Created on 23 de Dezembro de 2022, 13:24
 */


#include "screen.h"

void Tela_Menu(void) 
{
    LCD_Clear_Display();
    printf("  op  o 1        ");
    LCD_Move_Cursor(1,5);
    putch(C_CEDILHA);
    LCD_Move_Cursor(1,6);
    putch(A_TIL);
    
    LCD_Move_Cursor(2,1);
    printf("  op  o 2        ");
    LCD_Move_Cursor(2,5);
    putch(C_CEDILHA);
    LCD_Move_Cursor(2,6);
    putch(A_TIL);
}

void Tela_Option_1(void)
{
    LCD_Clear_Display();
    printf("op  o 1");
    LCD_Move_Cursor(1,3);
    putch(C_CEDILHA);
    LCD_Move_Cursor(1,4);
    putch(A_TIL);    
    
    LCD_Move_Cursor(2,1);
    printf("voltar<<press B2");
}

void Tela_Option_2(void)
{
    LCD_Clear_Display();
    printf("op  o 2");
    LCD_Move_Cursor(1,3);
    putch(C_CEDILHA);
    LCD_Move_Cursor(1,4);
    putch(A_TIL);    
    
    LCD_Move_Cursor(2,1);
    printf("voltar<<press B2");  
}

void Cursor_Select(unsigned char line)
{
    static unsigned char state = 2;
    
    LCD_Move_Cursor(state,1);
    printf(" ");
    LCD_Move_Cursor(state,11);
    printf("       ");
    
    LCD_Move_Cursor(line,1);
    printf(">");
    LCD_Move_Cursor(line,11);
    printf("[ENTER]");
    
    state = line;
}
