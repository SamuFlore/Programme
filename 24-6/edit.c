#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 512


typedef struct edit
{
    int op;
    int pos;
    int n;
    char str[512];
} Edit;

Edit stack[MAXSIZE];
int top = -1;

int isFull()
{
    return (top == MAXSIZE);
}

int isEmpty()
{
    return (top == -1);
}

void push(Edit stack[], int op, int pos, int n,char str[])
{
    if (isFull()) exit(1);
    top ++;
    stack[top].op = op;
    stack[top].pos = pos;
    stack[top].n = n;
    strcpy(stack[top].str, str);
}



void pop(Edit stack[], char string[])
{
    if (isEmpty()) return;
    if (stack[top].op == 1)
    {
        int len = strlen(stack[top].str);
        int total_len = strlen(string);
        for (int i = stack[top].pos + len; i <= total_len; i ++)
        {
            string[i - len] = string[i];//添加的逆操作
        }
    }
    else if (stack[top].op == 2)
    {
        int len;
        if (stack[top].n == 0)//第一类删除的逆操作
        {
            len = strlen(stack[top].str);
        }
        else if (stack[top].n != 0)//第二类删除的逆操作
        {
            len = stack[top].n;
        }
        int total_len = strlen(string);
        for (int i = total_len; i >= stack[top].pos; i --)
        {
            string[i + len] = string[i];
        }
        for (int i = stack[top].pos, j = 0; i < len + stack[top].pos; i ++, j ++)
        {
            string[i] = stack[top].str[j];//把str的内容放回string
        }
    }
    top --;
}

int main()
{
    char string[1000];

    gets(string);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
    {
        int op;
        int pos;
        char str[512];
        scanf("%d %d %s", &op, &pos, str);
        push(stack, op, pos, 0, str);
    }

    getchar();
    getchar();

    char order[50];
    while (1)
    {
        int op;
        gets(order);
        sscanf(order, "%d", &op);
        if (op == 1)
        {
            int pos;
            char strapp[512];
            sscanf(order, "%d %d %s", &op, &pos, strapp);
            int len = strlen(strapp);
            int total_len = strlen(string);
            for (int i = total_len; i >= pos; i --)
            {
                string[i + len] = string[i];
            }
            for (int i = pos, j = 0; i < pos + len; i ++, j ++)
            {
                string[i] = strapp[j];
            }
            push(stack, op, pos, 0, strapp);
        }
        else if (op == 2)
        {
            int pos;
            int delnum;
            sscanf(order, "%d %d %d", &op, &pos, &delnum);
            char delstr[MAXSIZE];
            int j = 0;
            for (int i = pos; (i < pos + delnum) && (string[i] != '\0'); i ++, j ++)
            {
                delstr[j] = string[i];
            }
            delstr[j] = '\0';
            delnum = j;
            int total_len = strlen(string);
            for (int i = pos + delnum; i <= total_len; i ++)
            {
                string[i - delnum] = string[i];//删除
            }
            push(stack, op, pos, delnum, delstr);
        }
        else if (op == 3)
        {
            pop(stack, string);
        }
        else if (op == -1) break;
    }
    printf("%s\n", string);
    return 0;
}