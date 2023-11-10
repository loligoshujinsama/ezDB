#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

//#include "declaration.c"

#define MAX_RECORDS 255
int records = 0;

struct records {
    char occupation[256];
    float salary;
};

struct records db[MAX_RECORDS];

void removeSpace(char* word) {
    int len = strlen(word);
    char* edit = word;

    // iterates char by char as long as it satisfies isspace
    // increment the pointer to start at next character instead
    while (isspace(*edit) && *edit) {
        edit++;
    }
    // copy start pointer of edit to original word
    // number of bytes +1 to acommodate for NULL terminator
    memmove(word, edit, strlen(edit) + 1);

    // remove the isspaces in front
    while (len > 0 && isspace(word[len - 1])) {
        word[len - 1] = '\0';
        len--;
    }
}

void insertRecord(const char* occupation, float salary) {
    if (records < MAX_RECORDS) {
        if (strlen(occupation) < sizeof(db[0].occupation)) {
            for (int i = 0; i < records; i++) {
                if (strcmp(db[i].occupation, occupation) == 0) {
                    printf("The record with Key=%s already exists in the database", occupation);
                    return;
                }
            }
            strcpy(db[records].occupation, occupation);
            db[records].salary = salary;
            records++;
            printf("A new record of Key=%s, Value=%.2f is successfully inserted.", occupation, salary);
        }
        else {
            printf("Occupation name is too long. Maximum length is %d characters.", sizeof(db[0].occupation) - 1);
        }
    }
    else {
        printf("Database is full. Cannot add more records.");
    }
}

void deleteRecord(FILE* file) {
}
bool DisplayFromStruc(char occ[]) {
    for (int i = 0; i < 255; i++) {
        if (strcmp(db[i].occupation, occ) == 0) {
            printf("A record of Key=%s, ", db[i].occupation);
            printf("Value=%.2f is found in the database.\n", db[i].salary);
            return true;
        }
    }
    printf("There is no record with Key=%s found in the database.\n", occ);
    
    return false;
}

void queryRecord(char Occ[256]) {

    bool found = DisplayFromStruc(Occ);
}

void updateRecord(FILE* file) {
}

void viewRecords() {
    printf("There are in total %d records found:\n", records);
    for (int i = 0; i < records; i++) {
        printf("%s %.2f\n", db[i].occupation, db[i].salary);
    }
}

void openRecords(FILE* file) {
    int i = 0;
    while (fscanf(file, "%255[^\t] %f", db[i].occupation, &db[i].salary) == 2) {
        removeSpace(db[i].occupation);
        i++;
    }
    records = i;
}

void saveRecords(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file != NULL) {
        for (int i = 0; i < records; i++) {
            fprintf(file, "%s %.2f\n", db[i].occupation, db[i].salary);
        }
        fclose(file);
        printf("File %s has been saved.\n", filename);
    }
    else {
        printf("Error opening file for saving.\n");
    }
}

int main() {
    FILE* file = NULL;
    char command[256];
    char command_2[256];
    char currentFile[256];

    //declaration();
    printf("Welcome to ezDB v1.0.1");

    while (1) {
        printf("\n> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';
        strcpy(command_2, command);

        char* token = strtok(command, " ");
        if (token != NULL) {
            // OPTION 1: OPEN
            if (strcmp(token, "OPEN") == 0) {
                char* filename = strtok(NULL, " ");
                strcpy(currentFile, filename);

                if (file != NULL) {
                    fclose(file);
                    file = NULL;
                    printf("Closing existing file... Run command again.");
                }
                else {
                    file = fopen(filename, "ab+");
                    if (file == NULL) {
                        printf("Error opening file");
                    }
                    else {
                        printf("Working on database file: %s", filename);
                        openRecords(file);
                    }
                }
            }
            // OPTION 2: SHOW ALL
            else if (strcmp(token, "SHOW") == 0) {
                token = strtok(NULL, " ");
                if (token != NULL && strcmp(token, "ALL") == 0) {
                    if (file == NULL) {
                        printf("Select a file first.");
                    }
                    else {
                        viewRecords(file);
                    }
                }
                else {
                    printf("Unknown command");
                }
            }
            // OPTION 3: INSERT
            else if (strcmp(token, "INSERT") == 0) {
                char occupation[255];
                float salary;

                if (file == NULL) {
                    printf("Select a file first.");
                }
                else {
                    //QUERY test test
                    if (sscanf(command_2, "INSERT %199[^0-9]%f", occupation, &salary) == 2) {
                        removeSpace(occupation);
                        insertRecord(occupation, salary);
                    }
                    else {
                        printf("Invalid INSERT input format.");
                    }
                }
            }
            // OPTION 4: SAVE
            else if (strcmp(token, "SAVE") == 0) {
                char* filename = strtok(NULL, " ");
                if (filename != NULL) {
                    if (strcmp(filename, currentFile) == 0) {
                        saveRecords(currentFile);
                    }
                    else {
                        printf("Invlid file name saved.");
                    }
                }
                else {
                    printf("Invalid SAVE input format.");
                }
            }
            // OPTION 5: Query
            else if (strcmp(token, "QUERY") == 0) {
                token = strtok(NULL, " ");
                if (file == NULL) {
                    printf("Select a file first.");
                }
                else {
                    // excecute query mode
                    char occupation[256];
                    if (sscanf(command_2, "QUERY %199[^0-9]", occupation) == 1) {
                        queryRecord(occupation);
                    } else {
                        printf("Invalid QUERY input format.");
                    }
                }
            }
        }
        else {
            printf("No input found.");
        }
    }

    return 0;
}
