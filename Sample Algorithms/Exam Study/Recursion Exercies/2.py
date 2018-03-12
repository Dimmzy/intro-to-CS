# Write a recursive program that returns the number of times the character 'c' appears in a string

def countC(array):
    if not array:
        return 0
    if(array[0] == 'c'):
        return 1 + countC(array[1:])
    else:
        return 0 + countC(array[1:])




a = 'hello world cx zx cc'
print("Number of C's: %d " % countC(a))