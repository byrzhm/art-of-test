import numpy as np

class Vector:
    def __init__(self, x, y) -> None:
        self.x = x
        self.y = y

    def add(self, other):
        return Vector(self.x + other.x,
                      self.y + other.y)

    def sub(self, other):
        return Vector(self.x - other.x,
                      self.y - other.y)
        

    def mul(self, scalar):
        return Vector(self.x * scalar,
                      self.y * scalar)

    def dot(self, other):
        return self.x * other.x + \
               self.y * other.y

    def __add__(self, other):
        return self.add(other)

    def __mul__(self, scalar):
        return self.mul(scalar)