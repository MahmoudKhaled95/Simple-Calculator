/******************************************************************************
 *
 * [File Name]: calculator_main.c
 *
 * [Description]: Source file for Calculator Application
 *
 * [Micro-controller]: Atmega16
 *
 * [Author]: Mahmoud Khaled
 *
*******************************************************************************/


#include "keypad.h"
#include "lcd.h"
#include <util/delay.h>


uint16 g_firstNum = 0, g_secondNum = 0;
uint8 g_operation;
uint16 g_result = 0;
uint8 g_key = 0;

void APP_welcomeScreen(void);

void APP_selectOperation(void);

int main(void)
{
	LCD_init();


	APP_welcomeScreen();

	LCD_displayStringRowColumn(0,0,"Simple Calculator");
	LCD_moveCursor(1,0);
	while(1)
	{
		/* Get first Number */
		g_key = KEYPAD_getPressedKey();

		while(g_key >= 0 && g_key <= 9){
			_delay_ms(500); /* Press time */
			LCD_intgerToString(g_key);
			g_firstNum = g_key + g_firstNum * 10;
			g_key = KEYPAD_getPressedKey();
			_delay_ms(500); /* Press time */
		}
		LCD_displayCharacter(' ');
		g_operation = g_key;
		LCD_displayCharacter(g_operation);
		LCD_displayCharacter(' ');

		/* Get second Number */
		g_key = KEYPAD_getPressedKey();
		while(g_key >= 0 && g_key <= 9){
			_delay_ms(500); /* Press time */
			LCD_intgerToString(g_key);
			g_secondNum = g_key + g_secondNum * 10;
			g_key = KEYPAD_getPressedKey();
			_delay_ms(500); /* Press time */
		}

		/* Once the user press = button the answer will be appear on LCD */
		if(g_key == '=')
		{
			LCD_displayCharacter(' ');
			LCD_displayCharacter('=');
			LCD_displayCharacter(' ');
			APP_selectOperation();
			LCD_intgerToString(g_result);
		}

		/* In case the user press ON/C button */
		if(g_key == 13)
		{
			LCD_clearScreen();
			g_firstNum = 0;
			g_secondNum = 0;
			LCD_displayStringRowColumn(0,0,"Simple Calculator");
			LCD_moveCursor(1,0);
		}
	}
}










void APP_welcomeScreen(void)
{
	LCD_clearScreen();
	LCD_displayString("Welcome to Calculator Application");
	_delay_ms(1000);
	LCD_clearScreen();
}


void APP_selectOperation(void)
{
	switch(g_operation)
	{
	case '+':
		g_result = g_firstNum + g_secondNum;
		break;
	case '-':
		g_result = g_firstNum - g_secondNum;
		break;
	case '*':
		g_result = g_firstNum * g_secondNum;
		break;
	case '/':
		g_result = g_firstNum + g_secondNum;
		break;
	}
}
