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
    """
    Let C(i, k) denote minimum raggedness of a line k containing ith word
    Then C(i, k) = min(r(i, i) + C(i + 1, k + 1), r(i, i + 1) + C(i + 2, k + 1), ...)

    :param i: starting position
    :param k: line
    :return: minimum total raggedness
    """
    # 6
    # See if we
    # care.
    #
    # C(i, k) = min(r(i, i) + C(i + 1, k + 1), r(i, i + 1) + C(i + 2, k + 1), ...)
    #
    # 11 = C(0, 0) = min(r(0, 0) + C(1, 1), r(0, 1) + C(2, 1)) = min(9 + C(1, 1), 0 + C(2, 1)) = 10 + 1|0
    # 2 = C(1, 1) = min(r(1, 1) + C(2, 2), r(1, 2) + C(3, 2)) = min(16 + C(2, 2), 1 + C(3, 2)) = 1 + 1|0
    # 17 = C(2, 2) = min(r(2, 2) + C(3, 3), r(2, 3) + C(5, 3)) = min(16 + C(3, 3), infinity) = 16 + 1|0
    # 1 = C(3, 3) = min(r(3, 3) + C(4, 4), infinity) = min(r(3, 3) + 0, infinity) = 1 | 0
    # 1 = C(3, 2) = min(r(3, 3) + C(4, 3), infinity) = min(r(3, 3) + 0, infinity) = 1 | 0
    # 17 = C(2, 1) = min(r(2, 2) + C(3, 2), r(2, 3) + 0) = min(16 + 1|0, infinity) = 16 + 1|0
    #
    global words, counter, words_on_lines
    raggedness = []

    if i > len(words) - 1 - last:
        # counter += 1
        return 0

    l = i
    while w(i, l) and l <= len(words) - 1 - last:
        if saved.get('{0}, {1}'.format(i, k)):
            raggedness.append(r(i, l) + saved['{0}, {1}'.format(i, k)][0])
        else:
            raggedness.append(r(i, l) + c(l + 1, k + 1, last))
        l += 1

    saved['{0}, {1}'.format(i, k)] = (min(raggedness), counter)
    words_on_lines[i] = k
    counter += 1
    return min(raggedness)


def minimize_total_raggedness():
    """
    DP

    Lay paragraphs out in a way that no line contains more than L characters,
    for a specified L, and so that you minimize the total raggedness
    added up over all lines except the last one.

    :return: a paragraph with a minimum total raggedness
    """
    global words, saved


    used = []
    answer = ''

    i = 0
    while i < len(words):
        word_index, line_index = saved[i].split(', ')
        used.append((int(word_index), int(line_index)))
        i += 1

    used.sort(key=lambda item: item[0])

    print(used)

    line_index = 0
    for word in used:
        if word[1] > line_index:
            answer += '\n'
            line_index += 1
        if word[0] < len(words):
            answer += words[word[0]] + ' '
    answer = answer[:-1]

    return answer


def a():
    global values, saved

    i = 1
    length = len(words[len(words) - i])
    while length < 25:
        values.append((c(0, 0, i), saved))
        saved = {}
        i += 1
        length += 1 + len(words[len(words) - i])

    values = sorted(values, key=lambda item: item[0])

    return values[0]


if __name__ == '__main__':
    while True:
        L = int(input())

        if L == 0:
            break

        words = []
        words_on_lines = {}
        number_of_lines = 250
        saved = {}
        counter = 0
        values = []

        while number_of_lines > 0:
            words_in_line = input().split()
            # terminated by an empty line
            if not words_in_line:
                break
            words.extend(words_in_line)
            number_of_lines -= 1

        # print(c(0, 0))
        # print(saved)
        # print(words_on_lines)
        saved = a()[1]
        c(0, 0, 1)
        # print(saved)
        # print(words_on_lines)
        # saved = sorted(saved, key=lambda item: saved[item][1], reverse=True)
        # print(minimize_total_raggedness())
        print('===')
