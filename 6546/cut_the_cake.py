""" Created by Henrikh Kantuni on 11/3/16 """


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return '(' + str(self.x) + ', ' + str(self.y) + ')'


class Line:
    def __init__(self, p1, p2):
        self.p1 = p1
        self.p2 = p2
        if p1.x != p2.x:  # y = ax + b
            self.a = (p2.y - p1.y) / (p2.x - p1.x)
            self.b = (p1.y * p2.x - p2.y * p1.x) / (p2.x - p1.x)
        else:
            self.a = None  # y = 0
            self.b = 0  # y = b

    def __repr__(self):
        if self.a is None:
            return 'y = 0'
        elif self.a == 0:
            return 'y = ' + str(self.b)
        else:
            if self.b == 0:
                return 'y = ' + str(self.a) + 'x'
            if self.b < 0:
                return 'y = ' + str(self.a) + 'x - ' + str(abs(self.b))
            else:
                return 'y = ' + str(self.a) + 'x + ' + str(self.b)

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
        return self.a == other.a  # assuming they are not the same


class Circle:
    def __init__(self, x, y, r):
        self.x = x
        self.y = y
        self.r = r

    def point_in_circle(self, point):
        """
        Check if the point is inside the circle

        :param point: {Point}
        :return: {bool}
        """
        return True if (point.x - self.x) ** 2 + (point.y - self.y) ** 2 <= self.r ** 2 else False

    def line_intersects_circle(self, line):
        """
        Check if the line intersects the circle

        :param line: {Line}
        :return: {bool}
        """
        # use perpendicular instead
        for x in range(-1000, 1001):
            y = line.calculate_y(x)
            print(Point(x, y))
            if self.point_in_circle(Point(x, y)):
                return True
        return False


c = Circle(16, 1, 7)
# l1 = Line(Point(-15, -9), Point(14, -11))
l2 = Line(Point(-4, 30), Point(-3, -20))
# l3 = Line(Point(-20, 12), Point(-10, 7))
# l4 = Line(Point(-20, 12), Point(-10, 7))

# print(l1, c.line_intersects_circle(l1))
print(l2, c.line_intersects_circle(l2))


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

        c = Circle(cx, cy, cr)

        lines = []
        while n > 0:
            x1, y1, x2, y2 = input().split()
            p1 = Point(int(x1), int(y1))
            p2 = Point(int(x2), int(y2))
            lines.append(Line(p1, p2))
            n -= 1

        processed_lines = []
        points_inside_the_circle = []

        for l in lines:
            # remove lines that don't intersect the circle
            if c.line_intersects_circle(l):
                parallel = True
                for pl in processed_lines:
                    if not l.is_parallel(pl):
                        parallel = False
                        break

                # if a line doesn't intersect other lines inside the circle (is parallel)
                if parallel:
                    count += 1
                # if a line intersects other lines inside the circle
                else:
                    # find all points of the line inside the circle
                    for x in range(-1000, 1001):
                        y = l.get_y_coordinate(x)
                        if c.point_in_circle(Point(x, y)):
                            # point inside the circle
                            if (x - c.x) ** 2 + (y - c.y) ** 2 < c.r ** 2:
                                if Point(x, y) in points_inside_the_circle:
                                    count += 1
                                else:
                                    points_inside_the_circle.append(Point(x, y))

                    # count = # of intersections inside the circle + 1
                    count += 1

                # keep the lines we already processed
                processed_lines.append(l)

        print(lines)
        print(processed_lines)

        print(count)
