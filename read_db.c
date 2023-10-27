#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* ptr;
	char ch;

	// Opening file in read mode
	ptr = fopen("C:\\Users\\joelc\\Downloads\\C Programming Files\\FruitPrice.txt", "r");

	if (NULL == ptr) {
		printf("file can't be opened \n");
	}

	printf("There are in total x records found \n");

	// Printing what is written in file
	// character by character using loop.
	do {
		ch = fgetc(ptr);
		printf("%c", ch);

		// Checking if character is not EOF.
		// If it is EOF stop reading.
	} while (ch != EOF);

	// Closing the file
	fclose(ptr);
	return 0;
}
