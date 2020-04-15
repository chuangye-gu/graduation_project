#include "time_init.h"
#include"stm32f10x_conf.h"
  
void Timer3_init()	//T3 1ms时钟
{	 //72000000/7200=100us
//
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM3,ENABLE);

TIM_TimeBaseStructure.TIM_Period = 9; //计数个数     //1ms
TIM_TimeBaseStructure.TIM_Prescaler =72-1;//分频值   	    
TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; 	//分割时钟			
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
 TIM_DeInit(TIM3);
TIM_TimeBaseInit(TIM3, & TIM_TimeBaseStructure); 
TIM_Cmd(TIM3, ENABLE); 	 //使能定时器2

 /*以下定时器4中断初始化*/
TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //向上计数溢出产生中断
	
	NVIC_InitTypeDef NVIC_InitStructure; 
	NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;// TIM3_IRQChannel; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init (&NVIC_InitStructure);
}

