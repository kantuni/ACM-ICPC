""" Created by Henrikh Kantuni on 11/2/16 """


def number_to_english(n):
    """
    Transformation of non-negative integers into conventional English wording

    :param n: {int} number from 0 to 999,999,999
    :return: {str} spelled-out equivalent of the number
    """
    pass


if __name__ == '__main__':
    while True:
        number = int(input())

        if number < 0:
            break

        print(number_to_english(number))
