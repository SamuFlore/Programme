#include <stdio.h>
#include <stdlib.h>

typedef struct MemoryBlock
{
    int index;
    int length;
    struct MemoryBlock *next;
} Memory;

int main()
{
    int n;
    scanf("%d", &n);
    Memory list[105];
    for (int i = 0; i < n; i ++)
    {
        scanf("%d%d", &list[i].index, &list[i].length);
        list[i].next = NULL;
    }
    for (int i = 0; i < n; i ++)
    {
        list[i].next = &list[i + 1];
    }
    list[n - 1].next = list;

    int query[105];
    int i = 0;
    
    while (1)
    {
        scanf("%d", &query[i]);
        if (query[i] == -1)
        {
            break;
        }
        i ++;
    }
    
    Memory *a = list;
    Memory *b = &list[n - 1];
    Memory *end = list;
    Memory *current = list;
    Memory *prev = NULL;
    int flag = 0;
    for (int j = 0; j < i; j ++)
    {

        do
        {
            if (a -> length != query[j])
            {
                if (((a -> length > query[j]) && ((a -> length < current -> length) || (current -> length < query[j]))) || ((a == current) && (a -> length > query[j])))
                //如果a长度大于query[j]，且a小于current，或者current小于query（current初始化为第一个节点），更新current，还有一种情况是刚开始或者删去某一节点后a就是current，若能满足大于query，也要更新
                {
                    current = a;
                    prev = b;
                    flag = 1;
                }
            }
            else
            {
                current = a;
                prev = b;
                flag = 2;
                break;
            }
            a = a -> next;
            b = b -> next;
            
        } while (a != end);

        if (flag == 1)
        {
            current -> length -= query[j];
            a = current;
            b = prev;
            end = a;
            flag = 0;//情况1，节点长度减少
        }
        else if (flag == 2)
        {
            if (current == prev)
            {
                goto exit;//删去节点前，若只有一个节点，说明空间正好用完，不输出
            }
            prev -> next = current -> next;
            current = current -> next;
            a = current;
            end = a;
            flag = 0;//否则删除节点
        }
    }

    Memory *start = current;
    while (start -> next != current)
    {
        printf("%d %d\n", start -> index, start -> length);
        start = start -> next;
    }
    printf("%d %d\n", start -> index, start -> length);
    exit:
    return 0;
}

