#ifndef TEST_H  // 如果未定义 TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 127
#define MAX_LENGTH 511
#define NUM_COL 35 // number of columns in total
#define NUM_DOUBLE 2


typedef struct {
    char* fields[NUM_COL-NUM_DOUBLE];  // 前33个字符串字段，每个指向动态分配的内存
    long double x;     // 数值字段x
    long double y;     // 数值字段y
} Address_t;



typedef struct Node {
    Address_t data;
    struct Node* next;
} Node_t;

Node_t* read_csv(char* filename, FILE* out_file);
Node_t* create_node(Address_t* address);
#endif 
