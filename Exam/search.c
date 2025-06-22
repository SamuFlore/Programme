
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int readInt() {
    int tem;
    scanf("%d",&tem);
    return tem;
}

const int INF = 0x3f3f3f3f;

typedef struct ver
{
    int id;
    int len;
    int list[10];
} Ver;

typedef struct roads
{
    int end;
    int total_len;
    int way_len;
    int way[100];
} Roads;

typedef struct node  node;
typedef struct node* nptr;

struct node {
    int v;
    int weight;
    nptr next;
};
nptr head[10005];      // 邻接表数组
int from[10005];   // 每个点被谁更新
int dis[10005];     // 每个点的最短距离
int vis[10005];     // 每个点是否被访问
int road[10005];    // 记录从起点到终点的路径

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

int cmp(const void *a, const void *b)
{
    Roads *p1 = (Roads *)a;
    Roads* p2 = (Roads *)b;
    if (p1 -> total_len < p2 -> total_len) return -1;
    else if (p1 -> total_len > p2 -> total_len) return 1;
    else return 0;
}

int main() {
    int n = readInt();//总结点数
    Ver vertex[205];
    int index = 0;
    for (; index < n; index ++)
    {
        int cnt = 0;
        int hobby;
        int id = readInt();
        vertex[index].id = id;
        while ((hobby = readInt()) != -1)
        {
            vertex[index].list[cnt] = hobby;
            cnt ++;
        }
        vertex[index].len = cnt;
    }

    while (1)
    {
        int u = readInt(), v = readInt(), weight = readInt();
        if (u == -1 && v == -1 && weight == -1) break;
        int u_index, v_index;
        for (u_index = 0; u_index < index; u_index ++)
        {
            if (vertex[u_index].id == u) break;
        }
        for (v_index = 0; v_index < index; v_index ++)
        {
            if (vertex[v_index].id == v) break;
        }
        u_index ++;
        v_index ++;
        addedge(u_index, v_index, weight);
        addedge(v_index, u_index, weight);
        //
        // printf("(%d %d)", u_index, v_index);
    }

    int start = readInt();
    int sta;
    for (sta = 0; sta < index; sta ++)
    {
        if (vertex[sta].id == start) break;
    }
    sta ++;
    // printf("(%d)", sta);
    int hobby = readInt();
    int index2 = 0;
    int endlist[205];
    for (int i = 0; i < index; i ++)
    {
        for (int j = 0; j < vertex[i].len; j ++)
        {
            if (vertex[i].list[j] == hobby)
            {
                endlist[index2] = vertex[i].id;
                index2 ++;
            }
            
        }
    }
    // //test
    // for (int i = 0; i < index2; i ++)
    // {
    //     printf("(%d)", endlist[i]);
    // }

    Roads ways[1005];
    int way_index = 0;
    for (int k = 0; k < index2; k ++)
    {
        int ends = endlist[k];
        int end_index;
        for (end_index = 0; end_index < index; end_index ++)
        {
            if (vertex[end_index].id == ends) break;
        }
        int end = end_index + 1;
    

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
        // printf("%d\n", dis[end]);
        ways[way_index].total_len = dis[end];
        ways[way_index].end = vertex[end_index].id;
        if (ways[way_index].end == vertex[sta - 1].id)
        {
            ways[way_index].total_len = 0;
        }
        int tem = end, cnt = 0;
        while(tem) {
            road[++cnt] = tem;
            tem = from[tem];
        }

        // for(int j = cnt; j > 0 ;j--)
        //     printf("%d ", road[j]);
        int x = 0;
        for(int j = cnt; j > 0 ;j--)
        {
            ways[way_index].way[x] = vertex[road[j] - 1].id;
            x ++;
        }
        ways[way_index].way_len = x;
           
        way_index ++;
        memset(from, 0, sizeof(int)*10005);
        memset(dis, 0, sizeof(int)*10005);
        memset(vis, 0, sizeof(int)*10005);
        memset(road, 0, sizeof(int)*10005);
    }
    qsort(ways, way_index, sizeof(Roads), cmp);

    for (int i = 0; i < way_index; i ++)
    {
        if (ways[i].total_len == 0)
        {
            printf("%d %d\n", ways[i].end, 0);
        }
        else
        {
            printf("%d %d ", ways[i].end, ways[i].total_len);
            for (int j = 0; j < ways[i].way_len; j ++)
            {
                printf("%d", ways[i].way[j]);
                if (j != ways[i].way_len - 1) printf("-");
            }
            printf("\n");
        }
    }
    return 0;
}