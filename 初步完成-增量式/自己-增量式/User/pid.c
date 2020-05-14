#include "pid.h"

PID pid; //���PID�㷨����Ҫ������

void PID_Init()
{
	/*
  pid.Sv=50;//�û��趨�¶�
	
	
	pid.Kp=350;
  pid.Ti=1000000;//����ʱ��
	pid.Td=1000;//΢��ʱ��
	pid.T=200;//PID��������
	
	pid.pwmcycle=1000;//pwm����1000
	pid.OUT0=1;
	*/
	/*===============================================================*/
	pid.Sv =60;
	pid.T=200;
	pid.pwmcycle=1000;    //
	
	pid.Kp=5;
	pid.Ti=4000;
	pid.Td=2000;
	
	pid.OUT=0;
	
	pid.K1=pid.Kp*(1+pid.T/pid.Ti+pid.Td/pid.T);
	pid.K2=pid.Kp*(1+(2*pid.Td)/pid.T);
	pid.K3=pid.Kp*pid.Td/pid.T;
}

void PID_Calc()  //pid����
{
	static u16 calc;
	calc++;
	 
	float t1,t2,t3;
	
	if(calc<pid.T) return ;  //
	pid.Ek=pid.Sv-pid.Pv;  //�������
	
  t1=pid.K1*pid.Ek;
	t2=pid.K2*pid.Ek_1;
	t3=pid.K3*pid.Ek_2;
	
  pid.increment=t1+t2+t3;  //����Ӧ�����������
	pid.OUT+=pid.increment;  //����Ӧ�������PWM
	if(pid.OUT>pid.pwmcycle)
	{
	  pid.OUT=pid.pwmcycle;
	}
	if(pid.OUT<0)
	{
	 pid.OUT=0;
	}
	
	pid.Ek_2=pid.Ek_1;
	pid.Ek_1=pid.Ek;

	calc=0;
}












