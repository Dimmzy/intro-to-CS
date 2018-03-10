
def calcGCD(x,y):
    if x>y:
        return calcGCD(x-y,y)
    for i in range(x,1,-1):
        if (y%i == 0 & x%i == 0):
            return i
            
print (calcGCD(15,5))
print (calcGCD(324,12312))