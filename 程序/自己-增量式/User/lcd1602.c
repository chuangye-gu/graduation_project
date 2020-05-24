#include "lcd1602.h"

void LCD1602_GPIO_Config(void)
{
	RCC_APB2PeriphClockCmd(LCD1602_CLK, ENABLE);
	GPIO_InitTypeDef LCD1602_GPIOStruct;
	LCD1602_GPIOStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	LCD1602_GPIOStruct.GPIO_Speed = GPIO_Speed_10MHz;
	LCD1602_GPIOStruct.GPIO_Pin =  LCD1602_E | LCD1602_RS | LCD1602_RW ;
	GPIO_Init(LCD1602_GPIO_PORT,&LCD1602_GPIOStruct);
	LCD1602_GPIOStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	LCD1602_GPIOStruct.GPIO_Pin =   DB0 |  DB1 | DB2 |DB3 |  DB4 | DB5|
																	DB6 |  DB7 ;     //����Ϊ��©��� 
	GPIO_Init(LCD1602_GPIO_PORT,&LCD1602_GPIOStruct);
}

void LCD1602_WaitReady(void) //���æ״̬
{
	uint8_t sta;

	GPIOB->ODR =0x00FF;
	RSO(0);
	RWO(1);
	EO(1);
	Delay_Us(1);
	do{
		sta=GPIO_ReadInputDataBit(LCD1602_GPIO_PORT,GPIO_Pin_7);
		EO(0);
	}while(sta);
}

void LCD1602_WriteCmd(uint8_t cmd) //дָ��
{
	LCD1602_WaitReady();
	RSO(0);
	RWO(0);
	EO(0);
	Delay_Us(1);
	EO(1);
	LCD1602_GPIO_PORT->ODR &= (cmd|0xFF00);
	EO(0);
	Delay_Us(400);
}

void LCD1602_WriteDat(uint8_t dat) //д����
{
	LCD1602_WaitReady();
	RSO(1);
	RWO(0);
	Delay_Us(30);
	EO(1);
	LCD1602_GPIO_PORT->ODR &=(dat|0xFF00);
	EO(0);
	Delay_Us(400);
}

void LCD1602_WriteOneDat(uint8_t dat) //д����
{
	LCD1602_WaitReady();
	RSO(1);
	RWO(0);
	Delay_Us(30);
	EO(1);
	LCD1602_GPIO_PORT->ODR &=(dat|0xFF00);
	EO(0);
	Delay_Us(400);
}

void LCD1602_SetCursor(uint8_t x, uint8_t y)
{
    uint8_t addr;
    
    if (y == 0)  //���������Ļ���������ʾRAM�ĵ�ַ
        addr = 0x00 + x;  //��һ���ַ���ַ��0x00��ʼ
    else
        addr = 0x40 + x;  //�ڶ����ַ���ַ��0x40��ʼ
    LCD1602_WriteCmd(addr|0x80);  //����RAM��ַ
}

void LCD1602_ShowStr(uint8_t x, uint8_t y, char *str)
{
		Delay_Us(20000);
    LCD1602_SetCursor(x, y);	//������ʼ��ַ
    while (*str)         //����д��len���ַ�����
    {
        LCD1602_WriteDat(*str++);
    }
}

void LCD1602_Init(void)
{
	  LCD1602_GPIO_Config();   //����GPIO��
    LCD1602_WriteCmd(0X38);  //16*2��ʾ��5*7����8λ���ݽӿ�
    LCD1602_WriteCmd(0x0C);  //��ʾ���������ر�
    LCD1602_WriteCmd(0x06);  //���ֲ�������ַ�Զ�+1
    LCD1602_WriteCmd(0x01);  //����
}

char *str;

void display_print_set(void)
{	

	sprintf(str, "SET:%d",(unsigned int)pid.Sv);
	LCD1602_ShowStr(4,0,str);
	LCD1602_WriteOneDat(0xdf);
	LCD1602_WriteDat('C');
}

void display_print_now(void)
{

		sprintf(str, "NOW:%d.%-3d",(unsigned int)pid.Pv,(unsigned int)((pid.Pv-(unsigned int)pid.Pv)*1000));
		LCD1602_ShowStr(2,1,str);
		LCD1602_WriteOneDat(0xdf);
		LCD1602_WriteDat('C');

		printf("S:%d    ",(unsigned int)pid.Sv);
		printf("P:%d.%-3d    ",(unsigned int)pid.Pv,(unsigned int)((pid.Pv-(unsigned int)pid.Pv)*1000));
		printf("O:%d.%-3d\r",(unsigned int)pid.OUT,(unsigned int)((pid.OUT-(unsigned int)pid.OUT)*1000));
}




