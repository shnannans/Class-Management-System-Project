#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILE_NAME "P14_2-CMS.txt" // The file name where all records will be stored
#define HEADER "Database Name: P14-2 CMS\n"
#define AUTHORS "Authors: Shannon, Jeanie, Jing Wen, Venecia\n"
#define TABLE_NAME "Table Name: StudentRecords\n"

// Define structure for linked list node
typedef struct StudentRecord {
    int id;
    char name[50];
    char programme[50];
    float mark;
    struct StudentRecord* next;
} StudentRecord;

StudentRecord* head = NULL;  // Head pointer for the linked list

// Function declarations
void print_declaration();
void get_input_and_trim(const char* prompt, char* input, int max_len);
int get_valid_int(const char* prompt);
void get_valid_input(const char* prompt, char* input, int max_len);
float get_valid_float(const char* prompt);
void capitalize_words(char* str);
void append_record(StudentRecord* new_record);
void clear_linked_list();
void open_database();
void save_database();
void show_all_records();
void insert_record();
void query_record();
void update_record();
void delete_record();
StudentRecord* create_record(int id, const char* name, const char* programme, float mark);
StudentRecord* find_record(int id);
int get_max_column_length(StudentRecord *head, int column);

// Function to print declaration
void print_declaration() {
    printf("\t\t\t\t\t\t\tDeclaration\n");
    printf("SIT's policy on copying does not allow the students to copy source code as well as assessment solutions from another person or other places. It is the students' responsibility to guarantee that their assessment solutions are their own work. Meanwhile, the students must also ensure that their work is not accessible by others. Where such plagiarism is detected, both of the assessments involved will receive ZERO mark.\n\n");
    printf("We hereby declare that:\n");
    printf("• We fully understand and agree to the abovementioned plagiarism policy.\n");
    printf("• We did not copy any code from others or from other places.\n");
    printf("• We did not share our codes with others or upload to any other places for public access and will not do that in the future.\n");
    printf("• We agree that our project will receive Zero mark if there is any plagiarism detected.\n");
    printf("• We agree that we will not disclose any information or material of the group project to others or upload to any other places for public access.\n\n");
    printf("Declared by: P14_2\n");
    printf("Team members:\n1. Jeanie Cherie Chua Yue-Ning\n2. Shannon Yum Wan Ning\n3. Goh Jing Wen\n4. Venecia Weng\n");
    printf("Date: 29th November 2024, Friday\n");
}

// Function to create a new node
StudentRecord* create_record(int id, const char* name, const char* programme, float mark) {
    StudentRecord* new_record = (StudentRecord*)malloc(sizeof(StudentRecord));
    if (!new_record) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    new_record->id = id;
    strcpy(new_record->name, name);
    strcpy(new_record->programme, programme);
    new_record->mark = mark;
    new_record->next = NULL;
    return new_record;
}

