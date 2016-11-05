""" Created by Henrikh Kantuni on 11/3/16 """


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return '({0}, {1})'.format(self.x, self.y)


class Line:
    def __init__(self, p1, p2, a=None, b=None):
        self.p1 = p1
        self.p2 = p2
        if p1 and p2:
            if p1.x != p2.x:  # y = ax + b
                self.a = (p2.y - p1.y) / (p2.x - p1.x)
                self.b = (p1.y * p2.x - p2.y * p1.x) / (p2.x - p1.x)
            else:
                self.a = None  # y = 0
                self.b = 0  # y = b
        elif (p1 or p2) and b is not None:
            self.a = a
            self.b = b
        else:
            raise ValueError("Line cannot be constructed.")

    def __repr__(self):
        if self.a is None:
            return 'y = 0'
        elif self.a == 0:
            return 'y = {0}'.format(self.b)
        else:
            if self.b == 0:
                return 'y = {0}x'.format(self.a)
            if self.b < 0:
                return 'y = {0}x - {1}'.format(self.a, abs(self.b))
            else:
                return 'y = {0}x + {1}'.format(self.a, self.b)

    def calculate_x(self, y):
        """
        Calculate the x coordinate given the y coordinate of the line

        :param y: {int}
        :return: {int}
        """
        return (y - self.b) / self.a if self.a else self.p1.x

    def calculate_y(self, x):
        """
        Calculate the y coordinate given the x coordinate of the line

        :param x: {int}
        :return: {int}
        """
        return 0 if (self.a is None) else self.a * x + self.b

    def is_parallel(self, other):
        """
        Check if 2 lines are parallel

        :param other: {Line}
        :return: {bool}
        """
        if self and other:  # why?
            return self.a == other.a  # assuming they are not the same
        return False

    def point_of_intersection(self, other):
        """
        Return the point of intersection of two lines

        :param other: {Line}
        :return: {Point} of intersection or None if they are parallel
        """
        if self.is_parallel(other):
            return None

        if self.a is not None and other.a is not None:
            x = (other.b - self.b) / (self.a - other.a)
            y = self.a * x + self.b
        elif self.a is None:
            x = self.p1.x
            y = other.a * x + other.b
        else:
            x = other.p1.x
            y = self.a * x + self.b

        return Point(x, y)

    def perpendicular(self, p):
        """
        Perpendicular from the given point to the line

        :param p: {Point}
        :return: {Line} perpendicular line or None if the point is on the line
        """
        # if the point is on the line
        if self.a is not None:
            if p.y == self.a * p.x + self.b:
                return None

            if self.a == 0:
                perpendicular = Line(p, None, None, p.x)
            else:
                b = p.y + p.x * (self.p2.x - self.p1.x) / (self.p2.y - self.p1.y)
                perpendicular = Line(p, None, -1 / self.a, b)
        else:
            if p.x == self.p1.x:
                return None
            perpendicular = Line(p, None, 0, p.y)

        return perpendicular


class Circle:
    def __init__(self, center, r):
        self.center = center
        self.r = r

    def __repr__(self):
        return '(x-{0})^2 + (y-{1})^2 = {2}^2'.format(self.center.x, self.center.y, self.r)

    def point_in_circle(self, point):
        """
        Check if the point is inside the circle

        :param point: {Point}
        :return: {bool}
        """
        return True if (point.x - self.center.x) ** 2 + (point.y - self.center.y) ** 2 <= self.r ** 2 else False

    def line_intersects_circle(self, line):
        """
        Check if the line intersects the circle

        :param line: {Line}
        :return: {bool}
        """
        dist = line.perpendicular(self.center)
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

        cr = params[0]
        cx = params[1]
        cy = params[2]
        n = params[3]

        count = 1

        if n == 0:
            # no cuts
            print(count)

        c = Circle(Point(cx, cy), cr)
        lines = []
        while n > 0:
            x1, y1, x2, y2 = input().split()
            p1 = Point(int(x1), int(y1))
            p2 = Point(int(x2), int(y2))
            lines.append(Line(p1, p2))
            n -= 1

        processed_lines = []
        for l in lines:
            # only lines that intersect the circle
            if c.line_intersects_circle(l):
                for pl in processed_lines:
                    lip = l.point_of_intersection(pl)  # lines intersection point
                    if lip:
                        # point inside the circle
                        if (lip.x - c.center.x) ** 2 + (lip.y - c.center.y) ** 2 < c.r ** 2:
                            count += 1

                # count = # of intersections inside the circle + 1
                count += 1

                # keep the lines we already processed
                processed_lines.append(l)
        print(count)
