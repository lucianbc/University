# Fie A1, A2, A3, A4 puncte din RxR, A1, A2, A3, A4 patrulater convex
# a) Sa se preciezez pozitia punctului A4 fata de cercul circumscris triunghiului A1A2A3
# b) Sa se precizeze daca patrulaterul A1A2A3A4 este circumscriptibil


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
    return [Point(0, 0), Point(4, 0), Point(1, 3), Point(0, 3)]


def distance(p1: Point, p2: Point):
    return math.sqrt((p1.x - p2.x)**2 + (p1.y - p2.y)**2)


def bullet_a(points: list):
    a2 = angle(cosine(points[0], points[1], points[2]))
    a4 = angle(cosine(points[2], points[3], points[0]))
    print(a2 + a4)
    if 180.0001 > a2 + a4 > 179.999:
        print("pe cerc")
    elif a2 + a4 > 180:
        print("in interiorul cercului")
    else:
        print("in exteriorul cercului")


def bullet_b(points: list):
    right = distance(points[0], points[1]) + distance(points[2], points[3])
    left = distance(points[0], points[3]) + distance(points[1], points[2])
    if left == right:
        print("Circumscriptibil")
    else:
        print("Nu e circumscriptibil")


def main():
    points = read()
    bullet_a(points)
    bullet_b(points)


if __name__ == '__main__':
    main()
