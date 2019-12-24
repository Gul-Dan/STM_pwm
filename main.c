#include "stm8s_conf.h"
#include "stm8s.h"
#include "stm8s_clk.h"
#include "stm8s_gpio.h"
#include "stm8s_tim2.h"
#include "stm8s_tim1.h"
#include "stdbool.h"
#include "sin.h"

#define F_CPU 				8000000UL 
#define dly_const			(F_CPU / 16000000.0F) 

void delay_us(unsigned int  value)
{
	register unsigned int loops =  (int)(dly_const * value) ;
	
	while(loops)
	{
		asm ("nop");
		loops--;
	};
}

void delay_ms(unsigned int  value)
{
	while(value)
	{
		delay_us(1000);
		value--;
	};
}
 
void clock_setup(void);
void GPIO_setup(void);
void TIM2_setup(void);
void TIM1_setup(void);
 

 
void main(void)
{                
     clock_setup();
     GPIO_setup();
     TIM2_setup();
     //TIM1_setup();
                
     //enable interrupt
     enableInterrupts();
     
     while(true)
     {
       delay_ms(1);
       GPIO_WriteReverse(GPIOB, GPIO_PIN_4);
     };
}
 
 
void clock_setup(void)
{
      CLK_DeInit();
      CLK_HSICmd(ENABLE);
      //CLK_ClockSwitchCmd(ENABLE);
      CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV2);
      CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
                
      //CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_ENABLE);
                
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, DISABLE);
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, DISABLE);
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, DISABLE);
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU, DISABLE);
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, DISABLE);
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, DISABLE);
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, ENABLE);
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, DISABLE);
}
 
 
void GPIO_setup(void)
{
      GPIO_DeInit(GPIOB);
      GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST);
  
      GPIO_DeInit(GPIOD);
      GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST);
}
 
void TIM1_setup(void)
{
  TIM1_DeInit();
  TIM1_TimeBaseInit(1, TIM1_COUNTERMODE_DOWN, 99, 0);
  TIM1_OC1Init(TIM1_OCMODE_PWM1, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE, 49, TIM1_OCPOLARITY_HIGH, TIM1_OCNPOLARITY_LOW, TIM1_OCIDLESTATE_SET, TIM1_OCNIDLESTATE_RESET);
      
  TIM1_OC1PreloadConfig(ENABLE);
  
  TIM1_CtrlPWMOutputs(ENABLE);
  
  /* TIM1 counter enable */
  TIM1_Cmd(ENABLE);
}
 
void TIM2_setup(void)
{
      TIM2_DeInit();
      TIM2_TimeBaseInit(TIM2_PRESCALER_1, 510);
      TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, getSin(getCount()), TIM2_OCPOLARITY_HIGH);
      
      TIM2_OC1PreloadConfig(DISABLE);
      TIM2_ARRPreloadConfig(ENABLE);
      TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);

      /* TIM2 Main Output Enable */
      //TIM2_CtrlPWMOutputs(ENABLE);
      //TIM2_PWMIConfig(TIM2_CHANNEL_1, TIM2_ICPOLARITY_FALLING, );

      //TIM2_SetCompare1(4);
      
      /* TIM2 counter enable */
      TIM2_Cmd(ENABLE);
}