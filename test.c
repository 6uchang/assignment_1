#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "test.h"

// 安全 CSV 行解析函数
static int parse_csv_line(char *line, char *fields[], int max_fields) {
    int count = 0;
    char *current_posi = line;
//这里删除了关于读取引号的部分
//把ptr改成了新名字
    while (*current_posi && count < max_fields) {
            fields[count] = current_posi;
            while (*current_posi && *current_posi != ',' && *current_posi != '\n') {
                current_posi++;
            }
            if (*current_posi == ',') { 
                *current_posi = '\0'; 
                current_posi++;
            }
        
        count++;
    }

    while (count < max_fields) {
        fields[count++] = "";
    }

    return count;
}

Node_t* read_csv(char* filename, FILE* out_file) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: File not found: %s\n", filename);
        return NULL;
    }

    /* if (!out_file) {
        fprintf(stderr, "Error: Output file is NULL\n");
        fclose(file);
        return NULL;
    } */ 

    Node_t* head = NULL;
    Node_t* tail = NULL;
    char line[MAX_LENGTH];

    // 跳过标题行
    if (!fgets(line, sizeof(line), file)) {
        fclose(file);
        return NULL;
    }

    int record_count = 0;
    while (fgets(line, sizeof(line), file)) {

        //修改了去掉换行符的方法，不然感觉太AI
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '\n') {  // 找到换行符
            line[i] = '\0';     // 替换为结束符
            break;              // 处理完即退出循环
    }
} // 去掉换行符

        char *fields[NUM_COL];
        int field_count = parse_csv_line(line, fields, NUM_COL);
        Address_t addr = {0};

            // 去掉前后空格 这个先去掉了
            /*
            while (*token == ' ') token++;
            char *end = token + strlen(token) - 1;
            while (end > token && *end == ' ') end--;
            *(end + 1) = '\0';
            */

            // 把addr当作字节数组处理 用一个pointer遍历
            char *every_field = (char *)&addr;  

            // 处理前 33 个字符串字段
            // fprintf(out_file, "-->");
            for (int i = 0; i < field_count-2; i++) {
                strncpy(every_field, fields[i], MAX_CHAR - 1);  // 拷贝字符串
                every_field[MAX_CHAR - 1] = '\0';               // 确保结尾 '\0'
                // fprintf(out_file, " %s: %s ||", field_names[i], every_field); 
                every_field += MAX_CHAR;// 跳到下一个字段
                                 
}

// 处理数值字段
            addr.x = strtold(fields[field_count-2], NULL);
            addr.y = strtold(fields[field_count-1], NULL);
            // fprintf(out_file," %s: %Lf ||", field_names[field_count-2], addr.x);
            // fprintf(out_file," %s: %Lf ||\n", field_names[field_count-1], addr.y);


            


        // 链表节点
        Node_t* new_node = create_node(&addr);
        if (new_node) {
            if (head == NULL) {
        // 第一个节点：头和尾都指向它
            head = new_node;
            tail = new_node;
    } else {
        // 后续节点：插入到尾部
            tail->next = new_node;  // 原尾部节点的next指向新节点
            tail = new_node;        // 更新尾部指针到新节点
    }
        } else {
            fprintf(stderr, "Error: Failed to create node for record %d\n", record_count + 1);
        }

        record_count++;
    }

    fclose(file);
    return head;
}

Node_t* create_node(Address_t* address) {
    Node_t* new_node = (Node_t*)malloc(sizeof(Node_t));
    if (!new_node) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    new_node->data = *address;
    new_node->next = NULL;
    return new_node;
}

