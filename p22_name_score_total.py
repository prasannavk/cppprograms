def name_score(name, rank):
    score = 0
    for c in name:
        score += ord(c) - ord('A') + 1
        #print(c, ord(c) - ord('A') + 1)
    return score*rank

def main():
    with open('p022_names.txt') as file:
        name_str = file.read()
    names = name_str[1:-1].split('","')
    print('Total num of names is {0}'.format(len(names)))
    names.sort()

    # for i in range(20):
    #     print(names[i])

    s = 0
    for i, name in enumerate(names):
        s += name_score(name, i+1)
    print('Total of the name scores is {0}'.format(s))

if __name__ == '__main__':
    main()