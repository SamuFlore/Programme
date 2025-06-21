#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Directory
{
    char name[200];
    char number[200];
};

int cmp(const void *a, const void *b)
{
    struct Directory *da = (struct Directory *)a;
    struct Directory *db = (struct Directory *)b;

    return strcmp(da -> name, db -> name);
}

int main()
{
    struct Directory directory[100];
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i ++)
    {
        scanf("%s %s", directory[i].name, directory[i].number);
    }

    qsort(directory, n, sizeof(struct Directory), cmp);
    

    struct Directory unique[105];
    unique[0] = directory[0];
    int unicount = 1;

    for (int i = 1; i < n; i ++)
    {
        int flag = 0;//1为有重复
        for(int j = 0; j < unicount; j ++)
        {
            if (strcmp(directory[i].name, unique[j].name) == 0 && strcmp(directory[i].number, unique[j].number) == 0)
            {
                flag = 1;
                break;
            }
        }

        if (! flag)
        {
            unique[unicount] = directory[i];
            unicount ++;
        }
    }
    
    
    int index = 0;

    for (int i = 1; i < unicount; i ++)
    {
        if (strcmp(unique[index].name, unique[i].name) != 0)
        {
            index = i;
        }
        else if (strcmp(unique[index].name, unique[i].name) == 0)
        {
            
            sprintf(unique[i].name, "%s%c%d", unique[i].name, '_', i - index);
        }
    }

    for (int i = 0; i < unicount; i ++)
    {
        printf("%s %s\n", unique[i].name, unique[i].number);
    }
    return 0;
}