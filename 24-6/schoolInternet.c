#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    int *p1 = (int *)a;
    int *p2 = (int *)b;
    if (*p1 < *p2)
    {
        return -1;
    }
    else if (*p1 > *p2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

const int INF = 0x3f3f3f3f;



typedef struct node  node;
typedef struct node* nptr;

struct node {
    int id;
    int v;
    int weight;
    nptr next;
};

int vis[100050];
int dis[100050];
int from[100050];    // 记录每个点分别是由哪条边加入的最小生成树
int ans[100050]; // 记录用来构建最小生成树的边集
nptr head[100050];

nptr newnode() { return (nptr)malloc(sizeof(node)); }
nptr getnode(int id, int v, int weight) {
    nptr p = newnode();
    p -> id = id;
    p -> v = v;
    p -> weight = weight;
    p -> next = NULL;
    return p;
}

nptr addedge(int id, int u, int v, int weight) {
    nptr e1 = getnode(id, v, weight);
    e1 -> next = head[u];
    head[u] = e1;

    nptr e2 = getnode(id, u, weight);
    e2 -> next = head[v];
    head[v] = e2;
}

int main() {
    int n, m, cnt = 0;    // cnt 表示加入最小生成树边的个数
    scanf("%d%d", &n, &m);
    int totalWeight = 0;
    int sta = 0;    // 起点
    int id, u, v, weight;
    for(int i = 0; i < n ;i++)
        if(i != sta)
            dis[i] = INF;

    for(int i = 0; i < m ;i++) {
        scanf("%d%d%d%d", &id, &u, &v, &weight);
        addedge(id, u, v, weight);
        addedge(id, v, u, weight);
    }

    // 每次选择一个距离最小的点加入最小生成树的点集
    for(int i = 0; i < n ;i++) {
        int tem = -1, minDis = INF;    // 表示当前选择的距离最短的点和最短距离
        for(int j = 0; j < n ;j++)
            if(dis[j] < minDis && !vis[j])
                minDis = dis[j], tem = j;
        ans[cnt++] = from[tem];
        vis[tem] = 1;
        totalWeight += minDis;

        for(nptr p = head[tem]; p ; p = p -> next) 
            if(!vis[p -> v] && dis[p -> v] > p -> weight)
                dis[p -> v] = p -> weight, from[p -> v] = p -> id;
    }

    printf("%d\n", totalWeight);
    qsort(ans, cnt, sizeof(int), cmp);
    for(int i = 1; i < n ;i++)
        printf("%d ", ans[i]);
    return 0;
}