/*******************************************************************************
* Title                 :   Buggy
* Filename              :   buggy.h
* Author                :   Sladjan Kantar
* Origin Date           :   27/12/2016
* Notes                 :   None
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "buggy.h"

sbit BREAK_LAMPS at GPIOE_ODR.B1;
sbit HEAD_LAMPS at GPIOE_ODR.B3;
sbit TURN_L at GPIOC_ODR.B4;
sbit TURN_R at GPIOE_ODR.B2;
sbit MAIN_BEAM at GPIOB_ODR.B6;

unsigned int SPEED_L;
unsigned int SPEED_R;

unsigned int PWM_A_PERIOD;
unsigned int PWM_B_PERIOD;
unsigned int PWM_C_PERIOD;
unsigned int PWM_D_PERIOD;



/******************************************************************************
* Function Definitions
*******************************************************************************/
void init_buggy() {
  GPIO_Digital_Output (&GPIOE_BASE, _GPIO_PINMASK_1 | _GPIO_PINMASK_2 | _GPIO_PINMASK_3);
  GPIO_Digital_Output (&GPIOB_BASE, _GPIO_PINMASK_6);
  GPIO_Digital_Output (&GPIOC_BASE, _GPIO_PINMASK_4);

  PWM_A_PERIOD = PWM_TIM4_Init(20000);
  PWM_B_PERIOD = PWM_TIM4_Init(20000); //PWM_A_PERIOD;
  PWM_C_PERIOD = PWM_TIM9_Init(20000);
  PWM_D_PERIOD = PWM_TIM3_Init(20000);

  break_buggy();
}

void break_buggy() {
  SPEED_L = 0;
  SPEED_R = 0;
  PWM_TIM4_Set_Duty(0,  _PWM_NON_INVERTED, _PWM_CHANNEL3);
  PWM_TIM4_Set_Duty(0,  _PWM_NON_INVERTED, _PWM_CHANNEL4);
  PWM_TIM9_Set_Duty(0,  _PWM_NON_INVERTED, _PWM_CHANNEL1);
  PWM_TIM3_Set_Duty(0,  _PWM_NON_INVERTED, _PWM_CHANNEL3);
}

void headlamps_blink() {
  HEAD_LAMPS = 1;
  delay_ms(200);
  HEAD_LAMPS = 0;
  delay_ms(500);
  HEAD_LAMPS = 1;
  delay_ms(200);
  HEAD_LAMPS = 0;
}

void forward(){
   double dbl_temp = 0.60;
   unsigned int spin_speed;
   break_buggy();
   spin_speed = (unsigned int) (PWM_A_PERIOD * dbl_temp);
   PWM_TIM4_Set_Duty(spin_speed,  _PWM_NON_INVERTED, _PWM_CHANNEL3);  //PWM_A  left_forward
   PWM_TIM3_Set_Duty(spin_speed,  _PWM_NON_INVERTED, _PWM_CHANNEL3);  //PWM_D  right_forward
   TURN_L = ~TURN_L;
   TURN_R = ~TURN_R;
}

void backward(){
   double dbl_temp = 0.60;
   unsigned int spin_speed;
   break_buggy();
   spin_speed = (unsigned int) (PWM_A_PERIOD * dbl_temp);
   PWM_TIM4_Set_Duty(spin_speed,  _PWM_NON_INVERTED, _PWM_CHANNEL4);  //PWM_B  left_reverse
   PWM_TIM9_Set_Duty(spin_speed,  _PWM_NON_INVERTED, _PWM_CHANNEL1);  //PWM_C  right_reverse}
   TURN_L = ~TURN_L;
   TURN_R = ~TURN_R;
}
    
void right(){
  double dbl_temp = 0.80;
  unsigned int spin_speed;
  break_buggy();
  spin_speed = (unsigned int) (PWM_A_PERIOD * dbl_temp);
  PWM_TIM4_Set_Duty(spin_speed,  _PWM_NON_INVERTED, _PWM_CHANNEL3);  //PWM_A  left_forward
  spin_speed = (unsigned int) (PWM_C_PERIOD * dbl_temp);
  PWM_TIM9_Set_Duty(spin_speed,  _PWM_NON_INVERTED, _PWM_CHANNEL1);  //PWM_C  right_reverse
  TURN_L = ~TURN_L;
  TURN_R = ~TURN_R;
}

void left() {
  double dbl_temp = 0.80;
  unsigned int spin_speed;
  break_buggy();
  spin_speed = (unsigned int) (PWM_D_PERIOD * dbl_temp);
  PWM_TIM3_Set_Duty(spin_speed,  _PWM_NON_INVERTED, _PWM_CHANNEL3);  //PWM_D  right_forward
  spin_speed = (unsigned int) (PWM_B_PERIOD * dbl_temp);
  PWM_TIM4_Set_Duty(spin_speed,  _PWM_NON_INVERTED, _PWM_CHANNEL4);  //PWM_B  left_reverse
  TURN_L = ~TURN_L;
  TURN_R = ~TURN_R;
}

void start_buggy() {
  PWM_TIM4_Start(_PWM_CHANNEL3, &_GPIO_MODULE_TIM4_CH3_PB8);
  PWM_TIM4_Start(_PWM_CHANNEL4, &_GPIO_MODULE_TIM4_CH4_PB9);
  PWM_TIM9_Start(_PWM_CHANNEL1, &_GPIO_MODULE_TIM9_CH1_PE5);
  PWM_TIM3_Start(_PWM_CHANNEL3, &_GPIO_MODULE_TIM3_CH3_PB0);

  headlamps_blink();
  forward();
}