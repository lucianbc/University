from grahamScan import *
from collections import namedtuple

Point = namedtuple('Point', 'x y')


def test_orientation_test():
    p1 = Point(1, 3)
    p2 = Point(5, 2)
    r1 = Point(3, 1)  # to the right
    r2 = Point(3, 5)  # to the left
    r3 = Point(9, 1)  # on the line
    rez = (orientation_test(p1, p2, r1), orientation_test(p1, p2, r2), orientation_test(p1, p2, r3))
    # should be (<0, >0, 0)
    print(rez)


def test_point_equals():
    p1 = Point(2, 3)
    p2 = Point(2, 3)
    p3 = Point(5, 1)
    print(p1 == p2)
    print(p1 is p2)
    print(p1 == p3)
    print(p1 is p3)


def test_get_sorted_points():
    # points = [Point(1, 3), Point(5, 2), Point(3, 1), Point(3, 5), Point(9, 1)]
    # points = [Point(3, 5), Point(4, 4), Point(5, 3), Point(6, 2)]
    points = [Point(1, 3), Point(5, 2), Point(3, 1), Point(3, 5), Point(9, 1), Point(1, 3), Point(4, 4), Point(3, 5),
              Point(6, 2)]
    sorted_points = get_sorted_points(points)
    print(sorted_points)


def test_remove_duplicates():
    points = [Point(1, 3), Point(5, 2), Point(3, 1), Point(3, 5), Point(9, 1), Point(1, 3)]
    print(remove_duplicates(points))


def test_graham_scan():
    points = [Point(1, 3), Point(5, 2), Point(3, 1), Point(3, 5), Point(9, 1), Point(1, 3), Point(4, 4), Point(3, 5),
              Point(6, 2)]
    # points = [Point(3, 5), Point(4, 4), Point(5, 3), Point(6, 2)]
    print(graham_scan(points))


if __name__ == '__main__':
    # test_get_sorted_points()
    test_graham_scan()
    # test_remove_duplicates()
    # test_points_sort()
    # test_point_equals()
    # test_orientation_test()
