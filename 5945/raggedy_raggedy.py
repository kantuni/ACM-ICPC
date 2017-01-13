""" Created by Henrikh Kantuni and Shahen Kosyan on 12/27/16 """


def w(i, j):
    """
    Define w(i,j) as the width of the line containing words i through j, inclusive,
    plus one blank space between each pair of words.

    :param i: {int} starting position
    :param j: {int} ending position
    :return: {int} w(i, j) value or 0
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
    r(i, j) = (L − w(i, j)) ** 2

    :param i: {int} starting position
    :param j: {int} ending position
    :return: {int} r(i, j) value
    """
    global L
    return (L - w(i, j)) ** 2


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

def c(i, k, last):
    """
    Let C(i, k, last) denote minimum raggedness of a line k containing ith word ignoring last words.
    Then C(i, k, last) = min(r(i, i) + C(i + 1, k + 1, last), r(i, i + 1) + C(i + 2, k + 1, last), ...)

    :param i: {int} starting position
    :param k: {int} line
    :param last: {int} number of words used in the last line
    :return: {tuple} a minimum total raggedness and an index of the minimum value (the winner)
    """
    global words
    raggedness = []

    # out of bounds
    if i > len(words) - 1 - last:
        return 0, -1

    l = i
    while w(i, l) > 0 and l <= len(words) - 1 - last:
        # add value to memo
        if not memo.get('{0}, {1}'.format(l + 1, k + 1)):
            memo['{0}, {1}'.format(l + 1, k + 1)] = c(l + 1, k + 1, last)
        # calculate all raggedness values
        raggedness.append(r(i, l) + memo['{0}, {1}'.format(l + 1, k + 1)][0])
        l += 1

    # find a total minimum raggedness
    minimum = min(raggedness)
    memo['{0}, {1}'.format(i, k)] = minimum, raggedness.index(minimum)
    return minimum, raggedness.index(minimum)


def minimize_total_raggedness():
    """
    Calculate raggedness values with different number of last words and
    return the minimum of them.

    :return: {tuple} minimum total raggedness and number of last line words
    """
    global L, words, memo

    # clean memo
    memo = {}
    # set the min value to a raggedness with 1 last word
    last = 1
    minimum = c(0, 0, last)[0]

    i = 0
    while i < len(words):
        # go as much as possible to find a minimum
        if 0 < w(len(words) - i - 1, len(words) - 1) <= L:
            # clean memo
            memo = {}
            # update minimum value
            if minimum > c(0, 0, i)[0]:
                minimum = c(0, 0, i)[0]
                last = i
        i += 1

    # clean memo
    memo = {}
    # call minimum once again to update memo
    c(0, 0, last)
    return minimum, last


def backtracking():
    """
    Build a string with a minimum total raggedness from a memo table

    :return: {str} string with minimum total raggedness
    """
    global memo, last_line_words
    string = ''

    # start with first word, i.e. the last winner
    i = 0
    k = 0
    winner_index = memo['{0}, {1}'.format(i, k)][1]

    while winner_index > -1:
        # add words to the appropriate line
        for word in words[i: i + winner_index + 1]:
            string += word + ' '
        # remove trailing space
        string = string[:-1]
        # move to the next line
        string += '\n'

        # move to the next winner
        i += winner_index + 1
        k += 1
        winner_index = memo['{0}, {1}'.format(i, k)][1]

    # if there are last line words
    if last_line_words > 0:
        for word in words[len(words) - last_line_words: len(words)]:
            string += word + ' '
        # remove trailing space
        string = string[:-1]

    # remove empty line
    if string[-1] == '\n':
        string = string[:-1]

    return string


if __name__ == '__main__':
    while True:
        # maximum line width
        L = int(input())

        # a value of zero indicates the end of input
        if L == 0:
            break

        # max number of lines
        number_of_lines = 250
        words = []
        memo = {}

        while number_of_lines > 0:
            words_in_line = input().split()
            # terminate by an empty line
            if not words_in_line:
                break
            # add words from new line
            words.extend(words_in_line)
            number_of_lines -= 1

        if len(words) < 2:
            print(words[0])
            print('===')
            continue

        mtr, last_line_words = minimize_total_raggedness()
        mtr_string = backtracking()
        print(mtr_string)
        print('===')
