import cmath
import csv
import math
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

xs = []
length = 92
for i in range(length):
    xs.append(i+1)

xs_control = []
length_control = 61
for i in range(length_control):
    xs_control.append(i+1)

xs_control_new = list(map(lambda x: x + length, xs_control))


xs_control_help = xs_control[:-1]
xs_another = xs[:40]

interval_start = 0
interval_end_1= 2000
interval_end_2= 200

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

covid_data_ill = {}
covid_data_ill_cum = {}
covid_data_deceased = {}
covid_data_deceased_cum = {}

covid_data_ill_a = []
covid_data_ill_cum_a = []
covid_data_deceased_a = []
covid_data_deceased_cum_a = []


covid_data_ill_control = {}
covid_data_ill_cum_control = {}
covid_data_deceased_control = {}
covid_data_deceased_cum_control = {}

covid_data_ill_a_control = []
covid_data_ill_cum_a_control = []
covid_data_deceased_a_control = []
covid_data_deceased_cum_a_control = []

with open('covid_19_data.csv', mode='r') as infile:
    reader = csv.reader(infile)
    lastrow = None
    for rows in reader:
        if rows[3] == 'Egypt':
            if lastrow is not None:
                if rows[1].split("/")[0] == '03' or rows[1].split("/")[0] == '04' or  rows[1].split("/")[0] == '05':
                    covid_data_ill[rows[1]] = float(rows[5]) - float(lastrow[5])
                    covid_data_ill_a.append(float(rows[5]) - float(lastrow[5]))
                    covid_data_ill_cum[rows[1]] = float(rows[5])
                    covid_data_ill_cum_a.append(float(rows[5]))
                    covid_data_deceased[rows[1]] = float(rows[6]) - float(lastrow[6])
                    covid_data_deceased_a.append(float(rows[6]) - float(lastrow[6]))
                    covid_data_deceased_cum[rows[6]] = float(rows[6])
                    covid_data_deceased_cum_a.append(float(rows[6]))

                # if rows[1].split("/")[0] == '07' and rows[1].split("/")[1] <= '20'  and rows[1].split("/")[1] > '10':
                if rows[1].split("/")[0] == '06' or rows[1].split("/")[0] == '07':
                    covid_data_ill_control[rows[1]] = float(rows[5]) - float(lastrow[5])
                    covid_data_ill_a_control.append(float(rows[5]) - float(lastrow[5]))
                    covid_data_ill_cum_control[rows[1]] = float(rows[5])
                    covid_data_ill_cum_a_control.append(float(rows[5]))
                    covid_data_deceased_control[rows[1]] = float(rows[6]) - float(lastrow[6])
                    covid_data_deceased_a_control.append(float(rows[6]) - float(lastrow[6]))
                    covid_data_deceased_cum_control[rows[6]] = float(rows[6])
                    covid_data_deceased_cum_a_control.append(float(rows[6]))

            lastrow = rows

# print(covid_data_deceased)
# print(covid_data_ill)
# print(covid_data_deceased_cum)
# print(covid_data_ill_cum)
print(covid_data_ill_a)
print(covid_data_deceased_a)

# covid_data_deceased_a.sort()
# covid_data_ill_a.sort()

def f(x,a,b):
    return a*np.exp(b*x)

def f_lin(x,a,b):
    return a*x + b
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
    a = math.exp(a0)
    return a,b

def approx_exp_new(xs, ys, n):
    sumx = 0
    sumy = 0
    sumx2 = 0
    sumxy = 0
    for i in range(n):
        # sumx += cmath.log(xs[i],cmath.e)
        # sumy += cmath.log(cmath.log(1-ys[i],cmath.e), cmath.e)
        # sumx2 +=cmath.log(xs[i],cmath.e)*cmath.log(xs[i],cmath.e)
        # sumxy+= cmath.log(xs[i],cmath.e)*cmath.log(cmath.log(1-ys[i],cmath.e), cmath.e)
        sumx += math.log(xs[i],math.e)
        sumy += math.log(-(math.log(math.fabs(1-ys[i]),math.e)), math.e)
        sumx2 += math.log(xs[i],math.e)*math.log(xs[i],math.e)
        sumxy+= math.log(xs[i],math.e)*math.log(-(math.log(math.fabs(1-ys[i]),math.e)), math.e)
    a1 = (n * sumxy - (sumx * sumy)) / (n * sumx2 - sumx * sumx)
    a0 = (sumy - a1 * sumx) / n

    b = a1
    a = -math.exp(a0)
    return a.real,b.real
    # a = math.exp(a0)
    # return a,b

