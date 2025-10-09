#pragma once
#include <inttypes.h>
#include <stdbool.h>
#include "stm32f4xx_conf.h"

#ifndef NULL
    #define NULL (void*)0
#endif
#define ALPHA 1.8

/* Macros */
#define pin_set(__PIN__) (__PIN__.port->ODR &= ~(0x1 << (uint32_t)(__PIN__.pin)))
#define pin_reset(__PIN__) (__PIN__.port->ODR |= (0x1 << (uint32_t)(__PIN__.pin)))

#define stp_enable(__STP__) do { \
    (pin_reset((__STP__)->en_pin)); \
    (__STP__)->enabled = true; } while (0)

#define stp_disable(__STP__) do { \
    (pin_set((__STP__)->en_pin)); \
    (__STP__)->enabled = false; } while (0)

#define stp_is_enabled(__STP__) ((__STP__)->enabled)

#define stp_stop_pulses(__STP__) ((__STP__)->tim->CCER &= ~(TIM_CCER_CC1E))
#define stp_start_pulses(__STP__) ((__STP__)->tim->CCER |= TIM_CCER_CC1E)

#define stp_setdir_clockwise(__STP__) (pin_set((__STP__)->dir_pin))
#define stp_setdir_counterclockwise(__STP__) (pin_reset((__STP__)->dir_pin))

#define stp_set_period_us(__STP__, __PERIOD_US__) do { \
    (__STP__)->tim->ARR = __PERIOD_US__;\
    (__STP__)->tim->CCR1 = __PERIOD_US__ / 2 - 1;} while (0)

#define stp_get_period_us(__STP__) ((__STP__)->tim->ARR)

/* Typedefs */

enum pin_num_t {
    PIN_NUM_0 = 0,
    PIN_NUM_1,
    PIN_NUM_2,
    PIN_NUM_3,
    PIN_NUM_4,
    PIN_NUM_5,
    PIN_NUM_6,
    PIN_NUM_7,
    PIN_NUM_8,
    PIN_NUM_9,
    PIN_NUM_10,
    PIN_NUM_11,
    PIN_NUM_12,
    PIN_NUM_13,
    PIN_NUM_14,
    PIN_NUM_15
};

struct stp_pin_t {
	GPIO_TypeDef *port;
	enum pin_num_t pin;
};

struct stp_t {
	struct stp_pin_t en_pin;
	struct stp_pin_t dir_pin;
	TIM_TypeDef *tim;
    bool enabled;
    void (*isr_callback)(void);
};

void stp_init(struct stp_t *stp);
bool stp_register(struct stp_t *stp);
void stp_register_isr_callback(struct stp_t *stp, void (*callback)(void));
