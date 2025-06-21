//输入格式：人数 出列的号码

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int num;
    struct node *next;
} Josephu;

Josephu *head = NULL;

Josephu *createCircle(Josephu *head, int n)
{
    Josephu *p = NULL, *q = NULL;
    for (int i = 0; i < n; i ++)
    {
        q = (Josephu *)malloc(sizeof(Josephu));
        q -> num = i + 1;
        q -> next = NULL;
        if (head == NULL)
        {
            head = q;
            p = q;
        }
        else
        {
            p -> next = q;
            p = q;
        }
    }
    p -> next = head;
    return head;
}

int printPeople(Josephu *head, int m)//报到m的人出列
{
    int i = 1;
    Josephu *cur = head, *prev = NULL;
    while (cur -> next != cur)
    {
        if (i == m)
        {
            i = 1;
            prev -> next = cur -> next;
            cur = prev -> next;
        }
        else
        {
            prev = cur;
            cur = cur -> next;
            i ++;
        }
    }
    return cur -> num;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    head = createCircle(head, n);
    printf("%d\n", printPeople(head, m));
    return 0;
}