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
           

            // Process first 33 string fields
            for (int i = 0; i < field_count-2; i++) {
                int str_len = strlen(fields[i]);  // 获取字段实际长度
    // 分配刚好足够的内存（长度+1用于存储\0）
                addr.fields[i] = malloc(str_len + 1);
                assert(addr.fields[i] != NULL);  // 检查分配是否成功
    // 复制字符串内容（包含\0）
                strcpy(addr.fields[i], fields[i]);
                                 
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

    // 深拷贝33个字符串字段
    for (int i = 0; i < 33; i++) {
        int str_len = strlen(address->fields[i]);
        new_node->data.fields[i] = malloc(str_len + 1);  // 重新分配
        assert(new_node->data.fields[i] != NULL);
        strcpy(new_node->data.fields[i], address->fields[i]);  // 复制内容
    }

    // 复制数值字段
    new_node->data.x = address->x;
    new_node->data.y = address->y;

    new_node->next = NULL;
    return new_node;
}