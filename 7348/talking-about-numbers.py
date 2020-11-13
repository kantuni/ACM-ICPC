""" Created by Henrikh Kantuni on 11/2/16 """


zero_to_nineteen = ["zero", "one", "two", "three", "four", "five",
                    "six", "seven", "eight", "nine", "ten", "eleven",
                    "twelve", "thirteen", "fourteen", "fifteen",
                    "sixteen", "seventeen", "eighteen", "nineteen"]

multiples_of_10 = ["you don't need this", "ten",
                   "twenty", "thirty", "forty", "fifty",
                   "sixty", "seventy", "eighty", "ninety"]


def from_0_to_99(n):
    """
    Spell all numbers in the range 0..99

    :param n: {int} number
    :return: {str} spelled-out equivalent of the number
    """
    global multiples_of_10

    if 0 <= n <= 19:
        # unique
        return zero_to_nineteen[n]

    elif 20 <= n <= 99:
        # tens
        if n % 10 == 0:
            return multiples_of_10[n // 10]
        return multiples_of_10[n // 10] + "-" + zero_to_nineteen[n % 10]


def from_100_to_999(n):
    """
    Spell all numbers in the range 100..999

    :param n: {int} number
    :return: {str} spelled-out equivalent of the number
    """
    answer = ""

    # hundreds
    answer += zero_to_nineteen[n // 100] + " hundred"
    # tens
    if n % 100 > 0:
        answer += " and " + from_0_to_99(n % 100)

    return answer


def from_1000_to_999999(n):
    """
    Spell all numbers in the range 1,000..999,999

    :param n: {int} number
    :return: {str} spelled-out equivalent of the number
    """
    answer = ""

    # tens of thousands
    if 0 <= n // 1000 <= 99:
        answer += from_0_to_99(n // 1000) + " thousand"
    # hundreds of thousands
    else:
        answer += from_100_to_999(n // 1000) + " thousand"

    # tens
    if 0 < n % 1000 <= 99:
        answer += " and " + from_0_to_99(n % 1000)
    # hundreds
    elif 100 <= n % 1000 <= 999:
        answer += ", " + from_100_to_999(n % 1000)

    return answer


def from_1000000_to_999999999(n):
    """
    Spell all numbers in the range 1,000,000..999,999,999

    :param n: {int} number
    :return: {str} spelled-out equivalent of the number
    """
    answer = ""

    # tens of millions
    if 0 < n // 1000000 <= 99:
        answer += from_0_to_99(n // 1000000) + " million"
    # hundreds of millions
    else:
        answer += from_100_to_999(n // 1000000) + " million"

    # tens
    if 0 < n % 1000000 <= 99:
        answer += " and " + from_0_to_99(n % 1000000)
    # hundreds
    elif 100 <= n % 1000000 <= 999:
        answer += ", " + from_100_to_999(n % 1000000)
    # thousands
    elif 1000 <= n % 1000000 <= 999999:
        answer += ", " + from_1000_to_999999(n % 1000000)

    return answer


def spell_number(n):
    """
    Transformation of non-negative integers into conventional English wording

    :param n: {int} number from 0 to 999,999,999
    :return: {str} spelled-out equivalent of the number
    """
    if 0 <= n <= 99:
        return from_0_to_99(n)
    elif 100 <= n <= 999:
        return from_100_to_999(n)
    elif 1000 <= n <= 999999:
        return from_1000_to_999999(n)
    else:
        return from_1000000_to_999999999(n)


if __name__ == "__main__":
    while True:
        number = int(input())

        if number < 0:
            break

        print(spell_number(number))
