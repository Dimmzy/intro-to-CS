# Write a recursive program that inverts the order of the elements in the array


a = ['d','o','m','o','a','r','r']
b = lambda a: (b (a[1:]) + a[:1] if a else[])

print (b(a))


def reverse(a):
    if len(a) == 0:
        return []
    return [a[-1]] + reverse(a[:-1])

    
a = [1,2,3,4,5]

print(reverse(a))