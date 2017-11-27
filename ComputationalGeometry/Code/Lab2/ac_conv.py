from collections import namedtuple
import functools
import numpy as np


Point = namedtuple('Point', 'x y')


def getInitialPointIndex(points):
    p = Point(10000, 10000)
    ix = 999
    for i in range(0, len(points)):
        cp = points[i]
        if cp.y < p.y or cp.y == p.y and cp.x < p.x:
            p = cp
            ix = i
    return ix


def orientation(p, q, r):
    val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y)
    #  0 - colinear
    #  1 - clockwise
    # -1 - counterclockwise
    return 0 if val == 0 else 1 if val > 0 else -1


def polarAngle(p, q):
    return np.arctan2(p.y - q.y, p.x - q.x)


def grahamScan(points):
    lowest = getInitialPointIndex(points)
    points[0], points[lowest] = points[lowest], points[0]
    rep = points[0]
    # print(points)
    points.sort(key = lambda x: polarAngle(x, rep))
    print(points)
    print(orientation(points[1], points[3], points[5]))
    # print(lowest)
    # print(points)
    # convexCover = []
    # convexCover.append(points[0])
    # convexCover.append(points[2])
    # for i in range(2, len(points)):
    #     convexCover.append(points[i])
    #



def main():
    p1 = Point(1, 1)
    p2 = Point(2, 2)
    p3 = Point(3, 3)
    p4 = Point(7, -2)
    p0 = Point(0, 1)
    p5 = Point(4, 1)
    points = [p1, p2, p3, p4, p0, p5]
    grahamScan(points)
    # print(orientation(points[0], points[1], points[2]))
    # print(orientation(p1, p2, p3))
    # print (getInitialPointIndex([p1, p2, p3]))

if __name__ == '__main__':
    main()
