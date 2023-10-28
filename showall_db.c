#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int choice(const char *command) {
	if (strcmp(command,"OPEN") == 0 || strcmp(command,"open") == 0 ) {
		return 1;
	} else {
		return 0;
	}
}

int main()
{
	FILE* ptr;
	char ch;
	char command[255];
	char file[255];
	printf("Welcome to ezDB, input your command below\n> ");
	scanf("%s %s",command,file);
	file[strcspn(file, "\n")] = '\0';
	command[strcspn(command, "\n")] = '\0';

	int result = choice(command);
	if (result == 1) {
		printf("%s\n",file);
		ptr = fopen(file, "r");
		// If file exists
		if (ptr != NULL) {
			do {
				ch = fgetc(ptr);
				printf("%c", ch);
			} while (ch != EOF);
			fclose(ptr);
		} else {
			printf("Error opening file \n");
		}
	}


}
