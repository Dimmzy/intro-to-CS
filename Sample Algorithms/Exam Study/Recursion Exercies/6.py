# Write a recursive function that divides a number array into two arrays, even and odds


def divideArr(arr,n,e,o):
    if (n > len(arr)-1):
        return
    elif(arr[n] % 2 == 0):
        e.append(arr[n])
        return divideArr(arr,n+1,e,o)
    else:
        o.append(arr[n])
        return divideArr(arr,n+1,e,o)


arr = [1,2,3,4,5,6,7,8,9]
n = 0
e = []
o = []
divideArr(arr,n,e,o)
print("Evens:",e)
print("Odds:",o)