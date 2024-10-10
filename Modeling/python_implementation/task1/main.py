import copy
import math
import random

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy import interpolate
from scipy.optimize import least_squares

from triangulation import triangulation

ax = plt.axes(projection='3d')
X = [
    219,
    760,
    331,
    138,
    836,
    396,
    391,
    146,
    100,
    50,
    181,
    407,
    195,
    360,
    319,
    427,
    166,
    244,
    269,
    298,
    68,
    306,
    77
]


Y = [
    5398064,
    7690863,
    3902888,
    1549151,
    5675462,
    1875872,
    2327821,
    1674676,
    1012512,
    544444,
    1139371,
    3202946,
    3756536,
    4310681,
    3183038,
    4197821,
    1104008,
    1466127,
    1002575,
    2798170,
    463088,
    3466369,
    488257
]
Z = [
    80.634,
    76.068,
    66.624,
    64.769,
    63.714,
    61.600,
    61.046,
    60.523,
    59.253,
    57.916,
    57.865,
    56.930,
    56.780,
    56.590,
    56.508,
    56.132,
    54.966,
    53.705,
    53.017,
    51.808,
    51.279,
    51.230,
    51.216
]

# print(len(Z))

# X = np.array(X)
# Y = np.array(Y)
# Z = np.array(Z)
# ax.plot_trisurf(X, Y, Z, cmap='viridis', edgecolor='none')
# ax.set_title('surface')
#
# plt.show()


# Tr = triangulation.Triangulation(X,Y,Z)
# square_points = Tr.get_square_points()
# x_square = y_square = z_square = []
# len_points = len(square_points)
# for i in range(len_points):
#     x_square.append(square_points[i].X)
#     y_square.append(square_points[i].Y)
#     z_square.append(square_points[i].Z)
#     print(square_points[i])
#
# triangles = Tr.get_triangles()
# len_points = len(triangles)
# x_f = y_f = z_f = []
# for i in range(len_points):
#     for k in range(3):
#         x_f.append(triangles[i].points[k].X)
#         y_f.append(triangles[i].points[k].Y)
#         z_f.append(triangles[i].points[k].Z)
    # plt.plot([triangles[i].points[0].X, triangles[i].points[1].X, triangles[i].points[2].X, triangles[i].points[0].X],
    #         [triangles[i].points[0].Y, triangles[i].points[1].Y, triangles[i].points[2].Y, triangles[i].points[0].Y],
            # [triangles[i].points[0].Z, triangles[i].points[1].Z, triangles[i].points[2].Z, triangles[i].points[0].Z]
            #  )

# plt.plot(x_f, y_f, z_f)



# ax.plot(x_f, y_f, z_f, cmap='viridis', edgecolor='none')
# ax.plot_trisurf(X, Y, Z,  cmap='viridis', edgecolor='none')
# ax.plot(x_f, y_f, z_f)
# ax.set_title('surface')

# min_x, min_y = 50, 463088
# max_x, max_y = 836, 7690863
# len_x, len_y = 100, 100
#
# x_grid = np.linspace(min_x, max_x, len_x)
# y_grid = np.linspace(min_y, max_y, len_y)
#
#
# spline_b = interpolate.Rbf(X, Y, Z, function='thin_plate')
# Z_t = spline_b(x_grid, y_grid)
#
# #
# #
# B1, B2 = np.meshgrid(x_grid, y_grid, indexing='xy')
#
# #
# Z_b = spline_b(B1,B2)
# # # ax.plot_wireframe(B1, B2, Z_b)
# # # ax.plot_surface(B1, B2, Z_b)
#
# b1 = B1.flatten()
# b2 = B2.flatten()
# zb = Z_b.flatten()
#
#
# def add_new_points(coord_x, coord_y, coord_z, x_new, y_new, z_new):
#     coord_x_new = coord_x
#     for x in x_new:
#         coord_x_new.append(x)
#
#     coord_y_new = coord_y
#     for y in y_new:
#         coord_y_new.append(y)
#
#     coord_z_new = coord_z
#     for z in z_new:
#         coord_z_new.append(z)
#
#     return coord_x_new, coord_y_new, coord_z_new
#
#
# # X, Y, Z = add_new_points(X, Y, Z, x_grid, y_grid, Z_t)
#
# ax.plot_trisurf(X, Y, Z, cmap='viridis', edgecolor='none')
#
# x_sum = 0
# y_sum = 0
# for i in range(len(X)):
#     x_sum += X[i]*Y[i]
# for i in range(len(Z_t)):
#     y_sum += Z_t[i]*Z_t[i]
# print(math.sqrt(x_sum), math.sqrt(y_sum))
#
#
#
# plt.show()


