#include <stdio.h>
#define MAXSIZE 1000

int stack[MAXSIZE];
int top = -1;

int isEmpty()//判断栈是否空
{
    return top == -1;
}

int isFull()//满
{
    return top == MAXSIZE - 1;
}

void push(int stack[], int n)
{
    if (isFull())
    {
        exit(1);//满
    }
    else
    {
        stack[++ top] = n;
    }
}

int pop(int stack[])
{
    if (isEmpty())
    {
        exit(0);//空
    }
    else
    {
        return stack[top --];
    }
}