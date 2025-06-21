#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct place
{
    char name[25];
    int distance;
} Place;

typedef struct carriage
{
    int id;
    char destination[25];
} Car;

Car stackA[55];
Car stackB[55];
Car stackC[55];
int topA = -1, topB = -1, topC = -1;
int pushTime = 0;

void pushA(int id, char city[])
{
    pushTime ++;
    // printf("(push)");
    topA ++;
    if (topA > 54) exit(1);
    else
    {
        strcpy(stackA[topA].destination, city);
        stackA[topA].id = id;
    }
}

void pushB(int id, char city[])
{
    topB ++;
    if (topB > 54) exit(1);
    else
    {
        strcpy(stackB[topB].destination, city);
        stackB[topB].id = id;
    }
}

void pushC(int id, char city[])
{
    topC ++;
    if (topC > 54) exit(1);
    else
    {
        strcpy(stackC[topC].destination, city);
        stackC[topC].id = id;
    }
}

Car popA()
{
    if(topA == -1) exit(1);
    else return stackA[topA --];
}
Car popB()
{
    if(topB == -1) exit(1);
    else return stackB[topB --];
}
Car popC()
{
    if(topC == -1) exit(1);
    else return stackC[topC --];
}




void AtoB()
{
    Car tmp = popA();
    pushB(tmp.id, tmp.destination);
}
void BtoA()
{
    Car tmp = popB();
    pushA(tmp.id, tmp.destination);
}
void AtoC()
{
    Car tmp = popA();
    pushC(tmp.id, tmp.destination);
}
void CtoA()
{
    Car tmp = popC();
    pushA(tmp.id, tmp.destination);
}

int findPlace(char city[], Place places[], int city_num)
{
    int dist;
    for (int i = 0; i < city_num; i ++)
    {
        if (strcmp(places[i].name, city) == 0)
        {
            dist = places[i].distance;
            break;
        }
    }
    return dist;
}

int findFar(int city_num, Place places[])
{
    int max_dis = 0;
    int max_index = topB;
    int index = topB;
    for (; index >= 0; index --)
    {
        int dist = findPlace(stackB[index].destination, places, city_num);
        if (dist > max_dis)
        {
            max_dis = dist;
            max_index = index;
        }
    }
    return max_index;
}


int main()
{
    Place places[55];
    int index = 0;
    int num;
    scanf("%d", &num);
    getchar();
    for (int i = 0; i < num; i ++)
    {
        char city[25];
        int distance;
        char order[100];
        gets(order);
        sscanf(order, "%s %d", city, &distance);
        places[index].distance = distance;
        strcpy(places[index].name, city);
        index ++;
    }
    int car_num;
    scanf("%d", &car_num);
    getchar();
    for (int i = 0; i < car_num; i ++)
    {
        int id;
        char city[25];
        char order[100];
        gets(order);
        sscanf(order, "%d %s", &id, city);
        pushA(id, city);
    }
    //测试
    // for (int i = 0; i <= topA; i ++)
    // {
    //     printf("%d ", stackA[i].id);
    // }
    //
    for (int i = 0; i < car_num; i ++)
    {
        AtoB();
    }
    //测试
    // for (int i = 0; i <= topB; i ++)
    // {
    //     printf("%d ", stackB[i].id);
    // }
    //
    int isDone = 0;
    while (topB != -1)
    {
        int max_index = findFar(num, places);
        while (topB != max_index - 1)
        {
            BtoA();
        }
        if (topA == isDone)
        {
            isDone ++;
        }
        else if (topA != isDone)
        {
            AtoC();
            while (topA != isDone - 1)
            {
                AtoB();
            }
            CtoA();
            isDone ++;
        }
    }

    for (int i = 0; i <= topA; i ++)
    {
        printf("%04d ", stackA[i].id);
    }
    printf("\n%d", pushTime - car_num);
    
    return 0;
}