def nelder_mead(f, x_start, step=0.1, no_improve_thr=10e-6, no_improve_break=10, max_iter=0, alpha=1., gamma=2.,
                rho=-0.5, sigma=0.5):
    # print_function.print_start("Nelder Mead")
    # init
    dim = len(x_start)
    prev_best = f(x_start)
    no_improve = 0
    res = [[x_start, prev_best]]

    for i in range(dim):
        x = copy.copy(x_start)
        x[i] = x[i] + step
        score = f(x)
        res.append([x, score])

    # simplex iter
    k = 0
    while 1:
        print(res[-1][1])
        # order
        res.sort(key=lambda elem: elem[1])
        best = res[0][1]

        # break after max_iter
        if max_iter and k >= max_iter:
            # print_function.print_end_function(k, res[0][0], f)
            return res[0][0]
        k += 1

        if best < prev_best - no_improve_thr:
            no_improve = 0
            prev_best = best
        else:
            no_improve += 1

        if no_improve >= no_improve_break:
            # print_function.print_end_function(k, res[0][0], f)
            return res[0][0]

        # centroid
        x0 = [0.] * dim
        for tup in res[:-1]:
            for i, c in enumerate(tup[0]):
                x0[i] += c / (len(res) - 1)

        # reflection
        xr = x0 + alpha * (np.array(x0) - res[-1][0])
        r_score = f(xr)
        print(r_score)
        if res[0][1] <= r_score < res[-2][1]:
            del res[-1]
            res.append([xr, r_score])
            print("REFLECTION")
            continue

        # expansion
        if r_score < res[0][1]:
            xe = x0 + gamma * (np.array(x0) - res[-1][0])
            e_score = f(xe)
            print(e_score)
            if e_score < r_score:
                del res[-1]
                res.append([xe, e_score])
                print("EXPANSION 1")
                continue
            else:
                del res[-1]
                res.append([xr, r_score])
                print("EXPANSION 2")
                continue

        # contraction
        xc = x0 + rho * (np.array(x0) - res[-1][0])
        c_score = f(xc)
        print(c_score)
        if c_score < res[-1][1]:
            del res[-1]
            res.append([xc, c_score])
            print("CONTRACTION")
            continue

        # reduction
        x1 = res[0][0]
        n_res = []
        for tup in res:
            red_x = x1 + sigma * (tup[0] - x1)
            score = f(red_x)
            n_res.append([red_x, score])
        print("REDUCTION")
        res = n_res


def my_function(x):
    return 100 * pow((pow(x[0], 2) - x[1]), 2) + 2 * pow((x[0] - 1), 2) + 100 * pow((pow(x[1], 2) - x[2]), 2) + 2 * pow((x[1] - 1), 2) + 45

xStart = [0, 0, 0]

res = nelder_mead(my_function, xStart)
print(res, my_function(res))


def gradientProjections(x0, eps1, eps2, f, h_1, h_2, h_3, grad, cond1, cond2, cond3):
    # print_function.print_start("Gradient Projections")
    max_iterations = 1000
    k = 0
    t_k_star = 3.4
    while k < max_iterations:
        if k >= max_iterations:
            # print_function.print_end_function(k, x0, f)
            return x0, k
        a_k = np.array([cond1(x0), cond2(x0), cond3(x0)])
        t_k = np.multiply(-1, np.array([h_1(x0), h_2(x0), h_3(x0)])).T
        a_m = np.matmul(a_k, a_k.T)
        a_i = np.linalg.inv(a_m)
        delta_2_x_k = np.matmul(np.matmul(a_k.T, a_i, t_k))
        norm_value = np.linalg.norm(delta_2_x_k)
        gradient_value = grad(x0)
        # if gradient_value == 0:
        #     print_function.print_end_function(k, x0, f)
        #     return x0
        V = a_k.T @ np.linalg.inv(a_k @ a_k.T)
        X = V @ a_k
        S = np.eye(X.shape[0]) - X
        delta_x_k = (-1 * S) @ gradient_value
        # if 0 > delta_x_k > eps1:
        #     active_restrictions.remove(gradient_value)
        if np.linalg.norm(delta_x_k) <= eps1 and norm_value <= eps2:
            # print_function.print_end_function(k, x0, f)
            return x0, k
        elif np.linalg.norm(delta_x_k) > eps1 and norm_value <= eps2:
            delta_2_x_k = 0
            new_func = lambda t: f(x0 + t * delta_x_k)
            # interval = method_svann(1.0, 0.001, new_func)
            # t_k_star = golden_section_method(0.001, interval, new_func)
        elif np.linalg.norm(delta_x_k) > eps1 and norm_value > eps2:
            new_func = lambda t: f(x0 + t * delta_x_k)
            # interval = method_svann(1.0, 0.001, new_func)
            # t_k_star = golden_section_method(0.001, interval, new_func)
        elif np.linalg.norm(delta_x_k) <= eps1 and norm_value > eps2:
            delta_x_k = 0
        x0 = x0 + t_k_star * delta_x_k + delta_2_x_k
        k += 1
def condFunction1(x):
    return x[0] ** 158 + x[1] ** 2 - 40.0


def condFunction2(x):
    return - x[0]


def condFunction3(x):
    return - x[1]


def derivativeCondFunction(x):
    return np.array([(4 * (30 * pow(x[0], 3) - 30 * x[0] * x[1] + x[0] - 1)), (-60 * (pow(x[0], 2) - x[1]))])


def derivativeCondFunction1(x):
    return 2 * x[0], 2 * x[1]


def derivativeCondFunction2(x):
    return -1.0, 0.0


def derivativeCondFunction3(x):
    return 0.0, -1.0

def gradient_function(x):
    return np.array([(4 * (30 * pow(x[0], 3) - 30 * x[0] * x[1] + x[0] - 1)), (-60 * (pow(x[0], 2) - x[1]))])

xStart = [random.randint(0, 1000) / 1000, random.randint(0, 1000) / 1000]
print(xStart)
epsilon = 0.0001
lambda_ = 1.0
betta = 1.5
curFunction = my_function
gradientFunction = gradient_function

gradientProjections(xStart, -0.1, 0.1, curFunction, condFunction1, condFunction2, condFunction3,
                                   gradientFunction, derivativeCondFunction1, derivativeCondFunction2, derivativeCondFunction3)