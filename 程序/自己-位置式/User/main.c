#include "stm32f10x.h"
#include "pid.h"
#include "lcd1602.h"
#include "usart.h"
#include "adc.h"
#include "pwm.h"
#include "pidout.h"
#include "time_init.h"

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
	char *str;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	usart_init();
	adc_init();
  LCD1602_Init();
	PID_Init();
	PIDOUT_init();
	Timer3_init();	//T3 10usʱ��

	while(1){	

		printf("S:%d    ",(unsigned int)pid.Sv);
		printf("P:%d.%-3d    ",(unsigned int)pid.Pv,(unsigned int)((pid.Pv-(unsigned int)pid.Pv)*1000));
		printf("O:%d.%-3d\r",(unsigned int)pid.OUT,(unsigned int)((pid.OUT-(unsigned int)pid.OUT)*1000));
		/*
		sprintf(str, "S:%d",(unsigned int)pid.Sv);
		LCD1602_ShowStr(0,0,str);
		sprintf(str, "P:%d.%-3d",(unsigned int)pid.Pv,(unsigned int)((pid.Pv-(unsigned int)pid.Pv)*1000));
		LCD1602_ShowStr(0,1,str);
		sprintf(str, "O:%d.%-3d",(unsigned int)pid.OUT,(unsigned int)((pid.OUT-(unsigned int)pid.OUT)*1000));
		LCD1602_ShowStr(7,1,str);
	*/
	}

}
