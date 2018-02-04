'''
Student Name: Dmitri Zinkevich
Student ID: 317301596
Course Exercise Group: 01
Exercise Name: Ex3 Python
'''

import math

# We will use while loop to be able to go back to mission select part.
# Inputting 0 in mission select will exit the program
while True:
	# User Mission Input
	missionInput = int(raw_input("please enter a mission number: \n"))

	# Mission 1
	if missionInput == 1:
		# Select Mission Type
		missionType = raw_input("please enter the mission type: \n")
		# Mission Type 'a'
		if missionType == 'a':
		# Receive an integer input that will be tested for being a prime number
			primeTestInput = int(raw_input("please enter a number: \n"))

			# A loop that checks the remainder of primeTestInput divided by 2 to
			# (primeTestInput-1)
			# Using xrange instead of range to avoid using large amounts of memory
			# Since range would have created a list of all the numbers from 2 to n-1,
			# while xrange compares without a list
			# We perform some basic checks for the first 3 instances, and afterwards continue to a for loop
			if primeTestInput < 2:
				print "NO"
			elif (primeTestInput == 2 or primeTestInput == 3):
				print "YES"
			elif (primeTestInput % 2 == 0 or primeTestInput % 3 == 0):
				print "NO"
			else:
				for i in xrange(2,primeTestInput-1):
					if (primeTestInput % i) == 0:
						print "NO"
						break
				else:
					print "YES"

		# Mission Type 'b'
		if missionType == 'b':
			primeTestInput = int(raw_input("please enter a number: \n"))

			# Same loop principle as before, except we check the numbers from 2 to the
			# square root of the prime
			if primeTestInput < 2:
				print "NO"
			elif (primeTestInput == 2 or primeTestInput == 3):
				print "YES"
			elif (primeTestInput % 2 == 0 or primeTestInput % 3 == 0):
				print "NO"
			else:
				for i in xrange(2,int(math.sqrt(primeTestInput))+1):
					if (primeTestInput % i) == 0:
						print "NO"
						break
				else:
					print "YES"

		# Mission Type 'c'
		if missionType == 'c':
			primeTestInput = int(raw_input("please enter a number: \n"))

			# To make the program run more efficiently, we'll be making the same checks
			# up until the square root of the prime
			# Except time we'll only be checking the uneven numbers, and rearrange our first if statements
			# to speed things up.
			if (primeTestInput == 2 or primeTestInput == 3):
				print "YES"
			elif (primeTestInput <= 1 or primeTestInput % 2 == 0):
				print "NO"
			else:
				for i in xrange(3,int(math.sqrt(primeTestInput))+1,2):
					if (primeTestInput % i) == 0:
						print "NO"
						break
				else:
					print "YES"

	# Mission 2
	elif missionInput == 2:
		# Receives an input of two numbers, converts them from str to int using list
		# iteration
		numInput1, numInput2 = [int(x) for x in raw_input("please enter two numbers: \n").split()]
		# an empty list we'll append the numbers that are divisible by the given input
		# numbers
		divisibleList = []
		for i in xrange(1,101):
			# To print a number that is divisible by both inputs only once, we'll use an
			# or operator to filter it out
			if (i % numInput1 == 0) or (i % numInput2 == 0):
				divisibleList.append(i)
		print divisibleList

	# If mission input is equal to zero, we'll exit the loop and the program by using break statement.
	elif missionInput == 0:
		break
	else:
		continue
