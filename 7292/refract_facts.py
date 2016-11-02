""" Created by Henrikh Kantuni on 11/1/16 """

import math

if __name__ == '__main__':
    while True:
        params = input().split()
        params = [float(x) for x in params]

        if params == [0, 0, 0, 0, 0]:
            break

        d = params[0]
        h = params[1]
        x = params[2]
        n1 = params[3]
        n2 = params[4]

        y = 0.01
        while True:
            sin_a = y / math.sqrt(y*y + d*d)
            sin_b = (x-y) / math.sqrt(h*h + (x-y)*(x-y))

            if math.isclose(sin_a * n2, sin_b * n1, rel_tol=1e-04):
                answer = round(math.degrees(math.atan(d / y)), 2)
                print('{:.2f}'.format(answer))
                break

            y += 0.01
