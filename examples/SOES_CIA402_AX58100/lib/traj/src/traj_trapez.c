#include "traj_trapez.h"

void traj_trapez_prime(struct traj_trapez_t *traj, struct traj_trapez_init_t *init) {
    traj->c_n = MAGIC * init->f * sqrtf(2 * ALPHA / init->accel);
    traj->n_target_accel = (init->vel_target*init->vel_target) / (2*ALPHA * init->accel);
    if (traj->n_target_accel == 0) {
        traj->n_target_accel = 1;
    }

    traj->n_start_decel = -(int32_t)(traj->n_target_accel * init->accel / init->decel);
    if (traj->n_start_decel == 0) {
        traj->n_start_decel = -1;
    }
    traj->n = 1;
    traj->state = TRAJ_TRAPEZ_STATE_ACCEL;
}

void traj_trapez_advance(struct traj_trapez_t *traj) {
    switch (traj->state) {
        case TRAJ_TRAPEZ_STATE_ACCEL:
            if (traj->n >= traj->n_target_accel) {
                traj->state = TRAJ_TRAPEZ_STATE_RUN;
            } else {
                traj->c_n = traj->c_n - 2*traj->c_n / (4 * traj->n + 1);
                traj->n++;
            }
            break;
        case TRAJ_TRAPEZ_STATE_DECEL:
            if (traj->n >= 0) {
                traj->state = TRAJ_TRAPEZ_STATE_STOP;
            } else {
                traj->c_n = traj->c_n - 2*traj->c_n / (4 * traj->n + 1);
                traj->n++;
            }
            break;
        case TRAJ_TRAPEZ_STATE_RUN:
        case TRAJ_TRAPEZ_STATE_STOP:
        default:
            return;
    }
}

void traj_trapez_execute_cmd(struct traj_trapez_t *traj, enum traj_trapez_cmd_t cmd) {
    switch (cmd) {
        case TRAJ_TRAPEZ_CMD_ACCELERATE:
            if (traj->state == TRAJ_TRAPEZ_STATE_STOP) {
                traj->n = 1;
                traj->state = TRAJ_TRAPEZ_STATE_ACCEL;
            }
            break;
        case TRAJ_TRAPEZ_CMD_DECELERATE:
            if (traj->state == TRAJ_TRAPEZ_STATE_RUN) {
                traj->n = traj->n_start_decel;
                traj->state = TRAJ_TRAPEZ_STATE_DECEL;
            } else if (traj->state == TRAJ_TRAPEZ_STATE_ACCEL) {
                /* Здесь придётся использовать float */
                float accel_ratio = (float)traj->n_start_decel / traj->n_target_accel;
                traj->n = accel_ratio * traj->n;
                traj->state = TRAJ_TRAPEZ_STATE_DECEL;
            }
            break;
        default:
            return;
    }
}