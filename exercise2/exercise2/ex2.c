
#include <stdio.h>
#define FLOAT_FIX 0.0005
#define ASCII_MOVEMENT 32

/**
* Function Name: exponent
* The Input: x = the base of the exponent , n = the power of the exponent, both integers.
* The Output: Outputs the value of the base n times itself as an integer, aka the exponential function.
* The Function Operation: a For loop that multiplies n (=1) with our given base, and then the result with the base
* again and so on so forth until our 'i' initialization v777ariable is equal to the given n exponent.
* Since we will be dealing with integers in the part of the exercise the function is being used in,
* we'll set it's type to int.
**/

int Exponent(int x, int n) {
	int i;
	int num = 1;
	for (i = 0; i < n; i++) {
		num *= x;
	}
	return num;
}

int main() {
	// Define a missionSelect variable we'll use to let our user pick his wanted mission
	int missionSelect;
	printf("Please enter the mission number:\n");
	scanf("%d", &missionSelect);
	// Mission 1:
	if (missionSelect == 1) {
		// Create two arrays we will use to convert our number into base 10
		char binArray[6];
		int intArray[6];
		// Create a result number variable we will print with the final base 10 number
		int resultNum = 0;
		// A power variable we will dynamically use for the base2 to base10 algorithm along with our expo function
		int power = 5;
		int i;
		printf("Enter six digits binary number:\n");
		// For loop that takes a six digit binary number as input and stores it into our char array as requested
		for (i = 0; i < sizeof(binArray); i++) {
			scanf(" %c", &binArray[i]);
		}
		// Convert the char array into an int array so we will have the correct value in terms of int
		for (i = 0; i < sizeof(binArray); i++) {
			// Subtract 48 from the value of each element in binArray,since 0 in ascii is 48 as an integer, 1 is 49...
			intArray[i] = binArray[i] - 48;
		}
		// If MSB = 0, performs the regular base2 to base10 conversion algorithm using our exponent function
		if (intArray[0] == 0) {
			for (i = 0; i < 6; i++) {
				resultNum += intArray[i] * Exponent(2, power);
				// Since we have 6 digits, we start by multiplying by 2 to the power of 5, subtracting by 1 every run
				power -= 1;
			}
			// Prints the final signed number
			printf("%d", resultNum);
		}
		// If MSB is equal to 1, we'll use the two's complement method to print the decimal representation
		else {
			// A for loop that replaces every 0 digit with 1 and vice versa (two's complement)
			for (i = 0; i < 6; i++) {
				if (intArray[i] == 0) {
					intArray[i] = 1;
				}
				else {
					intArray[i] = 0;
				}
			}
			// Add 1 to the LSB (two's complement)
			intArray[5] += 1;

			/*
			* A for loop that runs from the last digit (LSB) to the first, checking if the digit equals to 2
			* if it does, zero it and carry the 1 to the next bit.
			*/

			for (i = 6; i--> 0; ) {
				if (intArray[i] == 2) {
					intArray[i] = 0;
					intArray[i - 1] += 1;
				}
			}
			// Perform the regular base 2 to base 10 algorithm
			for (i = 0; i<6; i++) {
				resultNum += intArray[i] * Exponent(2, power);
				power -= 1;
			}
			// Multiply our final base10 number by -1 (two's complement)
			resultNum *= -1;
			// Prints the final signed number
			printf("%d", resultNum);
		}

	}
	// Mission 2:
	else if (missionSelect == 2) {
		int numInput;
		// Recieve an integer from the user, save it into numInput variable
		printf("Enter ASCII code of some character:\n");
		scanf("%d", &numInput);
		// Checks if the number is between 91 to 64 (Capital Letter representation in the ASCII table)
		if (numInput < 91 && numInput > 64) {

			/*
			* We'll print the number, the capital letter (we received the correct value from the user in range)
			* And the lower case letter we'll receive by adding the ASCII_MOVEMENT definition (32) to the input
			*/

			printf("The number is: %d\n", numInput);
			printf("The letter is: %c\n", numInput + ASCII_MOVEMENT);
			printf("The capital letter is: %c", numInput);
		}
		else if (numInput < 123 && numInput > 96) {
			// Same thing as last statement, but decrease the int value by ASCII_MOVEMENT to get the capital letter
			printf("The number is: %d\n", numInput);
			printf("The letter is: %c\n", numInput);
			printf("The capital letter is: %c", numInput - ASCII_MOVEMENT);
		}
		else {
			// if the given number isn't inside the range of ascii lower/uppercase characters, prints the int value
			printf("The number is: %d\n", numInput);
		}
	}
	// Mission 3:
	else if (missionSelect == 3) {
		// Recieve areal number as input from user (7 characters limit in a format of xyz.abc)
		printf("Enter a real number:\n");
		float realNum;
		scanf("%7f", &realNum);
		int fractPart;

		/*
		* We'll define a variable called fractPart that is going to be the difference between the float representation
		* of the real number and the integer representation. We will add "FLOAT_FIX" which is defined to be 0.0005
		* into the float representation to fix the rounding error that occurs with float number arithmetic.
		* The result we will multiply by 1000 to move the numbers after the decimal dot forward, so we'll
		* recieve an integer and print it as such as required in the excerise.
		*/

		fractPart = (int)(((realNum + FLOAT_FIX) - (int)realNum) * 1000);
		printf("The integer part: %d\n", (int)realNum);
		printf("The fractional part: %d\n", fractPart);
		// For the sum of odd digits we'll perform the modulo and divison operators to "fish out" the needed digits
		int x, z, a, c;
		x = ((((int)realNum / 10) / 10) % 10);
		z = (int)realNum % 10;
		a = (((fractPart / 10) / 10) % 10);
		c = fractPart % 10;
		printf("The sum of odd digits: %d", x + z + a + c);

	}
	// Mission 4:
	else if (missionSelect == 4) {
		int numInput1, numInput2;
		char crazyOperator;
		printf("Welcome to the crazy calculator:\nEnter two numbers: \n");
		// Recieve two integers as input from the user
		scanf("%d %d", &numInput1, &numInput2);
		printf("Enter an action from: {! @ # \\ %%}: \n");
		// Receive an char input from the user as the "new" operator
		scanf(" %c", &crazyOperator);

		/*
		* Create a switch statement that gives each valid character a case. each case prints the correct arithemetic
		* operation for the "crazy" operator ( ! = +, @ = -, # = *, \ = float division, % = floor divison)
		* if operation is invalid, it defaults to printing that the action is invalid.
		*/

		switch (crazyOperator) {
		case '!':
			printf("%d ! %d = %d", numInput1, numInput2, (numInput1 + numInput2));
			break;
		case '@':
			printf("%d @ %d = %d", numInput1, numInput2, (numInput1 - numInput2));
			break;
		case '#':
			printf("%d # %d = %d", numInput1, numInput2, (numInput1 * numInput2));
			break;
		case '\\':
			printf("%d \\ %d = %f", numInput1, numInput2, ((float)numInput1 / numInput2));
			break;
		case '%':
			printf("%d %% %d = %d", numInput1, numInput2, (numInput1 / numInput2));
			break;
		default:
			printf("The action '%c' is not \"good\" for me!", crazyOperator);
		}
	}
	// Mission 5:
	else if (missionSelect == 5) {
		// Initiate an integer array we'll use to store our coefficients in
		int numArray[3];
		printf("Enter three coefficients:\n");
		scanf("%d %d %d", &numArray[0], &numArray[1], &numArray[2]);

		/*
		* The next piece of code is a series of if's, else's and switches which check the values given
		* of the corresponding parts of the quadratic equation.
		* Like the exercise requires, we will not print x^2 or x if their coefficients are zero. (and as such we have
		* specific checks to make sure we need to print a "+" sign inbetween).
		* The program prints in several phases to reduce the amount of if/else if/switch statements we need
		* and as such reduces the length of the code, but the output remains in a single line as required.
		*/

		if (numArray[0] > 1 || numArray[0] < -1) {
			printf("%dx^2", numArray[0]);
		}
		else{
			switch (numArray[0]) {
			case(1):
				printf("x^2");
				break;
			case(-1):
				printf("-x^2");
			}
		}
		if (numArray[0] != 0 && numArray[1] > 0) {
			printf("+");
		}
		if (numArray[1] > 1 || numArray[1] < -1) {
			printf("%dx", numArray[1]);
		}
		else {
			switch (numArray[1]) {
			case(1):
				printf("x");
				break;
			case(-1):
				printf("-x");
			}
		}
		if ((numArray[1] != 0 && numArray[2] > 0) || (numArray[0] != 0 && numArray[2] > 0)) {
			printf("+");
		}
		if (numArray[2] > 0 || numArray[2] < 0) {
			printf("%d", numArray[2]);
		}
		else if (numArray[0] == 0 && numArray[1] == 0 && numArray[2] == 0) {
			printf("0");
		}
		printf(" = 0");
	}
	// If the mission number input is not in the 1-5 range,print "Error"
	else {
		printf("Error");
	}
	return 0;
}
