#include "pid.h"

PID pid;
extern u16 pidcalcms;
void PIDParament_Init()  //
{
  pid.set =100;
	pid.currpwm=0;
	pid.pwm_cycle=100;    //
//  pid.pid_P=8;
//	pid.pid_I=4;
//	pid.pid_D=5;
	pid.calc_cycle=100;  
	
	pid.Td=2000;
	pid.Ti=4000;
	pid.Kp=5;
	pid.Tsam=500;
}

/*
void pid_calc()  //pid??
{
  //int dk;

	
  short PID_out;
	
	if(pidcalcms<pid.calc_cycle) return ;

  pid.Ek=pid.set-pid.curr;//????(????-????)
  PID_out=((pid.pid_P)*((pid.Ek)-(pid.Ek_1)))+ \
          ((pid.pid_I)*(pid.Ek))+ \
          ((pid.pid_D)*((pid.Ek)-(2*(pid.Ek_1))+(pid.Ek_2)));   //??????
  pid.currpwm+=PID_out;
  pid.Ek_2=pid.Ek_1;  //???????
  pid.Ek_1=pid.Ek;    //??????

  if(pid.currpwm>pid.pwm_cycle)  //1000    //1s??PWM??
  {
     pid.currpwm=pid.pwm_cycle;   //????????1000???????
  }
  if(pid.currpwm<=0)  //??????0??0??(????)
  {
      pid.currpwm=0;//   
  }  //PID????
 pidcalcms=0;
} 
*/
void pid_calc()  //pid??
{
  float dk1;float dk2;
  float t1,t2,t3;
	
  //short PID_out;
	
	if(pidcalcms<pid.Tsam) return ;  //
	pid.En=pid.set-pid.curr;  //本次误差
	dk1=pid.En-pid.En_1;   //本次偏差与上次偏差之差
	dk2=pid.En-2*pid.En_1+pid.En_2;
	
  t1=pid.Kp*dk1;
	
	t2=(pid.Kp*pid.Tsam)/pid.Ti;
	t2=t2*pid.En;
	
	t3=(pid.Kp*pid.Td)/pid.Tsam;
	t3=t3*dk2;
	
  pid.Dout=t1+t2+t3;  //本次应该输出的增量
	pid.currpwm+=pid.Dout;  //本次应该输出的PWM
	if(pid.currpwm>pid.pwm_cycle)
	{
	  pid.currpwm=pid.pwm_cycle;
	}
	if(pid.currpwm<0)
	{
	 pid.currpwm=0;
	}
	pid.En_2=pid.En_1;
	pid.En_1=pid.En;
	
  pidcalcms=0;
}
