def extract_digits(num):
    digits = []
    if num == 0:
        return [0]
    while num != 0:
        rem = num % 10
        num /= 10
        digits.append(rem)
    return digits

def print_num_phrase(num):
    """

    :param num: integer number to be translated to phrase
    :return:
    """
    ones_phrase = ['zero', 'one', 'two', 'three', 'four', 'five', 'six',
                   'seven', 'eight', 'nine']
    tens_phrase = ['', 'ten', 'twenty', 'thirty', 'forty', 'fifty', 'sixty',
                   'seventy', 'eighty', 'ninety']
    teens = ['ten', 'eleven', 'twelve', 'thirteen', 'fourteen', 'fifteen',
             'sixteen', 'seventeen', 'eighteen', 'nineteen']
    other_places_phrase = ['', '', 'hundred', 'thousand', '', 'hundred',
                           'million', '', 'hundred', 'billion', '', 'hundred']

    digits = extract_digits(num)
    i = 0
    reversed_phrase = []
    num_digits = len(digits)
    if num_digits == 1 and digits[0] == 0:
        return 'zero'

    while i < num_digits:
        substr_to_add = ''
        if digits[i] == 0:
            i += 1
            continue
        if digits[i] == 1 and i == 1:
            reversed_phrase = []
            substr_to_add = teens[digits[0]]
        elif i == 1 or i == 4 or i == 7 or i == 10:
            if digits[i] == 1 and i != 1:
                if digits[i-1] != 0:
                    reversed_phrase[-1] = ''
                    reversed_phrase[-2] = other_places_phrase[i-1]
                else:
                    reversed_phrase.append(other_places_phrase[i-1])
                substr_to_add = teens[digits[i-1]]
            else:
                if digits[i-1] == 0:
                    reversed_phrase.append(other_places_phrase[i-1])
                substr_to_add = tens_phrase[digits[i]]
        elif i == 2 or i == 5 or i == 8 or i == 11:
            # the hundreds phrase
            if digits[i-1] == 0 and digits[i-2] == 0:
                reversed_phrase.append(other_places_phrase[i-2])
            substr_to_add = ones_phrase[digits[i]]
        else:
            substr_to_add = ones_phrase[digits[i]]
        #substr_to_add += ' ' + other_places_phrase[i]
        reversed_phrase.append(' ' + other_places_phrase[i])
        reversed_phrase.append(substr_to_add)
        i += 1
    reversed_phrase1 = []
    for word in reversed_phrase:
        if word != '':
            reversed_phrase1.append(word)

    return ' '.join(reversed_phrase1[::-1])

def main():
    print print_num_phrase(200030015014)

if __name__ == '__main__':
    main()