#include <stdio.h>
#include <stdlib.h>

typedef struct silver
{
    int weight;
    struct silver *next;
} Silver;

Silver *head = NULL;
int total_weight = 0;

Silver *insertNode(Silver *head, Silver *node)
{
    Silver *p = NULL, *q = NULL;
    total_weight += node -> weight;
    if (head == NULL)
    {
        head = node;
        return head;
    }
    for (p = head; p != NULL && node -> weight > p -> weight; q = p, p = p -> next);
    if (p == head)
    {
        node -> next = head;
        head = node;
        return head;
    }
    else
    {
        q -> next = node;
        node -> next = p;
    }
    return head;
}

Silver *sellNode(Silver *head, int n)//n为所要取出的重量
{
    int need_weight = -n;
    if (need_weight > total_weight)
    {
        return head;
    }
    else if (need_weight < total_weight)
    {
        total_weight -= need_weight;
        int out_weight = 0;//取出的总重量
        int isEnough = 0;
        while (head -> next != NULL)
        {
            Silver *tmp = head;
            out_weight += head -> weight;
            head = head -> next;
            free(tmp);
            if (out_weight >= need_weight)
            {
                isEnough = 1;
                break;
            }
        }
        if (!isEnough)
        {
            Silver *tmp = head;
            out_weight += head -> weight;
            head = NULL;
            free(tmp);
        }
        if (out_weight == need_weight) return head;
        else if (out_weight > need_weight)
        {
            Silver *node = (Silver *)malloc(sizeof(Silver));
            node -> weight = out_weight - need_weight;
            node -> next = NULL;
            head = insertNode(head, node);
        }
    }
    else
    {
        while (head -> next != NULL)
        {
            Silver *tmp = head;
            head = head -> next;
            free(tmp);
        }
        free(head);
        head = NULL;
    }
    return head;
}

Silver *merge(Silver *head)
{
    int total_weight2 = 0;
    while (head != NULL)
    {
        if (head -> weight >= 10) break;
        if (head -> weight < 10)
        {
            total_weight2 += head -> weight;
            Silver *tmp = head;
            head = head -> next;
            free(tmp);
        }
    }
    if (total_weight2 != 0)
    {
        Silver *node = (Silver *)malloc(sizeof(Silver));
        node -> weight = total_weight2;
        node -> next = NULL;
        total_weight -= total_weight2;
        return head = insertNode(head, node);
    }
    else return head;
}

int main()
{
    while (1)
    {
        int order = 0;
        scanf("%d", &order);
        if (order > 0 && order != 999999)
        {
            Silver *node = (Silver *)malloc(sizeof(Silver));
            node -> weight = order;
            node -> next = NULL;
            head = insertNode(head, node);
        }
        else if (order < 0)
        {
            head = sellNode(head, order);
        }
        else if (order == 0)
        {
            head = merge(head);
        }
        else if (order == 999999)
        {
            break;
        }
    }

    Silver *cur = head;
    if (cur == NULL)
    {
        printf("0");
        goto end;
    }
    while (cur -> next != NULL)
    {
        printf("%d ", cur -> weight);
        cur = cur -> next;
    }
    printf("%d", cur -> weight);
    end:
    return 0;
}