import math

class vector:
    
    def __init__(self, x, y):
        self.x = float(x)
        self.y = float(y)

    def __repr__(self):
        return "(" + repr(self.x) + ", " + repr(self.y) + ")"

    # adds other vector to existing vector
    def add(self, other):
        return vector(self.x + other.x, self.y + other.y)

    # subtracts other vector from exsiting vector
    def sub(self, other):
        return vector(self.x - other.x, self.y - other.y)

    # multiplies existing vector by given scalar
    def mult(self, scalar):
        return vector(self.x * scalar, self.y * scalar)

    # divides existing vector by given scalar
    def div(self, scalar):
        return vector(self.x / scalar, self.y / scalar)

    # returns magnitude of existing vector
    def magnitude(self):
        return math.sqrt(self.x ** 2 + self.y ** 2)

    # returns unit vector in direction of existing vector
    def unit(self):
        return self.div(self.magnitude())

