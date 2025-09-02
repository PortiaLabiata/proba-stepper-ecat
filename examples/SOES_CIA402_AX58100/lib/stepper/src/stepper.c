#include <stepper.h>

static uint32_t hclk_freq_hz(void) {
	switch ((RCC->CFGR & RCC_CFGR_HPRE)) {
		case RCC_CFGR_HPRE_DIV1:
			return SystemCoreClock;
		case RCC_CFGR_HPRE_DIV2:
			return SystemCoreClock / 2;
		case RCC_CFGR_HPRE_DIV4:
			return SystemCoreClock / 4;
		case RCC_CFGR_HPRE_DIV8:
			return SystemCoreClock / 8;
		case RCC_CFGR_HPRE_DIV16:
			return SystemCoreClock / 16;
		case RCC_CFGR_HPRE_DIV64:
			return SystemCoreClock / 64;
		case RCC_CFGR_HPRE_DIV256:
			return SystemCoreClock / 256;
		case RCC_CFGR_HPRE_DIV512:
			return SystemCoreClock / 512;
		default:
			return 0; // Случилось нечто ужасное
	}
}

static uint32_t pcklk2_freq_hz(void) {
	uint32_t freq = hclk_freq_hz();
	switch (RCC->CFGR & RCC_CFGR_PPRE2) {
		case RCC_CFGR_PPRE2_DIV1:
			return freq;
		case RCC_CFGR_PPRE2_DIV2:
			return freq / 2;
		case RCC_CFGR_PPRE2_DIV4:
			return freq / 4;
		case RCC_CFGR_PPRE2_DIV16:
			return freq / 16;
		default:
			return 0;
	}
}

static uint32_t pcklk1_freq_hz(void) {
	uint32_t freq = hclk_freq_hz();
	switch (RCC->CFGR & RCC_CFGR_PPRE1) {
		case RCC_CFGR_PPRE1_DIV1:
			return freq;
		case RCC_CFGR_PPRE1_DIV2:
			return freq / 2;
		case RCC_CFGR_PPRE1_DIV4:
			return freq / 4;
		case RCC_CFGR_PPRE1_DIV16:
			return freq / 16;
		default:
			return 0;
	}
}

static struct stp_t *_stp_instance = NULL; // Синглетон

bool stp_register(struct stp_t *stp) {
	if (_stp_instance != NULL) {
		return false;
	}
	_stp_instance = stp;
	return true;
}

// TODO: Добавить проверки на NULL и так далее
void stp_init(struct stp_t *stp) {
	stp_disable(stp);

	/* Конфигурация прескейлера */
	uint16_t psc = pcklk2_freq_hz() / 1000000;
	// Господи, выглядит прямо как в ST HAL. Буэээ :(
	if ((RCC->CFGR & RCC_CFGR_PPRE2) != RCC_CFGR_PPRE2_DIV1) {
		psc *= 2;
	}
	stp->tim->PSC = psc - 1;
	if (stp->tim == TIM1 || stp->tim == TIM8) {
		stp->tim->BDTR |= TIM_BDTR_MOE;
	}

	/* Начальная конфигурация ARR */
	stp->tim->ARR = 10000 - 1;
	stp->tim->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // Режим ШИМ 2
	stp->tim->CCER |= TIM_CCER_CC1E; // Включаем первый канал
	stp->tim->CCR1 = stp->tim->ARR / 2 - 1;
	stp->tim->DIER |= TIM_DIER_UIE;
	stp->tim->EGR |= TIM_EGR_UG;
	stp->tim->CR1 |= TIM_CR1_CEN;
}

void stp_register_isr_callback(struct stp_t *stp, void (*callback)(void)) {
	stp->isr_callback = callback;
}
