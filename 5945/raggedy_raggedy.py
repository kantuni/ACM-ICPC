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
        # length of a word + blank space
        width += len(word) + 1
    # remove last blank space
    width -= 1

    return width if 0 < width <= L else 0


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
    Let C(i, k, last) denote minimum raggedness of a line k containing ith word (ignore last words)
    Then C(i, k, last) = min(r(i, i) + C(i + 1, k + 1, last), r(i, i + 1) + C(i + 2, k + 1, last), ...)

    :param i: starting position
    :param k: line
    :param last: number of words used in the last line
    :return: minimum total raggedness
    """
    # C(i, k, last) = min(r(i, i) + C(i + 1, k + 1, last), r(i, i + 1) + C(i + 2, k + 1, last), ...)
    #
    # - Example 1 -
    # 6
    # See if we
    # care.
    #
    # C(0, 0, 1) = min(r(0, 0) + C(1, 1, 1), r(0, 1) + C(2, 1, 1)) = min(9 + 1, 0 + 16) = 10
    # C(1, 1, 1) = min(r(1, 1) + C(2, 2, 1), r(1, 2) + C(3, 2, 1)) = min(16 + 16, 1 + 0) = 1
    # C(2, 2, 1) = min(r(2, 2) + C(3, 3, 1)) = min(16 + 0) = 16
    # C(2, 1, 1) = min(r(2, 2) + C(3, 2, 1)) = min(16 + 0) = 16
    # C(3, 3, 1) = 0
    # C(3, 2, 1) = 0
    #
    # - Example 2 -
    # 20
    # Here are we.
    #
    # C(0, 0, 0) = min(r(0, 0) + C(1, 1, 0), r(0, 1) + C(2, 1, 0), r(0, 2) + C(3, 1, 0))
    # = min(256 + 169, 144 + 289, 64 + 0) = min(425, 433, 64) = 64
    # C(1, 1, 0) = min(r(1, 1) + C(2, 2, 0), r(1, 2) + C(3, 2, 0)) = min(289 + 289, 169 + 0) = min(578, 169) = 169
    # C(2, 2, 0) = min(r(2, 2) + C(3, 3, 0)) = min(289 + 0) = 289
    # C(2, 1, 0) = min(r(2, 2) + C(3, 1, 0)) = min(289 + 0) = 289
    # C(3, 3, 0) = 0
    # C(3, 2, 0) = 0
    # C(3, 1, 0) = 0
    #
    global words
    raggedness = []

    if i > len(words) - 1 - last:
        return 0

    l = i
    while w(i, l) > 0 and l <= len(words) - 1 - last:
        if not memo.get('{0}, {1}'.format(l + 1, k + 1)):
            memo['{0}, {1}'.format(l + 1, k + 1)] = c(l + 1, k + 1, last)
        raggedness.append(r(i, l) + memo['{0}, {1}'.format(l + 1, k + 1)])
        l += 1

    memo['{0}, {1}'.format(i, k)] = min(raggedness)
    return min(raggedness)


def minimize_total_raggedness():
    global L, words, memo

    memo = {}
    minimum = c(0, 0, 1)

    i = 0
    last = 1
    while i < len(words):
        if 0 < w(len(words) - i - 1, len(words) - 1) <= L:
            memo = {}
            if minimum > c(0, 0, i):
                minimum = c(0, 0, i)
                last = i
        i += 1

    # update memo
    memo = {}
    c(0, 0, last)
    return minimum


if __name__ == '__main__':
    while True:
        L = int(input())

        if L == 0:
            break

        words = []
        number_of_lines = 250
        memo = {}

        while number_of_lines > 0:
            words_in_line = input().split()
            # terminated by an empty line
            if not words_in_line:
                break
            words.extend(words_in_line)
            number_of_lines -= 1

        print(minimize_total_raggedness())
        print(memo)
        print('===')
