#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct dish
{
    char id[5];
    int price;
    int num;
} Dish;

int cmp(const void *a, const void *b)
{
    Dish *p1 = (Dish *)a;
    Dish *p2 = (Dish *)b;
    if (p1 -> price > p2 -> price) return -1;
    else if (p1 -> price < p2 -> price) return 1;
    else
    {
        if (p1 -> num > p2 -> num) return -1;
        else if (p1 -> num < p2 -> num) return 1;
        else return 0;
    }
}
Dish dishes[105];

int main()
{
    int index = 0;
    int n;
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i ++)
    {
        char order[100];
        int table;
        char name[5];
        int num;
        int price;
        gets(order);
        sscanf(order, "%d %s %d %d", &table, name, &num, &price);
        int isFind = 0;
        for (int j = 0; j < index; j ++)
        {
            if (strcmp(dishes[j].id, name) == 0)
            {
                dishes[j].num += num;
                dishes[j].price += price*num;
                isFind = 1;
                break;
            }
        }
        if (!isFind)
        {
            strcpy(dishes[index].id, name);
            dishes[index].num += num;
            dishes[index].price += price*num;
            index ++;
        }
    }

    int total_price = 0;
    for (int i = 0; i < index; i ++)
    {
        total_price += dishes[i].price;
    }
    printf("%d\n", total_price);
    qsort(dishes, index, sizeof(Dish), cmp);
    for (int i = 0; i < index; i ++)
    {
        printf("%s %d %d\n", dishes[i].id, dishes[i].num, dishes[i].price);
    }
    return 0;
}