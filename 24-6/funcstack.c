#include <stdio.h>
#include <string.h>

typedef struct 
{
    char name[21];
    char callees[10][21];
    int callee_count;
} Function;

Function functions[100];
int function_count = 0;

int order[100];//order记录出现的函数的顺序
int order_count = 0;

int stack[200];
int top = -1;

int find_function(const char *name) 
{
    for (int i = 0; i < function_count; i ++) 
    {
        if (strcmp(functions[i].name, name) == 0) 
        {
            return i;
        }
    }
    return -1;
}

int main() 
{
    char line[100];
    while (fgets(line, sizeof(line), stdin)) 
    {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0) 
            continue;

        char *op = strtok(line, " \t");//op是空格的前一个字符串
        if (op == NULL) 
            continue;

        if (strcmp(op, "8") == 0) 
        {
            char *name = strtok(NULL, " \t");
            if (name == NULL) 
                continue;

            int index = find_function(name);//find_function查找之前入栈的所有函数调用的函数，如果没有找到函数，创建新的
            if (index == -1) 
            {
                if (function_count >= 100) 
                    return 1;

                strcpy(functions[function_count].name, name);
                functions[function_count].callee_count = 0;
                index = function_count;//function_count是函数的个数，index是函数的索引
                order[order_count ++] = index;
                function_count ++;
            }

            stack[++ top] = index;

            if (top >= 1) 
            {
                int caller_index = stack[top - 1];
                Function *caller = &functions[caller_index];
                int found = 0;
                for (int i = 0; i < caller -> callee_count; i ++) //caller的callee_count是其调用的函数的个数
                {
                    if (strcmp(caller->callees[i], name) == 0) 
                    {
                        found = 1;
                        break;
                    }
                }
                if (!found && caller->callee_count < 10) 
                {
                    strcpy(caller -> callees[caller -> callee_count], name);//栈顶函数调用的函数如果没有新入栈的函数，就加入到caller的callees数组中
                    caller -> callee_count ++;
                }
            }
        } 
        else if (strcmp(op, "0") == 0) 
        {
            if (top >= 0) 
                top--;
            if (top == -1) 
                break;
        }
    }

    for (int i = 0; i < order_count; i ++) 
    {
        Function *func = &functions[order[i]];
        
        if (func -> callee_count == 0) 
            continue;
        
        printf("%s:", func -> name);

        for (int j = 0; j < func -> callee_count; j ++) 
        {
            if (j > 0) //第一轮循环跳过之
                printf(",");
            printf("%s", func -> callees[j]);
        }
        printf("\n");
    }

    return 0;
}