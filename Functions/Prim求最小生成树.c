/*
    ����һ���������Ի������رߵ�������ͨͼ���� Prim �㷨��������С������
    ���룺��һ����������������һ����ʾͼ�ϵ�ĸ��� n ����ı�Ŵ� 0 �� n - 1�����ڶ�����ʾͼ�ϱߵĸ��� m ��
        �ڶ���һ����������ʾ��һ��������С�������ĵ㣻
        ���� m �У�ÿ�д���һ���ߣ��ĸ����֣��ֱ��ʾ�ߵı�ţ������˵��ţ��ߵ�Ȩ��
    �������һ��һ��Ȩ�أ���ʾ��С��������Ȩ�أ��ڶ��д� n - 1 ����������ʾѡȡ�ߵı�ţ���������С��������˳�����

    ʾ�����룺
        6 10
        0
        1 0 1 600
        2 0 2 100
        3 0 3 500
        4 1 2 500
        5 2 3 500
        6 1 4 300
        7 2 4 600
        8 2 5 400
        9 3 5 200
        10 4 5 600

    ʾ�������
        1500
        2 8 9 4 6

*/

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

int read() {
    int tem;
    scanf("%d",&tem);
    return tem;
}

typedef struct node  node;
typedef struct node* nptr;

struct node {
    int id;
    int v;
    int weight;
    nptr next;
};

int vis[10005];
int dis[10005];
int from[10005];    // ��¼ÿ����ֱ����������߼������С������
int ans[10005]; // ��¼����������С�������ı߼�
nptr head[10005];

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
    int n = read(), m = read(), cnt = 0;    // cnt ��ʾ������С�������ߵĸ���
    int totalWeight = 0;
    int sta = 0;
    
    for(int i = 0; i < n ;i++)
        if(i != sta)
            dis[i] = INF;

    for(int i = 0; i < m ;i++) {
        int id = read(), u = read(), v = read(), weight = read();
        addedge(id, u, v, weight);
        addedge(id, v, u, weight);
    }

    // ÿ��ѡ��һ��������С�ĵ������С�������ĵ㼯
    for(int i = 0; i < n ;i++) {
        int tem = -1, minDis = INF;    // ��ʾ��ǰѡ��ľ�����̵ĵ����̾���
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