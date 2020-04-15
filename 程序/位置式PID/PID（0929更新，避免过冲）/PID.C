#include "pid.h"

PID pid; //´æ·ÅPIDËã·¨ËùÐèÒªµÄÊý¾Ý


void PID_Calc()  //pid¼ÆËã
{
 float DelEk;
	float ti,ki;
//	float Iout;
//	float Pout;
//	float Dout;
	float td;
	float kd;
	float out;
 if(pid.C10ms<(pid.T))  //¼ÆËãÖÜÆÚÎ´µ½
 {
    return ;
 }

 pid.Ek=pid.Sv-pid.Pv;   //µÃµ½µ±Ç°µÄÆ«²îÖµ
 pid.Pout=pid.Kp*pid.Ek;      //±ÈÀýÊä³ö
 
 pid.SEk+=pid.Ek;        //ÀúÊ·Æ«²î×ÜºÍ
 
 DelEk=pid.Ek-pid.Ek_1;  //×î½üÁ½´ÎÆ«²îÖ®²î
 
 ti=pid.T/pid.Ti;
 ki=ti*pid.Kp;
 
  pid.Iout=ki*pid.SEk*pid.Kp;  //»ý·ÖÊä³ö

 td=pid.Td/pid.T;
 
 kd=pid.Kp*td;
 
  pid.Dout=kd*DelEk;    //Î¢·ÖÊä³ö
 
 out= pid.Pout+ pid.Iout+ pid.Dout;
 
 //////////////////////////////////////////////////////////
 
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
 //pid.OUT+=; //±¾´ÎµÄ¼ÆËã½á¹û
 pid.Ek_1=pid.Ek;  //¸üÐÂÆ«²î
 
 pid.C10ms=0;
}


void PID_Calc_overshoot()  //pid¼ÆËã-¹ý³å´¦Àí¿
{
 float DelEk;
	float ti,ki;
//	float Iout;
//	float Pout;
//	float Dout;
	float td;
	float kd;
	float out;
  float SvSave;
 if(pid.C10ms<(pid.T))  //¼ÆËãÖÜÆÚÎ´µ½
 {
    return ;
 }
 
 
//ÅÐ¶ÏSv
  SvSave=pid.Sv;
 
 if(pid.Pv<(SvSave*0.55))//ÎÂ¶È´ïµ½¼ÆÊý¿ªÊ¼ 66¶È
 {
    pid.times=0;
 }
 
  if(pid.times<=60)//3·ÖÖÓ 72¶È  100s
 {
  pid.Sv=SvSave*0.6;
 }
 
 if((pid.times>60)&&(pid.times<=100))//3·ÖÖÓ 96¶È  100s
 {
  pid.Sv=SvSave*0.8;
 }
 
 if((pid.times>100)&&(pid.times<=200))//2·ÖÖÓ 102¶È 100s
 {
  pid.Sv=SvSave*0.85;
 }
 
 if((pid.times>200)&&(pid.times<=300))//2·ÖÖÓ 108¶È 100s
 {
  pid.Sv=SvSave*0.9;
 }
 
  if((pid.times>300)&&(pid.times<=400))//2·ÖÖÓ 114¶È 100s
 {
  pid.Sv=SvSave*0.95;
 }
 
 if(pid.times>400)
 {
  pid.Sv=SvSave;
 }
//////////////////////////////////


 pid.Ek=pid.Sv-pid.Pv;   //µÃµ½µ±Ç°µÄÆ«²îÖµ
 pid.Pout=pid.Kp*pid.Ek;      //±ÈÀýÊä³ö
 
 pid.SEk+=pid.Ek;        //ÀúÊ·Æ«²î×ÜºÍ
 
 DelEk=pid.Ek-pid.Ek_1;  //×î½üÁ½´ÎÆ«²îÖ®²î
 
 ti=pid.T/pid.Ti;
 ki=ti*pid.Kp;
 
  pid.Iout=ki*pid.SEk*pid.Kp;  //»ý·ÖÊä³ö

 td=pid.Td/pid.T;
 
 kd=pid.Kp*td;
 
  pid.Dout=kd*DelEk;    //Î¢·ÖÊä³ö
 
 out= pid.Pout+ pid.Iout+ pid.Dout;
 
 //////////////////////////////////////////////////////////
 
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
 //pid.OUT+=; //±¾´ÎµÄ¼ÆËã½á¹û
 pid.Ek_1=pid.Ek;  //¸üÐÂÆ«²î
 
 pid.C10ms=0;
 pid.Sv=SvSave;
}












