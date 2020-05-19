#include<reg52.h>
#include<math.h>
float R;
float Kp;
float T;
float Ti;
float Td;
float e2;
float e1,e;
float a0,a1,a2;
#define ui unsigned int
#define uc unsigned char
sbit bj=P2^4;							 //低电平报警模块工作
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
//LCD控制程序
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
void lcdinit()
{
	lcdrw=0;
	lcden=0;
	lcdwritecom(0x38);
	lcdwritecom(0x0c);
	lcdwritecom(0x06);
	lcdwritecom(0x01);
}
//LCD显示
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
//键盘扫描
void keyscan()
{
	uc test,num;
	num=0;
	test=P1;
	if(test!=0xff)
	delay(5);
	test=P1;
	if(test==0xf7)
	
	{
		while(P1!=0xff);
		num++;
		while(1)
		{
			test=P1;
			if(test!=0xff)
			delay(5);
			test=P1;
			if(test!=0xff)
			{
				if(test==0xf7)
					num++;
					if(num==2)
					{	lcdwritecom(0x0c);
						break;}
				switch(test)
				{
					case 0xfe:adjust();	
							break;
					case 0xfd:inc();
							break;
					case 0xfb:dec();
							break;
				}
		 	}
			while(P1!=0xff);
		
		}
		}
}
//PID
void PIDinit()
{
      
	   Kp=2;Ti=4;Td=1;T=1;R=25;
	   a0=Kp*(1+T/Ti+Td/T);
	   a1=-Kp*(1+(2*Td)/T);
	   a2=Kp*(Td/T);
	   e2=e1=0;
}
void PIDdeal()
{
	float y	,u ;
	y=gettemp();
	e=y/100-R;
	u=a0*e+a1*e1+a2*e2;
	e2=e1;e1=e;
	if(u>0.5||u<-0.5)
	control=0;
	else control=1;
}
void main()
{
	uc code tab2[]="SET:20~80C";
	uc i;
	TMOD=0x01;  //定时器方式一
	TH0=(65535-10000)/256;   //定时10ms
	TL0=(65535-10000)%256;
	ET0=1;
	TR0=1;
	lcdinit();
	lcdwritecom(0x87);
	lcdwritedata('C');
	lcdwritecom(0x80+0x40);
	for(i=0;i<10;i++)
		lcdwritedata(tab2[i]) ;
	lshi=2;lge=0;hshi=5;hge=0;
	while(1)
	{ 
		lcddisplay(gettemp());
    	keyscan() ;
		EA=1; while(1);
	}
}
void t0() interrupt 1
{	
	uc i;
	TH0=(65535-10900)/256;
	TL0=(65535-10900)%256;
	i++; 
	if(i==100)
	{
	   void PIDinit();
	   void PIDdeal();
	}
}
