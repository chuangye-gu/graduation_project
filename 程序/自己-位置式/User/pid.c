#include "pid.h"

PID pid; //���PID�㷨����Ҫ������

void PID_Init()
{
  pid.Sv=50;//�û��趨�¶�
	pid.T=200;//PID��������
	
	pid.Kp=350;
  pid.Ti=1000000;//����ʱ��
	pid.Td=1000;//΢��ʱ��
	
	pid.pwmcycle=1000;//pwm����1000
	pid.OUT0=1;
}

void PID_Calc()  //pid����
{
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
}












