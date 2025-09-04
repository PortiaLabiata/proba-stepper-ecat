#pragma once
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>

#define ALPHA   1.8
#define MAGIC   0.676

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
    uint32_t f;
    uint32_t accel;
    uint32_t decel;
    uint32_t vel_target;
};

struct traj_trapez_t {
    volatile int32_t n;
    volatile int32_t c_n;
    int32_t n_target_accel;
    int32_t n_start_decel;
    enum traj_trapez_state_t state;
};

void traj_trapez_prime(struct traj_trapez_t *traj, struct traj_trapez_init_t *init);
void traj_trapez_advance(struct traj_trapez_t *traj);
void traj_trapez_execute_cmd(struct traj_trapez_t *traj, enum traj_trapez_cmd_t cmd);