from collections import namedtuple
import math

Point = namedtuple('Point', 'x y')


RAD = 57.2957795


def length(p1: Point, p2: Point):
    return math.sqrt((p2.x - p1.x)**2 + (p2.y - p1.y)**2)


def dot_product(p1: Point, p2: Point, p3: Point, p4: Point):
    return (p2.x - p1.x) * (p4.x - p3.x) + (p2.y - p1.y) * (p4.y - p3.y)


def cosine(p1: Point, p2: Point, p3: Point):
    return dot_product(p1, p2, p3, p2) / (length(p1, p2) * length(p2, p3))


def angle(cos):
    return math.acos(cos) * RAD


def read():
    return [Point(-11.64, 1.76), Point(-7, 9), Point(-2.06, 6.38), Point(-2.22, 0.84)]


def main():
    points = read()
    print(cosine(points[0], points[1], points[2]))
    print(angle(cosine(points[0], points[1], points[2])))


if __name__ == '__main__':
    main()
