""" Created by Henrikh Kantuni on 11/3/16 """


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return '({0}, {1})'.format(self.x, self.y)


class Line:
    # TODO: add x-intercept
    def __init__(self, m, b, x=None):
        self.m = m
        self.b = b

    @classmethod
    def from_two_points(cls, p, q):
        """
        Get a line equation from 2 points

        :param p: {Point}
        :param q: {Point}
        :return: {Line}
        """
        m = None if p.x == q.x else (p.y - q.y) / (p.x - q.x)
        b = 0 if m is None else p.y - m * p.x
        return cls(m, b)

    @classmethod
    def from_point_and_slope(cls, p, m):
        """
        Get a line equation from a point and a slope

        :param p: {Point}
        :param m: slope
        :return: {Line}
        """
        b = 0 if m is None else p.y - m * p.x
        return cls(m, b)

    # TODO: refactor
    def __repr__(self):
        if self.m is None:
            return 'y = 0'
        elif self.m == 0:
            return 'y = {0}'.format(self.b)
        else:
            if self.b == 0:
                return 'y = {0}x'.format(self.m)
            if self.b < 0:
                return 'y = {0}x - {1}'.format(self.m, abs(self.b))
            else:
                return 'y = {0}x + {1}'.format(self.m, self.b)

    def is_parallel(self, other):
        """
        Check if 2 lines are parallel

        :param other: {Line}
        :return: {bool}
        """
        return self.m == other.m  # assuming they are not the same

# TODO: rewrite methods
#     def point_of_intersection(self, other):
#         """
#         Return the point of intersection of two lines
#         or None if they are parallel
#
#         :param other: {Line}
#         :return: {Point} or {None}
#         """
#         if self.is_parallel(other):
#             return None
#
#         if self.a is not None and other.a is not None:
#             x = (other.b - self.b) / (self.a - other.a)
#             y = self.a * x + self.b
#         elif self.a is None:
#             x = self.p1.x
#             y = other.a * x + other.b
#         else:
#             x = other.p1.x
#             y = self.a * x + self.b
#
#         return Point(x, y)
#
#     def perpendicular(self, p):
#         """
#         Perpendicular from the given point to the line
#
#         :param p: {Point}
#         :return: {Line} perpendicular line or {None} if the point is on the line
#         """
#         # if the point is on the line
#         if self.a is not None:
#             if p.y == self.a * p.x + self.b:
#                 return None
#
#             if self.a == 0:
#                 perpendicular = Line(p, None, None, p.x)
#             else:
#                 b = p.y + p.x * (self.p2.x - self.p1.x) / (self.p2.y - self.p1.y)
#                 perpendicular = Line(p, None, -1 / self.a, b)
#         else:
#             if p.x == self.p1.x:
#                 return None
#             perpendicular = Line(p, None, 0, p.y)
#
#         return perpendicular
#
#
# class Circle:
#     def __init__(self, center, r):
#         self.center = center
#         self.r = r
#
#     def __repr__(self):
#         return '(x-{0})^2 + (y-{1})^2 = {2}^2'.format(self.center.x, self.center.y, self.r)
#
#     def point_in_circle(self, point):
#         """
#         Check if the point is inside the circle
#
#         :param point: {Point}
#         :return: {bool}
#         """
#         return True if (point.x - self.center.x) ** 2 + (point.y - self.center.y) ** 2 <= self.r ** 2 else False
#
#     def line_intersects_circle(self, line):
#         """
#         Check if the line intersects the circle
#
#         :param line: {Line}
#         :return: {bool}
#         """
#         dist = line.perpendicular(self.center)
#         if dist is None:
#             return True
#         else:
#             intersection = line.point_of_intersection(dist)
#             if self.point_in_circle(intersection):
#                 return True
#             return False
#
#
# if __name__ == '__main__':
#     while True:
#         params = input().split()
#         params = [int(p) for p in params]
#
#         if params == [0, 0, 0, 0]:
#             break
#
#         cr = params[0]
#         cx = params[1]
#         cy = params[2]
#         n = params[3]
#
#         count = 1
#
#         if n == 0:
#             # no cuts
#             print(count)
#
#         c = Circle(Point(cx, cy), cr)
#         lines = []
#         while n > 0:
#             x1, y1, x2, y2 = input().split()
#             p1 = Point(int(x1), int(y1))
#             p2 = Point(int(x2), int(y2))
#             lines.append(Line(p1, p2))
#             n -= 1
#
#         processed_lines = []
#         for l in lines:
#             # only lines that intersect the circle
#             if c.line_intersects_circle(l):
#                 for pl in processed_lines:
#                     lip = l.point_of_intersection(pl)  # lines intersection point
#                     if lip:
#                         # point inside the circle
#                         if (lip.x - c.center.x) ** 2 + (lip.y - c.center.y) ** 2 < c.r ** 2:
#                             count += 1
#
#                 # count = # of intersections inside the circle + 1
#                 count += 1
#
#                 # keep the lines we already processed
#                 processed_lines.append(l)
#         print(count)
