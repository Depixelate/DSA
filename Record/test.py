def insertion_sort(array):
    for i in range(1, len(array)):
        j = i
        while j > 0 and array[j] < array[j-1]:
            array[j], array[j-1] = array[j-1], array[j]
            j -= 1
    for i in range(len(array)):
        print(array[i], end = " ")

insertion_sort([3, 1, 5, 2])