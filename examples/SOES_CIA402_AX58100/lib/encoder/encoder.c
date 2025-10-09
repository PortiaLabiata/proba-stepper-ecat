#include "encoder.h"
#include <string.h>
#include <delay.h>

void adc_init(struct adc_driver_s *adc) {
	adc->instance->CR1 &= ~ADC_CR1_RES;
	adc->instance->CR2 |= ADC_CR2_CONT;
	adc->instance->SQR3 |= ADC_SQR3_SQ1_1; // Channel 2
	adc->instance->CR1 |= ADC_CR1_EOCIE;
	adc->instance->SMPR2 |= (ADC_SMPR2_SMP2_2 | ADC_SMPR2_SMP2_1 | ADC_SMPR2_SMP2_0);

	NVIC_SetPriority(ADC_IRQn, 1);
	NVIC_EnableIRQ(ADC_IRQn);
}

void adc_start(struct adc_driver_s *adc) {
	adc->instance->CR2 |= ADC_CR2_ADON;
	adc->instance->CR2 |= ADC_CR2_SWSTART;
}

void adc_irq_callback(struct adc_driver_s *adc) {
	adc->reading_raw = adc->instance->DR;
}

 float adc_get_voltage(struct adc_driver_s *adc) {
	return (float)adc->reading_raw / 4096;
}

static void adc_irq_disable(void) {
	//adc->instance->CR1 &= ~(ADC_CR1_EOCIE);
	NVIC_DisableIRQ(ADC_IRQn);
}

static void adc_irq_enable(void) {
	//adc->instance->CR1 |= ADC_CR1_EOCIE;
	NVIC_EnableIRQ(ADC_IRQn);
}

static float average(float arr[], int size) {
	float acc = 0;
	for (int i = 0; i < size; i++) {
		acc += arr[i];	
	}
	return acc / size;
}

void adc_update(struct adc_driver_s *adc) {
	static float prev_angle = 0;
	adc_irq_disable();
	float angle = (float)adc->reading_raw * 360 / 4096;
	adc_irq_enable();
	uint32_t now_ms = millis();

	memmove(adc->window, adc->window+1, (WINDOW_SIZE - 1)*sizeof(float));
	adc->window[WINDOW_SIZE-1] = angle;
	float angle_average = average(adc->window, WINDOW_SIZE);
	float delta_angle = prev_angle - angle_average;
	prev_angle = angle_average;

	adc->velocity = delta_angle / (now_ms - adc->prev_update_ms);
	if (adc->velocity < 0) {
		adc->position -= delta_angle;
	} else {
		adc->position += delta_angle;
	}
}
