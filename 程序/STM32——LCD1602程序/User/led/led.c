#include "led.h"
/*
LED0---PA8
LED1---PD2
*/


void LED_Init()	  //LED��ʼ��
{ 
	GPIO_InitTypeDef  IO;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //��A��ʱ��


	IO.GPIO_Pin=GPIO_Pin_15;
	IO.GPIO_Speed=GPIO_Speed_50MHz;
	IO.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &IO);

	GPIO_ResetBits(GPIOA, GPIO_Pin_15);
}
