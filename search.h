#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "test.h"

char* char_turn_into_binary(char letter);
char* string_into_binary(const char* whole_str);
int compare_key(Node_t *head, char* input_key, FILE* out_file);

static const char *field_names[] = {
    "PFI", "EZI_ADD", "SRC_VERIF", "PROPSTATUS", "GCODEFEAT", "LOC_DESC",
    "BLGUNTTYP", "HSAUNITID", "BUNIT_PRE1", "BUNIT_ID1", "BUNIT_SUF1",
    "BUNIT_PRE2", "BUNIT_ID2", "BUNIT_SUF2", "FLOOR_TYPE", "FLOOR_NO_1",
    "FLOOR_NO_2", "BUILDING", "COMPLEX", "HSE_PREF1", "HSE_NUM1", "HSE_SUF1",
    "HSE_PREF2", "HSE_NUM2", "HSE_SUF2", "DISP_NUM1", "ROAD_NAME", "ROAD_TYPE",
    "RD_SUF", "LOCALITY", "STATE", "POSTCODE", "ACCESSTYPE", "x", "y"
};