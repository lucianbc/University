import pygame
import sys
import triangulation
import random

pygame.init()

WIDTH = 1280
HEIGHT = 720
FPS = 30

mode = 'POLY'

colors = {
    'WHITE': (255, 255, 255),
    'BLACK': (0, 0, 0),
    'RED': (255, 0, 0)
}

screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

poly = []
triangles = []
triangles_colors = []
poly_finished = False
point = None
triangle_point = None


def update():
    screen.fill(colors['WHITE'])
    for i in range(0, len(poly)):
        pygame.draw.circle(screen, colors['BLACK'], poly[i], 3)
        if (i + 1) < len(poly):
            pygame.draw.line(screen, colors['BLACK'], poly[i], poly[i + 1])
    for i in range(0, len(triangles)):
        pygame.draw.polygon(screen, triangles_colors[i], list(triangles[i]))
    if poly_finished and len(poly) >= 2:
        pygame.draw.line(screen, colors['BLACK'], poly[0], poly[len(poly) - 1])
    if point is not None:
        pygame.draw.circle(screen, colors['RED'], point, 3)
    if triangle_point is not None:
        pygame.draw.polygon(screen, colors['RED'], [*triangle_point])


def add_poly_vertex():
    pos = pygame.mouse.get_pos()
    poly.append(pos)


def set_external_point():
    global point
    global triangle_point
    point = pygame.mouse.get_pos()
    triangle_point = None


def get_random_color():
    return random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)


while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        if event.type == pygame.MOUSEBUTTONUP:
            if mode == 'POLY':
                add_poly_vertex()
            if mode == 'POINT':
                set_external_point()
        if event.type == pygame.KEYDOWN and event.key == pygame.K_r:
            poly_finished = True
            mode = 'POINT'
            triangle_point = None
        if event.type == pygame.KEYDOWN and event.key == pygame.K_p:
            poly_finished = False
            poly = []
            triangles = []
            triangles_colors = []
            triangle_point = None
            mode = 'POLY'
        if event.type == pygame.KEYDOWN and event.key == pygame.K_t:
            mode = 'TRIANGULATION'
            poly_finished = True
            triangles = triangulation.get_triangulation(list(map(lambda p: triangulation.Point(*p), poly)))
            triangles_colors = list(map(lambda c: get_random_color() + (0.1,), range(0, len(triangles))))
        if event.type == pygame.KEYDOWN and event.key == pygame.K_l:
            if point is not None:
                in_poly = triangulation.check_point(triangulation.Point(*point),
                                                    list(map(lambda p: triangulation.Point(*p), poly)), None)
                if in_poly and len(in_poly) == 3:
                    triangle_point = in_poly
                else:
                    print("Punctul nu este in poligon")

    update()
    clock.tick(FPS)
    pygame.display.update()
