#include "key.h"

void key_init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void key_set()
{
	
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0){
		Delay_Us(200);
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 1){
			char *str;
			sprintf(str, "SET:___");
			LCD1602_ShowStr(4,0,str);
			sprintf(str, "SET:%d",(unsigned int)pid.Sv);
			LCD1602_ShowStr(4,0,str);
			
		}
	}
	
}
