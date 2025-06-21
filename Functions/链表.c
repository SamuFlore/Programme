#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} Node;

Node *head = NULL;

Node *createList(int n)//创建一个n个结点的链表
{
    Node *p, *q, *list = NULL;
    for (int i = 0; i < n; i ++)
    {
        q = (Node *)malloc(sizeof(Node));
        q -> data = read();//读取数据函数
        q -> next = NULL;
        if (list == NULL)
        {
            list = p = q;
        }
        else
        {
            p -> next = q;
        }
        p = q;
    }
    return list;
}//调用：head = createList(n);

Node *insertNode(Node *list, int data)//有序列表中插入结点
{
   Node *p = NULL, *q = NULL, *r = NULL;
   r = (Node *)malloc(sizeof(Node));
   r -> data = data;
   r -> next = NULL;
   if (list == NULL)//空链表
   {
    return r;
   }
   for (p = list; p != NULL && data > p -> data; q = p, p = p -> next);//q是p前序结点，找到插入位置
   if (p == list)
   {
    r -> next = p;
    return r;
   }
   else
   {
    q -> next = r;
    r -> next = p;
   }
   return list;
}//调用：head = insertNode(head, n);

Node *deleteNode(Node *head, int n)
{
    Node *p, *q;
    if (head == NULL) return head;//空链表
    for (p = head; p != NULL; p = p -> next)
    {
        if (p -> data == n) break;
    }
    if (p == head)
    {
        head = head -> next;
        free(p);
    }
    if (q -> next != NULL)
    {
        q -> next = p -> next;
        free(p);
    }
    return head;
}//调用：head = deleteNode(head, n);