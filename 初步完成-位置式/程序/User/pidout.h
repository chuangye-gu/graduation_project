#ifndef _pidout_
#define _pidout_

#include "stm32f10x_conf.h"

#define pwmout_1    GPIO_SetBits(GPIOA, GPIO_Pin_11)    //ֹͣ����
#define pwmout_0    GPIO_ResetBits(GPIOA, GPIO_Pin_11)  //����
void PIDOUT_init(void);//pid����ų�ʼ��
void PID_out(void); //���PID������������

#endif

