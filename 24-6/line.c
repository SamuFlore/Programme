#include <stdio.h>
#include <stdlib.h>


struct line
{
    int x1, y1, x2, y2;
    struct line *next;
};

int cmp(const void *a, const void *b)
{
    struct line *p1 = (struct line *)a;
    struct line *p2 = (struct line *)b;
    if (p1 -> x1 < p2 -> x1)
    {
        return -1;
    }
    else if (p1 -> x1 > p2 -> x1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int main()
{
    int n;
    scanf("%d", &n);
    struct line lines[105];
    for (int i = 0; i < n; i ++)
    {
        scanf("%d %d %d %d", &lines[i].x1, &lines[i].y1, &lines[i].x2, &lines[i].y2);
    }

    qsort(lines, n, sizeof(struct line), cmp);

    int max = 1;
    struct line *maxline;

    struct line *p, *q, *r;
    {
        for (int i = 0, i2 = 0; i < n; i ++, i2 ++)
        {
            p = (struct line *)malloc(sizeof(struct line));
            p -> x1 = lines[i].x1;
            p -> y1 = lines[i].y1;
            p -> x2 = lines[i].x2;
            p -> y2 = lines[i].y2;
            p -> next = NULL;
            r = p;
            int max2 = 1;
            struct line *maxline2;
            do
            {
                int flag = 0;
                for (int j = i2 + 1; j < n; j ++)
                {
                    q = (struct line *)malloc(sizeof(struct line));
                    q -> x1 = lines[j].x1;
                    q -> y1 = lines[j].y1;
                    q -> x2 = lines[j].x2;
                    q -> y2 = lines[j].y2;
                    if (r -> x2 == q -> x1 && r -> y2 == q -> y1)
                    {
                        r -> next = q;
                        r = q;
                        i2 = j;
                        max2 ++;
                        maxline2 = p;
                        flag = 1;
                        break;
                    }
                    
                }
                if (flag == 0)
                {
                    break;
                }
            } while (i2 < n - 1);
            
            if (max2 > max)
            {
                max = max2;
                maxline = maxline2;
            }
            
            i2 = i;
            

        }
    }
    printf("%d %d %d\n", max, maxline -> x1, maxline -> y1);

    return 0;
}