def get_shortest_unique_substring_slower(arr, str_in):
    # this method has a time complexity of O(N^2)
    arr_set = set(arr)
    n = len(str_in)
    if n == 0:
        return ''
    smallest_ss = ""
    smallest_len = 2 ** 16
    i = 0

    while i < n:
        if not str_in[i] in arr_set:
            continue
        # print('first', str_in[i])
        end = i + len(arr)
        while end < n + 1:
            if not str_in[end - 1] in arr_set:
                continue
            substr = str_in[i:end]

            all_present = True
            for s in arr_set:
                if s not in substr:
                    all_present = False

            if all_present:
                if substr != '' and smallest_len > len(substr):
                    # print('here')
                    smallest_ss = substr
                    smallest_len = len(substr)
                    break
            end += 1

        i += 1

    return smallest_ss


def get_shortest_unique_substring(arr, str_in):
    m = len(arr)
    n = len(str_in)
    head_i = 0
    result = ''

    # number of unique characters in current substring
    unique_char_count = 0

    counter_list = [0]*m
    # dictionary to hold counts of characters in the current substring.
    count_current_substr = dict(zip(arr, counter_list))

    for tail_i in range(n):
        tail_char = str_in[tail_i]

        if tail_char not in count_current_substr:
            continue

        if count_current_substr[tail_char] == 0:
            unique_char_count += 1

        count_current_substr[tail_char] += 1

        while unique_char_count == m:
            sub_len = tail_i - head_i + 1
            if sub_len == m:
                return str_in[head_i:tail_i + 1]

            if result == '' or sub_len < len(result):
                result = str_in[head_i:tail_i + 1]

            head_char = str_in[head_i]
            if head_char in count_current_substr:
                head_count = count_current_substr[head_char] - 1

                if head_count == 0:
                    unique_char_count -= 1
                count_current_substr[head_char] = head_count

            head_i += 1

    return result


#print(get_shortest_unique_substring(['x', 'y', 'z', 'i'], 'xyyzyzyi'))

print(get_shortest_unique_substring(["A","B","C"], "ADOBECODEBANCDDD"))