ys_norm = []
for i in range(length):
    ys_norm.append(interval_start + i*interval_end_1/length)

ys_norm_2= []
for i in range(length):
    ys_norm_2.append(interval_start + i*interval_end_2/length)


ys_empir_1 = []
for i in range(length):
    ys_empir_1.append(f_empir(covid_data_ill_a[i],length, ys_norm))

ys_empir_2 = []
for i in range(length):
    ys_empir_2.append(f_empir(covid_data_deceased_a[i],length, ys_norm_2))

print(ys_empir_1)
print(ys_empir_2)

def f_new(x,a,b):
    # print(math.exp(x))
    # print(math.pow(math.exp(x), b))
    # print(math.exp(a*math.pow(math.exp(x), b)))
    return 1 - np.exp(a*pow(x, b))

def f_new_1(x, a, b):
    return 1- np.exp(a * x)

ys_empir_1_help = []
for i in range(length):
    ys_empir_1_help.append(-np.log(1-ys_empir_1[i]))

xs_help = []
for i in range(length):
    xs_help.append(-xs[i])

A = np.vstack([np.log(xs), np.ones(len(xs))]).T
beta_1, log_alpha = np.linalg.lstsq(A, np.log(ys_empir_1_help), rcond = None)[0]
alpha_1 = np.exp(log_alpha)

print(alpha_1,  beta_1)

ys_empir_2_help = []
for i in range(length):
    ys_empir_2_help.append(-np.log(1-ys_empir_2[i]))

A = np.vstack([np.log(xs), np.ones(len(xs))]).T
beta_2, log_alpha = np.linalg.lstsq(A, np.log(ys_empir_2_help), rcond = None)[0]
alpha_2 = np.exp(log_alpha)

print(alpha_2,  beta_2)

a_new_1, b_new_1 = approx_exp_new(xs,ys_empir_1,length)

a_new_2, b_new_2 = approx_exp_new(xs,ys_empir_2,length)

max_ill_cum = 0
for c in covid_data_ill_cum_a:
    if c > max_ill_cum:
        max_ill_cum = c

max_deceased_cum = 0
for c in covid_data_deceased_cum_a:
    if c > max_deceased_cum:
        max_deceased_cum = c

covid_data_ill_cum_norm = []
for c in covid_data_ill_cum_a:
    covid_data_ill_cum_norm.append(c/max_ill_cum)

covid_data_deceased_cum_norm = []
for c in covid_data_deceased_cum_a:
    covid_data_deceased_cum_norm.append(c/max_deceased_cum)

print(covid_data_deceased_cum_norm)
print(covid_data_ill_cum_norm)

max_ill_simple = 0
for c in covid_data_ill_a:
    if c > max_ill_simple:
        max_ill_simple = c

max_deceased_simple = 0
for c in covid_data_deceased_a:
    if c > max_deceased_simple:
        max_deceased_simple = c

covid_data_ill_simple_norm = []
for c in covid_data_ill_a:
    covid_data_ill_simple_norm.append(c/max_ill_simple)

covid_data_deceased_simple_norm = []
for c in covid_data_deceased_a:
    covid_data_deceased_simple_norm.append(c/max_deceased_simple)

print(covid_data_deceased_simple_norm)
print(covid_data_ill_simple_norm)

# a_new_3, b_new_3 = approx_exp_new(xs,covid_data_ill_cum_norm[:-1],length-1)
# print(a_new_3, b_new_3)
res_3, res3_1 = curve_fit(f_new, np.array(xs), np.array(covid_data_ill_cum_norm), p0 = [0, 1])
a_new_3 = res_3[0]
b_new_3 = res_3[1]

print(a_new_3, b_new_3)

res_4, res4_1= curve_fit(f_new, np.array(xs), np.array(covid_data_deceased_cum_norm),  p0 = [0, 1])
a_new_4 = res_4[0]
b_new_4 = res_4[1]
print(a_new_4, b_new_4)



# a_new_4, b_new_4 = approx_exp_new(xs,covid_data_deceased_cum_norm[:-1],length-1)

print(a_new_1,  b_new_1)
print(a_new_2,  b_new_2)


# def f_new(x,a,b):
#     return 1 - math.exp(-a*math.pow(math.exp(x), b))



ys_new_1 = []
for i in range(length):
    ys_new_1.append(f_new(i,a_new_1,b_new_1))

ys_new_2 = []
for i in range(length):
    ys_new_2.append(f_new(i,a_new_2,b_new_2))

