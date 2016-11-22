""" Created by Henrikh Kantuni on 11/3/16 """


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return '({0}, {1})'.format(self.x, self.y)


class Line:
    def __init__(self, m, b, a):
        """
        Create a line from a slope, a y-intercept, and an x-intercept

        :param m: slope
        :param b: y-intercept
        :param a: x-intercept
        """
        self.m = m
        self.b = b
        self.a = a

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
        a = p.x if m is None else (0 if m == 0 else -b / m)

        return cls(m, b, a)

    @classmethod
    def from_point_and_slope(cls, p, m):
        """
        Get a line equation from a point and a slope

        :param p: {Point}
        :param m: slope
        :return: {Line}
        """
        b = 0 if m is None else p.y - m * p.x
        a = p.x if m is None else (0 if m == 0 else -b / m)

        return cls(m, b, a)

    def __repr__(self):
        if self.m is None:
            return 'y = 0, x = {0}'.format(self.a)
        elif self.m == 0:
            return 'y = {0}, x = 0'.format(self.b)
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

    def point_of_intersection(self, other):
        """
        Return the point of intersection of two lines
        or None if they are parallel

        :param other: {Line}
        :return: {Point} or {None}
        """
        if self.is_parallel(other):
            return None

        if self.m is not None and other.m is not None:
            x = (other.b - self.b) / (self.m - other.m)
            y = self.m * x + self.b
        elif self.m is None:
            x = self.a
            y = other.a * x + other.b
        else:
            x = other.a
            y = self.a * x + self.b

        return Point(x, y)

    def perpendicular(self, p):
        """
        Drop a perpendicular from a point to a line

        :param p: {Point}
        :return: {Line} perpendicular or {None} if the point is on the line
        """
        if self.m is not None:
            # if the point is on the line
            if p.y == self.m * p.x + self.b:
                return None

            if self.m == 0:
                # vertical line
                perpendicular = Line(None, 0, p.x)
            else:
                # line with a "negative reciprocal" slope
                perpendicular = self.from_point_and_slope(p, -1 / self.m)
        else:
            # if the point is on the line
            if p.x == self.a:
                return None

            # horizontal line
            perpendicular = Line(0, p.y, 0)

        return perpendicular


class Circle:
    def __init__(self, center, r):
        self.center = center
        self.r = r

    def __repr__(self):
        return '(x-{0})^2 + (y-{1})^2 = {2}^2'.format(self.center.x, self.center.y, self.r)

    def point_in_circle(self, point):
        """
        Check if a point is inside a circle

        :param point: {Point}
        :return: {bool}
        """
        return True if (point.x - self.center.x) ** 2 + (point.y - self.center.y) ** 2 <= self.r ** 2 else False

    def line_intersects_circle(self, line):
        """
        Check if a line intersects a circle

        :param line: {Line}
        :return: {bool}
        """
        dist = line.perpendicular(self.center)
        # line through a circle center
        if dist is None:
            return True
        else:
            intersection = line.point_of_intersection(dist)
            if self.point_in_circle(intersection):
                return True
            return False


if __name__ == '__main__':
    while True:
        params = input().split()
        params = [int(p) for p in params]

        if params == [0, 0, 0, 0]:
            break

        # parse params
        cr = params[0]
        cx = params[1]
        cy = params[2]
        n = params[3]

        count = 1

        if n == 0:
            # no cuts
            print(count)
            continue

        # construct a circle
        c = Circle(Point(cx, cy), cr)

        # construct lines
        lines = []
        while n > 0:
            x1, y1, x2, y2 = input().split()
            p1 = Point(int(x1), int(y1))
            p2 = Point(int(x2), int(y2))
            lines.append(Line.from_two_points(p1, p2))
            n -= 1

        processed_lines = []
        for l in lines:
            # only lines that intersect the circle
            if c.line_intersects_circle(l):
                for pl in processed_lines:
                    lip = l.point_of_intersection(pl)  # lines intersection point
                    if lip:
                        # check if intersection point is inside the circle
                        if (lip.x - c.center.x) ** 2 + (lip.y - c.center.y) ** 2 < c.r ** 2:
                            count += 1

                # count = # of intersections inside the circle + 1
                count += 1

                # keep the processed lines that intersected the circle
                processed_lines.append(l)
        
        print(count)
