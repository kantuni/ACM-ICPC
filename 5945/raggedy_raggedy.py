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

    return width if width <= L else False


def minimize_total_raggedness():
    """
    DP

    Lay paragraphs out in a way that no line contains more than L characters,
    for a specified L, and so that you minimize the total raggedness
    added up over all lines except the last one.

    :return: a paragraph with a minimum total raggedness
    """
    # 6
    # See if we
    # care.
    #
    # C(i, j, k) = min(r(i, i) + C(i + 1, j, k + 1), r(i, i + 1) + C(i + 2, j, k + 1), ...)
    #
    # C(0, 3, 0) = min(r(0, 0) + C(1, 3, 1), r(0, 1) + C(2, 3, 1)) = min(9 + C(1, 3, 1), 0 + C(2, 3, 1)) = 10 + 1|0
    # C(1, 3, 1) = min(r(1, 1) + C(2, 3, 2), r(1, 2) + C(3, 3, 2)) = min(16 + C(2, 3, 2), 1 + C(3, 3, 2)) = 1 + 1|0
    # - C(2, 3, 2) = min(r(2, 2) + C(3, 3, 3), r(2, 3) + C(5, 3, 3)) = min(16 + C(3, 3, 3), infinity) = 16 + 1|0
    # - C(3, 3, 3) = min(r(3, 3) + 0, infinity) = 1 | 0
    # C(3, 3, 2) = min(r(3, 3) + 0, infinity) = 1 | 0
    # - C(2, 3, 1) = min(r(2, 2) + C(3, 3, 2), r(2, 3) + 0) = min(16 + 1|0, infinity) = 16 + 1|0
    # 
    global L, words

    paragraph = ''
    return paragraph


if __name__ == '__main__':
    while True:
        L = int(input())

        if L == 0:
            break

        words = []
        number_of_lines = 250

        while number_of_lines > 0:
            words_in_line = input().split()
            # terminated by an empty line
            if not words_in_line:
                break
            words.extend(words_in_line)
            number_of_lines -= 1

        print(minimize_total_raggedness())
        print('===')