ys_new_3 = []
for i in range(length):
    ys_new_3.append(f_new(xs[i], a_new_3, b_new_3))

ys_new_4 = []
for i in range(length):
    ys_new_4.append(f_new(xs[i], a_new_4, b_new_4))

print(ys_new_1)
print(ys_new_2)
print(ys_new_3)
print(ys_new_4)


xs_1 = []
xs_2 = []
ys_1 = []
ys_2 = []

for i in range(length):
    if i != 0:
        xs_1.append(i)
        ys_1.append(ys_empir_1[i - 1])
        xs_2.append(i)
        ys_2.append(ys_empir_2[i - 1])
    xs_1.append(i)
    ys_1.append(ys_empir_1[i])
    xs_2.append(i)
    ys_2.append(ys_empir_2[i])


# plt.xlim([0, length])
# plt.ylim([0, 1])
# plt.plot(xs_1,ys_1)
# plt.show()
#
# plt.xlim([0, length])
# plt.ylim([0, 1])
# plt.plot(xs_2,ys_2)
# plt.show()
#
# plt.xlim([0, length])
# plt.ylim([0, 1])
# plt.plot(xs,ys_new_1)
# plt.show()
#
# plt.xlim([0, length])
# plt.ylim([0, 1])
# plt.plot(xs,ys_new_2)
# plt.show()


plt.xlim([0, length])
plt.ylim([0, 1])
plt.plot(xs,ys_new_3, label="theoretical prob distib ill")

plt.xlim([0, length])
plt.ylim([0, 1])
plt.plot(xs,covid_data_ill_cum_norm, label="empirical prob distib ill")
plt.legend()
plt.show()

plt.xlim([0, length])
plt.ylim([0, 1])
plt.plot(xs,ys_new_4, label="theoretical prob distib deceased")

plt.xlim([0, length])
plt.ylim([0, 1])
plt.plot(xs,covid_data_deceased_cum_norm, label="empirical prob distib deceased")
plt.legend()
plt.show()


max = 0

for i in range(length):
    v = math.fabs(covid_data_deceased_cum_norm[i] - ys_new_4[i])
    if v > max:
        max = v
print(max)
print(max <= 0.03)


max = 0

for i in range(length):
    v = math.fabs(covid_data_ill_cum_norm[i] - ys_new_3[i])
    if v > max:
        max = v
print(max)
print(max <= 0.03)

a_div = a_new_4/a_new_3

b_div = b_new_4/b_new_3

print(a_div,  b_div)


max_ill_control = 0
for c in covid_data_ill_a_control:
    if c > max_ill_control:
        max_ill_control = c

max_deceased_control = 0
for c in covid_data_deceased_a_control:
    if c > max_deceased_control:
        max_deceased_control = c

covid_data_ill_control_norm = []
for c in covid_data_ill_a_control:
    if c != max_ill_control:
       covid_data_ill_control_norm.append(c/max_ill_control)


compare = []
for i in range(length_control-1):
    val = (math.log(math.fabs(1-covid_data_ill_control_norm[i]), math.e)/a_new_3).real
    val_pow = math.pow(val, b_new_4/b_new_3)
    compare.append(1-cmath.exp(a_new_4*val_pow).real)
    # compare.append(pow(covid_data_ill_control_norm[i]/a_new_3, b_new_4/b_new_3))


for i in range(length_control-1):
    compare[i]*=max_deceased_control


print(compare)

max_compare = 0
max_origin = 0

for i in range(length_control-1):
    if covid_data_deceased_a_control[i] > max_origin:
        max_origin = covid_data_deceased_a_control[i]
    if compare[i] > max_compare:
        max_compare = compare[i]







koef = 15
def contagious ():
    r = []
    for i in range(length-1 - koef):
        if i != 0:
            # r.append((covid_data_ill_cum_a[i+koef]+covid_data_ill_cum_a[i-1+koef]+covid_data_ill_cum_a[i-2+koef]+covid_data_ill_cum_a[i-3+koef])/
            #          (covid_data_ill_cum_a[i-4+koef]+covid_data_ill_cum_a[i-5+koef]+covid_data_ill_cum_a[i-6+koef]+covid_data_ill_cum_a[i-7+koef]))
            r.append(covid_data_ill_cum_a[i + koef]  / covid_data_ill_cum_a[i - 1 + koef])

        else:
            r.append(0)
    return r

r = contagious()

