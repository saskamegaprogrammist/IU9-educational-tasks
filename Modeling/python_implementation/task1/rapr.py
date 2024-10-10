import cmath
import math
import matplotlib.pyplot as plt
import numpy as np

interval_start = 0
interval_end = 15000
length = 16

def heavyside(x):
   if x<0:
       return 0
   else:
       return 1

def f_empir(x, n, xs):
    sum = 0
    for x_i in xs:
        sum += heavyside(x-x_i)
    return sum/n



def approx_exp_new(xs, ys, n):
    sumx = 0
    sumy = 0
    sumx2 = 0
    sumxy = 0
    for i in range(n):
        sumx += cmath.log(xs[i],cmath.e)
        sumy += cmath.log(cmath.log(1-ys[i],cmath.e), cmath.e)
        sumx2 += cmath.log(xs[i],cmath.e)*cmath.log(xs[i],cmath.e)
        sumxy+= cmath.log(xs[i],cmath.e)*cmath.log(cmath.log(1-ys[i],cmath.e), cmath.e)
    a1 = (n * sumxy - (sumx * sumy)) / (n * sumx2 - sumx * sumx)
    a0 = (sumy - a1 * sumx) / n

    b = a1
    a = cmath.exp(a0)
    return a.real,b.real

def approx_exp(xs, ys, n):
    sumx = 0
    sumy = 0
    sumx2 = 0
    sumxy = 0
    for i in range(n):
        sumx += xs[i]
        sumy += math.log(ys[i], math.e)
        sumx2 += xs[i]*xs[i]
        sumxy+= xs[i]*math.log(ys[i],math.e)
    a1 = (n * sumxy - (sumx * sumy)) / (n * sumx2 - sumx * sumx)
    a0 = (sumy - a1 * sumx) / n

    b = a1
    a = cmath.exp(a0)
    return a.real,b.real

def approx_lin(xs, ys, n):
    sumx = 0
    sumy = 0
    sumx2 = 0
    sumxy = 0
    for i in range(n):
        sumx += xs[i]
        sumy += ys[i]
        sumx2 += xs[i]*xs[i]
        sumxy+= xs[i]*ys[i]
    a = (n * sumxy - (sumx * sumy)) / (n * sumx2 - sumx * sumx)
    b = (sumy - a * sumx) / n
    return a, b

def f_new(x,a,b):
    return 1 - math.exp(a*math.pow(math.exp(x), b))

def flin(x,a,b):
    return a*x + b

def f(x,a,b):
    return a*math.exp(b*x)

ys_norm = []
for i in range(length):
    ys_norm.append(interval_start + i*interval_end/length)
xs = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]
ys = [11450, 10441, 10416,11263, 10906, 10909,10478,10145,9342,8976,9167,9695,9808,9985,9347,9305]


ys_old = [11450, 10441, 10416,11263, 10906, 10909,10478,10145,9342,8976,9167,9695,9808,9985,9347,9305]


ys.sort()
xs_sorted = []

for y in ys:
    for i in range(length):
        if y == ys_old[i]:
            xs_sorted.append(xs[i])
            break


ys_empir = []
for i in range(length):
    ys_empir.append(f_empir(ys[i],length, ys_norm))

a, b = approx_exp(xs,ys_empir,length)

a_new, b_new = approx_exp_new(xs,ys_empir,length)

print(a_new, b_new)
print(a, b)


a_lin, b_lin = approx_lin(xs,ys_empir,length)

ys_new = []
for i in range(length):
    ys_new.append(f_new(i,a_new,b_new))

ys_new_lin = []
for i in range(length):
    ys_new_lin.append(flin(i,a_lin,b_lin))

# ys_empir_new = []
# for i in range(length):
#     ys_empir_new.append(f_empir(ys_new[i],length, ys_norm))

max = 0
for i in range(length):
    # print(ys_new[i])
    # print(" ")
    # print(ys_empir[i])
    # print("\n")
    v = math.fabs(ys_new[i]-ys_empir[i])
    if v > max:
        max = v

print(max)
print(max <= 0.03)

max_lin = 0
for i in range(length):
    # print(ys_new_lin[i])
    # print(" ")
    # print(ys_empir[i])
    # print("\n")
    v = math.fabs(ys_new_lin[i]-ys_empir[i])
    if v > max_lin:
        max_lin = v

print(max_lin)
print(max_lin <= 0.03)

xs_1 = []
xs_2 = []
ys_1 = []
ys_2 = []


for i in range(length):
    if i != 0:
        xs_1.append(i)
        ys_1.append(ys_empir[i-1])
        # xs_2.append(i)
        # ys_2.append(ys_empir_new[i - 1])
    xs_1.append(i)
    ys_1.append(ys_empir[i])
    # xs_2.append(i)
    # ys_2.append(ys_empir_new[i])
plt.xlim([0, 20])
plt.ylim([0, 1])
plt.plot(xs_1,ys_1)
plt.show()
plt.xlim([0, 20])
plt.ylim([0, 1])
plt.plot(xs,ys_new)
plt.show()
plt.xlim([0, 20])
plt.ylim([0, 1])
plt.plot(xs,ys_new_lin)
plt.show()


# x_grid = np.linspace(1, 100, 100)
# y_grid = []
# for x in x_grid:
#     y_grid.append(f(x, a, b))
# plt.plot(x_grid,y_grid)
# plt.show()

