/*
 * pwm.h
 *
 *  Created on: 2015年10月9日
 *      Author: Administrator
 */

#ifndef PWM_H_
#define PWM_H_
	//#define PWM_CARRIER_FREQ (96000)//Hz
	//TIM_Prescaler = 0, TIM_ClockDivision = TIM_CKD_DIV1
	//#define PWM_PERIOD ((SystemCoreClock / PWM_CARRIER_FREQ) - 1)
	#define PWM_PERIOD (750)//对应频率约为96KHz
	#define PWM_DUTY_ADDR (0x5555)
	extern int16_t pwm_duty;
	void pwm_init(void);
	void pwm_output(int16_t pwm);
#endif /* PWM_H_ */
