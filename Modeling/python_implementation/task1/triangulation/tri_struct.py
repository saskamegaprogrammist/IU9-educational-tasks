from triangulation.point import Point


class Triangle:

    def __init__(self, points):
        self.points = points
        self.center = self.calc_center()

    def calc_center(self):
        x = (self.points[0].X + self.points[1].X + self.points[2].X)/3
        y = (self.points[0].Y + self.points[1].Y + self.points[2].Y)/3
        return Point(x, y, self.points[0].Z)


    def contains(self, point):
        return self.points[0].equals_flat(point) or self.points[1].equals_flat(point) or self.points[2].equals_flat(point)

    def inside(self, point):
        a = (self.points[0].X - point.X)*(self.points[1].Y - self.points[0].Y) - (self.points[1].X - self.points[0].X)*(self.points[0].Y - point.Y)
        b = (self.points[1].X - point.X)*(self.points[2].Y - self.points[1].Y) - (self.points[2].X - self.points[1].X)*(self.points[1].Y - point.Y)
        c = (self.points[2].X - point.X)*(self.points[0].Y - self.points[2].Y) - (self.points[0].X - self.points[2].X)*(self.points[2].Y - point.Y)

        return (a>=0 and b>=0 and c>= 0) or (a<=0 and b<=0 and c<= 0)

    def get_different_point(self, triangle):
        for i in range(3):
            if not self.points[0].equals_flat(triangle.points[i]) and not self.points[1].equals_flat(
                    triangle.points[i]) and not self.points[2].equals_flat(triangle.points[i]):
                return triangle.points[i]

    def get_same_and_different_point(self, triangle):
        tri = [0, 0, 0]
        self_t = [0, 0, 0]
        same = []
        diff = []
        for i in range(3):
            for j in range(3):
                if self.points[i].equals_flat(triangle.points[j]):
                    self_t[i] += 1
                    tri[j] += 1
        for i in range(3):
            if self_t[i] == 0:
                diff.append(self.points[i])
            else:
                same.append(self.points[i])
        for i in range(3):
            if tri[i] == 0:
                diff.append(triangle.points[i])
        return same, diff


class TriStruct:

    def __init__(self, triangle):
        self.triangle = triangle
        self.neighbours = []

    def get_triangle(self):
        return self.triangle

    def get_neighbours(self):
        return self.neighbours

    def add_neighbour(self, neighbour):
        self.neighbours.append(neighbour)

    def remove_neighbour(self, neighbour):
        for i in range(len(self.neighbours)):
            if self.neighbours[i] == neighbour:
                self.neighbours.pop(i)
                return

    def add_neighbours(self, neighbours):
        self.neighbours.extend(neighbours)

    def clear_neighbours(self):
        self.neighbours = []

    def add_new_neighbours(self, neighbours):
        self.neighbours = []
        self.add_neighbours(neighbours)