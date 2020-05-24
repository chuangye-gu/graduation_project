#include "stm32f10x.h"
#include "systick.h"
#include "pid.h"
#include "lcd1602.h"
#include "usart.h"
#include "adc.h"
#include "pwm.h"
#include "pidout.h"
#include "time_init.h"
#include "key.h"

void TIM3_IRQHandler() //1ms 1��
{		  
	if(TIM_GetFlagStatus(TIM3, TIM_IT_Update)!=0)
	{ 
		TIM_ClearFlag(TIM3, TIM_IT_Update);
		read_temper();//��ȡ��ǰ�¶�
		PID_Calc(); //pid����
		PID_out(); //���PID������������
	}
}
int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	usart_init();
	adc_init();
  LCD1602_Init();
	PID_Init();
	PIDOUT_init();
	Timer3_init();	//T3 10usʱ��
	
	display_print_set();
	while(1){	
		display_print_now();
		
	}

}
