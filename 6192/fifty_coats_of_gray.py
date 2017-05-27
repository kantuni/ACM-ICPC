""" Created by Henrikh Kantuni on 11/1/16 """

import math

if __name__ == '__main__':
    while True:
        params = input().split()
        params = [int(x) for x in params]

        if params == [0, 0, 0, 0, 0, 0]:
            break

        # input data
        n, w, l, h, area, m = params

        not_painted_area = 0
        while m > 0:
            windows_and_doors = map(int, input().split())
            not_painted_area += windows_and_doors[0] * windows_and_doors[1]
            m -= 1

        painted_area = 2 * h * (l + w) + l * w
        cans = math.ceil((painted_area - not_painted_area) * n / area)
        print(cans)
