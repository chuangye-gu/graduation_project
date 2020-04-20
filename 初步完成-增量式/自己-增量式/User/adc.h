/*
 * adc.h
 *
 *  Created on: 2018年11月14日
 *      Author: Administrator
 */

#ifndef __ADC_H_
#define __ADC_H_
#include "stm32f10x.h"
#include "pid.h"
void adc_init(void);
uint16_t adc_get_value(void);
double adc_get_res(void);
double adc_get_temp(void);
void read_temper(void);
#endif /* ADC_H_ */
