from math import sqrt

accel = 20
decel = 10
vel_target = 30
omega_0 = 0
f = 1e6
ALPHA = 1.8

magic = (sqrt(omega_0**2 + 4*accel*ALPHA) - sqrt(omega_0**2 + 2*accel*ALPHA)) / \
    ((sqrt(omega_0**2 + 2*accel*ALPHA) - omega_0)*(2*omega_0**2+3*ALPHA*accel) / (2*omega_0**2+5*ALPHA*accel))
c_n = int(magic * f / accel) * (-omega_0 + sqrt(omega_0**2 + 2*accel*ALPHA))

for n in range(1, 11):
    print(f * ALPHA / c_n, c_n)
    c_n = c_n * int(2*omega_0**2 + ALPHA*accel*(4*n - 1)) / int(2*omega_0**2 + ALPHA*accel*(4*n + 1))
    n += 1