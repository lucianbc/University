from collections import namedtuple
from enum import Enum
from math import atan2, sqrt
import matplotlib.pyplot as plt

Point = namedtuple('Point', 'x y')


class Turn(Enum):
    COLLINEAR = 0
    LEFT = 1
    RIGHT = -1


# Orientation test
# Checks the position of test_point relative to the oriented segment p1p2
# = 0 - test point is on the line defined by p1 and p2
# < 0 - test point is on the right of the line defined by p1 and p2
# > 0 - test point is on the left of the line defined by p1 and p2
def orientation_test(p1, p2, test_point):
    cross = (p1.x - test_point.x) * (p2.y - test_point.y) - (p1.y - test_point.y)*(p2.x - test_point.x)
    return Turn.COLLINEAR if cross == 0 else Turn.LEFT if cross > 0 else Turn.RIGHT


def remove_duplicates(points):
    point_set = set(points)
    return list(point_set)


def get_lowest_point(points):
    lowest = 0
    for i in range(1, len(points)):
        if points[i].y < points[lowest].y or (points[i].y == points[lowest].y and points[i].x < points[lowest].x):
            lowest = i
    return points[lowest]


def get_sorted_points(points):

    lowest = get_lowest_point(points)

    sorted_points = sorted(points, key=lambda p: (atan2(p.y - lowest.y, p.x - lowest.x),
                                                  sqrt((p.x - lowest.x)**2 + (p.y - lowest.y)**2)))
    return sorted_points


def graham_scan(points):
    points = remove_duplicates(points)
    points = get_sorted_points(points)
    if len(points) < 2:
        return None
    point_stack = [points[0], points[1]]
    for i in range(2, len(points)):
        while True:
            head = points[i]
            middle = point_stack.pop()
            tail = point_stack.pop()
            test = orientation_test(tail, head, middle)
            if test == Turn.RIGHT:
                point_stack.append(tail)
                point_stack.append(middle)
                point_stack.append(head)
                break
            elif test == Turn.LEFT:
                point_stack.append(tail)
            else:
                point_stack.append(tail)
                point_stack.append(head)
                break
    return point_stack


def partition(points, convex_hull):
    i, j = None, None
    if len(convex_hull) == 4:
        i = {convex_hull[1], convex_hull[3]}
        j = {convex_hull[0], convex_hull[2]}
    elif len(convex_hull) == 3 or len(convex_hull) == 2:
        i = set(convex_hull)
        j = set(points) - i

    return i, j


def main():
    points = [Point(0, 0), Point(2, 2), Point(3, 3), Point(1, 1)]
    convex_hull = graham_scan(points)
    i, j = partition(points, convex_hull)
    print(i)
    print(j)
    plt.scatter(list(zip(*list(i)))[0], list(zip(*list(i)))[1])
    plt.scatter(list(zip(*list(j)))[0], list(zip(*list(j)))[1])
    plt.show()


if __name__ == '__main__':
    main()
