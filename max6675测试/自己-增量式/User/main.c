#include "stm32f10x.h"
#include "pid.h"
#include "lcd1602.h"
#include "usart.h"
//#include "adc.h"
#include "pwm.h"
#include "pidout.h"
#include "time_init.h"
#include "max6675.h"

void TIM3_IRQHandler() //1ms 1次
{		  
	if(TIM_GetFlagStatus(TIM3, TIM_IT_Update)!=0)
	{ 
		TIM_ClearFlag(TIM3, TIM_IT_Update);
		read_temper();//读取当前温度
		PID_Calc(); //pid计算
		PID_out(); //输出PID运算结果到负载
	}
}
int main(void)
{
	char *str;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	usart_init();
//	adc_init();
  LCD1602_Init();
	PID_Init();
	PIDOUT_init();
	Timer3_init();	//T3 10us时钟
	
	sprintf(str, "SET:%d",(unsigned int)pid.Sv);
	LCD1602_ShowStr(4,0,str);
	LCD1602_WriteOneDat(0xdf);
	LCD1602_WriteDat('C');
	u16 t=0;
	Max6675_Init();
	while(1){	
		++t;
		
	//	printf("%d :  S:%d.%-3d\r",t,(unsigned int)pid.Pv,(unsigned int)((pid.Pv-(unsigned int)pid.Pv)*1000));
		
		sprintf(str, "NOW:%d.%-3d",(unsigned int)pid.Pv,(unsigned int)((pid.Pv-(unsigned int)pid.Pv)*1000));
		LCD1602_ShowStr(2,1,str);
		LCD1602_WriteOneDat(0xdf);
		LCD1602_WriteDat('C');
/*
		printf("%d :  S:%d    ",t,(unsigned int)pid.Sv);
		printf("P:%d.%-3d    ",(unsigned int)pid.Pv,(unsigned int)((pid.Pv-(unsigned int)pid.Pv)*1000));
		printf("O:%d.%-3d\r",(unsigned int)pid.OUT,(unsigned int)((pid.OUT-(unsigned int)pid.OUT)*1000));
		
		sprintf(str, "S:%d",(unsigned int)pid.Sv);
		LCD1602_ShowStr(0,0,str);
		sprintf(str, "P:%d.%-3d",(unsigned int)pid.Pv,(unsigned int)((pid.Pv-(unsigned int)pid.Pv)*1000));
		LCD1602_ShowStr(0,1,str);
		sprintf(str, "O:%d.%-3d",(unsigned int)pid.OUT,(unsigned int)((pid.OUT-(unsigned int)pid.OUT)*1000));
		LCD1602_ShowStr(7,1,str);
	*/
	}

}
