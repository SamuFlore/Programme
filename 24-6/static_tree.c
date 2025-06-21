#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct treenode
{
    int times;
    char word[100];
    struct treenode *left;
    struct treenode *right;
} Treenode;




int type(int ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

int getWord(FILE *in, char word[])
{
    int ch, cnt = 0;
    while (type(ch = fgetc(in)) == -1)
    {
        if (ch == EOF)
        {
            return ch;
        }
        else
        {
            continue;
        }
    }
    do
    {
        word[cnt] = tolower(ch);
        cnt ++;
    
    } while (type(ch = fgetc(in)) == 1);
    word[cnt] = '\0';
    return 1;
}

Treenode *insertBST(Treenode *node, char word[])//将数据插入入口为node的二叉查找树中
{
    if (node == NULL)
    {
        node = (Treenode *)malloc(sizeof(Treenode));
        strcpy(node -> word, word);
        node -> times = 1;
        node -> left = NULL;
        node -> right = NULL;
    }
    else if (strcmp(word, node -> word) < 0)
        node -> left = insertBST(node -> left, word);//数据比本结点小，则将数据存在本结点的左子，下同理
    else if (strcmp(word, node -> word) > 0)
        node -> right = insertBST(node -> right, word);
    else //找到相同的元素
        node -> times ++;
    //替换，或是别的操作
    return node;
}

void pre_order(Treenode *node)//访问根节点->遍历左子树->遍历右子树
{
    if (node == NULL)
        return;
    
    pre_order(node -> left);
    printf("%s %d\n", node -> word, node -> times);
    pre_order(node -> right);
}

int main()
{
    FILE *in = fopen("article.txt", "r");
    char word[100];
    Treenode *root = NULL;
    while (getWord(in, word) != EOF)
    {
        // printf("%s\n", word);
        root = insertBST(root, word);
    }
    fclose(in);
    printf("%s ", root -> word);
    if (root -> right != NULL) printf("%s ", root -> right -> word);
    if (root -> right -> right != NULL) printf("%s ", root -> right -> right -> word);
    printf("\n");
    pre_order(root);

    return 0;
}