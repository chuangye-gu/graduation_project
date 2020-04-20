#ifndef _pid_
#define _pid_
#include "stm32f10x_conf.h"
#include <stdio.h>
typedef struct
{
	float Sv;//�û��趨ֵ
	float Pv;

	float Kp;
	float T;  //PID��������--��������
	float Ti;
	float Td; 
	
	
	
	float Ek;  //����ƫ��
	float Ek_1;//�ϴ�ƫ��
	float Ek_2;  //����ƫ��
	float SEk; //��ʷƫ��֮��
	
	float Iout;
	float Pout;
	float Dout;
	
	float OUT0;
	float increment;
	float OUT;   //����
	
	u16 pwmcycle;//pwm����
 
	
}PID;

extern PID pid; //���PID�㷨����Ҫ������
void PID_Calc(void); //pid����
void PID_Init(void);
#endif
