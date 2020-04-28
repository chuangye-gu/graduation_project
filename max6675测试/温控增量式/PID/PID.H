#ifndef _pid_
#define _pid_
#include "stm32f10x_conf.h"

typedef struct
{
  float curr;  //当前温度
	float set;   //设定温度
	

//  float pid_P;       //P
//  float pid_I;       //I
//  float pid_D;       //D
	
	
//  short Ek;//
//  short Ek_1;//
//  short Ek_2;//
  //int PID_OUT;//

	float En;
	float En_1;
	float En_2;
	
	float Kp;   //比例系数
	float Tsam; //采样周期---控制周期，每隔Tsam控制器输出一次PID运算结果
	float Ti;//积分时间常数
	float Td;//微分时间常数
	
	float Dout;//增量PID计算本次应该输出的增量值--本次计算的结果
	
	u16 calc_cycle;
	short currpwm;  //当前的pwm宽度
	u16 pwm_cycle;//pwm的周期
}PID;


extern u8 STATUS;
extern PID pid;
void PIDParament_Init(void);  //
void pid_calc(void);  //pid??

#endif

