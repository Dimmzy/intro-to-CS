# Write a recursive program that calculates the sum of all the elements in an array

def calcSum(arr,n):
    if n < 0:
        return 0
    return arr[n] + calcSum(arr,n-1)


a = [1,2,3,4,5,6]
print (calcSum(a,len(a)-1))