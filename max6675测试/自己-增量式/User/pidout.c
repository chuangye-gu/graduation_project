#include "pidout.h"
#include "pid.h"
void PIDOUT_init()//pid����ų�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //��B��ʱ��  
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	pwmout_1;
}

void PID_out()  //���PID������������---ÿ1ms������1��
{
   static u16 pw;
	 pw++;
	 if(pw>=pid.pwmcycle)  //
	 {
	   pw=0;
	 }
	  //0  ~  pid.pwmcycle-1
	 
	 if(pw<pid.OUT)
	 {
	   pwmout_0;//����
	 }
	 else
	 {
	   pwmout_1;//ֹͣ����
	 }
	 
}
