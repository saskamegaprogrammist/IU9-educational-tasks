import math


class Point:

    def __init__(self, X, Y, Z):
        self.X = X
        self.Y = Y
        self.Z = Z

    def __str__(self):
        return 'X:{}, Y:{}, Z:{}'.format(self.X, self.Y, self.Z)

    def equals_flat(self, point):
        return self.X == point.X and self.Y == point.Y