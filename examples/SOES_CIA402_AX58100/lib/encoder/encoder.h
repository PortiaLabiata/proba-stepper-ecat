#include "stm32f4xx.h"

#define WINDOW_SIZE 5
#define ANGLE_TOLERANCE 1.8 / 32

struct adc_driver_s {
	ADC_TypeDef *instance;	
	uint16_t reading_raw;
	float window[WINDOW_SIZE];
	float velocity;
	float position;
	uint32_t prev_update_ms;
};

void adc_init(struct adc_driver_s *adc);
void adc_irq_callback(struct adc_driver_s *adc);
float adc_get_voltage(struct adc_driver_s *adc);
void adc_start(struct adc_driver_s *adc);

void adc_update(struct adc_driver_s *adc);
