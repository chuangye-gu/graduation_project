#include "pid.h"

PID pid; //存放PID算法所需要的数据

void PID_Init()
{
	/*
  pid.Sv=50;//用户设定温度
	
	
	pid.Kp=350;
  pid.Ti=1000000;//积分时间
	pid.Td=1000;//微分时间
	pid.T=200;//PID计算周期
	
	pid.pwmcycle=1000;//pwm周期1000
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

void PID_Calc()  //pid计算
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
	if(calc<pid.T)  //计算周期未到
		return ;
	pid.Ek=pid.Sv-pid.Pv;   //得到当前的偏差值
	pid.Pout=pid.Kp*pid.Ek;      //比例输出

	pid.SEk+=pid.Ek;        //历史偏差总和

	DelEk=pid.Ek-pid.Ek_1;  //最近两次偏差之差

	ti=pid.T/pid.Ti;
	ki=ti*pid.Kp;
 
	pid.Iout=ki*pid.SEk*pid.Kp;  //积分输出

	td=pid.Td/pid.T;

	kd=pid.Kp*td;
 
	pid.Dout=kd*DelEk;    //微分输出

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
	 
	pid.Ek_1=pid.Ek;  //更新偏差

	calc=0;
	 */
	 /*===============================================================*/
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
}












