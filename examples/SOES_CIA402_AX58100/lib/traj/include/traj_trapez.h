#pragma once
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>

#define ALPHA   1.8

enum traj_trapez_state_t {
    TRAJ_TRAPEZ_STATE_STOP,
    TRAJ_TRAPEZ_STATE_ACCEL,
    TRAJ_TRAPEZ_STATE_DECEL,
    TRAJ_TRAPEZ_STATE_RUN
};

enum traj_trapez_cmd_t {
    TRAJ_TRAPEZ_CMD_ACCELERATE,
    TRAJ_TRAPEZ_CMD_DECELERATE
};

struct traj_trapez_init_t {
    int32_t f;
    int16_t accel;
    int16_t decel;
    int16_t omega_target;
};

struct traj_trapez_t {
    volatile uint16_t n;
    volatile int32_t c_n;
    int16_t omega_0;
    int16_t accel;

    int16_t n_omega_target;
    int16_t n_decel_start;
};

void traj_trapez_prime(struct traj_trapez_t *traj, struct traj_trapez_init_t *init);
void traj_trapez_advance(struct traj_trapez_t *traj);