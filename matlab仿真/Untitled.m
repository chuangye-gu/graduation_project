%ִ�л�����Ҫ���ǿ������������������������������ʱ�򣬲�������ʽPID���ƣ�
%����ʽPID�����㷨�в���Ҫ�ۼӣ���������u(k)�������k�εĲ����йأ���������Ӱ��С��
%��һ���ض���G��s��=50/(0.125s^2+7s),  
%������ʽPID�����㷨��д�������  
%������ֱ�Ϊ��λ��Ծ�������źţ�����ʱ��Ϊ1ms������������޷���[-5,5],  
%  �������߰���ϵͳ�����������ߣ�������ע�͡�ͼ������  
  
clc;
clear ;     
ts=0.001;                  %����ʱ��  
%sys=tf(50,[0.125,7, 0]);  %tf�Ǵ��ݺ���������ʵ��G��s��;  ���Զ��������򾭳��õ���
sys=tf(400,[1,50,0]);   
dsys=c2d(sys,ts,'z');        %�ѿ��ƺ�����ɢ����ת��Ϊ��ַ���
[num,den]=tfdata(dsys,'v');  % ��ɢ������ȡ���ӡ���ĸ ����ȡ��ַ���ϵ��   
u_1=0.0;  
u_2=0.0;  
y_1=0.0;  
y_2=0.0;  
x=[0,0,0]';  
error_1=0;  
error_2=0;  
for k=1:1:3000  
time(k)=k*ts;    %��������  
 
S=4;   %ѡ����Ҫ���ٵĺ���
if S==1  
   % kp=10;ki=0.1;kd=15;             %��ʼ��PID
    kp=8;ki=0.1;kd=10;
    rin(k)=1;            %Step Signal ����Ծ�ź�  
end
if S==2  
    kp=10;ki=0.1;kd=15;               
    rin(k)=0.5*sin(2*pi*k*ts);       %Sine Signal   �����ź�  
end    
if S==3          %���ǲ��ź� 
     kp=10;ki=0.1;kd=15;
     if mod(time(k),2)<1
         rin(k)=mod(time(k),1);
     else
         rin(k)=1-mod(time(k),1);
     end
     rin(k)=rin(k)-0.5;
end
if S==4     %��ݲ��ź�
    kp=8;ki=0.05;kd=4; %���Եú��ʲ��������������壬�ɽ�kd��С��
    rin(k)=mod(time(k),1);
end
 
du(k)=kp*x(1)+kd*x(2)+ki*x(3);      %PID Controller   ����ϵ��    
u(k)=u_1+du(k); 
 
if u(k)>=10         %Restricting the output of controller������޷�
   u(k)=10;  
end  
if u(k)<=-10  
   u(k)=-10;  
end  
%Linear model  
yout(k)=-den(2)*y_1-den(3)*y_2+num(2)*u_1+num(3)*u_2;          %ʵ�����  
error(k)=rin(k)-yout(k);                                       %Return of parameters ���  
u_2=u_1;                                                       %�������ϴ�����   Ϊ�´μ���  
u_1=u(k);                                                      %������һ�ο���ϵ��   Ϊ�´μ���  
y_2=y_1;                                                       %�������ϴδ����   Ϊ�´μ���  
y_1=yout(k);                                                   %������һ�����   Ϊ�´μ���  
x(1)=error(k)-error_1;            %Calculating P  
x(2)=error(k)-2*error_1+error_2;  %Calculating D  
x(3)=error(k);                    %Calculating I  
error_2=error_1;                      
error_1=error(k);                      
end  
figure(1);  
plot(time,rin,'b',time,yout,'r');                        %���� ��ʵ�ʿ������  
xlabel('time(s)'),ylabel('rin,yout');   
% figure(2);  
% plot(time,error,'r')                                     %�������������������  
% xlabel('time(s)');ylabel('error');  