# Write a recursive function that replaces the small characters with large characters

def replaceLowercase(array,n,uparr):
    if (n > len(array)-1):
        return
    elif (ord('a') <= ord(array[n]) <= ord('z')):
        uparr.append(chr(ord(array[n]) -32))
    else:
        uparr.append(array[n])
    replaceLowercase(array,n+1,uparr)


a = "This IS suPPosed to be UppEr CasE"
b = []
replaceLowercase(a,0,b)
print(a)
print(''.join(b))