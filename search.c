#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "search.h"
#include "test.h"  

// 单个字符转8位二进制


char* char_turn_into_binary(char letter){
    int ascii = (int)letter;
    char *binary = malloc(9) ;
    for (int position = 7; position>= 0; position--){
        if (ascii & (1 << position)) {
    binary[7 - position] = '1';
} else {
    binary[7 - position] = '0';
}
    }
    binary[8]='\0';
    return binary;
}
char* string_into_binary(const char* whole_str){
    int str_len = strlen(whole_str);
    char* str_binary = malloc(str_len * 8 + 1);
    str_binary[0] = '\0';
    for(int str_index =0; str_index < str_len; str_index++){
        char * char_binary = char_turn_into_binary(whole_str[str_index]);
         strcat(str_binary, char_binary);
         free(char_binary);
    }
    return str_binary;
}


int compare_key(Node_t *head, char* input_key, FILE* out_file){
    if(!head || !input_key){
        return 0;
    }
    Node_t * curr_line = head;
    int result = 0;
    char *input_binary = string_into_binary(input_key);
    fprintf(out_file, "%s\n", input_key);
    while(curr_line){
        char *curr_line_binary = string_into_binary(curr_line->data.EZI_ADD);
        if(strcmp(input_binary, curr_line_binary) == 0){
            result +=1;
            char *every_field = (char *)&(curr_line->data);  

            // 处理前 33 个字符串字段
            fprintf(out_file, "-->");
            for (int i = 0; i < NUM_COL-2; i++) {
                 // 拷贝字符串
                every_field[MAX_CHAR - 1] = '\0';               // 确保结尾 '\0'
                fprintf(out_file, " %s: %s ||", field_names[i], every_field); 
                every_field += MAX_CHAR;// 跳到下一个字段
}

// 处理数值字段
            
            fprintf(out_file," %s: %Lf ||", field_names[NUM_COL-2], curr_line->data.x);
            fprintf(out_file," %s: %Lf ||\n", field_names[NUM_COL-1], curr_line->data.y);
            fflush(out_file);
        }
        free(curr_line_binary);
        curr_line = curr_line->next;
       }
       free(input_binary);
       return result;
       
       }

