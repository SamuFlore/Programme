#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define min(a, b) ((a) < (b)? (a) : (b))


typedef struct stu
{
    int id;
    char name[25];
    int seat;
} Stu;

Stu stu[105];



int cmp(const void *a, const void *b)
{
    Stu *p1 = (Stu *)a;
    Stu *p2 = (Stu *)b;
    if (p1 -> seat < p2 -> seat) return -1;
    else if (p1 -> seat > p2 -> seat) return 1;
    else
    {
        if (p1 -> id < p2 -> id) return -1;
        else if (p1 -> id > p2 -> id) return 1;
        else return 0;
    }
}

int cmp2(const void *a, const void *b)
{
    Stu *p1 = (Stu *)a;
    Stu *p2 = (Stu *)b;
    if (p1 -> id < p2 -> id) return -1;
    else if (p1 -> id > p2 -> id) return 1;
    else return 0;
}

int main()
{
    FILE *in, *out;
    int index = 0;
    in = fopen("in.txt", "r");
    out = fopen("out.txt", "w");
    int stu_num;
    scanf("%d", &stu_num);
    for (int i = 0; i < stu_num; i ++)
    {
        int id, seat;
        char name[25];
        fscanf(in, "%d %s %d", &id, name, &seat);
        stu[index].id = id;
        strcpy(stu[index].name, name);
        stu[index].seat = seat;
        index ++;
    }

    qsort(stu, stu_num, sizeof(Stu), cmp);

    int minNum = min(stu_num, stu[stu_num - 1].seat);
    printf("%d\n", minNum);

    int list[105];
    int list_index = 0;

    int num = 1;
    if (stu[0].seat != 1)
    {
        list[list_index] = 1;
        list_index ++;
    }
    for (int i = 0; i < stu_num; i ++)
    {
        if (stu[i].seat == num) continue;
        if (stu[i].seat == num + 1) num ++;
        if (stu[i].seat == num + 2) 
        {
            if (num + 1 <= minNum)
            {
                list[list_index] = num + 1;
                list_index ++;
                num += 2;
            }

        }
        
    }

    for (int i = 0; i < list_index; i ++)//
    {
        printf("%d ", list[i]);
    }

    int reverse_index = stu_num - 1;
    for (int i = 0; i < list_index; i ++)
    {
        if (list[i] < stu[reverse_index].seat)
        {
             stu[reverse_index].seat = list[i];
            reverse_index --;
        }
    }

    qsort(stu, stu_num, sizeof(Stu), cmp);
    int max_seat = stu[stu_num - 1].seat;
    printf("\n%d\n", max_seat);

    for (int i = 0; i < stu_num; i ++)
    {
        if (i > 0 && stu[i].seat == stu[i - 1].seat)
        {
            stu[i].seat = max_seat + 1;
            max_seat ++;
        }
    }

    qsort(stu, stu_num, sizeof(Stu), cmp2);

    for (int i = 0; i < stu_num; i ++)
    {
        fprintf(out, "%d %s %d\n", stu[i].id, stu[i].name, stu[i].seat);
    }
}