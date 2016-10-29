""" Created by Henrikh Kantuni on 10/29/16. """


def is_equal(a, b, ignore):
    """
    Determine if a is equal to b ignoring an element with the given index
    :param a: {list} a
    :param b: {list} b
    :param ignore: {int} index of an element to ignore
    :return: True or False
    """
    a, b = a[:], b[:]
    del a[ignore]
    del b[ignore]
    return True if a == b else False


while True:
    sequence = input()
    if sequence == '-1 -1 -1 -1':
        break

    original = sequence.split()
    original = [int(s) for s in original]
    derived = original[:]
    index_of_unknown = original.index(-1)

    # arithmetic sequence
    if index_of_unknown < 2:
        diff = derived[3] - derived[2]
        derived[1] = derived[2] - diff
        derived[0] = derived[1] - diff
    else:
        diff = derived[1] - derived[0]
        derived[2] = derived[1] + diff
        derived[3] = derived[2] + diff

    if is_equal(original, derived, index_of_unknown):
        if 1 <= derived[index_of_unknown] <= 1000000:
            print(derived[index_of_unknown])
            continue

    # geometric sequence
    if index_of_unknown < 2:
        factor = int(derived[3] / derived[2])
        derived[1] = int(derived[2] / factor)
        derived[0] = int(derived[1] / factor)
    else:
        factor = int(derived[1] / derived[0])
        derived[2] = derived[1] * factor
        derived[3] = derived[2] * factor

    if is_equal(original, derived, index_of_unknown):
        if 1 <= derived[index_of_unknown] <= 1000000:
            print(derived[index_of_unknown])
            continue

    print(-1)
