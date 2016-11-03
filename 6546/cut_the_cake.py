""" Created by Henrikh Kantuni on 11/3/16 """


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


class Circle:
    def __init__(self, x, y, r):
        self.x = x
        self.y = y
        self.r = r


if __name__ == '__main__':
    while True:
        params = input().split()
        params = [int(p) for p in params]

        if params == [0, 0, 0, 0]:
            break

        r = params[0]
        x = params[1]
        y = params[2]
        n = params[3]

        if n == 0:
            # no cuts
            print(1)

        cake = Circle(x, y, r)

        lines = []
        while n > 0:
            coords = input().split()
            x_1, y_1, x_2, y_2 = int(coords[0]), int(coords[1]), int(coords[2]), int(coords[3])
            lines.append((Point(x_1, y_1), Point(x_2, y_2)))
