# Write a recursive function that arranges the elements in the array in order

def Sort(arr,n,flag):
    if(n < 1):
        if(flag == 1):
            return Sort(arr,len(arr)-1,0)
        return
    if(arr[n] < arr[n-1]):
        arr[n],arr[n-1] = arr[n-1],arr[n]
        return Sort(arr,n,1)
    return Sort(arr,n-1,flag)
        

a = [1,-212321,12412421,112,344,-55,11]
Sort(a,len(a)-1,0)
print("Sorted array:",a)