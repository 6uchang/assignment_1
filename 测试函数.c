#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char* char_turn_into_binary(char letter){
    int ascii = (int)letter;
    char *binary = malloc(9) ;
    for (int position = 7; position>= 0; position--){
        if(ascii - (int)pow(2, position) >= 0){
            binary[7-position] ='1';
            ascii -=(int)pow(2,position);
        }else{
            binary[7-position] ='0';
        }
    }
    binary[8]='\0';
    return binary;
}

char* string_to_binary(const char* whole_str){
    int str_len = strlen(whole_str);
    char* str_binary = malloc(str_len * 8 + 1);
    for(int str_index =0; str_index < str_len; str_index++){
        char * char_binary = char_turn_into_binary(whole_str[str_index]);
         strcat(str_binary, char_binary);
         free(char_binary);
    }
    return str_binary;
}
int main() {
    char *bits_1 = char_turn_into_binary('A');
    char *bits_2 = char_turn_into_binary('B');
    char *bits_3 = char_turn_into_binary('C');
    char *aaa = string_to_binary("Spencer st");
    printf("%s\n", bits_1);  // 输出 01000001
    printf("%s\n", bits_2);
    printf("%s\n", bits_3);
    printf("%s\n", aaa);
    free(bits_1);
    free(bits_2);
    free(bits_3);
    free(aaa);

    return 0;
}
