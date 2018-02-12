
numbersLists = []

while True:
    print("Please enter a number to add to the list")
    numToAdd = int(input())
    if numToAdd == -1:
        break
    numbersLists.append(numToAdd)


def PrintList(listToPrint):
    i = 0
    for number in listToPrint:
        print("In the index: %d The number is: %d" % (i,number))
        i += 1
    return

PrintList(numbersLists)
    
def InsertionSort(listToSort):

    for i in range(1, len(listToSort)):

        key = listToSort[i]
        j = i-1

        while(j >= 0 and listToSort[j] > key):
            listToSort[j+1] = listToSort[j]
            j -= 1
        listToSort[j+1] = key

InsertionSort(numbersLists)

PrintList(numbersLists)
