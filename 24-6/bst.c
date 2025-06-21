#include <stdio.h>
#include <stdlib.h>

typedef struct treenode
{
    int data;
    struct treenode *left;
    struct treenode *right;
} Treenode;

Treenode *initBST(Treenode *root, int data)//初始化二叉查找树
{
    Treenode *p;
    if (root == NULL)
    {
        p = (Treenode *)malloc(sizeof(Treenode));
        p -> data = data;
        p -> left = NULL;
        p -> right = NULL;
        return p;
    }
    else if (data < root -> data)//左子小于根
    {
        root -> left = initBST(root -> left, data);//
    }
    else//右子大于根
    {
        root -> right = initBST(root -> right, data);
    }
    return root;
}

void pre_order(Treenode *node, int height)//前序遍历
{
    if (node == NULL)
        return ;
    if (node -> left == NULL && node -> right == NULL)
        printf("%d %d\n", node -> data, height);
    pre_order(node -> left, height + 1);
    pre_order(node -> right, height + 1);
}

int main()
{
    Treenode *root = NULL;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
    {
        int num;
        scanf("%d", &num);
        root = initBST(root, num);
    }
    pre_order(root, 1);
    return 0;
}