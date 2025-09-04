#include "traj_trapez.h"

static int16_t square(int16_t x) {
    // Можно было бы использовать pow, но там скорее всего цикл
    return x*x;
}

static int32_t traj_trapez_get_c0(struct traj_trapez_init_t *init, int32_t omega_0) {
    return (init->f / init->accel) * (-omega_0 + sqrtf(square(omega_0) + 2*init->accel*ALPHA));
}

static int16_t traj_trapez_get_n_target(struct traj_trapez_init_t *init, int16_t omega_0) {
    return 0;
}

static float traj_trapez_get_magic(struct traj_trapez_init_t *init, int16_t omega_0) {
    return (sqrtf(square(omega_0) + 4*init->accel*ALPHA) - sqrtf(square(omega_0) + 2*init->accel*ALPHA)) / \
        ((sqrtf(square(omega_0) + 2*init->accel*ALPHA) - omega_0) * ((2*square(omega_0) + 3*ALPHA*init->accel) / (2*square(omega_0) + 5*ALPHA*init->accel)));
}

void traj_trapez_prime(struct traj_trapez_t *traj, struct traj_trapez_init_t *init) {
    // В самом начале скорость ноль
    traj->c_n = traj_trapez_get_c0(init, 0);
    traj->n_omega_target = traj_trapez_get_n_target(init, 0);
    traj->accel = init->accel;
    traj->omega_0 = 0;
    traj->n = 1;
}

void traj_trapez_advance(struct traj_trapez_t *traj) {
    traj->c_n *= (2*square(traj->omega_0) + ALPHA*traj->accel*(4*traj->n - 1)) / \
        (2*square(traj->omega_0) + ALPHA*traj->accel*(4*traj->n + 1));
    traj->n++;
}