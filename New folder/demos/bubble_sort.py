# in r3 there's one scalar and 3 vectors

# vectors anticommute

# 0 1 2 3

# 0 1 2 3 12 23 31 123


# 3221


def bubble_sort(arr):
    # using adjacent swaps
    # move the highest value to the nth place
    # then move the second highest value to the n-1th place
    # and so on.

    n = len(arr)
    for i in range(n-1):
        for j in range(0, n-i-1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                print(arr)



def get_sign_of_multivector(arr):
    # every time a swap occurs between different elements
    # the sign is negated
    # this is consistent with anticommutativity

    n = len(arr)
    sign = 1
 
    for i in range(n-1):
        for j in range(0, n-1-i):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                sign = -sign
                print(arr)
    
    print(sign, list(set(arr)))

multivector_directions = [ [],[1],[2],[3],[1,2],[2,3],[3,1],[1,2,3]]
arr = [3,1]
print(arr)
get_sign_of_multivector(arr)
 