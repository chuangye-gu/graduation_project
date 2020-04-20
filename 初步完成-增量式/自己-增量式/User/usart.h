/*
 * usart.h
 *
 *  Created on: 2019年4月3日
 *      Author: ac
 */

#ifndef USART_H_
#define USART_H_
#include "stm32f10x.h"
#include <stdio.h>
int fputc(int ch, FILE *p);
	void usart_init(void);
	void usart_putchar(char c);
	char usart_getchar(void);
	void usart_puts(const char *str);

#endif /* USART_H_ */
