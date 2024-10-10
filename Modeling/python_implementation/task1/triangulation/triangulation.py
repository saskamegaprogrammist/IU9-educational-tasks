import numpy as np

from .point import Point
from .tri_struct import TriStruct, Triangle
import math
import matplotlib.pyplot as plt

ax = plt.gca()


class Triangulation:

    def make_points(self, X, Y, Z):
        if len(X) != len(Y) != len(Z):
            print("there is different number of coordinates")
            return
        len_points = len(X)
        for i in range(len_points):
            self.points.append(Point(X[i], Y[i], Z[i]))

    def __init__(self, X, Y, Z):
        self.points = []
        self.square_points = []
        self.tri_structs = []
        self.tri_ponts = []
        self.triangles = []
        self.triangles_len = 0
        self.square_center = Point
        self.make_points(X, Y, Z)
        self.create_square_points()
        self.init_triangulation()
        self.triangulate()
        # self.delete_square_points()

        # self.cube_center = Point
        # self.cube_len_side = 0
        # self.tethra_points = []
        # self.create_cube_points()
        # self.create_tethra_points()

    def delete_square_points(self):
        new_triangles = []
        for i in range(self.triangles_len):
            def inner():
                has = False
                for k in range(4):
                    if self.triangles[i].contains(self.square_points[k]):
                        has = True
                        return has
                return has
            has = inner()
            if not has:
                new_triangles.append(self.triangles[i])
        self.triangles = new_triangles


    def init_triangulation(self):
        fstriangle = Triangle([self.square_points[0], self.square_points[1], self.points[0]])
        striangle = Triangle([self.square_points[1], self.square_points[2], self.points[0]])
        ttriangle = Triangle([self.square_points[2], self.square_points[3], self.points[0]])
        frtriangle = Triangle([self.square_points[3], self.square_points[0], self.points[0]])

        self.tri_ponts.extend([self.square_points[0], self.square_points[1], self.square_points[2], self.square_points[3], self.points[0]])
        self.triangles.extend([fstriangle, striangle, ttriangle, frtriangle])
        self.triangles_len += 4

        fsts = TriStruct(0)
        fsts.add_neighbours([3, 1])
        sts = TriStruct(1)
        sts.add_neighbours([0, 2])
        tts = TriStruct(2)
        tts.add_neighbours([1, 3])
        frts = TriStruct(3)
        frts.add_neighbours([0, 2])

        self.tri_structs.extend([fsts, sts, tts, frts])

        for i in range(4):
            self.check(self.tri_structs[i])

    def check(self, tri_struct: TriStruct):
        triangle = self.triangles[tri_struct.get_triangle()]
        neighbours = tri_struct.get_neighbours().copy()
        # print(tri_struct.get_triangle())
        # print(neighbours)
        for i in range(len(neighbours)):
            self.compare(triangle, self.triangles[neighbours[i]], tri_struct.get_triangle(), neighbours[i])

    def compare(self, triangle, neigbour, triangle_index, neigbour_index):
        diff_point = triangle.get_different_point(neigbour)
        ch = self.check_delaunay(triangle, diff_point)
        if not ch:
            # plt.plot(
            #     [triangle.points[0].X, triangle.points[1].X, triangle.points[2].X, triangle.points[0].X],
            #     [triangle.points[0].Y, triangle.points[1].Y, triangle.points[2].Y, triangle.points[0].Y])
            # plt.plot(
            #     [diff_point.X, triangle.points[0].X],
            #     [diff_point.Y, triangle.points[0].Y])
            self.rebuild(triangle, neigbour, triangle_index, neigbour_index)

    def rebuild(self, triangle, neigbour, triangle_index, neigbour_index):
        same, diff = triangle.get_same_and_different_point(neigbour)
        fstriangle = Triangle([same[0], diff[0], diff[1]])
        striangle = Triangle([same[1], diff[0], diff[1]])
        self.triangles[triangle_index] = fstriangle
        self.triangles[neigbour_index] = striangle

        tris_old_1 = self.tri_structs[triangle_index]
        neighbours_1 = tris_old_1.get_neighbours().copy()

        tris_old_2 = self.tri_structs[neigbour_index]
        neighbours_2 = tris_old_2.get_neighbours().copy()

        for i in range(len(neighbours_1)):
            if neighbours_1[i] != neigbour_index and self.triangles[neighbours_1[i]].contains(same[1]):
                self.tri_structs[neighbours_1[i]].remove_neighbour(triangle_index)
                self.tri_structs[neighbours_1[i]].add_neighbour(neigbour_index)
                tris_old_1.remove_neighbour(neighbours_1[i])
                tris_old_2.add_neighbour(neighbours_1[i])

        for i in range(len(neighbours_2)):
            if neighbours_2[i] != triangle_index and self.triangles[neighbours_2[i]].contains(same[0]):
                self.tri_structs[neighbours_2[i]].remove_neighbour(neigbour_index)
                self.tri_structs[neighbours_2[i]].add_neighbour(triangle_index)
                tris_old_2.remove_neighbour(neighbours_2[i])
                tris_old_1.add_neighbour(neighbours_2[i])

        self.tri_structs[triangle_index] = tris_old_1
        self.tri_structs[neigbour_index] = tris_old_2

    def find_next_triangle(self, tristruct, point1, point2):
        neigbours = tristruct.neighbours
        print(tristruct.triangle)
        triangle = self.triangles[tristruct.triangle]
        print(triangle.points[0])
        print(triangle.points[1])
        print(triangle.points[2])
        print()
        print(point1, point2)
        print(neigbours)
        for i in range(len(neigbours)):
            neigbour = neigbours[i]
            print()
            print(self.triangles[neigbour].points[0])
            print(self.triangles[neigbour].points[1])
            print(self.triangles[neigbour].points[2])

            if self.triangles[neigbour].contains(point1) and self.triangles[neigbour].contains(point2):
                return neigbour

    def create_new_triangles(self, trisctruct, index, point):
        # print("old index:{}".format(index))
        triangle = self.triangles[trisctruct.triangle]
        # print(triangle.points[0])
        # print(triangle.points[1])
        # print(triangle.points[2])
        # print()

        neighbours = trisctruct.get_neighbours().copy()

        fstriangle = Triangle([triangle.points[0], triangle.points[1],point])
        # print(index)
        # print(triangle.points[0])
        # print(triangle.points[1])
        # print(point)
        # print()

        striangle = Triangle([triangle.points[1], triangle.points[2], point])
        # print(self.triangles_len)
        # print(triangle.points[1])
        # print(triangle.points[2])
        # print(point)
        # print()

        ttriangle = Triangle([triangle.points[2], triangle.points[0], point])
        # print(self.triangles_len + 1)
        # print(triangle.points[2])
        # print(triangle.points[0])
        # print(point)
        # print()

        self.triangles[index] = fstriangle

        self.triangles.extend([striangle, ttriangle])
        self.triangles_len += 2

        fsts = TriStruct(index)
        sts = TriStruct(self.triangles_len-2)
        tts = TriStruct(self.triangles_len-1)

        for i in range(len(neighbours)):
            neigbour = neighbours[i]
            if self.triangles[neigbour].contains(triangle.points[0]) and self.triangles[neigbour].contains(triangle.points[1]):
                fsts.add_neighbour(neigbour)
            if self.triangles[neigbour].contains(triangle.points[1]) and self.triangles[neigbour].contains(triangle.points[2]):
                sts.add_neighbour(neigbour)
                self.tri_structs[neigbour].add_neighbour(self.triangles_len-2)
                self.tri_structs[neigbour].remove_neighbour(index)
            if self.triangles[neigbour].contains(triangle.points[2]) and self.triangles[neigbour].contains(triangle.points[0]):
                tts.add_neighbour(neigbour)
                self.tri_structs[neigbour].add_neighbour(self.triangles_len-1)
                self.tri_structs[neigbour].remove_neighbour(index)

        fsts.add_neighbours([self.triangles_len-1, self.triangles_len-2])
        sts.add_neighbours([index, self.triangles_len - 1])
        tts.add_neighbours([index, self.triangles_len - 2])

        self.tri_structs[index] = fsts
        self.tri_structs.extend([sts, tts])

        self.check(self.tri_structs[index])
        self.check(self.tri_structs[self.triangles_len - 2])
        self.check(self.tri_structs[self.triangles_len - 1])

    def check_in_line(self, x, y, point1, point2):
        return  ((x >= point1.X and x <= point2.X) or (x <= point1.X and x >= point2.X) )and( (y >= point1.Y and y <= point2.Y) or (y <= point1.Y and y >= point2.Y))

    def get_new_triangle(self, trisctruct, point, checked):
        # print(trisctruct.triangle)
        # print(point)
        triangle = self.triangles[trisctruct.triangle]
        A1 = triangle.center.Y - point.Y
        B1 = point.X - triangle.center.X
        C1 = triangle.center.X*point.Y - point.X*triangle.center.Y

        A2 = triangle.points[0].Y - triangle.points[1].Y
        B2 = triangle.points[1].X - triangle.points[0].X
        C2 = triangle.points[0].X * triangle.points[1].Y - triangle.points[1].X * triangle.points[0].Y

        denominator = (A1*B2 - A2*B1)
        x = - (C1*B2-C2*B1)/denominator
        y = - (A1 * C2 - A2 * C1) /denominator

        if self.check_in_line(x, y, triangle.points[0], triangle.points[1]):
            # print("aaa")
            new_tr_index = self.find_next_triangle(trisctruct, triangle.points[0], triangle.points[1])
            if new_tr_index is not None and new_tr_index not in checked:
                return new_tr_index

        A3 = triangle.points[1].Y - triangle.points[2].Y
        B3 = triangle.points[2].X - triangle.points[1].X
        C3 = triangle.points[1].X * triangle.points[2].Y - triangle.points[2].X * triangle.points[1].Y


        denominator = (A1 * B3 - A3 * B1)
        x = - (C1 * B3 - C3 * B1) / denominator
        y = - (A1 * C3 - A3 * C1) / denominator

        if self.check_in_line(x, y, triangle.points[1], triangle.points[2]):
            # print("bbb")
            new_tr_index = self.find_next_triangle(trisctruct, triangle.points[1], triangle.points[2])
            if new_tr_index is not None and new_tr_index not in checked:
                return new_tr_index


        A4 = triangle.points[2].Y - triangle.points[0].Y
        B4 = triangle.points[0].X - triangle.points[2].X
        C4 = triangle.points[2].X * triangle.points[0].Y - triangle.points[0].X * triangle.points[2].Y

        denominator = (A1 * B4 - A4 * B1)
        x = - (C1 * B4 - C4 * B1) / denominator
        y = - (A1 * C4 - A4 * C1) / denominator

        if self.check_in_line(x, y, triangle.points[2], triangle.points[0]):
            # print("ccc")
            new_tr_index = self.find_next_triangle(trisctruct, triangle.points[2], triangle.points[0])
            if new_tr_index is not None and new_tr_index not in checked:
                return new_tr_index





    def triangulate(self):
        len_points = len(self.points)
        for i in range(1, len_points):
            point = self.points[i]
            j=0
            checked = []
            while True:
                tristruct = self.tri_structs[j]
                triangle = self.triangles[tristruct.triangle]
                if triangle.inside(point):
                    self.create_new_triangles(tristruct, j, point)
                    break
                else:
                    j_new = self.get_new_triangle(tristruct, point, checked)
                    checked.append(j)
                    j = j_new
                    print(j)



    def check_delaunay(self, triangle, point):
        # print(triangle.points[0], triangle.points[1], triangle.points[2],)
        # print(point)
        a_matrix = [[triangle.points[0].X, triangle.points[0].Y, 1],
                    [triangle.points[1].X, triangle.points[1].Y, 1],
                    [triangle.points[2].X, triangle.points[2].Y, 1]]
        sqr1 = math.pow(triangle.points[0].X, 2) + math.pow(triangle.points[0].Y, 2)
        sqr2 = math.pow(triangle.points[1].X, 2) + math.pow(triangle.points[1].Y, 2)
        sqr3 = math.pow(triangle.points[2].X, 2) + math.pow(triangle.points[2].Y, 2)
        b_matrix = [[sqr1, triangle.points[0].Y, 1],
                    [sqr2, triangle.points[1].Y, 1],
                    [sqr3, triangle.points[2].Y, 1]]
        c_matrix = [[sqr1, triangle.points[0].X, 1],
                    [sqr2, triangle.points[1].X, 1],
                    [sqr3, triangle.points[2].X, 1]]
        d_matrix = [[sqr1, triangle.points[0].X, triangle.points[0].Y],
                    [sqr2, triangle.points[1].X, triangle.points[1].Y],
                    [sqr3, triangle.points[2].X, triangle.points[2].Y]]
        a = math.fabs(self.get_determinant(a_matrix))
        b = math.fabs( self.get_determinant(b_matrix))
        c = math.fabs(self.get_determinant(c_matrix))
        d = math.fabs(self.get_determinant(d_matrix))
        if a == 0:
            return False
        x_c = b/(2*a)
        y_c = -c/(2*a)
        # print(a, b, c, d)
        r_2 = (math.pow(b, 2)+math.pow(c, 2) - 4*a*d) / (4*math.pow(a, 2))
        # ax.add_patch(plt.Circle((x_c, y_c), r_2, color='r', fill=False))
        # print(math.pow(point.X - x_c, 2) + math.pow(point.Y - y_c, 2))
        # print(r_2)

        return math.pow(point.X - x_c, 2) + math.pow(point.Y - y_c, 2) >= r_2


    def get_determinant(self, matrix):
        a = np.array(matrix)
        return np.linalg.det(a)

    def get_square_points(self):
        return self.square_points

    def get_triangles(self):
        return self.triangles

    def create_square_points(self):
        len_points = len(self.points)
        max_X = max_Y = max_Z = 0
        min_X = self.points[0].X
        min_Y = self.points[0].Y
        min_Z = self.points[0].Z

        for i in range(len_points):
            if self.points[i].X > max_X:
                max_X = self.points[i].X
            if self.points[i].Y > max_Y:
                max_Y = self.points[i].Y
            if self.points[i].Z > max_Z:
                max_Z = self.points[i].Z
            if self.points[i].X < min_X:
                min_X = self.points[i].X
            if self.points[i].Y < min_Y:
                min_Y = self.points[i].Y
            if self.points[i].Z < min_Z:
                min_Z = self.points[i].Z
        # print(max_X, min_X, max_Y, min_Y)
        len_X = max_X - min_X
        len_Y = max_Y - min_Y
        len_Z = max_Z - min_Z
        if len_X > len_Y:
            max = len_X
        else:
            max = len_Y
        self.square_center = Point(min_X + len_X/2, min_Y + len_Y/2, min_Z + len_Z/2)
        self.square_points.append(Point(self.square_center.X - max/2, self.square_center.Y - max/2, self.square_center.Z))
        self.square_points.append(Point(self.square_center.X - max/2, self.square_center.Y + max/2, self.square_center.Z))
        self.square_points.append(Point(self.square_center.X + max/2, self.square_center.Y + max/2, self.square_center.Z))
        self.square_points.append(Point(self.square_center.X + max/2, self.square_center.Y - max/2, self.square_center.Z))













    def get_tethra_points(self):
        return self.tethra_points

    def create_cube_points(self):
        len_points = len(self.points)
        max_X = max_Y = max_Z = min_X = min_Y = min_Z = min_i = 0
        for i in range(len_points):
            if self.points[i].X > max_X:
                max_X = self.points[i].X
            if self.points[i].Y > max_Y:
                max_Y = self.points[i].Y
            if self.points[i].Z > max_Z:
                max_Z = self.points[i].Z
            if self.points[i].X < min_X:
                min_X = self.points[i].X
                min_i = i
            if self.points[i].Y < min_Y:
                min_Y = self.points[i].Y
            if self.points[i].Z < min_Z:
                min_Z = self.points[i].Z
        len_X = max_X - min_X
        len_Y = max_Y - min_Y
        len_Z = max_Z - min_Z
        max = len_Y
        if len_X > len_Y:
            max = len_X
        if len_Z > max:
            max = len_Z
        self.cube_center = self.points[min_i]
        self.cube_len_side = 2 * max

    def create_tethra_points(self):
        self.tethra_points.append(Point(self.cube_center.X - self.cube_len_side * 3 * math.sqrt(2) / 2,
                                        self.cube_center.Y - self.cube_len_side * math.sqrt(3) / 2,
                                        self.cube_center.Z - self.cube_len_side * 3 * math.sqrt(6) / 2))
        self.tethra_points.append(Point(self.cube_center.X + self.cube_len_side * 3 * math.sqrt(2) / 2,
                                        self.cube_center.Y - self.cube_len_side * math.sqrt(3) / 2,
                                        self.cube_center.Z - self.cube_len_side * 3 * math.sqrt(6) / 2))
        self.tethra_points.append(Point(self.cube_center.X,
                                        self.cube_center.Y - self.cube_len_side * math.sqrt(3) / 2,
                                        self.cube_center.Z + self.cube_len_side * math.sqrt(6)))
        self.tethra_points.append(Point(self.cube_center.X,
                                        self.cube_center.Y - self.cube_len_side * 3 * math.sqrt(3) / 2,
                                        self.cube_center.Z))
