#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Books
{
    char title[60];
    char author[60];
    char publisher[60];
    int year;
};

int cmp(const void *a, const void *b)
{
    struct Books *t1 = (struct Books *)a;
    struct Books *t2 = (struct Books *)b;
    return strcmp(t1 -> title, t2 -> title);
}

int main()
{
    FILE *in, *out;
    in = fopen("books.txt", "r");
    out = fopen("ordered.txt", "w");
    struct Books book[1000];
    int i = 0;
    int choose;
    while (fscanf(in, "%s %s %s %d", book[i].title, book[i].author, book[i].publisher, &book[i].year) != EOF)
    {
        i ++;
    }

    qsort(book, i, sizeof(struct Books), cmp);


    while (scanf("%d", &choose) != EOF)
    {
        if (choose == 1)
        {
            char title[60], author[60], publisher[60];
            int year;
            scanf("%s %s %s %d", title, author, publisher, &year);
            
            strcpy(book[i].title, title);
            strcpy(book[i].author, author);
            strcpy(book[i].publisher, publisher);
            book[i].year = year;
            i ++;

            qsort(book, i, sizeof(struct Books), cmp);
        }
        else if (choose == 2)
        {
            char title[60];
            scanf("%s", title);
            
            for (int j = 0; j < i; j ++)
            {
                if (strstr(book[j].title, title) != NULL)
                {
                    printf("%-50s%-20s%-30s%-10d\n", book[j].title, book[j].author, book[j].publisher, book[j].year);
                }
            }
        }
        else if (choose == 3)
        {
            char title[60];
            scanf("%s", title);

            for (int j = 0; j < i; j ++)
            {
                if (strstr(book[j].title, title) != NULL)
                {
                    for (int k = j; k < i - 1; k ++)
                        {
                            book[k] = book[k + 1];
                        }
                        i --;
                        j --;
                }
            }
        }
        else if (choose == 0)
        {
            break;
        }
    }
    
    for (int j = 0; j < i; j ++)
    {
        fprintf(out, "%-50s%-20s%-30s%-10d\n", book[j].title, book[j].author, book[j].publisher, book[j].year);
    }

    fclose(in);
    fclose(out);
    return 0;
}