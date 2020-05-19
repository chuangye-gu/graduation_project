#include<reg52.h>
#include<math.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
#define ui unsigned int
#define uc unsigned char
uchar lcd[]="0123456789";
uchar A1,A2,A3;
sbit rd=P1^6; //IO???
sbit wr=P1^7;
sbit cs=P1^5;
sbit A=P2^0;
sbit BB=P2^1;
sbit C=P2^2;
sbit D=P2^4;

sbit k0 = P1^0;
sbit k1 = P1^1;
sbit k2 = P1^2;
sbit k3 = P1^3;

 float R;
 float Kp;
 float T;
 float Ti;
 float Td;
 float Pt;
 float Ek;
 float Ek_1;
 float SEk;
 float u;
 float u0 = 1;

ui summer;

//sbit bj=P2^4;							 //低电平报警模块工作
sbit lcden=P2^7;						 //LCD E
sbit lcdrs=P2^6;						 //LCD	RS
sbit lcdrw=P2^5; //						 //LCD RW
sbit control=P2^3;						 //加热模块相关。低电平启动
char lshi,lge,hshi,hge;
uc num,flag;
ui temp;
sbit dsio=P3^7;							//DS18B20输入口
//延时
void delay(ui z)
{
	uc x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void sm_delay(ui z)
{
	uc x,y,t;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--)
			for(t=30;t>0;t--);
}
//DS18B20控制
void dsinit()
{
	uc i;
	dsio=0;
	i=70;
	while(i--);
	dsio=1;
	i=4;
	while(i--);
}
void dswritebyte(uc dat)
{
	uc i,j;
	for(j=0;j<8;j++)
	{
		dsio=0;
		i++;
		dsio=dat&0x01;
		i=6;
		while(i--);
		dsio=1;
		dat>>=1;
	}
}
uc dsreadbyte()
{
	uc i,j,byte,b;
	for(j=0;j<8;j++)
	{
		dsio=0;
		i++;
		dsio=1;
		i++;i++;
		b=dsio;
		byte=(byte>>1)|(b<<7);
		i=4;
		while(i--);
	}
	return byte;
}
void dschangetemp()
{
	dsinit();
	delay(1);
	dswritebyte(0xcc);
	dswritebyte(0x44);

}
void dsreadtemp()
{
	dsinit();
	delay(1);
	dswritebyte(0xcc);
	dswritebyte(0xbe);
}
ui gettemp()
{
	int temp;
	uc h,l;
	dschangetemp();
	dsreadtemp();
	l=dsreadbyte();
	h=dsreadbyte();
	temp=h;
	temp<<=8;
	temp|=l;
	temp=temp*0.0625*100+0.5;
	return temp;
}

void lcdwritecom(uc com)
{
	lcdrs=0;
	P0=com;
	delay(10);
	lcden=1;
	delay(10);
	lcden=0;
}
void lcdwritedata(uc date)
{
	lcdrs=1;
	P0=date;
	delay(10);
	lcden=1;
	delay(10);
	lcden=0;
}
void lcdinit()  //lcd显示初始化
{
	lcdrw=0;
	lcden=0;
	lcdwritecom(0x38);
	lcdwritecom(0x0c);
	lcdwritecom(0x06);
	lcdwritecom(0x01);
}

void lcddisplay(int temp)
{
	ui  tab[]={0,0,0,-2,0,0};
	lcdwritecom(0x80);
	lcdwritedata('+');
	tab[0]=temp/10000;
	tab[1]=temp%10000/1000;
	tab[2]=temp%1000/100;
	tab[4]=temp%100/10;
	tab[5]=temp%10;
	lcdwritecom(0x81);
	for(num=0;num<6;num++)
	{
		lcdwritedata('0'+tab[num]);
	}
}

void adjust()
{
	delay(100);
	flag++;
	if(flag==5)flag=1;
	if(flag==1)
	{
		lcdwritecom(0x80+0x44);
		lcdwritecom(0x0f);	
	 }
	 if(flag==2)
	{
		lcdwritecom(0x80+0x45);
		lcdwritecom(0x0f);	
	 }
	if(flag==3)
	{
		lcdwritecom(0x80+0x47);
		lcdwritecom(0x0f);	
	 }
	if(flag==4)
	{
		lcdwritecom(0x80+0x48);
		lcdwritecom(0x0f);	
	 }
}
void inc()
{
	delay(100);
	switch(flag)
	{
		case 1:lshi++; if(lshi==10)lshi=0;
						lcdwritedata('0'+lshi);
						lcdwritecom(0x10);
						break;
		case 2:lge++; if(lge==10)lge=0;
						lcdwritedata('0'+lge);
						lcdwritecom(0x10);
						break;
		case 3:hshi++; if(hshi==10)hshi=0;
						lcdwritedata('0'+hshi);
						lcdwritecom(0x10);
						break;
		case 4:hge++; if(hge==10)hge=0;
						lcdwritedata('0'+hge);
						lcdwritecom(0x10);
						break;
	}
}
void dec()
{
	delay(100);
	switch(flag)
	{
		case 1:lshi--; if(lshi<0)lshi=9;
						lcdwritedata('0'+lshi);
						lcdwritecom(0x10);
						break;
		case 2:lge--; if(lge<0)lge=9;
						lcdwritedata('0'+lge);
						lcdwritecom(0x10);
						break;
		case 3:hshi--; if(hshi<0)hshi=9;
						lcdwritedata('0'+hshi);
						 lcdwritecom(0x10);
						break;
		case 4:hge--; if(hge<0)hge=9;
						lcdwritedata('0'+hge);
						 lcdwritecom(0x10);
						break;
	}
}