# ill_predicted = []
#
# print(covid_data_ill_a_control[0])
#
# for i in range(length_control-1):
#     if i == 0:
#         ill_predicted.append(covid_data_ill_a_control[0])
#     else:
#         ill_predicted.append(r[i]*ill_predicted[i-1])
# print(covid_data_ill_a_control)
# print(ill_predicted)

# a_r, b_r = approx_lin(xs[50:],r[50:],length-51)
a_r, b_r = curve_fit(f_lin, np.array(xs[:-1-koef]), np.array(r[:]))[0]

print(a_r,  b_r)

# def f_new(x,a,b):
#     return 1 - math.exp(-a*math.pow(math.exp(x), b))



r_new = []
for i in range(length_control):
    r_new.append(f_lin(i, a_r, b_r))

print(r)
print(r_new)

r = r+r_new


# a_d, b_d = approx_exp_new(xs_another,r_new[length_control-10:], 10)
#
# for i in range(10):
#     r_new[length_control-10+i] = f_new(i, a_d, b_d)

ill_predicted_new_cum = []

for i in range(length_control-1):
    if i == 0:
        ill_predicted_new_cum.append(covid_data_ill_cum_a_control[0])
    else:
        ill_predicted_new_cum.append(r_new[i]*ill_predicted_new_cum[i-1])
print(ill_predicted_new_cum)

ill_predicted_new = []
for i in range(length_control-1):
    if i == 0:
        ill_predicted_new.append(covid_data_ill_a_control[0])
    else:
        ill_predicted_new.append(ill_predicted_new_cum[i] - ill_predicted_new_cum[i-1])
print(ill_predicted_new)

print(covid_data_ill_a_control)

# plt.xlim([0, length_control-1])
# plt.ylim([0, 2000])
# plt.plot(xs_control_help, ill_predicted_new)
# plt.show()
#
# plt.xlim([0, length_control])
# plt.ylim([0, 2000])
# plt.plot(xs_control, covid_data_ill_a_control)
# plt.show()


max_ill_new_predicted = 0
for c in ill_predicted_new:
    if c > max_ill_new_predicted:
        max_ill_new_predicted = c

ill_predicted_new_norm = []
for c in ill_predicted_new:
    if c != max_ill_new_predicted:
       ill_predicted_new_norm.append(c/max_ill_new_predicted)
    # else:
    #     ill_predicted_new_norm.append(0.999999999)

deceased_predicted = []
for i in range(length_control-2):
    val = math.log(1-ill_predicted_new_norm[i], math.e)/(a_new_3)
    val_pow = pow(val, b_new_4/b_new_3)
    deceased_predicted.append(1-math.exp(a_new_4*val_pow.real))
    # deceased_predicted.append(pow(ill_predicted_new_norm[i]/a_new_3, b_new_4/b_new_3))


for i in range(length_control-2):
    deceased_predicted[i]*=max_deceased_control

print(deceased_predicted)
print(covid_data_deceased_a_control)


plt.xlim([0, length+length_control])
plt.ylim([0, 500])
plt.plot(xs, covid_data_deceased_a, label="deceased data")

plt.xlim([0, length+length_control])
plt.ylim([0, 500])
plt.plot(xs_control_new, covid_data_deceased_a_control, label="deceased data control")

plt.xlim([0, length+length_control])
plt.ylim([0, 500])
plt.plot(xs_control_new[:-2], deceased_predicted, label="deceased data predicted")

plt.xlim([0, length+length_control])
plt.ylim([0, 500])
plt.plot(xs_control_new[:-1], compare, label="deceased by ill data")
plt.legend()
plt.show()



plt.xlim([0, length+length_control])
plt.ylim([0, 500000])
plt.plot(xs_control_new[:-1], ill_predicted_new_cum, label="ill data cum predicted")

plt.xlim([0, length+length_control])
plt.ylim([0, 500000])
plt.plot(xs_control_new, covid_data_ill_cum_a_control, label="ill data cum control")

plt.xlim([0, length+length_control])
plt.ylim([0, 500000])
plt.plot(xs, covid_data_ill_cum_a, label="ill data cum")
plt.legend()
plt.show()
#
#
plt.xlim([0, length+length_control])
plt.ylim([0, 5000])
plt.plot(xs_control_new[:-1], ill_predicted_new,  label="ill data predicted")

plt.xlim([0, length+length_control])
plt.ylim([0, 5000])
plt.plot(xs_control_new, covid_data_ill_a_control, label="ill data control")

plt.xlim([0, length+length_control])
plt.ylim([0, 5000])
plt.plot(xs, covid_data_ill_a, label="ill data")
plt.legend()
plt.show()






