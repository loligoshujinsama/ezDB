#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "declaration.c"
#include "function.c"

int main() {
    FILE *file = NULL;
    char filename2[256],command[256],command_2[256],key[256]; // 255 char, 1 NULL
    float value;

    declaration();
    printf("Welcome to ezDB v3.0 - HELP for commands");

    while (1) {
        // User input and remove newline
        printf("\n> ");
        fgets(command,sizeof(command),stdin);

        // Handle when user input more than 255 characters
        // Remove extra characters from stdin (input stream)
        if (command[strlen(command) - 1] != '\n') {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        command[strcspn(command, "\n")] = '\0';
        strcpy(command_2,command);
        char *token = strtok(command, " ");
        if (token != NULL) {
            // OPTION 1: OPEN
            if (strcmp(token,"OPEN") == 0) {
                char *filename = strtok(NULL, " ");
                if (filename != NULL) {
                    strcpy(filename2,filename);

                    // Close existing file if exists
                    if (file != NULL) {
                        fclose(file);
                        printf("Closing existing file...\n");
                        file = NULL;
                    }

                    // Open file
                    if (fileExists(filename)) {
                        file = fopen(filename, "ab+");
                        printf("Working on database file: %s", filename);
                        openRecords(file);
                    } else {
                        printf("File doesn't exist or is not a .txt file. Please OPEN an existing .txt file.");
                    }
                } else {
                    printf("Please provide a filename.");
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
                    printf("Invalid SHOW ALL format.");
                }

            // OPTION 3: INSERT
            } else if (strcmp(token, "INSERT") == 0) {
                if (file == NULL) {
                    printf("Select a file first.");
                }
                else {
                    // Scan for key and value based on format
                    if (sscanf(command_2, "INSERT %199[^-0-9]%f", key, &value) == 2 && strlen(key) > 0 && value >= 0.0) {
                        removeSpace(key);
                        insertRecord(key, value);
                    }
                    else {
                        printf("Invalid INSERT format");
                    }
                }

            // OPTION 4: QUERY
            } else if (strcmp(token, "QUERY") == 0) {
                token = strtok(NULL, " ");
                if (file == NULL) {
                    printf("Select a file first.");
                }
                else {
                    // Scan for key based on format
                    if (sscanf(command_2, "QUERY %199[^0-9]", key) == 1) {
                        queryRecord(key);
                    } else {
                        printf("Invalid QUERY format");
                    }
                }
            
            // OPTION 5: UPDATE
            } else if (strcmp(token, "UPDATE") == 0) {
                if (file == NULL) {
                    printf("Select a file first.");
                } 
                else {
                    if (sscanf(command_2, "UPDATE %199[^-0-9]%f",key, &value) == 2) {
                        if (strlen(key) > 0 && value >= 0.0) {
                            removeSpace(key);
                            updateRecord(key, value);
                        } else {
                            printf("Invalid salary format.");
                        }
                    } else {
                        printf("Invalid UPDATE format");
                    }
                }

            // OPTION 6: DELETE
            } else if (strcmp(token, "DELETE") == 0) {
                if (file == NULL) {
                    printf("Select a file first.");
                } else if (token == NULL) {
                    printf("Invalid DELETE input format");
                } else {
                    char *key = strtok(NULL, "");
                    deleteRecord(key);
                }

            // OPTION 7: SAVE
            } else if (strcmp(token, "SAVE") == 0) { 
                if (file == NULL) {
                    printf("Select a file first.");
                } else {
                    char *filename = strtok(NULL, " ");
                    if (filename == NULL) {
                        printf("Please give a valid filename");
                    } else if (strcmp(filename2,filename) == 0) {   
                        saveRecords(filename2);
                    } else {
                        printf("Error saving file. Must be the same file you opened.");
                    }
                }

            // OPTION 8: HELP
            } else if (strcmp(token, "HELP") == 0) {
                help();

            // OPTION 9: EXIT
            } else if (strcmp(token, "EXIT") == 0) {
                printf("Have a nice day.");
                break;

            } else {
                printf("Invalid command");
            }
        } else {
            printf("No input found.");
        }
    }

    return 0;
}
