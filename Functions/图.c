#include <stdio.h>
#define MAXV 256
#define INFINITY 32768

typedef struct edge//边的结构
{
    int adjvex;//记录边指向的顶点序号
    int weight;//边的权重
    struct edge *next;//指向下一条边的指针
} Elink;

typedef struct vertex//顶点的结构
{
    Elink *link;//指向第一条边的指针
} Vlink;

Vlink G[MAXV];//全部顶点的数组
Elink *queue[MAXV];//辅助队列，将待访问的顶点存入队列
int front = 0, rear = 0;//队列头、尾指针

/*在Glink某元素的邻接结点序列尾增加一个元素*/
Elink *insertEdge(Elink *head, int adjvex, int weight)
{
    Elink *e, *p;
    e = (Elink *)malloc(sizeof(Elink));
    e -> adjvex = adjvex;
    e -> weight = weight;
    e -> next = NULL;
    if (head == NULL)
    {
        head = e;
        return head;
    }
    else
    {
        for (p = head; p -> next != NULL; p = p -> next);
        p -> next = e;
        return head;
    }
}

int visited[MAXV];//记录是否已经访问过的数组

/*深度优先遍历*/
void DFS(Vlink G[], int v)//深度优先遍历的递归函数
{
    Elink *p;
    visited[v] = 1;
    printf("%d ", v);
    for (p = G[v].link; p!= NULL; p = p->next)
    {
        if (! visited[p->adjvex])
        {
            DFS(G, p->adjvex);
        }
    }
}

void travelDFS(Vlink G[], int n)//调用深度优先遍历的函数
{
    int i;
    for (i = 0; i < n; i ++) visited[i] = 0;
    for (i = 0; i < n; i ++)
    {
        if (! visited[i])
        {
            DFS(G, i);
            printf("\n");
        }
    }
    
}

/*广度优先遍历*/
void BFS(Vlink G[], int v)
{
    Elink *p;
    printf("%d ", v);//访问顶点v，可替换之
    visited[v] = 1;
    queue[rear] = G[v].link;//v所指的第一个顶点入队,queue是全局数组，front和rear是全局变量，记得拷贝
    rear = (rear + 1) % MAXV;
    while (front!= rear)
    {
        p = queue[front];//取出队首顶点
        front = (front + 1) % MAXV;
        for (; p != NULL; p = p -> next)
        {
            if (! visited[p->adjvex])
            {
                printf("%d ", p->adjvex);//访问之
                visited[p->adjvex] = 1;
                queue[rear] = G[p->adjvex].link;//将刚访问完的顶点的相邻顶点入队待访问
                rear = (rear + 1) % MAXV;
            }
        }
    }
}

void travelBFS(Vlink G[], int n)//调用广度优先遍历的函数
{
    int i;
    for (i = 0; i < n; i ++) visited[i] = 0;
    for (i = 0; i < n; i ++)
    {
        if (! visited[i])
        {
            BFS(G, i);
        }
    }
}

