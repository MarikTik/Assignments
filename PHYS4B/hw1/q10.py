from globals import *
q1=0.91e-6
q2=2.07e-6
d=0.398
x0 = d - 2*d/(1 + sqrt(q2/q1))
print("x0", x0)