// Function to find a record by ID
StudentRecord* find_record(int id) {
    StudentRecord* current = head;
    while (current) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Utility function to trim leading and trailing spaces
void get_input_and_trim(const char* prompt, char* input, int max_len) {
    printf("%s", prompt);

    if (fgets(input, max_len, stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';  // Remove newline character if present
    } else {
        clearerr(stdin);  // Clear error state in case of input error
    }

    // Trim leading spaces
    char* start = input;
    while (isspace((unsigned char)*start)) {
        start++;
    }

    if (start != input) {
        memmove(input, start, strlen(start) + 1);
    }

    // Trim trailing spaces
    char* end = input + strlen(input) - 1;
    while (end > input && isspace((unsigned char)*end)) {
        end--;
    }

    *(end + 1) = '\0';  // Null-terminate after the last non-space character
}

// Function to calculate the length of the longest string in a given column
int get_max_column_length(StudentRecord *head, int column) {
    int max_length = 0;
    StudentRecord *current = head;

    while (current != NULL) {
        int length = 0;
        if (column == 1) {
            length = strlen(current->name); // Column 1 is Name
        } else if (column == 2) {
            length = strlen(current->programme); // Column 2 is Programme
        } else if (column == 3) {
            length = snprintf(NULL, 0, "%.1f", current->mark); // Column 3 is Mark (as string)
        }

        if (length > max_length) {
            max_length = length;
        }
        current = current->next;
    }

    // Add some buffer space for the header text
    if (column == 2) {
        max_length += 2;  // Optionally, add some extra space for Programme column
    }

    return max_length;
}

// Utility Function: Get a valid name or programme with a 50-character limit
void get_valid_input(const char* prompt, char* input, int max_len) {
    int valid;
    do {
        char buffer[100]; // Temporary buffer for validation
        valid = 1;        // Assume input is valid

        get_input_and_trim(prompt, buffer, sizeof(buffer));

        // Check if the input is blank
        if (strlen(buffer) == 0) {
            printf("Input cannot be blank. Please enter a valid value.\n");
            valid = 0;
            continue;
        }

        // Check length
        if (strlen(buffer) > max_len - 1) {
            printf("Input is too long. Please enter a value with up to %d characters.\n", max_len - 1);
            valid = 0;
            continue;
        }

        // Check for valid characters (alphabets, spaces, and allowed special characters: (), -, :)
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (!isalpha((unsigned char)buffer[i]) &&
                !isspace((unsigned char)buffer[i]) &&
                buffer[i] != '(' && buffer[i] != ')' &&
                buffer[i] != '-' && buffer[i] != ':') {
                printf("Invalid input. Only alphabets, spaces, and the following special characters are allowed: (), -, :\n");
                valid = 0;
                break;
            }
        }

        if (valid) {
            strncpy(input, buffer, max_len - 1);
            input[max_len - 1] = '\0';  // Ensure null termination
            capitalize_words(input);    // Capitalize the first letter of each word
        }

    } while (!valid);
}

// Utility function to get a valid 7-digit integer with no leading zeros
int get_valid_int(const char* prompt) {
    char input[100];
    int value;

    while (1) {
        get_input_and_trim(prompt, input, sizeof(input));
        if (strlen(input) == 7 && input[0] != '0' && strspn(input, "0123456789") == 7) {
            sscanf(input, "%d", &value);
            return value;
        }
        printf("Invalid input. The ID must be a 7-digit number not starting with 0.\n");
    }
}

// Utility function to get a valid floating-point input
float get_valid_float(const char* prompt) {
    char input[100];
    float value;

    while (1) {
        get_input_and_trim(prompt, input, sizeof(input));

        // Check if the input is blank
        if (strlen(input) == 0) {
            printf("Input cannot be blank. Please enter a valid value.\n");
            continue;
        }

        int is_valid = 1;  // Assume input is valid
        int dot_count = 0;  // To count the number of dots in the input

        // Check each character in the input
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == '.') {
                dot_count++;
                if (dot_count > 1) {
                    is_valid = 0;  // More than one dot is invalid
                    break;
                }
            } else if (!isdigit((unsigned char)input[i])) {
                is_valid = 0;  // Non-digit and non-dot character is invalid
                break;
            }
        }

        if (is_valid && sscanf(input, "%f", &value) == 1 && value >= 0 && value <= 100) {
            return value;  // Valid float within range
        } else {
            printf("Invalid input. Please enter a valid mark (a number between 0 and 100).\n");
        }
    }
}

// Utility Function: Capitalize the first letter of each word
void capitalize_words(char* str) {
    int capitalize_next = 1; // Flag to capitalize next character
    for (int i = 0; str[i] != '\0'; i++) {
        if (isspace((unsigned char)str[i])) {
            capitalize_next = 1; // Next character should be capitalized
        } else if (capitalize_next && isalpha((unsigned char)str[i])) {
            str[i] = toupper((unsigned char)str[i]); // Capitalize first letter
            capitalize_next = 0;
        } else {
            str[i] = tolower((unsigned char)str[i]); // Lowercase other letters
        }
    }
}

// Function to append a new record at the end of the linked list
void append_record(StudentRecord* new_record) {
    if (!head) {
        head = new_record;
    } else {
        StudentRecord* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_record;
    }
}

// Function to clear the linked list
void clear_linked_list() {
    StudentRecord* current = head;
    while (current) {
        StudentRecord* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}

// Function to open and load records from the database file
void open_database() {
    FILE* file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("CMS: Error opening file \"%s\".\n", FILE_NAME);
        return;
    }

    clear_linked_list();

    char line[256];
    fgets(line, sizeof(line), file); // Skip header lines
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        int id;
        char name[50], programme[50];
        float mark;

        if (sscanf(line, "%d\t%49[^\t]\t%49[^\t]\t%f", &id, name, programme, &mark) == 4) {
            append_record(create_record(id, name, programme, mark));
        }
    }

    fclose(file);
    printf("CMS: The database file \"%s\" is successfully opened.\n", FILE_NAME);
}

