#include <stdio.h>
#define MAXSIZE 100


int top = -1;

int isFull()//判断栈是否满
{
    return (top == MAXSIZE - 1);
}

int isEmpty()//空
{
    return (top == -1);
}

void push(int stack[], int data)//进栈
{
    if (isFull())
    {
        printf("error ");
    }
    else
    {
        top ++;
        stack[top] = data;
    }
}

void pop(int stack[])
{
    if (isEmpty())
    {
        printf("error ");
    }
    else
    {
        printf("%d ", stack[top]);
        top --;
        
    }
}


int main()
{
    int stack[105] = {0};
    int order[10000];
    int i = 0;
    while (1)
    {
        scanf("%d", &order[i]);
        if (order[i] == -1)
        {
            break;
        }
        i ++;//命令长度为i
    }

    // printf("%d\n", i);
    // for (int j = 0; j < i; j ++)
    // {
    //     printf("%d ", order[j]);
    // }
    for (int j = 0; j < i; j ++)
    {
        if (order[j] == 1)
        {
            push(stack, order[j + 1]);
            j ++;
        }
        else if (order[j] == 0)
        {
            pop(stack);
        }
    }
    return 0;
}