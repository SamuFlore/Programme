#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MMAX 1000000

int pathAmount[1005][1005], path[1005][1005];
int edge[1005][1005], pointNum, edgeNum;

void EdgeSet();
void Floyed();

int main()
{
    EdgeSet();
    Floyed();
    for (int i = 1; i <= pointNum; i++)
    {
        for (int j = 1; j <= pointNum; j++)
        {
            printf("%d->%d:amount:%d ||path:", i, j, edge[i][j]);
            PathPrint(i, j);
            printf("\n");
        }
    }
    return 0;
}

void EdgeSet()
{
    scanf("%d %d", &pointNum, &edgeNum);
    for (int i = 1; i <= pointNum; i++)
        for (int j = 1; j <= pointNum; j++)
        {
            if (i == j)
                edge[i][j] = 0;
            else
                edge[i][j] = MMAX;
            path[i][j] = -1;
        }

    for (int i = 0; i < edgeNum; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        
        if (edge[u][v] > w)
        {
            edge[u][v] = w;
            path[u][v] = u;
            //edge[v][u] = w;//无向图
        }
    }
}

void Floyed()
{
    for (int i = 1; i <= pointNum; i++)
    {
        for (int j = 1; j <= pointNum; j++)
        {
            for (int k = 1; k <= pointNum; k++)
            {
                if (edge[j][k] > edge[j][i] + edge[i][k])
                {
                    edge[j][k] = edge[j][i] + edge[i][k];
                    path[j][k] = path[i][k];
                }
            }
        }
    }
}


void PathPrint(int start,int end)
{
    if (start == end)
        return;
    PathPrint(start, path[start][end]);
    printf("%d ", path[start][end]);
    
        

   
}