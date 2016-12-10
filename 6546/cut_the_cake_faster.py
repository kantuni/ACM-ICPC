""" Created by Henrikh Kantuni on 12/10/16 """


def get_point_of_intersection(l1, l2):
    """
    Return the point of intersection of two lines
    or None if they are parallel

    :param l1: {tuple} (x1, y1, x2, y2)
    :param l2: {tuple} (x1, y1, x2, y2)
    :return: {tuple} (x, y) or None
    """
    # calculate the slope, the y-intercept, and the x-intercept for line 1
    m1 = None if l1[0] == l1[2] else (l1[3] - l1[1]) / (l1[2] - l1[0])
    b1 = 0 if m1 is None else l1[1] - m1 * l1[0]
    a1 = l1[0] if m1 is None else (0 if m1 == 0 else -b1 / m1)

    # calculate the slope, the y-intercept, and the x-intercept for line 2
    m2 = None if l2[0] == l2[2] else (l2[3] - l2[1]) / (l2[2] - l2[0])
    b2 = 0 if m2 is None else l2[1] - m2 * l2[0]
    a2 = l2[0] if m2 is None else (0 if m2 == 0 else -b2 / m2)

    # check if parallel
    if m1 == m2:
        return None

    # find an intersection point
    if m1 is not None and m2 is not None:
        x = (b2 - b1) / (m1 - m2)
        y = m1 * x + b1
    elif m1 is None:
        x = a1
        y = m2 * x + b2
    else:
        x = a2
        y = m1 * x + b1

    return x, y


def line_intersects_circle(circle, line):
    """
    Check if a line intersects a circle

    :param circle: {tuple} (cx, cy, cr)
    :param line: {tuple} (x1, y1, x2, y2)
    :return: {bool}
    """
    pass


if __name__ == '__main__':
    while True:
        params = input().split()
        params = (int(p) for p in params)

        if params == (0, 0, 0, 0):
            break

        # parse params
        cr, cx, cy, n = params

        count = 1

        if n == 0:
            # no cuts
            print(count)
            continue

        # construct lines
        lines = []
        while n > 0:
            x1, y1, x2, y2 = (int(x) for x in input().split())
            lines.append((x1, y1, x2, y2))
            n -= 1

        processed_lines = []
        for l in lines:
            # only lines that intersect the circle
            if line_intersects_circle((cx, cy, cr), l):
                for pl in processed_lines:
                    lip = get_point_of_intersection(l, pl)  # lines intersection point
                    if lip:
                        # check if intersection point is inside the circle
                        point_in_circle = (lip[0] - cx) ** 2 + (lip[1] - cy) ** 2 < cr ** 2
                        if point_in_circle:
                            count += 1

                # count = # of intersections inside the circle + 1
                count += 1

                # keep the processed lines that intersected the circle
                processed_lines.append(l)

        print(count)
