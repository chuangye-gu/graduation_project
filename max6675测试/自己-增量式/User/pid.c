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
}

void PID_Calc()  //pid����
{
	/*
	static u16 calc;
	calc++;
	float DelEk;
	float ti,ki;
	//	float Iout;
	//	float Pout;
	//	float Dout;
	float td;
	float kd;
	float out;
	if(calc<pid.T)  //��������δ��
		return ;
	pid.Ek=pid.Sv-pid.Pv;   //�õ���ǰ��ƫ��ֵ
	pid.Pout=pid.Kp*pid.Ek;      //�������

	pid.SEk+=pid.Ek;        //��ʷƫ���ܺ�

	DelEk=pid.Ek-pid.Ek_1;  //�������ƫ��֮��

	ti=pid.T/pid.Ti;
	ki=ti*pid.Kp;
 
	pid.Iout=ki*pid.SEk*pid.Kp;  //�������

	td=pid.Td/pid.T;

	kd=pid.Kp*td;
 
	pid.Dout=kd*DelEk;    //΢�����

	out= pid.Pout+ pid.Iout+ pid.Dout;
 
 
	 if(out>pid.pwmcycle)
	 {
		pid.OUT=pid.pwmcycle;
	 }
	 else if(out<0)
	 {
		pid.OUT=pid.OUT0; 
	 }
	 else 
	 {
		pid.OUT=out;
	 }
	 
	pid.Ek_1=pid.Ek;  //����ƫ��

	calc=0;
	 */
	 /*===============================================================*/
	static u16 calc;
	calc++;
	 
	float dk1;float dk2;
	float t1,t2,t3;
	
	if(calc<pid.T) return ;  //
	pid.Ek=pid.Sv-pid.Pv;  //�������
	dk1=pid.Ek-pid.Ek_1;   //����ƫ�����ϴ�ƫ��֮��
	dk2=pid.Ek-2*pid.Ek_1+pid.Ek_2;
	
  t1=pid.Kp*dk1;
	
	t2=(pid.Kp*pid.T)/pid.Ti;
	t2=t2*pid.Ek;
	
	t3=(pid.Kp*pid.Td)/pid.T;
	t3=t3*dk2;
	
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












