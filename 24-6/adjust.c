#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000

// int main()
// {
//     char str[MAXSIZE];
//     while (gets(str)!= NULL)
//     {
//         printf("%s\n", str);
//     }
// }

typedef struct treenode
{
    int num;
    int isPort;
    int people;
    struct treenode *mid;
    struct treenode *left;
    struct treenode *right;
} Treenode;

int cmp(const void *a, const void *b)
{
    int *p1 = (int *)a;
    int *p2 = (int *)b;
    if (*(p1 + 1) < *(p2 + 1))
    {
        return 1;
    }
    else if (*(p1 + 1) > *(p2 + 1))
    {
        return -1;
    }
    else
    {
        if (*(p1) < *(p2))
        {
            return -1;
        }
        else if (*(p1) > *(p2))
        {
            return 1;
        }
        else
        {
            return 0;
        }   
    }
}

Treenode *pre_order(Treenode *node, int key)
{
    if (node != NULL)
    {
        if (node -> num == key)
            return node; // 找到节点后立即返回
        Treenode *found = pre_order(node -> left, key); // 先遍历左子树
        if (found != NULL)
            return found; // 如果在左子树中找到了节点，立即返回
        found = pre_order(node -> mid, key); // 再遍历中子树
        if (found != NULL)
            return found; // 如果在中子树中找到了节点，立即返回
        return pre_order(node -> right, key); // 最后遍历右子树
    }
    return NULL; // 如果节点为空，返回NULL
}


void layer_order(Treenode *node, int matrix[][2])//层次遍历
{
    int cnt = 0;
    Treenode *nodequeue[MAXSIZE];
    Treenode *p;
    int head, tail;
    if (node != NULL)
    {
        nodequeue[0] = node;
        head = 0;
        tail = 1;
        while (head < tail)
        {
            p = nodequeue[head];
            head ++;//挨个输出node
            if (p -> isPort == 1)
            {
                printf("%d->", matrix[cnt][0]);
                cnt ++;
                printf("%d\n", p -> num);
            }
            if (p -> left != NULL)
                nodequeue[tail ++] = p -> left;//把左子放到数组中
            if (p -> mid != NULL)
                nodequeue[tail ++] = p -> mid;//把左子放到数组中
            if (p -> right != NULL)
                nodequeue[tail ++] = p -> right;
        } 
    }
}

void addNode(int portnum, Treenode *node)
{
    Treenode *tmp_node = (Treenode *)malloc(sizeof(Treenode));
    tmp_node -> num = portnum;
    tmp_node -> left = NULL;
    tmp_node -> right = NULL;
    tmp_node -> mid = NULL;
    if (portnum >= 100)
    {
        tmp_node -> isPort = 0;
    }
    else if (portnum < 100)
    {
        tmp_node -> isPort = 1;
    }
    if (node -> left == NULL)
        node -> left = tmp_node;
    else if (node -> mid == NULL)
        node -> mid = tmp_node;
    else if (node -> right == NULL)
        node -> right = tmp_node;
}

int main()
{
    Treenode *root = NULL;
    int num;
    scanf("%d", &num);
    while(num != -1)
    {
        Treenode *node = NULL;
        if (root == NULL)
        {
            root = (Treenode *)malloc(sizeof(Treenode));
            root -> num = num;
            root -> isPort = 0;
            root -> left = NULL;
            root -> right = NULL;
            root -> mid = NULL;
            node = root;
        }
        else
        {
            node = pre_order(root, num);

        }
        int portnum1;
        while (1)
        {
            scanf("%d", &portnum1);
            if (portnum1 == -1)
                break;
            addNode(portnum1, node);
        }
        
        scanf("%d", &num);
    }
    int matrix[MAXSIZE][2];
    int i = 0;
    for (; ; i ++)
    {
        if(scanf("%d%d", &matrix[i][0], &matrix[i][1]) == EOF)
        {
            break;
        }
    }
    qsort(matrix, i, sizeof(matrix[0]), cmp);
    // for (int j = 0; j < i; j++) 
    // {
    //     printf("%d %d\n", matrix[j][0], matrix[j][1]);
    // }
    layer_order(root, matrix);
    return 0;
}