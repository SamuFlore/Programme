#include <stdio.h>
#include <stdlib.h>

typedef struct memory
{
    int start;
    int end;
    int isMerged;
} Mem;

Mem memList[105];

int cmp(const void *a, const void *b)
{
    Mem *p1 = (Mem *)a;
    Mem *p2 = (Mem *)b;
    if (p1 -> start < p2 -> start) return -1;
    else if (p1 -> start > p2 -> start) return 1;
    else return 0;
}

int main()
{
    int n;
    int index = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
    {
        int start, end;
        scanf("%d%d", &start, &end);
        memList[index].start = start;
        memList[index].end = end;
        memList[index].isMerged = 0;
        index ++;
    }

    qsort(memList, index, sizeof(Mem), cmp);

    Mem memList2[105];
    int index2 = 0;
    int isLast = 0;

    for (int i = 0; i < index - 1; i ++)
    {
        if (memList[i].end + 1 == memList[i + 1].start && memList[i].isMerged == 0 && memList[i + 1].isMerged == 0)
        {
            memList2[index2].start = memList[i].start;
            memList2[index2].end = memList[i + 1].end;
            memList[i].isMerged = 1;
            memList[i + 1].isMerged = 1;
            index2 ++;
        }
        else if (memList[i].end + 1 == memList[i + 1].start && memList[i].isMerged == 1 && memList[i + 1].isMerged == 0)
        {
            memList2[index2 - 1].end = memList[i + 1].end;
            memList[i + 1].isMerged = 1;
        }
        else if (memList[i].end + 1 != memList[i + 1].start && memList[i].isMerged == 1 && memList[i + 1].isMerged == 0)
        {
            continue;
        }
        else
        {
            memList2[index2].start = memList[i].start;
            memList2[index2].end = memList[i].end;
            index2 ++;
        }
        if (i == index - 1) isLast = 1;
    }
    if (!isLast)
    {
        memList2[index2].start = memList[index - 1].start;
        memList2[index2].end = memList[index - 1].end;
        index2 ++;
    }
    qsort(memList2, index2, sizeof(Mem), cmp);

    for (int i = 0; i < index2; i ++)
    {
        printf("%d %d\n", memList2[i].start, memList2[i].end);
    }
    return 0;
}