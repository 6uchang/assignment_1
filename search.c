#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "search.h"

#include "test.h"  

/* Converts a single character to its 8-bit binary string representation. */
char* char_turn_into_binary(char letter){
    int ascii = (int)letter; // Get ASCII value of the character
    char *binary = malloc(BITS_PER_CHAR + NULL_TERMINATOR); // Allocate space for 8 bits + null terminator
    assert(binary); 

    // Convert the ASCII value of the character to an 8-bit binary string
    for (int position = 7; position>= 0; position--){
        if (ascii & (1 << position)) {
    binary[7 - position] = '1'; // Set '1' if bit is set
} else {
    binary[7 - position] = '0'; // Set '0' if bit is not set
}
    }
    binary[8]='\0';
    return binary;
}

/* Converts an entire string to a concatenated binary string representation. */
char* string_into_binary(const char* whole_str){
    int str_len = strlen(whole_str); // // Get length of input string
    char* str_binary = malloc(str_len * BITS_PER_CHAR + NULL_TERMINATOR);
    assert(str_binary); 
    str_binary[0] = '\0';

    // Convert each character to binary and append to result
    for(int str_index =0; str_index < str_len; str_index++){
        char * char_binary = char_turn_into_binary(whole_str[str_index]);
        strcat(str_binary, char_binary); // Append current character's binary
        free(char_binary);
    }
    return str_binary;
}

/*  Counts the number of bits compared until the first mismatch. */
int count_bit(const char* a, const char* b){
    if (!a || !b) return 0; // 空指针检查
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return i + 1; // Return count including mismatched bit
            }
        i++;
    }
    return i + sizeof(Address_t*); // If all compared bits match, return total bits checked
}

// 返回值改成了void
void compare_key(Node_t *head, char* input_key, FILE* out_file){
    // 检查空指针或空输入
    if(!head || !input_key){
        return;
    }
    Node_t * curr_line = head;
    int result = 0;

    // 记录比较数量
    int node_comparisons = 0;
    int string_comparisons = 0;
    int bit_comparisons = 0;

    char *input_binary = string_into_binary(input_key);
    fprintf(out_file, "%s \n", input_key);
    while(curr_line){
        node_comparisons++; // 访问了一个节点
        char *curr_line_binary = string_into_binary(curr_line->data.fields[1]);
        if (!curr_line_binary) {
            free(input_binary);
            return; // 内存分配失败
        }
        string_comparisons++; // 访问了一个字符串
        
        bit_comparisons += count_bit(input_binary, curr_line_binary);

        if(strcmp(input_binary, curr_line_binary) == 0){
            result++;
            fprintf(out_file, "-->");
            for (int i = 0; i < NUM_COL-2; i++) {  // NUM_COL-2 对应33个字符串字段
                // fields[i] 是第i个动态分配的字符串，已确保以\0结尾
                fprintf(out_file, " %s: %s ||", field_names[i], curr_line->data.fields[i]); 
            }

            // 处理数值字段
            
            fprintf(out_file," %s: %Lf ||", field_names[NUM_COL-2], curr_line->data.x);
            fprintf(out_file," %s: %Lf ||\n", field_names[NUM_COL-1], curr_line->data.y);
            fflush(out_file);
        }
        free(curr_line_binary);
        // 链接到下一个节点
        curr_line = curr_line->next;
    }
    free(input_binary);

    // 输出终端里的比较结果
    printf(" --> %d records found - comparisons: ", result);
    printf("b%d ", bit_comparisons);
    printf("n%d ", node_comparisons);
    printf("s%d", string_comparisons);
    printf("\n");

}
