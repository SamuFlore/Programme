#include <stdio.h>
#include <stdlib.h>
#define MAXV 128

typedef struct edge
{
    int adjvex;
    int weight;
    struct edge *next;
} Elink;

typedef struct vertex
{
    Elink *link;
} Vlink;

Vlink G[MAXV];
Elink *queue[MAXV];//辅助队列，将待访问的顶点存入队列
int front = 0, rear = 0;//队列头、尾指针

Elink *insertEdge(Elink *head, int adjvex, int weight)
{
    Elink *e, *p, *q = NULL;
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
        for (p = head; p != NULL && e -> adjvex > p -> adjvex; q = p, p = p -> next);
        if (p == head)
        {
            e -> next = head;
            head = e;
            return head;
        }
        else
        {
            e -> next = p;
            q -> next = e;
            return head;
        }
    }
}

int visited[MAXV];//记录是否已经访问过的数组

/*深度优先遍历*/
void DFS(Vlink G[], int v, int ver)//深度优先遍历的递归函数
{
    Elink *p;
    visited[v] = 1;
    printf("%d ", v);
    for (p = G[v].link; p != NULL; p = p->next)
    {
        if ((! visited[p->adjvex]) && (p -> adjvex != ver))
        {
            DFS(G, p->adjvex, ver);
        }
    }
}

void travelDFS(Vlink G[], int n, int ver)//调用深度优先遍历的函数
{
    int i;
    for (i = 0; i < n; i ++) visited[i] = 0;
    for (i = 0; i < n; i ++)
    {
        if ((!visited[i]) && (i != ver))
        {
            DFS(G, i, ver);
        }
    }
    
}

/*广度优先遍历*/
void BFS(Vlink G[], int v, int ver)
{
    Elink *p;
    printf("%d ", v);//访问顶点v，可替换之
    visited[v] = 1;
    queue[rear] = G[v].link;//v所指的第一个顶点入队
    rear = (rear + 1) % MAXV;
    while (front!= rear)
    {
        p = queue[front];//取出队首顶点
        front = (front + 1) % MAXV;
        for (; p != NULL; p = p -> next)
        {
            if ((! visited[p->adjvex]) && (p -> adjvex != ver))
            {
                printf("%d ", p->adjvex);//访问之
                visited[p->adjvex] = 1;
                queue[rear] = G[p->adjvex].link;//将刚访问完的顶点的相邻顶点入队待访问
                rear = (rear + 1) % MAXV;
            }
        }
    }
}

void travelBFS(Vlink G[], int n, int ver)//调用广度优先遍历的函数
{
    int i;
    for (i = 0; i < n; i ++) visited[i] = 0;
    for (i = 0; i < n; i ++)
    {
        if ((! visited[i]) && (i != ver))
        {
            BFS(G, i, ver);
        }
    }
}

int main()
{
    int vertex, edge;
    scanf("%d %d", &vertex, &edge);
    for (int i = 0; i < edge; i ++)
    {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        G[v1].link = insertEdge(G[v1].link, v2, 1);
        G[v2].link = insertEdge(G[v2].link, v1, 1);
    }
    int ver;//要删除的顶点
    scanf("%d", &ver);
    travelDFS(G, vertex, MAXV);
    printf("\n");
    travelBFS(G, vertex, MAXV);
    printf("\n");
    travelDFS(G, vertex, ver);
    printf("\n");
    travelBFS(G, vertex, ver);
}