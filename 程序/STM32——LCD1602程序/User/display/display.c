#include "display.h"
#include "bsp-lcd1602.h"
#include "pid.h"

extern u8 rtc[3];
void Show_clock()
{
 char s[10];
	sprintf(s,"%02d:%02d:%02d",rtc[0],rtc[1],rtc[2]);
//	Show_string(0X9A,s) ; ----------------------�Լ�ע�͵���
}


void Show_temperauter()
{
  char s[20];
  sprintf(s,"��ǰ�¶�:% 3.1f ",pid.curr);	
//	Show_string(0x90,s);----------------------�Լ�ע�͵���
	sprintf(s,"�趨�¶�:% 3.1f ",pid.set);	
//	Show_string(0x88,s);----------------------�Լ�ע�͵���
}





void Display()
{
  // Show_float(0x90,pid.Tcurr);
 // Show_temperauter();     ----------------------�Լ�ע�͵���
	//Show_clock();
//	Show_number(0x98,pid.currpwm);----------------------�Լ�ע�͵���
}



