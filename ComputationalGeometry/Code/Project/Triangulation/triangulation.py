from collections import namedtuple

Point = namedtuple('Point', 'x y')


def delta(a, b, c):
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)


# Checks whether the angle made by point a, b and c is convex or not,
# assuming that the points are walked in counter clockwise order
def is_convex(a, b, c):
    cross = delta(a, b, c)
    if cross >= 0:
        return True
    return False


# Checks whether the point p is in the triangle made by a, b and c
def in_triangle(a, b, c, p):
    error_correction = 0.0000001
    coefs = [0, 0, 0]
    coefs[0] = delta(c, p, b) / (delta(c, a, b) + error_correction)
    coefs[1] = delta(c, a, p) / (delta(c, a, b) + error_correction)
    coefs[2] = 1 - coefs[0] - coefs[1]

    for x in coefs:
        if x > 1 or x < 0:
            return False
    return True


def in_triangle2(a, b, c, p):
    coefs = [0, 0, 0]
    coefs[0] = delta(c, p, b) / (delta(c, a, b))
    coefs[1] = delta(c, a, p) / (delta(c, a, b))
    coefs[2] = 1 - coefs[0] - coefs[1]

    pt_map = [a, b, c]
    zero_ix = None

    for i in range(0, len(coefs)):
        x = coefs[i]
        if x > 1 or x < 0:
            return False
        if x == 1:
            return pt_map[i]
        if x == 0:
            zero_ix = i

    if zero_ix is None:
        return a, b, c

    segment = ()
    for i in range(0, len(pt_map)):
        if not i == zero_ix:
            segment = segment + (pt_map[i],)
    return segment


# Checks whether the points the list are in clockwise order
def is_clockwise(pts):
    def twice_area(p1, p2):
        return (p1.x - p2.x) * (p1.y + p2.y)

    area_t = twice_area(pts[0], pts[len(pts) - 1])
    for i in range(len(pts) - 1):
        area_t += twice_area(pts[i + 1], pts[i])

    if area_t > 0:
        return True
    return False


def get_ear(pts):

    if len(pts) < 3:
        return ()
    if len(pts) == 3:
        ear = (pts[0], pts[1], pts[2])
        del pts[:]
        return ear
    for i in range(len(pts)):
        is_ear = True
        p1 = pts[(i - 1) % len(pts)]
        p2 = pts[i % len(pts)]
        p3 = pts[(i + 1) % len(pts)]
        if is_convex(p1, p2, p3):
            for x in pts:
                if x not in (p1, p2, p3) and in_triangle(p1, p2, p3, x):
                    is_ear = False
            if is_ear:
                del pts[i % len(pts)]
                return p1, p2, p3
    print("Could not get an ear")
    return ()


def get_triangulation(pts):
    pts = pts[::-1] if is_clockwise(pts) else pts[:]
    triangulation = []
    while len(pts) >= 3:
        ear = get_ear(pts)
        if len(ear) == 0:
            break
        triangulation.append(ear)
    return triangulation


def read():
    # return list(map(lambda t: Point(t[0], t[1]), [(1, 1), (3, 1), (3, 3), (2, 3), (2, 5), (11, 5), (11, 3), (8, 3),
    #                                               (8, 1), (13, 1), (13, 7), (1, 7)]))
    return list(map(lambda t: Point(t[0], t[1]), [(347, 191), (478, 397), (774, 406), (886, 174), (610, 44)]))


# Returns true if the point is in the triangulated polygon
# def check_point(triangulation, point):
#     for t in triangulation:
#         if in_triangle(t[0], t[1], t[2], point):
#             return True
#     return False

# Checks if a point is in a polygon
# Returns true if the point is in the polygon, false if not
def check_point(point, poly, triangulation):
    if len(poly) < 3:
        return False
    edges = set()
    for i in range(0, len(poly) - 1):
        edges.add((poly[i], poly[i + 1]))
    edges.add((poly[len(poly) - 1], poly[0]))

    if triangulation is None:
        triangulation = get_triangulation(poly)
    for t in triangulation:
        resp = in_triangle2(t[0], t[1], t[2], point)
        if not resp:  # point not in current triangle
            continue
        return resp
        # if type(resp) is bool:
        #     return resp
        # if type(resp[0]) is int:
        #     return resp  # if the response is a point, it is a point of the polygon
        # if resp in edges or (resp[1], resp[0]) in edges:
        #     return resp
        # else:
        #     return True
    return False


def main():
    poly = read()
    triangulation = get_triangulation(poly)
    # print(triangulation)
    print(check_point(Point(2 - 0.002, 2 - 0.0004), [Point(1, 1), Point(2, 2), Point(0, 2)], None))


if __name__ == '__main__':
    main()
