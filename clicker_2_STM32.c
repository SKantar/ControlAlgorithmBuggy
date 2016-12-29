/*
 * Project name:
     Escape barriers
 * Copyright:
     Sladjan Kantar, Racunarski fakultet
 * Revision History:
     20140924:
       - initial release;
 * Description:
     This is a simple mikroC project. Escape dinamic barriers using Buggy with IR Distance sensors.
 * Test configuration:
     MCU:             STM32F407VG
                      http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00037051.pdf
     Dev.Board:       clicker 2 for STM32 - ac:clicker_2_STM32
                      http://www.mikroe.com/stm32/clicker-2/
     Oscillator:      HSI-PLL, 120.000MHz
     Ext. Modules:    None.
     SW:              mikroC PRO for ARM
                      http://www.mikroe.com/mikroc/arm/
 */

#include "ir_distance.h"
#include "buggy.h"

//0 none
//1 forward
//2 backward
//3 right
//4 left

int direction;

int new_direction;
int old_direction;

// pin definitions
sbit LD1 at ODR12_GPIOE_ODR_bit;
sbit LD2 at ODR15_GPIOE_ODR_bit;

void main() {
	GPIO_Digital_Output(&GPIOE_BASE, _GPIO_PINMASK_12 | _GPIO_PINMASK_15);
	ADC1_Init();
	LD1 = 0;
	LD2 = 0;
	direction = 1;

	new_direction = 1;
	old_direction = 1;

	init_buggy();
	start_buggy();
	while( 1 )
	{
		if(direction == 1 && ir_measure_cm(10) < 30)
		{
			do{
				LD1 = 1;
				right();
				delay_ms(300);
			
				if(ir_measure_cm(10) > 40)
				{
					direction = 1;
					forward();
					delay_ms(1000);
					left();
					delay_ms(300);
					forward();
					break;
				}
				else if(ir_measure_cm(12) > 40)
				{
					direction = 2;
					backward();
					delay_ms(1000);
					right();
					delay_ms(300);
					backward();
					break;
				}
			}while(1);
			LD1 = 0;
		}

		if(direction == 2 && ir_measure_cm(12) < 30)
		{
			do{
				LD2 = 1;
				left();
				delay_ms(300);
			
				if(ir_measure_cm(12) > 40)
				{
					direction = 2;
					backward();
					delay_ms(1000);
					right();
					delay_ms(300);
					backward();
					break;	
				}
				else if(ir_measure_cm(10) > 40)
				{
					direction = 1;
					forward();
					delay_ms(1000);
					left();
					delay_ms(300);
					forward();
					break;
				}
			}while(1);
			LD2 = 0;
		}
	}
}