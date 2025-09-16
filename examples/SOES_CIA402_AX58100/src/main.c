#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "delay.h"
#include "usart.h"

#include "esc.h"
#include "ecat_slv.h"
#include "ecatapp.h"

#include "stepper.h"
#include "traj_trapez.h"

void stp_isr_callback(void);
void stp_ll_config(void);

struct traj_trapez_t traj;

int main(void)
{
  	SysTick_Config(SystemCoreClock / 1000);
	APP_USART_Init();
	delay_init(); 
	stp_ll_config();
    STM_EVAL_PBInit(BUTTON_MODE_GPIO);
    ecatapp_init();

	//traj_trapez_prime(&traj, &init);

	while (1) {
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

	NVIC_SetPriority(TIM1_CC_IRQn, 0);
	NVIC_EnableIRQ(TIM1_CC_IRQn);
}

/* 
void stp_isr_callback(void) {
	if (traj_is_running(&traj)) {
		stp_enable(&stp);
	} else {
		stp_disable(&stp);
	}

	stp.tim->ARR = traj.c_n - 1;
	stp.tim->CCR1 = traj.c_n / 2 - 1;
	traj_trapez_advance(&traj);
} */