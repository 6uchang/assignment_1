#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"

int main(int argc, char* argv[]) {
    // Check if the number of command-line arguments is 4
    if (argc != 4) {
        fprintf(stderr, "Invalid arguments. Need 4 parameters: program name, stage, input file, output file\n");
        return 1;
    }
    
    // Check if the stage parameter is "1"
    if (strcmp(argv[1], "1") != 0) {
        fprintf(stderr, "Invalid stage: %s\n", argv[1]);
        return 1;
    }

    // Open the output file
    FILE* out_file = fopen(argv[3], "a");

    // Check if file opening failed
    if (!out_file) {
        fprintf(stderr, "Cannot open output file %s\n", argv[3]);
        return 1;
    } 

    // No output when reading file 
    Node_t* head = read_csv(argv[2], NULL); 
    
    char keyword[MAX_CHAR];

    // Continuously accept user input
    while(1){
        fflush(stdout);
        // Exit on the end of file or input error 
        if(fgets(keyword, MAX_CHAR, stdin) == NULL){
            break;
        }
        keyword[strcspn(keyword, "\n")] = '\0';

        printf("\033[A"); // Move cursor up one line to align input and output // 这个方法感觉有点奇怪但是没找到别的
        printf("%s", keyword);       
        compare_key(head, keyword, out_file); // Find records matching the keyword

    }

    fclose(out_file);
    
    // Free memory allocated for the linked list
    Node_t* current = head;
    while (current != NULL) {
        Node_t* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}