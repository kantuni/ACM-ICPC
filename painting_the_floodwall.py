""" Created by Henrikh Kantuni on 12/25/16 """


def get_maximum_total_length():
    """
    DP

    Calculate the maximum total length of the fence that can be painted
    without allowing any two artists' work to overlap.

    Recursive formula:
    Let C[i, j] denote the maximum total length of the fence that can be painted using murals from i to j (inclusive)
    that don't overlap, then C[i, j] =

    :return: {int} maximum total length of the fence
    """
    # Example:
    # 3
    # 100 200
    # 190 210
    # 200 300
    #
    # C[0, 2] = the maximum total length of ... using murals from 0 to 2 (inclusive) that don't overlap
    #
    # Case 1: (100, 200) is used
    # then the maximum total length = (200 - 100) + maximum of the rest that don't overlap with (100, 200)
    #
    # Case 2: (100, 200) is not used
    # then the maximum total length = maximum of the rest
    pass


if __name__ == '__main__':
    while True:
        params = input().split()
        params = [int(p) for p in params]

        # number of paintings
        n = params[0]

        # ???
        if n == 1:
            print(1)
            continue

        paintings = []
        C = []  # costs

        while n > 0:
            x0, x1 = input().split()
            paintings.append((int(x0), int(x1)))
            n -= 1

        print(get_maximum_total_length())
