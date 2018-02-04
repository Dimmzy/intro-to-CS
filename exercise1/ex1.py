'''
Student Name: Dmitri Zinkevich
Student ID: 317301596
Course Exercise Group: 01
Exercise Name: Ex1 Python
'''

# User Mission Number Input
missionNum = int(raw_input('please enter the mission number:\n'))

# Mission 1
if missionNum == 1:
    # We'll take two inputs from the user, a number and the base it is represented as
    numInput = raw_input('please enter a number:\n')
    baseInput = int(raw_input('please enter a base (2-9):\n'))
    # Set a variable we use as an exponent that we'll dynamically change while the algorithm runs
    powerMod = (len(numInput) - 1)
    resultNumber = 0
    # Loop that iterates through the digits and multiplies it by the given base to the power of the reversed index -1
    for i in numInput:
        resultNumber += (int(i) * (baseInput ** powerMod))
        powerMod -= 1
    print resultNumber

# Mission 2
elif missionNum == 2:
    numInput = raw_input('please enter a number:\n')
    baseInput = int(raw_input('please enter a base (16 or 8):\n'))
    # Create dictionaries that'll assist us with changing to base8/16
    base8Dict = {'0': '000', '1': '001', '2': '010', '3': '011',
                 '4': '100', '5': '101', '6': '110', '7': '111'}
    base16Dict = {'0': '0000', '1': '0001', '2': '0010', '3': '0011',
                  '4': '0100','5': '0101', '6': '0110', '7': '0111',
                  '8': '1000', '9': '1001', 'A': '1010', 'B': '1011',
                  'C': '1100', 'D': '1101', 'E': '1110', 'F': '1111'}
    # Create an empty list onto which to append the binary strings
    resultNumberlst = []
    # Distinguish between two situations per the given base, so the program knows which dictionary to access
    if baseInput == 8:
        for i in numInput:
            # Pulls the vslue of the key correpsonding to the digit and appends it into the result list
            resultNumberlst.append(base8Dict[i])
        # Use .join to create a single string that contains the whole binary representation and print the number
        resultNumber = ''.join(resultNumberlst)
        print resultNumber
    if baseInput == 16:
        # Just like the base 8 for loop, we'll pull the corresponding value for each digit and join into a number
        for i in numInput:
            resultNumberlst.append(base16Dict[i])
        resultNumber = ''.join(resultNumberlst)
        print resultNumber

# Mission 3
elif missionNum == 3:
    numInput = int(raw_input('please enter a number:\n'))
    baseInput = int(raw_input('please enter a base (16,8,4 or 2):\n'))
    # Create an empty list we can append the remainder of the division
    remainderList = []
    # a While loop that runs as long as the given number didn't reach 0 from the division operation
    while numInput > 0:
        # Perform the module operator on the number and the base, and append the remainder into our empty list
        remainderList.append(str(numInput % baseInput))
        numInput = numInput / baseInput
    # Reverse the list (which in turn reverses the order of the remainders) as given by the algorithm.
    reversedList = list(reversed(remainderList))
    # Check if we need to replace any elements in the list with hexadecimal characters (if given base 16)
    if baseInput != 16:
        # If we don't, join the list and print the final number
        resultNumber = ''.join(reversedList)
        print resultNumber
    # Else, we'll replace the needed elements with their hexadecimal strings.
    else:
        # Create a dictionary we're going to use as a reference for the list iteration and replacement
        hexaDict = {'10': 'A', '11': 'B', '12': 'C', '13': 'D', '14': 'E',
                    '15': 'F'}
        # We check each element, and if it exists as a key in the dictionary, we replace it with the key's value
        for i, n in enumerate(reversedList):
            if n in hexaDict.keys():
                reversedList[i] = hexaDict[n]
        # Joins the list and print the final number
        resultNumber = ''.join(reversedList)
        print resultNumber

# Misson 4
elif missionNum == 4:
    numInput = raw_input('please enter an 8-bit binary number\n')
    # Assign two variables we'll print as the final signed and unsigned numbers
    unsignedNum = 0
    signedNum = 0
    # Use a variable that dictates the power we multiply our base with
    powerMod = (len(numInput) - 1)
    # We'll start by translating the binary number into an unsigned value
    for i in numInput:
        # Converts the element to an integer and translates to base10
        unsignedNum += (int(i) * (2 ** powerMod))
        # Substract 1 from our Power variable to properly translate to unsigned
        powerMod -= 1
    print 'unsigned:', unsignedNum
    # Resets the value of the power for the second operation (printing signed)
    powerMod = (len(numInput) - 1)
    # Creates a list of integers we can iterate through
    lstNum = [int(i) for i in numInput]
    # Check if our MSB is one, if it is we will convert it to a negative number
    if lstNum[0] == 1:
        # Creates an empty list we'll use for our conversion operations
        convList = []
        # Appends the opposite bit to our list (if 0 then append 1 and vice versa)
        for i in lstNum:
            if i == 0:
                convList.append(1)
            else:
                convList.append(0)
        # Add 1 to the LSB in our list according to two's complement
        convList[-1] += 1
        # Reverse iterate through the list, check if there's any 2's. If so, reset them to 0 and and add 1 to the left.
        for bit in convList[::-1]:
            if convList[bit] == 2:
                convList[bit] = 0
                convList[bit-1] += 1
        # Convert our elements in the list to str so we can create a full binary string
        convList = [str(x) for x in convList]
        # Perform standard conversion from binary to base 10
        for i in convList:
            signedNum += int(i) * (2 ** powerMod)
            powerMod -= 1
        # Multiply our final base 10 number with -1 to display it as negative
        signedNum = signedNum * (-1)
        print 'signed: ',signedNum
    # if our MSB 0 we'll perform a standard binary to base 10 conversion
    else:
        for i in lstNum:
            signedNum += i * (2 ** powerMod)
            powerMod -= 1
        print 'signed:', signedNum

# Invalid Mission Selected
else:
    print 'Error'
