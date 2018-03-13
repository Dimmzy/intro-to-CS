# Find the largest number in an array of numbers using recursion

def findLargest(x):
    if len(x) == 1:
        return x
    elif x[0] > x[1]:
        x.remove(x[1])
        return findLargest(x)
    else:
        x.remove(x[0])
        return findLargest(x)

print(findLargest([1,2,3,4322,111,-11,2232]))

