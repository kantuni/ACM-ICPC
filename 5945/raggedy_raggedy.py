""" Created by Henrikh Kantuni on 12/27/16 """


def w(i, j):
    """
    Define w(i,j) as the width of the line containing words i through j, inclusive,
    plus one blank space between each pair of words.

    :param i: starting position
    :param j: ending position
    :return: w(i, j) value
    """
    global L

    width = 0
    for word in words[i: j + 1]:
        # length of word + blank space
        width += len(word) + 1
    # remove last blank space
    width -= 1

    return width if 0 < width <= L else False


def r(i, j):
    """
    Define the raggedness of a line containing words i though j as
    r(i, j) = (L − w(i, j))**2

    :param i: starting position
    :param j: ending position
    :return: r(i, j) value
    """
    global L
    return (L - w(i, j)) ** 2


def c(i, k, last):
    # TODO: revise C(i, k) definition
    """
    Let C(i, k) denote minimum raggedness of a line k containing ith word (ignore last words)
    Then C(i, k) = min(r(i, i) + C(i + 1, k + 1), r(i, i + 1) + C(i + 2, k + 1), ...)

    :param i: starting position
    :param k: line
    :param last: number of words used in the last line
    :return: minimum total raggedness
    """
    # C(i, k) = min(r(i, i) + C(i + 1, k + 1), r(i, i + 1) + C(i + 2, k + 1), ...)
    #
    # - Example 1 -
    # 6
    # See if we
    # care.
    #
    # 11 = C(0, 0) = min(r(0, 0) + C(1, 1), r(0, 1) + C(2, 1)) = min(9 + C(1, 1), 0 + C(2, 1)) = 10 + 1|0
    # 2 = C(1, 1) = min(r(1, 1) + C(2, 2), r(1, 2) + C(3, 2)) = min(16 + C(2, 2), 1 + C(3, 2)) = 1 + 1|0
    # 17 = C(2, 2) = min(r(2, 2) + C(3, 3), r(2, 3) + C(5, 3)) = min(16 + C(3, 3), infinity) = 16 + 1|0
    # 1 = C(3, 3) = min(r(3, 3) + C(4, 4), infinity) = min(r(3, 3) + 0, infinity) = 1 | 0
    # 1 = C(3, 2) = min(r(3, 3) + C(4, 3), infinity) = min(r(3, 3) + 0, infinity) = 1 | 0
    # 17 = C(2, 1) = min(r(2, 2) + C(3, 2), r(2, 3) + 0) = min(16 + 1|0, infinity) = 16 + 1|0
    #
    # - Example 2 -
    # 20
    # Here are we.
    #
    # C(0, 0, 0) = min(r(0, 0) + C(1, 1, 0), r(0, 1) + C(2, 1, 0), r(0, 2) + C(3, 1, 0))
    # = min(256 + 169, 144 + 64, 64 + 0) = 64
    # C(1, 1, 0) = min(r(1, 1) + C(2, 2, 0), r(1, 2) + C(3, 2, 0)) = min(289 + 64, 169 + 0) = 169
    # C(2, 2, 0) = min(r(2, 2) + C(3, 3, 0)) = min(64 + 0) = 64
    # C(2, 1, 0) = min(r(2, 2) + C(3, 1, 0)) = min(64 + 0) = 64
    #
    global words
    raggedness = []

    if i > len(words) - 1 - last:
        return 0

    l = i
    while w(i, l) and l <= len(words) - 1 - last:
        if memo.get('{0}, {1}'.format(l, k)):
            raggedness.append(r(i, l) + memo['{0}, {1}'.format(l, k)])
        else:
            raggedness.append(r(i, l) + c(l + 1, k + 1, last))
        l += 1

    memo['{0}, {1}'.format(i, k)] = min(raggedness)
    return min(raggedness)


if __name__ == '__main__':
    while True:
        L = int(input())

        if L == 0:
            break

        words = []
        number_of_lines = 250
        memo = {}
        counter = 0

        while number_of_lines > 0:
            words_in_line = input().split()
            # terminated by an empty line
            if not words_in_line:
                break
            words.extend(words_in_line)
            number_of_lines -= 1

        print(c(0, 0, 1))
        print('===')
