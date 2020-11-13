""" Created by Henrikh Kantuni on 11/1/16 """

import math


def find_y(start, end):
    """
    Use binary search to find a value of y (the little piece of x), such that

        sin(a) / sin(b) = n1 / n2, where
        sin(a) = y / sqrt(y^2 + d^2)
        sin(b) = sqrt(h^2 + (x-y)^2) / (x-y)

    :param start: {float}
    :param end: {float}
    :return: {float} value of y
    """
    y = (start + end) / 2
    sin_a = y / math.sqrt(y * y + d * d)
    sin_b = (x - y) / math.sqrt(h * h + (x - y) * (x - y))

    if math.isclose(sin_a * n2, sin_b * n1, rel_tol=1e-04):
        return y

    if sin_a * n2 > sin_b * n1:
        return find_y(start, y)
    return find_y(y, end)


if __name__ == "__main__":
    while True:
        params = map(float, input().split())
        if params == [0, 0, 0, 0, 0]:
            break

        d, h, x, n1, n2 = params
        answer = 90 if x == 0 else round(math.degrees(math.atan(d / find_y(0, x))), 2)
        print("{:.2f}".format(answer))