void PIDinit()//pid参数初始值设定
{
      
	Kp=10;
	Ti=100000;
	Td=1000;
	T=50;
	R=60;
	Pt = 100;

}


uchar read_adc0804()
{
	char b=0;
	uchar a; 
	cs=1;
	wr=1;
	cs=0;
	wr=0;
	_nop_();
	wr=1;
  
	P3=0xff;        
	rd=1;
	rd=0;
	_nop_();
	a=P3;
	rd=1;
	cs=1; 

	a=a/2;

 return a;
}

void PIDdeal()
{
	float Ek;
	float Po,Io,Do;
	
	float Ki;
	float Kd;
	float EK;
	
	Ek=R-summer; //偏差
	
	SEk+=Ek;      //偏差累累积
	Po=Kp*Ek;       //P输出
	Ki = (T/Ti);   
	Ki = Ki*Kp;    
	Io=Ki*SEk;  //I输出

	Kd = (Td/T);
	Kd = Kd*Kp;
	EK = Ek-Ek_1;
	Do=Kd*EK;    //D输出

	u= Po+Io+Do;   //PID输出
	Ek_1=Ek;    //下次输出准备
	

	 if(u>Pt)   //输出范围
	 {
		u=Pt;
	 }else if(u==0)
	 {
		u=u0; 
	 }else if(u<-100)
	 {
			u=-100;
	 }
}

void stepping_motor()  //电机控制
{
		if(u>=0) return ;
		control=1;
		D=0;
		
		sm_delay(10000);
		D=1;
}
void display_content()
{
		A1=(unsigned int)R/100; //设定值显示
		A2=(unsigned int)R%100/10;
		A3=(unsigned int)R%10;
		lcdwritecom(0x80);
		lcdwritedata('s');
		lcdwritedata('e');
		lcdwritedata('t');
		lcdwritedata(':');
		lcdwritedata(0x10);
		lcdwritedata(lcd[A1]);
		lcdwritedata(lcd[A2]);
		lcdwritedata(lcd[A3]);
	
		A1=summer/100; //设定值显示
		A2=summer%100/10;
		A3=summer%10;
		lcdwritecom(0x89);
		lcdwritedata('n');
		lcdwritedata('o');
		lcdwritedata('w');
		lcdwritedata(':');
		lcdwritedata(lcd[A1]);
		lcdwritedata(lcd[A2]);
		lcdwritedata(lcd[A3]);
		if(u>=0){
			A1=(unsigned int)u/100;
			A2=(unsigned int)u%100/10;
			A3=(unsigned int)u%10;
			lcdwritecom(0x80+0X40);
			lcdwritedata('p');
			lcdwritedata('w');
			lcdwritedata('m');
			lcdwritedata(':');
			lcdwritedata(0x10);
			lcdwritedata(lcd[A1]);
			lcdwritedata(lcd[A2]);
			lcdwritedata(lcd[A3]);
		}
		else{
			A1=(unsigned int)u/100;
			A2=(unsigned int)u%100/10;
			A3=(unsigned int)u%10;
			lcdwritecom(0x80+0X40);
			lcdwritedata('p');
			lcdwritedata('w');
			lcdwritedata('m');
			lcdwritedata(':');
			lcdwritedata(0x2d);
			lcdwritedata(lcd[A1]);	
			lcdwritedata(lcd[A2]);
			lcdwritedata(lcd[A3]);
		}
}
void pwm()
{
	static uc i;
	if(u<0) return ;

	i++; 
	
	if(i>Pt)
	{
		i = 0;  
	} 
	if(i < u)
	{
		control=0;
	} else if(i>u){
		control=1;
	};
}
int keyscan()
{
	if(k0==0)   //设置键
	{
		delay(5);
		if(k0==0)
		{
			while(k0==0);
			while(1)
			{
				A1=(unsigned int)R/100; //设定值显示
				A2=(unsigned int)R%100/10;
				A3=(unsigned int)R%10;
				lcdwritecom(0x80);
				lcdwritedata('s');
				lcdwritedata('e');
				lcdwritedata('t');
				lcdwritedata(':');
				lcdwritedata(0x10);
				lcdwritedata(lcd[A1]);
				lcdwritedata(lcd[A2]);
				lcdwritedata(lcd[A3]);
				delay(5000);
				lcdwritecom(0x85);
				lcdwritedata('-');
				lcdwritedata('-');
				lcdwritedata('-');
				delay(5000);
				if(k1==0)   //加温键
				{
					delay(5);
					if(k1==0)
						while(k1==0);
						R+=1;
				}
				if(k2==0)  //减温键
				{
					delay(5);
					if(k2==0)
						while(k2==0);
						R-=1;
				}
				if(k3==0)  //完成键
				{
					delay(5);
					if(k3==0)
						while(k3==0);
						return;
				}
				delay(5);
			}
		}
	}			
}
void main()
{
	TMOD=0x01;//定时器方式一
	TH0=(65535-10900)/256;//定时10ms
	TL0=(65535-10900)%256;
	ET0=1;
	TR0=1;
	EA=1;
	PIDinit();//PID初始化
	lcdinit();//lcd初始化
	while(1)
	{ 	
		summer=read_adc0804();//温度拂读取
		PIDdeal();//pid计算
		stepping_motor();//电机控制
		display_content();//显示
	}
}

void t0() interrupt 1
{	
	TH0=(65535-10900)/256;
	TL0=(65535-10900)%256;
	pwm();//pwm控制
	keyscan();
	EA=1;//启动定时器
}

