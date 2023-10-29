#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declaration.c"


typedef struct {
    char occupation[256];
    float salary;
} Record;

void insertRecord(FILE *file) {
}

void deleteRecord(FILE *file) {
}

void queryRecord(FILE *file) {
}

void updateRecord(FILE *file) {
}

void showallRecords(FILE *file) {
    Record db;
    rewind(file); 
    int sum=0;

    char temp_1[256];
    while (fgets(temp_1, sizeof(temp_1), file) != NULL) {
        // Can be improved
        if (sscanf(temp_1, "%99[^0-9]\t%f",db.occupation,&db.salary) == 2) {
            printf("Job Title: %s, Salary: %.2f\n", db.occupation, db.salary);
            sum++;
        }
    }
    printf("Total records: %d\n",sum);
}


int main() {
    FILE *file = NULL;
    char command[256];
    declaration();
    printf("Welcome to ezDB v1.0.1\n");

    while (1) {
        printf("> ");
        fgets(command,sizeof(command),stdin);
        command[strcspn(command, "\n")] = '\0';

        char *token = strtok(command, " ");

        if (token != NULL) {
            // OPTION 1: OPEN
            if (strcmp(token,"OPEN") == 0) {
                char *filename = strtok(NULL, " ");
                if (file != NULL) {
                    fclose(file);
                    file = NULL;
                    printf("Closing existing file... Run command again.\n");
                } else {
                    file = fopen(filename, "ab+");
                    if (file == NULL) {
                        printf("Error opening file\n");
                    } else {
                        printf("Working on database file: %s\n",filename);
                    }
                }
            // OPTION 2: SHOW ALL
            } else if (strcmp(token, "SHOW") == 0) {
                token = strtok(NULL, " ");
                if (token != NULL && strcmp(token, "ALL") == 0) {
                    if (file == NULL) {
                        printf("Select a file first.\n");
                    } else {
                        printf("OK\n");
                        showallRecords(file);
                    }
                } else {
                    printf("Unknown command\n");
                }
            } else {
                printf("Unknown command.\n");
            }
        } else {
            printf("No input found.\n");
        }
    }

    return 0;
}
