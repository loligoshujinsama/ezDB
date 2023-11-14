#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <io.h>

#define MAX_RECORDS 255
int records = 0;

struct records {
    char occupation[200];
    float salary;
};

struct records db[MAX_RECORDS];

int fileExists(const char *filename) {
    return _access(filename, 0) == 0;
}

void removeSpace(char *word) {
    int len = strlen(word);
    char *edit = word;

    // iterates char by char as long as it satisfies isspace
    // increment the pointer to start at next character instead
    while (isspace(*edit) && *edit) {
        edit++;
    }

    // copy start pointer of edit to original word
    // number of bytes +1 to acommodate for NULL terminator
    memmove(word, edit, strlen(edit)+1);

    // remove the isspaces in front
    while (len>0 && isspace(word[len-1])) {
        word[len-1] = '\0';
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
            // Using sizeof will need to use %zu - z for sizeof arguments, u for unsigned integers
            printf("Occupation name is too long. Maximum length is %zu characters.", sizeof(db[0].occupation) - 1);
        }
    }
    else {
        printf("Database is full. Cannot add more records.");
    }
}

void deleteRecord(char *key) {
    int deleted = 0;     // delete flag

    for (int i = 0; i < records; i++) {
        if (strcmp(db[i].occupation, key) == 0) {
            // User's deletion choice found in db
            for (int j = i; j < records - 1; j++) {
                //Replace the current field with the field that comes after and so on
                strcpy(db[j].occupation, db[j + 1].occupation);
                db[j].salary = db[j + 1].salary;
            }
            records--;
            deleted++; 
            i--; 
        }
    }

    if (deleted) {
        printf("'%s' deleted successfully.\n", key);
    }
    else {
        printf("No record containing '%s' found.\n", key);
    }
}

void queryRecord(char occ[]) {
    int flag = 0;
    for (int i = 0; i < 255; i++) {
        if (strcmp(db[i].occupation, occ) == 0) {
            flag = 1;
            printf("A record of Key=%s, ", db[i].occupation);
            printf("Value=%.2f is found in the database.\n", db[i].salary);
        }
    }
    if (flag == 0) {
        printf("There is no record with Key=%s found in the database.\n", occ);
    }
}

void updateRecord(char* occupation, float salary) {
    int result = -1;
    for (int i = 0; i < records; i++) {
        if (strcmp(db[i].occupation, occupation) == 0) {
            result = i;
            if (db[i].salary == salary) {
                printf("The salary for this occupation Key=%s is already the same!\n", occupation);
                return; 
            }
        }
    }
    if (result == -1) {
        printf("There is no record with Key=%s foudn in the database.\n", occupation);
    } else {
        db[result].salary = salary;
        printf("The value for the record of Key=%s is successfully updated.\n", occupation);
    }
}

void viewRecords() {
    printf("There are in total %d records found:\n",records);
    for (int i = 0; i < records; i++) {
        printf("%s %.2f\n", db[i].occupation,db[i].salary);
    }
    printf("END OF RECORDS");
}

void openRecords(FILE *file) {
    if (fscanf(file, "%*[^\n]") == EOF) {
        return;
    }

    int i = 0;
    while (fscanf(file, "%255[^\t] %f",db[i].occupation,&db[i].salary) == 2) {
        removeSpace(db[i].occupation);
        i++;
    }
    records = i; 
}

void saveRecords(const char *filename) {
    FILE *file = fopen(filename, "w");
    fprintf(file,"Occupation\tSalary\n");
    for (int i=0;i<records;i++) {
        fprintf(file,"%s\t%.2f\n",db[i].occupation,db[i].salary);
    }
    printf("Successfully saved into %s",filename); 
    fclose(file);

}

void help() {
    printf("Available options:\n");
    printf("  OPEN <filename>       - Open a database file for reading and writing.\n");
    printf("  SHOW ALL              - Display all records in the currently opened file.\n");
    printf("  INSERT <key> <value>  - Insert a new record with the specified key and value.\n");
    printf("  QUERY <key>           - Display information for the record with the specified key.\n");
    printf("  UPDATE <key> <value>  - Update the value of the record with the specified key.\n");
    printf("  DELETE <key>          - Delete the record with the specified key.\n");
    printf("  SAVE <filename>       - Save the records to the specified file.\n");
    printf("  HELP                  - Display this help message.\n");
    printf("  EXIT                  - Exit the program.\n");
}
