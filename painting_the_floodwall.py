""" Created by Henrikh Kantuni and Shahen Kosyan on 12/25/16 """


def max_total_length(murals):
    """
    DP

    Calculate the maximum total length of the fence that can be painted
    without allowing any two artists' work to overlap.

    Recursive formula:
    Let C(A) denote the maximum total length of the fence
    that can be painted using murals in array A that don't overlap.
    
    Then C(A) = max(A[0][1] - A[0][0] + C(B), C(A \ A[0]),
    where B = array of murals that don't overlap with A[0]

    :param: {int} starting position
    :param: {int} ending position
    :return: {int} maximum total length of the fence
    """
    if not murals:
        return 0

    no_overlap = []
    for mural in murals:
        if mural[1] <= murals[0][0] or mural[0] >= murals[0][1]:
            no_overlap.append(mural)

    value = murals[0][1] - murals[0][0]
    del murals[0]
    return max(value + max_total_length(no_overlap), max_total_length(murals))


if __name__ == '__main__':
    n = int(input())

    paintings = []

    while n > 0:
        x0, x1 = input().split()
        paintings.append((int(x0), int(x1)))
        n -= 1

    answer = max_total_length(paintings)
    print(answer)
