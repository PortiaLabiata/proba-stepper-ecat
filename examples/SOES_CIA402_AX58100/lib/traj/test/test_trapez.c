#include <stdio.h>
#include <traj_trapez.h>

void traj_test(struct traj_trapez_t *traj, struct traj_trapez_init_t *init, int n);

int main(int argc, char **argv) {
    struct traj_trapez_t traj;
    struct traj_trapez_init_t init = {
        .accel = 10,
        .decel = 10,
        .f = 1000000,
        .omega_target = 30
    };
    traj_trapez_prime(&traj, &init);
    traj_test(&traj, &init, 100);
}

void traj_test(struct traj_trapez_t *traj, struct traj_trapez_init_t *init, int n) {
    static float t = 0;
    for (int i = 0; i < n; i++) {
        float delta_t = (float)traj->c_n / init->f;
        printf("%f,%f,%f,%d\n", t, delta_t, ALPHA * init->f / (float)traj->c_n, traj->c_n);
        t += delta_t;
        traj_trapez_advance(traj);
    }
}