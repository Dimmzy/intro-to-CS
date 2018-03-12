# Write a function that checks if an array is a palindrome

def isPalindrome(array,start,end):
    if(start >= end):
        return True
    elif(array[start] != array[end]):
        return False
    else:
        return isPalindrome(array,start+1,end-1)

a = "bob is a cat bob"
b = "bob"
c = "kaaaaaabaaaaaab"

print("#1 %d" % isPalindrome(a,0,len(a)-1))
print("#2 %d" % isPalindrome(b,0,len(b)-1))
print("#3 %d" % isPalindrome(c,0,len(c)-1))