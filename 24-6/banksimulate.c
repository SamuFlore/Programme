#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 200
#define MAXWIN 5
#define MINWIN 3
#define THRESHOLD 7

typedef struct client
{
    int id;
    int level;
    int waittime;
    int isServed;
    int isServing;
} Client;

int windows = MINWIN;
int freewindows = MINWIN;

Client clientqueue[MAXSIZE];
int head = 0, tail = MAXSIZE - 1, cnt = 0, count = 1;

int isEmpty()
{
    return (cnt == 0);
}

int isFull()
{
    return (cnt == MAXSIZE);
}

void enQueue(Client c)
{
    if (isFull()) return;
    else
    {
        tail = (tail + 1) % MAXSIZE;
        clientqueue[tail] = c;
        cnt ++;
    }
}


int main()
{
    int list[MAXSIZE];
    int time;
    scanf("%d", &time);
    for (int i = 0; i < time; i ++)
    {
        scanf("%d", &list[i]);
    }
    for (int i = 0; i < time; i ++)
    {
        for (int j = 0; j < list[i]; j ++)
        {
            int level;
            scanf("%d", &level);
            Client c;
            c.id = count;
            count ++;
            c.level = level;
            c.waittime = 0;
            c.isServed = 0;
            c.isServing = 0;
            enQueue(c);
        }
        while (((cnt * 1.0 / windows) >= THRESHOLD) && (windows < MAXWIN))
        {
            windows ++;
            freewindows ++;
        }
        for (int j = head; j != (tail + 1) % MAXSIZE; j = (j + 1) % MAXSIZE)
        {
            if (clientqueue[j].isServing == 0)
            {
                if (freewindows > 0)
                {
                    clientqueue[j].isServing = 1;
                    printf("%d : %d\n", clientqueue[j].id, clientqueue[j].waittime);
                    freewindows --;
                    cnt --;//走一个
                    // if (((cnt * 1.0 / windows) < THRESHOLD) && (windows > MINWIN))
                    // {
                    //     windows --;
                    //     freewindows --;
                    // }
                    // while (((cnt * 1.0 / windows) >= THRESHOLD) && (windows < MAXWIN))
                    // {
                    //     windows ++;
                    //     freewindows ++;
                    // }
                }
                else
                {
                    clientqueue[j].waittime ++;
                }
            }
            else if (clientqueue[j].isServing == 1)
            {
                if (clientqueue[j].level > 0)
                {
                    clientqueue[j].level --;
                }
                if (clientqueue[j].isServed == 0 && clientqueue[j].level == 0)
                {
                    freewindows ++;
                    clientqueue[j].isServed = 1;
                    // cnt --;
                    // if (((cnt * 1.0 / windows) < THRESHOLD) && (windows > MINWIN))
                    // {
                    //     windows --;
                    //     freewindows --;
                    // }
                    // while (((cnt * 1.0 / windows) >= THRESHOLD) && (windows < MAXWIN))
                    // {
                    //     windows ++;
                    //     freewindows ++;
                    // }
                }
            }
        }
        if (((cnt * 1.0 / windows) < THRESHOLD) && (windows > MINWIN))
        {
            windows --;
            freewindows --;
        }
    }
    while (!isEmpty())
    {
        for (int j = head; j != (tail + 1) % MAXSIZE; j = (j + 1) % MAXSIZE)
        {
            if (clientqueue[j].isServing == 0)
            {
                if (freewindows > 0)
                {
                    clientqueue[j].isServing = 1;
                    printf("%d : %d\n", clientqueue[j].id, clientqueue[j].waittime);
                    freewindows --;
                    cnt --;//走一个
                    // if (((cnt * 1.0 / windows) < THRESHOLD) && (windows > MINWIN))
                    // {
                    //     windows --;
                    //     freewindows --;
                    // }
                }
                else
                {
                    clientqueue[j].waittime ++;
                }
            }
            else if (clientqueue[j].isServing == 1)
            {
                if (clientqueue[j].level > 0)
                {
                    clientqueue[j].level --;
                }
                if (clientqueue[j].isServed == 0 && clientqueue[j].level == 0)
                {
                    freewindows ++;
                    clientqueue[j].isServed = 1;
                    // cnt --;
                    // if (((cnt * 1.0 / windows) < THRESHOLD) && (windows > MINWIN))
                    // {
                    //     windows --;
                    //     freewindows --;
                    // }
                }
            }
        }
        if (((cnt * 1.0 / windows) < THRESHOLD) && (windows > MINWIN))
        {
            windows --;
            freewindows --;
        }
    }
    return 0;
}











