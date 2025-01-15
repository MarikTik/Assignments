from globals import *
q=55e-9
D1 = 0.18
D2 = 0.07
theta = atan(D2/D1)
fx_net = q ** 2 * k / D1 ** 2 + q ** 2 * k / (D1 ** 2 + D2 ** 2) * cos(theta)
print("fx_net", fx_net)
fy_net = -q * q * k / (D2 ** 2) + (q**2 * k / (D1**2 + D2 ** 2)) * sin(theta)
print("fy_net", fy_net)
f_net = sqrt(fx_net ** 2 + fy_net ** 2)
print("f_net", f_net)
phi = atan(fy_net / fx_net) * 180 / pi
print("phi", phi)