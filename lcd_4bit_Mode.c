/*
 * File:   lcd.c
 * Author: LucasGabriel
 *
 * Created on December 9, 2022, 9:06 PM
 */

#include "lcd_4bit_Mode.h"
#include "../../system_config.h"

/******************************************************************************/
/*                             Display Defines                                */
/******************************************************************************/
//Set DDRAM address
#define SET_DDRAM_ADDRESS           0x80

//Set CGRAM Address
#define SET_CGRAM_ADDRESS           0x40

//Function Set
#define DATA_8_BIT_MODE             0x30
#define TWO_LINE_DISPLAY            0x28
#define FIVE_BY_TEN_DOTS_MATRIX     0x24
#define DATA_4_BIT_MODE             0x20

//Cursor or Display Shift
#define DISPLAY_SHIFT               0x18
#define SHIFT_TO_RIGHT              0x14

//Display on/off
#define DISPLAY_ON                  0x0C
#define CURSOR_ON                   0x0A
#define BLINKING_CURSOR_ON          0x09
#define DISPLAY_OFF                 0x08

//Entry mode set
#define MOVE_FOWARD                 0x06
#define SHIFT_ENTYRE_DISPLAY        0x05

//Return home
#define RETURN_HOME                 0x03 //This instruction takes a bit more time (~1.52 ms)
                                         //therefore, always put a Delay_ms(2) after instruction
//Clear Display
#define CLEAR_DISPLAY               0x01 //This instruction takes a bit more time (~1.52 ms)
                                         //therefore, always put a Delay_ms(2) after instruction

//Set the level in the display Port
#define LCDSetPort(instruction)     do{D7 = (0x80==(instruction&0x80));\
                                       D6 = (0x40==(instruction&0x40));\
                                       D5 = (0x20==(instruction&0x20));\
                                       D4 = (0x10==(instruction&0x10));}while(0)

/******************************************************************************/
/*                        Display Ports Definitions                           */
/******************************************************************************/
//#define D7
//#define D6                 ///////////////////////////////////////////
//#define D5                 //BEFORE USE THIS LIBRARY IS NECESSARY ////
//#define D4                 //TO MEKE DISPLAY PORT DEFINIES        ////
//#define EN                 ///////////////////////////////////////////
//#define RS

/******************************************************************************/
/*                       Display internal Functions                            */
/******************************************************************************/



/******************************************************************************/
/*                               Display Functions                            */
/******************************************************************************/

void LCD_Set_Port(unsigned char instruction)
{
    D7 = (0x80==(instruction&0x80));
    D6 = (0x40==(instruction&0x40));
    D5 = (0x20==(instruction&0x20));
    D4 = (0x10==(instruction&0x10));
}

void LCD_Instruction(unsigned char instruction)
{
    RS = 0;
    EN = 1;
   
    LCDSetPort(instruction);
    
    EN = 0;
    __delay_us(45);
    
    EN = 1;
    
    instruction <<= 4;
    LCDSetPort(instruction);
    
    EN = 0;
    __delay_us(45);
}

void LCD_Move_Cursor(unsigned char line, unsigned char column)
{
    if((1 > column) || (20 < column))         return;
    switch(line)
    {
        case 1:
            LCD_Instruction(0x80+column-1);
            break;
        case 2:
            LCD_Instruction(0xC0+column-1);
            break;
        case 3:
            LCD_Instruction(0x94+column-1);
            break;
        case 4:
            LCD_Instruction(0xD4+column-1);
            break;
        default:
            break;
    }
}

void LCD_Clear_Display(void)
{
    LCD_Instruction(CLEAR_DISPLAY);
    __delay_ms(2);    
}

void LCD_Return_Home(void)
{
    LCD_Instruction(RETURN_HOME);
    __delay_ms(2);    
}

void putch(char data)
{
    RS = 1;   
    EN = 1;
    
    LCDSetPort(data);

    EN = 0;
    __delay_us(45);

    EN = 1;
    
    data <<= 4;
    LCDSetPort(data);
    
    EN = 0;
    __delay_us(45);      
}

void LCD_Set_New_Simbol(unsigned char *simbol, unsigned char simbol_address)
{
    LCD_Instruction(SET_CGRAM_ADDRESS|simbol_address);
    
    for(unsigned char i=0; 8>i; i++)
        putch(*(simbol++));
    
    LCD_Instruction(SET_DDRAM_ADDRESS);
}

void LCD_Set_Latin_Char(void)
{
    uint8_t c_cedilha[8] = {0b00000000,
                            0b00000000,
                            0b00001110,
                            0b00010000,
                            0b00010001,
                            0b00001110,
                            0b00000100,
                            0b00001100}; 
    LCD_Set_New_Simbol(c_cedilha,0);

    uint8_t a_til[8]    =  {0b00001101,
                            0b00010010,
                            0b00000000,
                            0b00001110,
                            0b00000001,
                            0b00001111,
                            0b00010001,
                            0b00011111};
    LCD_Set_New_Simbol(a_til,8);
    
    uint8_t a_agudo[8]  =  {0b00000010,
                            0b00000100,
                            0b00000000,
                            0b00001110,
                            0b00000001,
                            0b00001111,
                            0b00010001,
                            0b00011111};
    LCD_Set_New_Simbol(a_agudo,16);
}

void LCD_Initializer()
{    
    __delay_ms(40);
    RS = 0;
    
    EN = 1;
    LCDSetPort(DATA_8_BIT_MODE);
    EN = 0;
    __delay_us(45);
    
    __delay_ms(5);
    
    EN = 1;
    LCDSetPort(DATA_8_BIT_MODE);
    EN = 0;
    __delay_us(45);
    
    __delay_us(500);
    
    EN = 1;
    LCDSetPort(DATA_8_BIT_MODE);
    EN = 0;
    __delay_us(45); 

    EN = 1;    
    LCDSetPort(DATA_4_BIT_MODE);
    EN = 0;
    __delay_us(45);        
    
    LCD_Instruction(DATA_4_BIT_MODE|TWO_LINE_DISPLAY);
    LCD_Instruction(DISPLAY_ON);
    LCD_Instruction(CLEAR_DISPLAY);
    __delay_ms(2);
    LCD_Instruction(MOVE_FOWARD);
}