
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
    
def BubbleSort(listToSort):
    length = len(listToSort)
    for i in range(length):
        swapped = False

        for j in range(0,length-i-1):

            if listToSort[j] > listToSort[j+1]:
                swapped = True
                listToSort[j],listToSort[j+1] = listToSort[j+1],listToSort[j]
        if swapped == False:
            break

BubbleSort(numbersLists)

PrintList(numbersLists)
