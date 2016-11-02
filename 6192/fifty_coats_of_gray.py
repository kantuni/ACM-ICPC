""" Created by Henrikh Kantuni on 11/1/16 """

import math

if __name__ == '__main__':
    while True:
        params = input().split()
        params = [int(x) for x in params]

        if params == [0, 0, 0, 0, 0, 0]:
            break

        n = params[0]
        w = params[1]
        l = params[2]
        h = params[3]
        area = params[4]
        m = params[5]

        not_painted_area = 0
        while m > 0:
            windows_and_doors = input().split()
            not_painted_area += int(windows_and_doors[0]) * int(windows_and_doors[1])
            m -= 1

        painted_area = 2 * h * (l + w) + l * w
        cans = math.ceil((painted_area - not_painted_area) * n / area)
        print(cans)
