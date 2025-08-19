#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "test.h"

/* Parses a single CSV line into an array of field strings. */
static int parse_csv_line(char *line, char *fields[], int max_fields) {
    int count = 0;
    char *current_posi = line;

    // Parse each field until end of string or max fields reached
    while (*current_posi && count < max_fields) {
            fields[count] = current_posi; // // Record start address of current field
            // Move pointer to end of current field
            while (*current_posi && *current_posi != ',' && *current_posi != '\n') {
                current_posi++;
            }
            // Convert comma into null terminator, to mark end of current field
            if (*current_posi == ',') { 
                *current_posi = '\0'; 
                current_posi++;
            }
        
        count++;
    }

    // Fill remaining fields with empty strings to ensure consistent field count
    while (count < max_fields) {
        fields[count++] = "";
    }

    return count;
}

// Reads CSV file and converts data into a linked list
Node_t* read_csv(char* filename, FILE* out_file) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: File not found: %s\n", filename);
        return NULL;
    }

    Node_t* head = NULL;
    Node_t* tail = NULL;
    char line[MAX_LENGTH]; // Buffer to store read line data

    // Skip header line
    if (!fgets(line, sizeof(line), file)) {
        fclose(file);
        return NULL;
    }

    // Read file line by line until end of file
    while (fgets(line, sizeof(line), file)) {
        // Replace newline character with null terminator
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '\n') {  
            line[i] = '\0';     
            break;          
    }
} 

        char *fields[NUM_COL]; // Array to hold parsed fields
        int field_count = parse_csv_line(line, fields, NUM_COL); // Parse current line
        Address_t addr = {0};

        

             // Treat address structure as byte array and use pointer to traverse fields
            char *every_field = (char *)&addr;  

            // Process first 33 string fields
            for (int i = 0; i < field_count-2; i++) {
                strncpy(every_field, fields[i], MAX_CHAR - 1);  // Copy string
                every_field[MAX_CHAR - 1] = '\0';             
                every_field += MAX_CHAR; // Move to next field in structure
                                 
}
            // Process numeric fields (last two fields) 
            addr.x = strtold(fields[field_count-2], NULL);
            addr.y = strtold(fields[field_count-1], NULL);
            
        // Create new linked list node with address data
        Node_t* new_node = create_node(&addr);
       
        // Add new node to linked list
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
       // New nodes: append to tail
        tail->next = new_node;  
        tail = new_node;        
    }
    
    }

    fclose(file);
    return head;
}
/* // Create a new linked list node. */
Node_t* create_node(Address_t* address) {
    Node_t* new_node = (Node_t*)malloc(sizeof(Node_t));
    assert(new_node);
    new_node->data = *address;
    new_node->next = NULL;
    return new_node;
}