#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declaration.c"

#define MAX_RECORDS 255
int records = 0;

struct records {
    char occupation[256];
    float salary;
};

struct records db[MAX_RECORDS];

void insertRecord(FILE *file) {
}

void deleteRecord(FILE *file) {
}

void queryRecord(FILE *file) {
}

void updateRecord(FILE *file) {
}

void viewRecords() {
    printf("There are in total %d records found:\n",records);
    for (int i = 0; i < records; i++) {
        printf("%s %.2f", db[i].occupation,db[i].salary);
    }
}

void openRecords(FILE *file) {
    int i = 0;
    while (fscanf(file, "%255[^\t] %f",db[i].occupation,&db[i].salary) == 2) {
        i++;
    }
    records = i; 
}


int main() {
    FILE *file = NULL;
    char command[256];
    char command_2[256];

    declaration();
    printf("Welcome to ezDB v1.0.1");

    while (1) {
        printf("\n> ");
        fgets(command,sizeof(command),stdin);
        command[strcspn(command, "\n")] = '\0';
        strcpy(command_2,command);

        char *token = strtok(command, " ");
        if (token != NULL) {
            // OPTION 1: OPEN
            if (strcmp(token,"OPEN") == 0) {
                char *filename = strtok(NULL, " ");

                if (file != NULL) {
                    fclose(file);
                    file = NULL;
                    printf("Closing existing file... Run command again.");
                } else {
                    file = fopen(filename, "ab+");
                    if (file == NULL) {
                        printf("Error opening file");
                    } else {
                        printf("Working on database file: %s",filename);
                        openRecords(file);
                    }
                }
            // OPTION 2: SHOW ALL
            } else if (strcmp(token, "SHOW") == 0) {
                token = strtok(NULL, " ");
                if (token != NULL && strcmp(token, "ALL") == 0) {
                    if (file == NULL) {
                        printf("Select a file first.");
                    } else {
                        viewRecords(file);
                    }
                } else {
                    printf("Unknown command");
                }
            // OPTION 3: INSERT
            } else if (strcmp(token, "INSERT") == 0) {

            }
        } else {
            printf("No input found.");
        }
    }

    return 0;
}