// Function to save the records to the database file
void save_database() {
    FILE* file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("CMS: Error opening file \"%s\".\n", FILE_NAME);
        return;
    }

    // Dynamically calculate the maximum column length for each column
    int name_max_length = get_max_column_length(head, 1);
    int programme_max_length = get_max_column_length(head, 2);

    // Write the header to the file
    fprintf(file, HEADER);
    fprintf(file, AUTHORS);
    fprintf(file, "\n");
    fprintf(file, TABLE_NAME);
    fprintf(file, "ID\t%-*s\t%-*s\tMark\n", name_max_length, "Name", programme_max_length, "Programme");

    // Write each record to the file with the calculated column widths
    StudentRecord* current = head;
    while (current != NULL) {
        fprintf(file, "%d\t%-*s\t%-*s\t%.1f\n",
            current->id, name_max_length, current->name, programme_max_length, current->programme, current->mark);
        current = current->next;
    }

    fclose(file);
    printf("CMS: The database file \"%s\" has been saved.\n", FILE_NAME);
}

// Function to show all records
void show_all_records() {
    if (!head) {
        printf("CMS: No records found.\n");
        return;
    }

    // Dynamically calculate the maximum column length for each column
    int name_max_length = get_max_column_length(head, 1);
    int programme_max_length = get_max_column_length(head, 2);

    // Print the header with adjusted column widths
    printf("CMS: Here are all the records found in the table \"StudentRecords\".\n");
    printf("%-12s %-*s %-*s %-10s\n", "ID", name_max_length, "Name", programme_max_length, "Programme", "Mark");

    // Print each record with adjusted column widths
    StudentRecord* current = head;
    while (current) {
        printf("%-12d %-*s %-*s %-10.1f\n",
            current->id, name_max_length, current->name, programme_max_length, current->programme, current->mark);
        current = current->next;
    }
}

// Function to insert a new record
void insert_record() {
    int id = get_valid_int("ID=");  // Validate ID input
    if (find_record(id)) {
        printf("The record with ID=%d already exists.\n", id);
        return;
    }

    char name[50], programme[50];
    get_valid_input("Name (max 50 characters)=", name, sizeof(name));  // Get and validate Name
    get_valid_input("Programme (max 50 characters)=", programme, sizeof(programme));  // Get and validate Programme

    float mark = get_valid_float("Mark=");  // Get valid Mark input

    // Insert the new record at the head of the list
    StudentRecord* new_record = create_record(id, name, programme, mark);
    new_record->next = head;
    head = new_record;

    printf("CMS: A new record with ID=%d is successfully inserted.\n", id);
}

// Function to query a record by ID
void query_record() {
    int id = get_valid_int("ID="); // Validate ID input
    StudentRecord* record = find_record(id);

    if (!record) {
        printf("CMS: The record with ID=%d does not exist.\n", id);
        return;
    }

    printf("The record with ID=%d is found in the data table.\n", id);
    // Dynamically calculate column width
    int name_max_length = get_max_column_length(head, 1);
    int programme_max_length = get_max_column_length(head, 2);

    printf("%-12s %-*s %-*s %-10s\n", "ID", name_max_length, "Name", programme_max_length, "Programme", "Mark");
    printf("%-12d %-*s %-*s %-10.1f\n", record->id, name_max_length, record->name, programme_max_length, record->programme, record->mark);
}

