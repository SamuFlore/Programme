#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef struct news
{
    char type;
    char name[100];
    int time;
    int isLock;
} News;

News stackE[MAXSIZE];
News stackD[MAXSIZE];
News stackC[MAXSIZE];
int topE = -1;
int topD = -1;
int topC = -1;

void pushE(char type, char name[], int time)
{
    if (topE == MAXSIZE - 1) exit(1);
    else
    {
        topE ++;
        strcpy(stackE[topE].name, name);
        stackE[topE].time = time;
        stackE[topE].isLock = 0;
        stackE[topE].type = 'E';
    }
}
void pushD(char type, char name[], int time)
{
    if (topD == MAXSIZE - 1) exit(1);
    else
    {
        topD ++;
        strcpy(stackD[topD].name, name);
        stackD[topD].time = time;
        stackD[topD].isLock = 0;
        stackD[topD].type = 'D';
    }
}
void pushC(char type, char name[], int time)
{
    if (topC == MAXSIZE - 1) exit(1);
    else
    {
        topC ++;
        strcpy(stackC[topC].name, name);
        stackC[topC].time = time;
        stackC[topC].isLock = 0;
        stackC[topC].type = 'C';
    }
}

void popE()
{
    if (topE == -1) exit(1);
    printf("%c %s %d\n", stackE[topE].type, stackE[topE].name, stackE[topE].time);
    topE --;
}
void popD()
{
    if (topD == -1) exit(1);
    printf("%c %s %d\n", stackD[topD].type, stackD[topD].name, stackD[topD].time);
    topD --;
}
void popC()
{
    if (topC == -1) exit(1);
    printf("%c %s %d\n", stackC[topC].type, stackC[topC].name, stackC[topC].time);
    topC --;
}

int main()
{
    char order[100];
    News List[100];
    int index = 0;
    while (1)
    {
        gets(order);
        if (order[0] == 'R') break;
        if (order[0] == 'E' || order[0] == 'D' || order[0] == 'C')
        {
            char type;
            char name[100];
            int time;
            sscanf(order, "%c %s %d", &type, name, &time);
            List[index].type = type;
            List[index].isLock = 0;
            index ++;
            if (type == 'E') pushE(type, name, time);
            else if (type == 'D') pushD(type, name, time);
            else pushC(type, name, time);
        }
        if (order[0] == 'S')
        {
            int num;
            char type;
            sscanf(order, "%c %d", &type, &num);
            int cnt = 0;
            for (int i = index - 1; i >= 0; i --)
            {
                if (cnt == num) break;
                if (List[i].type == 'E' && List[i].isLock == 0)
                {
                    List[i].isLock = 1;
                    popE();
                    cnt ++;
                }
            }
            for (int i = index - 1; i >= 0; i --)
            {
                if (cnt == num) break;
                if (List[i].type == 'D' && List[i].isLock == 0)
                {
                    List[i].isLock = 1;
                    popD();
                    cnt ++;
                }
            }
            for (int i = index - 1; i >= 0; i --)
            {
                if (cnt == num) break;
                if (List[i].type == 'C' && List[i].isLock == 0)
                {
                    List[i].isLock = 1;
                    popC();
                    cnt ++;
                }
            }
        }
    }
    while (topE != -1) popE();
    while (topD != -1) popD();
    while (topC != -1) popC();
    return 0;
}