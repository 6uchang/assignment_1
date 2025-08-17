#ifndef TEST_H  // 如果未定义 TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 127
#define MAX_LENGTH 511
#define MAX_LEN_NUM 10 // max length of number
#define NUM_COL 35 // number of columns in total


typedef struct Address {
    char PFI[MAX_CHAR];//改了长度
    char EZI_ADD[MAX_CHAR];
    char SRC_VERIF[MAX_CHAR];
    char PROPSTATUS[MAX_CHAR];
    char GCODEFEAT[MAX_CHAR];
    char LOC_DESC[MAX_CHAR];
    char BLGUNTTYP[MAX_CHAR];
    char HSAUNITID[MAX_CHAR];
    char BUNIT_PRE1[MAX_CHAR];
    char BUNIT_ID1[MAX_CHAR];
    char BUNIT_SUF1[MAX_CHAR];
    char BUNIT_PRE2[MAX_CHAR];
    char BUNIT_ID2[MAX_CHAR];
    char BUNIT_SUF2[MAX_CHAR];
    char FLOOR_TYPE[MAX_CHAR];
    char FLOOR_NO_1[MAX_CHAR];
    char FLOOR_NO_2[MAX_CHAR];
    char BUILDING[MAX_CHAR];
    char COMPLEX[MAX_CHAR];
    char HSE_PREF1[MAX_CHAR];
    char HSE_NUM1[MAX_CHAR];
    char HSE_SUF1[MAX_CHAR];
    char HSE_PREF2[MAX_CHAR];
    char HSE_NUM2[MAX_CHAR];
    char HSE_SUF2[MAX_CHAR];
    char DISP_NUM1[MAX_CHAR];
    char ROAD_NAME[MAX_CHAR];
    char ROAD_TYPE[MAX_CHAR];
    char RD_SUF[MAX_CHAR];
    char LOCALITY[MAX_CHAR];
    char STATE[MAX_CHAR];
    char POSTCODE[MAX_CHAR];
    char ACCESSTYPE[MAX_CHAR];
    long double x;
    long double y;
} Address_t;



typedef struct Node {
    Address_t data;
    struct Node* next;
} Node_t;

Node_t* read_csv(char* filename, FILE* out_file);
Node_t* create_node(Address_t* address);
#endif 