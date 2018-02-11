
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
    
def SelectionSort(listToSort,startingIndex):
    minimalIndex = startingIndex
    for i in range(startingIndex,len(listToSort)):
        if listToSort[minimalIndex] > listToSort[i]:
            minimalIndex = i
    listToSort[startingIndex],listToSort[minimalIndex] = listToSort[minimalIndex],listToSort[startingIndex]
    if len(listToSort)-1 == startingIndex:
        return
    else:
        startingIndex += 1
        SelectionSort(listToSort,startingIndex)

SelectionSort(numbersLists,0)

PrintList(numbersLists)
