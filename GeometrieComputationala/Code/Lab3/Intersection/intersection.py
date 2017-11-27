# Given 4 points in RxR, find the intersection of the segments between the first two points and the last two
from numbers import Real
import matplotlib.pyplot as plt


class Vector:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        if isinstance(other, Real):
            return Vector(self.x + other, self.y + other)
        else:
            return Vector(self.x + other.x, self.y + other.y)

    __radd__ = __add__

    def __sub__(self, other):
        if isinstance(other, Real):
            return Vector(self.x - other, self.y - other)
        else:
            return Vector(self.x - other.x, self.y - other.y)

    __rsub__ = __sub__

    def __mul__(self, other):
        if isinstance(other, Real):
            return Vector(self.x * other, self.y * other)
        else:
            return self.x * other.x + self.y * other.y

    __rmul__ = __mul__

    def cross(self, other):
        return self.x * other.y - self.y * other.x

    def __str__(self):
        return f"({self.x}, {self.y})"


def read():
    # p1 = Vector(*map(int, input().split(" ")))
    # p2 = Vector(*map(int, input().split(" ")))
    # p3 = Vector(*map(int, input().split(" ")))
    # p4 = Vector(*map(int, input().split(" ")))
    # return p1, p2, p3, p4
    return Vector(0, 0), Vector(2, 2), Vector(3, 3), Vector(1, 1)


def min_max(p, q):
    return (p, q) if p < q else (q, p)


def intersect(p, q, l, r):
    if q < l or p > r:
        return None, None
    return max(p, l), min(q, r)


def get_intersection(p: Vector, r: Vector, q: Vector, s: Vector):
    r = r - p
    s = s - q

    cross_direction = r.cross(s)
    cross_origin = (q - p).cross(r)

    if cross_direction == 0:
        if cross_origin == 0:               # the segments are collinear
            t0, t1 = min_max(((q - p) * r)/(r * r), ((q - p + s) * r)/(r * r))
            t0, t1 = intersect(t0, t1, 0, 1)
            if (t0, t1) == (None, None):
                return None                 # Not overlapping
            return [p + t0 * r, p + t1 * r]
        if cross_origin != 0:
            return None                     # the segments are parallel

    t = (q - p).cross(s) / (r.cross(s))
    u = (q - p).cross(r) / (r.cross(s))

    print(p + t * r)
    if 0 <= t <= 1 and 0 <= u <= 1:         # the segments intersect
        return [p + t * r]

    return None                             # the segments do not intersect


def plot(points, intersection):
    plt.plot(list(p.x for p in points), list(p.y for p in points), marker='o', zorder=-1)
    plt.scatter(list(p.x for p in intersection), list(p.y for p in intersection), c="r", zorder=2)
    plt.plot(list(p.x for p in intersection), list(p.y for p in intersection), zorder=3, c="r")
    plt.show()


def main():
    pts = read()
    intersection = get_intersection(*pts)
    if intersection is not None:
        print([str(el) for el in intersection])
        plot(pts, intersection)
    else:
        print("Segments do not intersect")


if __name__ == '__main__':
    main()
