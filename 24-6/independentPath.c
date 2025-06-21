// 5 6
// 1 0 1
// 2 0 2
// 3 1 2
// 4 1 3
// 5 3 4
// 6 1 4

// 6 11
// 1 0 1
// 2 0 3
// 3 0 3
// 4 0 2
// 5 1 3
// 6 3 2
// 7 1 4
// 8 3 4
// 9 3 5
// 10 2 5
// 11 4 5


#include <stdio.h>
#include <stdlib.h>
#define MAXV 1024

int vNum;
int vStart = 0, vEnd;

typedef struct edge
{
    int edgenum;
    int adjvex;
    int weight;
    struct edge *next;
} Elink;

typedef struct vertex
{
    Elink *link;
} Vlink;

Vlink G[MAXV];
int visited[MAXV] = {0};
int Paths[MAXV] = {0};

void printPath(int n)
{
    for (int i = 0; i < n; i ++)
    {
        printf("%d ", Paths[i]);
    }
    printf("\n");
    return ;
}

Elink *insertEdge(Elink *head, int edgenum, int adjvex, int weight)
{
    Elink *e, *p;
    e = (Elink *)malloc(sizeof(Elink));
    e -> edgenum = edgenum;
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

void eDFS(int v, int level)
{
    Elink *p;
    if (v == vEnd)
    {
        printPath(level);//level记录着从起始位置到结束位置走过多少层，即这段路径的长度
        return ;
    }
    for (p = G[v].link; p != NULL; p = p -> next)
    {
        if (! visited[p -> adjvex])
        {
            Paths[level] = p -> edgenum;
            visited[p -> adjvex] = 1;
            eDFS(p -> adjvex, level + 1);
            visited[p -> adjvex] = 0;//回溯的时候，该节点在之前那条路径被访问，而可能还有别的路径通向该节点，因此必须归零
        }
    }

}

int main()
{
    int vNum, edge_num;
    scanf("%d %d", &vNum, &edge_num);
    vEnd = vNum - 1;
    for (int i = 0; i < edge_num; i ++)
    {
        int edgenum, v1, v2;
        scanf("%d %d %d", &edgenum, &v1, &v2);
        G[v1].link = insertEdge(G[v1].link, edgenum, v2, 1);
        G[v2].link = insertEdge(G[v2].link, edgenum, v1, 1);
    }
    visited[vStart] = 1;
    eDFS(vStart, 0);
    return 0;
}