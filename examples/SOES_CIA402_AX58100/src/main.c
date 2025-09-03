#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "delay.h"
#include "usart.h"

#include "esc.h"
#include "ecat_slv.h"
#include "ecatapp.h"
#include "stepper.h"

#include <rml_api_wrapper.h>
#include <rml_vel_ip_wrapper.h>

void stp_isr_callback(void);
void stp_ll_config(void);

int main(void)
{
  	SysTick_Config(SystemCoreClock / 1000);
	APP_USART_Init();
	delay_init(); 
    STM_EVAL_PBInit(BUTTON_MODE_GPIO);
    ecatapp_init();

	rml_vel_ip_ptr_t ip = rml_vel_ip_create();
	rml_vel_ip_current_pos_set(ip, 0);
	rml_vel_ip_current_vel_set(ip, 0);
	rml_vel_ip_current_acc_set(ip, 0);

	stp_ll_config();

	struct stp_t stp = {
		.en_pin = {
			.port = GPIOA,
			.pin = PIN_NUM_10
		},
		.dir_pin = {
			.port = GPIOA,
			.pin = PIN_NUM_9
		},
		.tim = TIM1
	};

	stp_init(&stp);
	stp_register(&stp);
	//stp_enable(&stp);

	while (1)
	{
        ecatapp_loop();
	}
}

void stp_ll_config(void) {
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	
	GPIOA->MODER |= GPIO_MODER_MODER8_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_0;
	GPIOA->AFR[1] |= GPIO_AF_TIM1;

	GPIOA->MODER |= (GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0);
}

void stp_isr_callback(void) {
	asm("nop");
}