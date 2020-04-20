#include "adc.h"

#define ADC_BUFFER_SIZE (4)

static volatile uint16_t adc_buffer[ADC_BUFFER_SIZE];

static void adc_dma_init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	/* DMA1 channel1 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)adc_buffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = ADC_BUFFER_SIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);
}

void adc_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	//时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);
	//PA0/ADC12_IN0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//ADC初始化
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);//72MHz / 8 = 9MHz
	ADC_DeInit(ADC1);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	/* Enable ADC1 reset calibration register */
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
//	while(ADC_GetResetCalibrationStatus(ADC1));
	/* Start ADC1 calibration */
//	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
//	while(ADC_GetCalibrationStatus(ADC1));
	adc_dma_init();//DMA数据采集初始化
	/* Start ADC1 Software Conversion */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

uint16_t adc_get_value(void)
{
	int i;
	uint32_t sum;
	sum = 0;
	for (i = 0; i < ADC_BUFFER_SIZE; i++)
	{
		sum += adc_buffer[i];
	}
	return sum / ADC_BUFFER_SIZE;
}

double adc_get_temp()
{
	int i;
	double temp;
	uint32_t sum;
	sum = 0;
	for (i = 0; i < ADC_BUFFER_SIZE; i++)
	{
		sum += adc_buffer[i];
	}
	sum *= 25;
	temp = sum / 819.0;
	temp /= ADC_BUFFER_SIZE;
//	temp *=10;
	return temp;
}
extern u16 Kms10;
void read_temper()//??????
{
//  u16 d;
	static u16 samtim;
	samtim++;
	if(samtim<pid.T)  
		return ;
//  d=read_max6675();//¶ÁÈ¡MAX6675µ±Ç°µÄÎÂ¶ÈÖµ
//  pid.Pv=((d>>4)&0x0fff)*0.25;//????
	
	pid.Pv=adc_get_temp();
  samtim=0;
}
