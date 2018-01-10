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
    return [Point(-4, 10), Point(-2, 2), Point(6, 6), Point(2.93, 11.8679)]


def distance(p1: Point, p2: Point):
    return math.sqrt((p1.x - p2.x)**2 + (p1.y - p2.y)**2)


def bullet_a(points: list):
    a2 = angle(cosine(points[0], points[1], points[2]))
    a4 = angle(cosine(points[2], points[3], points[0]))
    print(a2 + a4)
    if a2 + a4 == 180:
        print("pe cerc")
    elif a2 + a4 > 180:
        print("in interiorul cercului")
    else:
        print("in exteriorul cercului")


def bullet_b(points: list):
    right = distance(points[0], points[1]) + distance(points[2], points[3])
    left = distance(points[0], points[3]) + distance(points[1], points[2])
    if left == right:
        print("Inscriptibil")
    else:
        print("Nu e inscriptibil")


def main():
    points = read()
    bullet_a(points)
    bullet_b(points)


if __name__ == '__main__':
    main()
