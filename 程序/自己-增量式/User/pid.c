#include "pid.h"

PID pid; //存放PID算法所需要的数据

void PID_Init()
{
	pid.Sv =70;
	pid.T=200;
	pid.pwmcycle=1000;    
	
	pid.Kp=5;
	pid.Ti=4000;
	pid.Td=2000;
	
	pid.OUT=0;
	
	/*
	pid.Sv =70;
	pid.T=200;
	pid.pwmcycle=1000;    //
	
	pid.Kp=5;
	pid.Ti=4000;
	pid.Td=2000;

	pid.OUT=0;
	
	pid.K1=pid.Kp*(1+pid.T/pid.Ti+pid.Td/pid.T);
	pid.K2=pid.Kp*(1+2*pid.Td/pid.T);
	pid.K3=pid.Kp*pid.Td/pid.T;
	*/
}

void PID_Calc()  //pid计算
{
	static u16 calc;
	calc++;
	 
	float dk1;float dk2;
	float t1,t2,t3;
	
	if(calc<pid.T) return ;  //
	pid.Ek=pid.Sv-pid.Pv;  //本次误差
	dk1=pid.Ek-pid.Ek_1;   //本次偏差与上次偏差之差
	dk2=pid.Ek-2*pid.Ek_1+pid.Ek_2;
	
  t1=pid.Kp*dk1;
	
	t2=(pid.Kp*pid.T)/pid.Ti;
	t2=t2*pid.Ek;
	
	t3=(pid.Kp*pid.Td)/pid.T;
	t3=t3*dk2;
	
  pid.increment=t1+t2+t3;  //本次应该输出的增量
	pid.OUT+=pid.increment;  //本次应该输出的PWM
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
	
	/*
	static u16 calc;
	calc++;
	
	float t1,t2,t3;
	
	if(calc<pid.T) return ;  //
	pid.Ek=pid.Sv-pid.Pv;  //本次误差
	
  t1=pid.K1*pid.Ek;
	t2=pid.K2*pid.Ek_1;
	t3=pid.K3*pid.Ek_2;
	
  pid.increment=t1+t2+t3;  //本次应该输出的增量
	pid.OUT+=pid.increment;  //本次应该输出的PWM
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
	*/
}












