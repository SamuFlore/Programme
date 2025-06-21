/*
    ����һ�������޻�ͼ����ָ��ԭ�㵽ָ���յ�����·
    ���룺��һ����������������һ����ʾͼ�ϵ�ĸ��� n ����ı�Ŵ� 1 �� n�����ڶ�����ʾͼ�ϱߵĸ��� m ��
        �ڶ��������������֣���ʾ�����յ���
        ���� m �У�ÿ�д���һ���ߣ��������֣���һ�����ִ���ߵ���㣬�ڶ������ִ���ߵ��յ㣬����������ߵ�Ȩ��
    �������һ��һ���������������·���ȣ�
        �ڶ����������㵽�յ㾭�������ж���ı�ţ����ж������ŷ�����������ֵ�����С��һ��

    ʾ�����룺
        7 10
        1 7
        1 2 3
        1 3 2
        1 4 3
        2 3 3
        2 5 1 
        3 5 3
        6 3 1
        4 6 3
        5 7 1
        6 7 5

    ʾ�������
        5
        1 2 5 7

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int readnum() {
    int tem;
    scanf("%d",&tem);
    return tem;
}

const int INF = 0x3f3f3f3f;

typedef struct node  node;
typedef struct node* nptr;
//�ߵĽṹ��
struct node {
    int v;
    int weight;
    nptr next;
};
nptr head[10005];      // �ڽӱ�����
int from[10005];   // ÿ���㱻˭����
int dis[10005];     // ÿ�������̾���
int vis[10005];     // ÿ�����Ƿ񱻷���
int road[10005];    // ��¼����㵽�յ��·��

nptr newnode() { return (nptr)malloc(sizeof(node)); }
nptr getnode(int v, int weight) {
    nptr p = newnode();
    p -> v = v;
    p -> weight = weight;
    p -> next = NULL;
    return p;
}

void addedge(int u, int v, int weight) {
    nptr p = getnode(v, weight);
    p -> next = head[u];
    head[u] = p;
}

int main() {
    int n = readnum(), m = readnum();
    int sta = readnum(), end = readnum();

    for(int i = 0; i < m ;i++) {
        int u = readnum(), v = readnum(), weight = readnum();
        addedge(u, v, weight);  // �����
    }

    for(int i = 1; i <= n ;i++)
        if(i != sta)
            dis[i] = INF;

    for(int i = 1; i <= n ;i++) {
        int tem = -1, minDis = INF;
        for(int j = 1; j <= n ;j++)
            if(!vis[j] && dis[j] < minDis)
                minDis = dis[j], tem = j;
        
        vis[tem] = 1;
        for(nptr p = head[tem]; p ; p = p -> next)
            if(!vis[p -> v] && p -> weight + dis[tem] < dis[p -> v])
                dis[p -> v] = p -> weight + dis[tem], from[p -> v] = tem;
    }

    printf("%d\n", dis[end]);

    int tem = end, cnt = 0;
    while(tem) {
        road[++cnt] = tem;
        tem = from[tem];
    }

    for(int j = cnt; j > 0 ;j--)
        printf("%d ", road[j]);

    return 0;
}