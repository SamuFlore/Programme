#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct telephone
{
    long long number;
    int time1;
    int time2;
    char site;
} Tele;

int cmp(const void *a, const void *b)
{
    Tele *p1 = (Tele *)a;
    Tele *p2 = (Tele *)b;
    if (p1 -> number < p2 -> number) return -1;
    else if (p1 -> number > p2 -> number) return 1;
    else
    {
        if (p1 -> site < p2 -> site) return -1;
        else if (p1 -> site > p2 -> site) return 1;
        else return 0;
    }
}

int main()
{
    Tele List[1000];
    Tele Ans[1000];
    int num;
    scanf("%d", &num);
    getchar();
    for (int i = 0; i < num; i ++)
    {
        long long number;
        char site;
        int time1, time2;
        char log[100];
        fgets(log, 100, stdin);
        sscanf(log, "%lld %c %d %d", &number, &site, &time1, &time2);
        List[i].number = number;
        List[i].site = site;
        List[i].time1 = time1;
        List[i].time2 = time2;
    }
    long long phone;
    int time1, time2;
    char phoneSite;
    scanf("%lld", &phone);
    int cnt = 0;
    for (int i = 0; i < num; i ++)
    {
        if (List[i].number == phone)
        {
            time1 = List[i].time1;
            time2 = List[i].time2;
            phoneSite = List[i].site;
            for (int j = 0; j < num; j ++)
            {
                if (List[j].site == phoneSite)
                {
                    if (phone == List[j].number) continue;
                    if ((time1 <= List[j].time2 && time1 >= List[j].time1) || (time2 <= List[j].time2 && time2 >= List[j].time1) || (time1 <= List[j].time1 && time2 >= List[j].time2))
                    {
                        int isFind = 0;
                        for (int k = 0; k < cnt; k ++)
                        {
                            if (Ans[k].number == List[j].number && Ans[k].site == List[j].site)
                            {
                                isFind = 1;
                                break;
                            }
                        }
                        if (!isFind)
                        {
                            Ans[cnt].number = List[j].number;
                            Ans[cnt].site = List[j].site;
                            cnt ++;
                        }
                    }
                }
            }
        }
    }
    qsort(Ans, cnt, sizeof(Tele), cmp);
    for (int i = 0; i < cnt; i ++)
    {
        printf("%lld %c\n", Ans[i].number, Ans[i].site);
    }
}