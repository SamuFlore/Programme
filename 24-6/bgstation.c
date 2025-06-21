#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXNUM 512
#define MAXLEN 16
#define INFINITY 32767

struct station
{
    char sname[MAXLEN];//车站名称
    int ischange;//是否为换乘站
};

struct weight
{
    int wei;//边的权重，两站之间的距离为1
    int lno;//线路号
};

struct station BGvertex[MAXNUM];
struct weight BGweights[MAXNUM][MAXNUM];//邻接矩阵
int Vnum = 0;//车站总数

//增加一个车站
int addVertex(struct station st)
{
    int i;
    for (i = 0; i < Vnum; i++)
    {
        if (strcmp(BGvertex[i].sname, st.sname) == 0)
            return i;
    }
    if (Vnum >= MAXNUM)
        return -1;
    strcpy(BGvertex[Vnum].sname, st.sname);
    BGvertex[Vnum].ischange = st.ischange;
    Vnum++;
    return Vnum - 1;
}

void initMap()
{
    FILE *fp;
    int i, j, snum, lno, lnum, v1, v2;
    struct station st;

    // 初始化邻接矩阵
    for (i = 0; i < MAXNUM; i++)
    {
        for (j = 0; j < MAXNUM; j++)
        {
            BGweights[i][j].wei = INFINITY;
            BGweights[i][j].lno = 0;
        }
    }

    fp = fopen("bgstations.txt", "r");
    if (fp == NULL)
    {
        printf("文件打开失败！\n");
        return;
    }
    fscanf(fp, "%d", &snum);//线路的总数
    for (i = 0; i < snum; i++)
    {
        fscanf(fp, "%d %d", &lno, &lnum);//线路号和车站总数
        v1 = v2 = -1;
        for (j = 0; j < lnum; j++)
        {
            fscanf(fp, "%s %d", st.sname, &st.ischange);
            v2 = addVertex(st);//addvertex在车站列表中找这个站，如果没有，增加一个，返回索引，如果有，直接返回索引
            if (v2 < 0)
                continue;
            if (v1 != -1)//如果v2不是这条线的第一个站，则v1和v2之间有边
            {
                BGweights[v1][v2].wei = 1;
                BGweights[v2][v1].wei = 1;
                BGweights[v1][v2].lno = lno;
                BGweights[v2][v1].lno = lno;
            }
            v1 = v2;
        }
    }
    fclose(fp);
    return;
}


void Dijkstra(int v0, int v1, int spath[], int *found)
{
    //spath记录最短路径经过的顶点序列，spath[v] = j 表示v的前驱顶点是j
    int i, j, v, minweight;//v是当前权值最小的顶点
    char wfound[MAXNUM] = {0};//标记是否已经找到起点到各顶点最短路径
    int sweight[MAXNUM];//起始点到各顶点的最短路径长度，初始化为无穷大

    for (i = 0; i < Vnum; i++)
    {
        sweight[i] = INFINITY;
        spath[i] = -1;
    }

    sweight[v0] = 0;//起点到起点的最短路径长度为0
    spath[v0] = v0;//起点到起点的路径只有一个顶点

    for (i = 0; i < Vnum; i++)//外层循环：要建立起点到各点的最短路径，则需要循环Vnum次（包括到自己）
    {
        minweight = INFINITY;
        v = -1;
        for (j = 0; j < Vnum; j++)//内层循环：找出到起点权值最小的点，令v保存其索引
        {
            if (!wfound[j] && sweight[j] < minweight)
            {
                minweight = sweight[j];
                v = j;
            }
        }

        if (v == -1 || v == v1)//如果找到的这个权值最小的顶点是终点，则找到了最短路径。
            break;

        wfound[v] = 1;//标记这个顶点已经找到了最短路径

        for (j = 0; j < Vnum; j++)
        {
            if (!wfound[j] && BGweights[v][j].wei != INFINITY)//如果j没有找到最短路径，且v到j有边，则更新起点到j的路径长度和路径，v是当前权值最小的顶点
            {
                if (sweight[v] + BGweights[v][j].wei < sweight[j])//如果起点到v的路径长度加v到j的路径长度小于起点直接到j的路径长度，则更新起点到j的路径长度和路径，假设一开始起点到j无边，则相当于找到了最短路径
                {
                    sweight[j] = sweight[v] + BGweights[v][j].wei;
                    spath[j] = v;//这表示j的前驱顶点是v
                }
            }
        }
    }

    *found = (sweight[v1] != INFINITY);//若起点到终点的权值不是无穷大，则必然找到了最短路径
}

void printPath(int v0, int v1, int spath[])
{
    if (v0 == v1)
    {
        printf("%s-无需移动\n", BGvertex[v0].sname);
        return;
    }

    int path[MAXNUM], count = 0;//count记录两站间的长度
    int current = v1;//从v1开始往前找，倒序
    while (current != v0)
    {
        path[count++] = current;
        current = spath[current];//spath记录的是前驱顶点，这样current就移动到了上一站
        if (current == -1)
        {
            printf("路径错误\n");
            return;
        }
    }//current等于v0，回到了起点
    path[count] = v0;

    int startLine = BGweights[path[count]][path[count - 1]].lno;//即第一站到第二站的边是哪条线
    int lastLine = startLine;//上一条线
    int startIndex = count;
    int lastChange = count;
    printf("%s 出发", BGvertex[v0].sname);
    for (int i = count - 1; i >= 0; i--)
    {
        int currentLine = BGweights[path[i + 1]][path[i]].lno;
        if (currentLine != lastLine)
        {
            printf(" - %d号线 (%d站)", lastLine, lastChange - i - 1);
            printf(" - %s 换乘", BGvertex[path[i + 1]].sname);
            lastChange = i + 1;
            lastLine = currentLine;
        }
    }
    printf(" - %d号线 (%d站) - 到达 %s\n", lastLine, lastChange, BGvertex[v1].sname);
}

int findStationIndex(char *name)
{
    for (int i = 0; i < Vnum; i++)
    {
        if (strcmp(BGvertex[i].sname, name) == 0)
            return i;
    }
    return -1;
}

int main()
{
    initMap();

    char startName[MAXLEN], endName[MAXLEN];
    printf("请输入起点站：");
    scanf("%s", startName);
    printf("请输入终点站：");
    scanf("%s", endName);

    int v0 = findStationIndex(startName);
    int v1 = findStationIndex(endName);

    if (v0 == -1)
    {
        printf("起点站不存在！\n");
        return 1;
    }
    if (v1 == -1)
    {
        printf("终点站不存在！\n");
        return 1;
    }

    int spath[MAXNUM];
    int found;
    Dijkstra(v0, v1, spath, &found);

    if (!found)
    {
        printf("无法从 %s 到达 %s\n", startName, endName);
        return 0;
    }
    printPath(v0, v1, spath);
    getchar();
    getchar();
    return 0;
}