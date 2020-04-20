#include "usart.h"

int fputc(int ch, FILE *p)
{
	USART_SendData(USART1, (u8)ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return ch;
}
void usart_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	//PA9 TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//PA10 RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//串口参数初始化
	USART_DeInit(USART1);
	USART_InitStructure.USART_BaudRate = 9600 / 9;                  //波特率9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //字长8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;      //1位停止字节
	USART_InitStructure.USART_Parity = USART_Parity_No;         //无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//打开Rx接收和Tx发送功能
	USART_Init(USART1,&USART_InitStructure);                   //初始化
	USART_Cmd(USART1, ENABLE);                                  //启动串口
	USART_ClearFlag(USART1, USART_FLAG_TC);                     //发送完成标志位
}

void usart_putchar(char c)
{
	USART_SendData(USART1, c);
	//等待发送完成
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

char usart_getchar(void)
{
	/* Loop until the USARTz Receive Data Register is not empty */
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	/* Store the received byte in RxBuffer */
	return (USART_ReceiveData(USART1) & 0x00ff);

}

void usart_puts(const char *str)
{
	for (; *str; str++)
	{
		usart_putchar(*str);
	}
}
