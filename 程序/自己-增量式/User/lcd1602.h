#ifndef _BSP_LCD1602_H
#define _BSP_LCD1602_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "systick.h"
#include "pid.h"

#define LCD1602_CLK  RCC_APB2Periph_GPIOB  

#define LCD1602_GPIO_PORT   GPIOB

#define LCD1602_E    GPIO_Pin_10              //����ʹ������
#define LCD1602_RW   GPIO_Pin_11             //�����д����
#define LCD1602_RS   GPIO_Pin_12             //�������ݡ���������



#define EO(X)         X? (GPIO_SetBits(LCD1602_GPIO_PORT,LCD1602_E)):(GPIO_ResetBits(LCD1602_GPIO_PORT,LCD1602_E))
#define RWO(X)        X? (GPIO_SetBits(LCD1602_GPIO_PORT,LCD1602_RW)):(GPIO_ResetBits(LCD1602_GPIO_PORT,LCD1602_RW))
#define RSO(X)        X? (GPIO_SetBits(LCD1602_GPIO_PORT,LCD1602_RS)):(GPIO_ResetBits(LCD1602_GPIO_PORT,LCD1602_RS))

//ֻ����ĳ��GPIO�ڵĵͰ�λ
#define DB0					GPIO_Pin_0
#define DB1					GPIO_Pin_1
#define DB2					GPIO_Pin_2
#define DB3					GPIO_Pin_3
#define DB4					GPIO_Pin_4
#define DB5					GPIO_Pin_5
#define DB6					GPIO_Pin_6
#define DB7					GPIO_Pin_7

void LCD1602_Init(void);  //��ʼ��LCD602��
void LCD1602_ShowStr(uint8_t x, uint8_t y, char *str);
void LCD1602_WriteDat(uint8_t dat);
void LCD1602_WriteOneDat(uint8_t dat);
void display_print(void);
void display_print_set(void);
void display_print_now(void);


#endif //_BSP_LCD1602_H