// Function to update a record by ID
void update_record() {
    int id = get_valid_int("ID=");  // Validate ID input
    StudentRecord* record = find_record(id);

    if (!record) {
        printf("CMS: The record with ID=%d does not exist.\n", id);
        return;
    }

    char input[150];
    get_input_and_trim("Enter fields and values to update (e.g., Name=John,Programme=AI,Mark=85.5): ", input, sizeof(input));

    char* pair = strtok(input, ","); // Split input into field=value pairs
    while (pair) {
        char* equals_sign = strchr(pair, '=');
        if (!equals_sign) {
            printf("CMS: Invalid format for \"%s\". Please use field=value.\n", pair);
            pair = strtok(NULL, ","); // Move to the next pair
            continue;
        }

        *equals_sign = '\0';  // Split pair into field and value
        char* field = pair;
        char* value = equals_sign + 1;

        // Check if value is blank
        if (strlen(value) == 0) {
            printf("CMS: Value for \"%s\" cannot be blank.\n", field);
            pair = strtok(NULL, ",");
            continue;
        }

        // Check the field and validate value
        if (strcasecmp(field, "Name") == 0) {
            // Validate Name (Only allow letters, spaces, and special characters (), -, :)
            int valid_name = 1;
            for (int i = 0; value[i] != '\0'; i++) {
                if (!isalpha((unsigned char)value[i]) &&
                    !isspace((unsigned char)value[i]) &&
                    value[i] != '(' && value[i] != ')' &&
                    value[i] != '-' && value[i] != ':') {
                    valid_name = 0;
                    break;
                }
            }

            if (!valid_name) {
                printf("CMS: Invalid Name. Only letters, spaces, and the following special characters are allowed: (), -, :.\n");
            } else if (strlen(value) > 50) {
                printf("CMS: Name is too long. Max 50 characters allowed.\n");
            } else {
                strncpy(record->name, value, sizeof(record->name) - 1);
                record->name[sizeof(record->name) - 1] = '\0';  // Ensure null termination
                capitalize_words(record->name);  // Capitalize the first letter of each word
                printf("CMS: The record with ID=%d, Name updated to: %s\n", id, record->name);
            }
        }
        else if (strcasecmp(field, "Programme") == 0) {
            // Validate Programme (Only allow letters, spaces, and special characters (), -, :)
            int valid_programme = 1;
            for (int i = 0; value[i] != '\0'; i++) {
                if (!isalpha((unsigned char)value[i]) &&
                    !isspace((unsigned char)value[i]) &&
                    value[i] != '(' && value[i] != ')' &&
                    value[i] != '-' && value[i] != ':') {
                    valid_programme = 0;
                    break;
                }
            }

            if (!valid_programme) {
                printf("CMS: Invalid Programme. Only letters, spaces, and the following special characters are allowed: (), -, :.\n");
            } else if (strlen(value) > 50) {
                printf("CMS: Programme is too long. Max 50 characters allowed.\n");
            } else {
                strncpy(record->programme, value, sizeof(record->programme) - 1);
                record->programme[sizeof(record->programme) - 1] = '\0'; // Ensure null termination
                capitalize_words(record->programme);  // Capitalize the first letter of each word
                printf("CMS: The record with ID=%d, Programme updated to: %s\n", id, record->programme);
            }
        }
        else if (strcasecmp(field, "Mark") == 0) {
            float mark = atof(value);
            if (mark >= 0 && mark <= 100) {
                record->mark = mark;
                printf("CMS: The record with ID=%d, Mark updated to: %.1f\n", id, record->mark);
            } else {
                printf("CMS: Invalid Mark. Mark must be between 0 and 100.\n");
            }
        }

        pair = strtok(NULL, ",");  // Continue with the next pair
    }
}

// Function to delete a record
void delete_record() {
    int id = get_valid_int("ID="); // Validate ID input
    StudentRecord *current = head, *prev = NULL;

    while (current) {
        if (current->id == id) {
            printf("CMS: Are you sure you want to delete record with ID=%d? Type \"Y\" to Confirm or \"N\" to cancel.\n", id);
            char confirm; // User input variable
            printf("P14_2: ");
            // Read the confirmation input
            scanf(" %c", &confirm);  // Space before %c to skip any leftover newline characters

            // Clear the buffer of any extra input (in case there's any after scanf)
            while (getchar() != '\n'); // Clear the buffer

            // Check if the user confirms or cancels the deletion
            if (confirm == 'Y' || confirm == 'y') {
                if (prev) {
                    prev->next = current->next; // Bypass the current node
                } else {
                    head = current->next; // Update head if first node is deleted
                }
                free(current);
                printf("CMS: The record with ID=%d is successfully deleted.\n", id);
                return;
            } else {
                printf("CMS: The deletion is cancelled.\n");
                return;
            }
        }
        prev = current;
        current = current->next;
    }

    printf("CMS: The record with ID=%d does not exist.\n", id);
}

// Main function to handle user inputs
int main() {
    print_declaration();

    char command[50];
    while (1) {
        printf("\nClass Management System\n");
        printf("Available Commands: OPEN, SHOW ALL, INSERT, QUERY, UPDATE, DELETE, SAVE, EXIT\n");
        printf("\nP14_2: ");

        get_input_and_trim("", command, sizeof(command));

        if (strlen(command) == 0) {
            continue;  // Skip if the command is empty
        }

        // Match the command with the corresponding function
        if (strcasecmp(command, "OPEN") == 0) {
            open_database();
        } else if (strcasecmp(command, "SHOW ALL") == 0) {
            show_all_records();
        } else if (strcasecmp(command, "INSERT") == 0) {
            insert_record();
        } else if (strcasecmp(command, "QUERY") == 0) {
            query_record();
        } else if (strcasecmp(command, "UPDATE") == 0) {
            update_record();
        } else if (strcasecmp(command, "DELETE") == 0) {
            delete_record();
        } else if (strcasecmp(command, "SAVE") == 0) {
            save_database();
        } else if (strcasecmp(command, "EXIT") == 0) {
            printf("Exiting... Goodbye!\n");
            break;
        } else {
            printf("Invalid command.\n");
        }
    }

    return 0;
}
