import math

def gen_squares_dict():
    squares = {}
    for i in range(10000000):
        squares[i*i] = 1

    return squares

def find_minimal_solns(squares, D):
    best_y = -1
    best_x = -1
    for y in range(1, 100000):
        candidate = 1 + D*y*y
        if candidate in squares:
            best_y = y
            best_x = math.sqrt(candidate)
            break
    return best_x, best_y

def main():
    squares = gen_squares_dict()
    x_list = []
    for D in range(2, 1001):
        if D in squares:
            continue
        best_x, _ = find_minimal_solns(squares, D)
        x_list.append(best_x)
    print('Largest value of x obtained is {0}'.format(max(x_list)))

if __name__ == '__main__':
    main()