/*
    ����һ���������Ի������رߵ�������ͨͼ���� Kruskal �㷨��������С������
    ���룺��һ����������������һ����ʾͼ�ϵ�ĸ��� n ����ı�Ŵ� 0 �� n - 1�����ڶ�����ʾͼ�ϱߵĸ��� m ��
        ���� m �У�ÿ�д���һ���ߣ��ĸ����֣��ֱ��ʾ�ߵı�ţ������˵��ţ��ߵ�Ȩ��
    �������һ��һ��Ȩ�أ���ʾ��С��������Ȩ�أ��ڶ��д� n - 1 ����������ʾѡȡ�ߵı�ţ���������С��������˳�����

    ʾ�����룺
        6 10
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
        2 9 6 8 4

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int read() {
    int tem;
    scanf("%d",&tem);
    return tem;
}

typedef struct edge  edge;

struct edge {
    int id;
    int u;
    int v;
    int weight;
};

int f[10005];   // ����ά�����鼯
edge e[10005];  // ����ά�����б�
int ans[10005]; // ��¼ MST ѡ��ı�

// ��
int find(int i) {
    return f[i] = f[i] == i ? i : find(f[i]);
}

// ��
void link(int u, int v) {
    f[find(u)] = find(v);
}

int cmp(const void *a, const void *b) {
    edge x = *(edge *)a;
    edge y = *(edge *)b;
    return x.weight - y.weight ? x.weight - y.weight : x.id - y.id;
}

int main() {
    int n = read(), m = read();
    for(int i = 0; i < m ;i++) 
        e[i].id = read(), e[i].u = read(), e[i].v = read(), e[i].weight = read();
    qsort(e, m, sizeof(e[0]), cmp);
    int totalWeight = 0, cnt = 0;

    // ���鼯��ʼ��
    for(int i = 0; i < n;i++)   
        f[i] = i;

    for(int i = 0; i < m ;i++) {
        if(find(e[i].u) != find(e[i].v))
            ans[++cnt] = e[i].id, totalWeight += e[i].weight, link(e[i].u, e[i].v);
    }

    printf("%d\n", totalWeight);
    for(int i = 1; i < n ;i++)
        printf("%d ", ans[i]);
    return 0;
}