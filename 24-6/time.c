#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stu
{
    int id;
    char name[25];
    int time;
} Stu;

int cmp(const void *a, const void *b)
{
    Stu *p1 = (Stu *)a;
    Stu *p2 = (Stu *)b;
    if (p1 -> time < p2 -> time) return 1;
    else if (p1 -> time > p2 -> time) return -1;
    else
    {
        if (p1 -> id < p2 -> id) return -1;
        else if (p1 -> id > p2 -> id) return 1;
        else return 0;
    }
}


Stu stu[105];
int cnt = 0;

int main()
{
    int num;
    scanf("%d", &num);
    getchar();
    for (int i = 0; i < num; i ++)
    {
        int id, time;
        char name[25];
        char log[100];
        gets(log);
        sscanf(log, "%d %s %d", &id, name, &time);
        int isFind = 0;
        for (int j = 0; j < cnt; j ++)
        {
            if (stu[j].id == id)
            {
                stu[j].time += time;
                isFind = 1;
                break;
            }
        }
        if (! isFind)
        {
            stu[cnt].id = id;
            strcpy(stu[cnt].name, name);
            stu[cnt].time = time;
            cnt ++;
        }
    }
    qsort(stu, cnt, sizeof(Stu), cmp);
    for (int i = 0; i < cnt; i ++)
    {
        printf("%d %s %d\n", stu[i].id, stu[i].name, stu[i].time);
    }
    return 0;
}