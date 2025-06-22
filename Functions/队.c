#include <stdio.h>
#define MAXSIZE 1000

int queue[MAXSIZE];
int front = 0;//队首
int rear = MAXSIZE - 1;//队尾
int cnt = 0;//计数

int isEmpty()
{
    return cnt == 0;
}
int isFull()
{
    return cnt == MAXSIZE;
}

void enQueue(int queue[], int data)//入队
{
    if (isFull())
    {
        exit(1);
    }
    else
    {
        rear = (rear + 1) % MAXSIZE;//循环
        queue[rear] = data;
        cnt ++;
    }
}

int deQueue(int queue[])//出队
{
    int e;
    if (isEmpty())
    {
        exit(1);
    }
    else
    {
        e = queue[front];
        cnt --;
        front = (front + 1) % MAXSIZE;
        return e;
    }
}