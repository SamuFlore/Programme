#include <stdio.h>
#include <stdlib.h>

typedef struct Multi
{
    int num, power;
    struct Multi *next;
} Multi;

Multi *create(int num, int power)//返回新节点的指针
{
    Multi *new = (Multi *)malloc(sizeof(Multi));
    new -> num = num;
    new -> power = power;
    new -> next = NULL;
    return new;
}

Multi *createlist()
{
    Multi *head = NULL;//第一个节点指针
    Multi *tail = NULL;//下一个
    int num, power;
    char ch;
    while (scanf("%d %d%c", &num, &power, &ch) == 3)
    {
        Multi *new = create(num, power);
        if (head == NULL)
        {
            head = new;
            tail = new;
        }
        else
        {
            tail -> next = new;
            tail = new;
        }
        if (ch == '\n')
        {
            break;
        }
    }
    return head;
}

void multiply(Multi *node1, Multi *node2, Multi **resulth, Multi **resultt)
{
    int num1 = node1 -> num * node2 -> num;
    int power1 = node1 -> power + node2 -> power;
    Multi *now = *resulth;
    Multi *previous = NULL;
    while (now != NULL && now -> power > power1)//找到大于power的最后一个节点，把num1置于其后，即new在now和previous之间
    {
        previous = now;
        now = now -> next;//往后移动一位
    }
    if (now != NULL && now -> power == power1)//指数相同，相加
    {
        now -> num += num1;
    }
    else
    {
        Multi *new = create(num1, power1);
        if (previous == NULL)//该节点指数是最大的，插入到头部
        {
            new -> next = *resulth;
            *resulth = new;
        }
        else
        {
            new -> next = now;
            previous -> next = new;
        }
        if (*resultt == previous)//如果new的指数比原来的末尾还小，则更新末尾指针
        {
            *resultt = new;
        }
    }
}

Multi *multiplylist(Multi *head1, Multi *head2)
{
    Multi *resulth = NULL, *resultt = NULL;
    Multi *p = head1;
    while (p != NULL)
    {
        Multi *q = head2;
        while (q != NULL)
        {
            multiply(p, q, &resulth, &resultt);
            q = q -> next;
        }
        p = p -> next;
    }
    return resulth;
}

int main()
{
    Multi *head1 = createlist();//*head1是链表1的头指针
    Multi *head2 = createlist();
    // for (Multi *p = head1; p != NULL; p = p -> next)
    // {
    //     printf("%d %d ", p -> num, p -> power);
    // }
    Multi *result = multiplylist(head1, head2);
    Multi *p = result;
    while (p != NULL)
    {
        printf("%d %d ", p -> num, p -> power);
        p = p -> next;
    }

    return 0;
}
