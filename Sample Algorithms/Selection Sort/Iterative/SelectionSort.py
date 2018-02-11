
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
    
def SelectionSort(listToSort):
    for i in range(0,len(listToSort)):
        minimalIndex = i
        for j in range(i + 1,len(listToSort)):
            if listToSort[minimalIndex] > listToSort[j]:
                minimalIndex = j
        listToSort[minimalIndex], listToSort[i] = listToSort[i], listToSort[minimalIndex]

SelectionSort(numbersLists)

PrintList(numbersLists)
