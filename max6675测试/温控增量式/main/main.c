
#include "led.h"
#include "12864.h"
#include "max6675.h"
 #include "time_init.h"
#include "display.h"
#include "pid.h"
#include "pidout.h"
#include "24c02.h"

u8 STATUS=0;

u8 rtc[3];  //实时时钟
u16 Kms10;
u16 sec;
u16 pidcalcms;
void delay(u32 x)
{
  while(x--);
}

void delay_us(u16 us)
{
	 u8 i;
  while(us--)
	{
	  for(i=0;i<6;i++)
		{
		
		}
	}
}

void run_clock()
{
 rtc[2]++;
	if(rtc[2]>=60)
	{
	  rtc[2]=0;
		rtc[1]++;
		if(rtc[1]>=60)
		{
		  rtc[1]=0;
			rtc[0]++;
			if(rtc[0]>=24)
			{
			  rtc[0]=0;
			}
		}
	}
}
 void TIM4_IRQHandler() //10ms
{					  
  
	static u8 tsec; u8 st;
	st=TIM_GetFlagStatus(TIM4, TIM_IT_Update);
	if(st!=0)
	{  TIM_ClearFlag(TIM4, TIM_IT_Update); 
		Kms10++;

		if(tsec++>=100)
		{
		  tsec=0;
			 run_clock();
			//sec++;
			if(rtc[2]%2)  led_on ;
			else          led_off;
		}
	}
}

 void TIM3_IRQHandler() //1ms
{					  
  u8 st;
	
	st=TIM_GetFlagStatus(TIM3, TIM_IT_Update);
	if(st!=0)
	{ 
		TIM_ClearFlag(TIM3, TIM_IT_Update); 
		pidcalcms++;
		pwm_out();
	}
}

void Isr_Init()
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
NVIC_InitStructure.NVIC_IRQChannel =TIM4_IRQn;// TIM4_IRQChannel; 
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
NVIC_Init (&NVIC_InitStructure); 


NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;// TIM4_IRQChannel; 
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
NVIC_Init (&NVIC_InitStructure);
	
}

u8 a;
int main()
{
  SystemInit();  //将主频调整到72M
  LED_Init();
  LCD_Init();
	IIC_Init();
  Max6675_Init();
	PIDParament_Init();  //
	PWM_init();
	Timer4_init();	//T4 10ms时钟	
	Timer3_init();	//T3 1ms时钟	
	Isr_Init();


   while(1)
   {
		   pid_calc();  //pid??
		  Display();
		  read_temper();//?????? 
     // Show_clock();
   }
}

