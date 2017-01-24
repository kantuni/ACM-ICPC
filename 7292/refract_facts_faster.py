""" Created by Henrikh Kantuni on 1/23/17 """

import math


def find_phi(start, end):
    """
    Use binary search to find a value of φ, such that

        tg(φ) = d / y
        sin(a) / sin(b) = n1 / n2, where
        sin(a) = y / sqrt(y^2 + d^2)
        sin(b) = (x-y) / sqrt(h^2 + (x-y)^2)

    :param start: {float}
    :param end: {float}
    :return: {float} value of φ
    """
    phi = (start + end) / 2
    y = d / math.tan(math.radians(phi))
    sin_a = y / math.sqrt(y ** 2 + d ** 2)
    sin_b = (x - y) / math.sqrt(h ** 2 + (x - y) ** 2)

    if math.isclose(sin_a * n2, sin_b * n1, rel_tol=1e-04):
        return phi

    if sin_a * n2 < sin_b * n1:
        return find_phi(start, phi)
    return find_phi(phi, end)


if __name__ == '__main__':
    while True:
        params = input().split()
        params = [float(x) for x in params]

        if params == [0, 0, 0, 0, 0]:
            break

        d, h, x, n1, n2 = params

        answer = 90 if x == 0 else round(find_phi(0, 90), 2)
        print('{:.2f}'.format(answer))
