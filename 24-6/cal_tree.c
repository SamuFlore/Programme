#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000

int NUMtop = -1;
int OPtop = -1;
int TREEtop = -1;

typedef struct treenode
{
    int isOP;
    int data;
    struct treenode *left;
    struct treenode *right;
} Treenode;

void pushNUM(int stackN[], int data)
{
    if(NUMtop == MAXSIZE - 1)
    {
        exit(1);
    }
    else
    {
        NUMtop ++;
        stackN[NUMtop] = data;
    }
}

void pushOP(char stack[], char data)
{
    if(OPtop == MAXSIZE - 1)
    {
        exit(1);
    }
    else
    {
        OPtop ++;
        stack[OPtop] = data;
    }
}

void pushPtr(Treenode *stackPtr[], Treenode *node)
{
    if (TREEtop == MAXSIZE - 1)
    {
        exit(1);
    }
    else
    {
        TREEtop ++;
        stackPtr[TREEtop] = node;
    }
}

Treenode *popPtr(Treenode *stackPtr[])
{
    if (TREEtop == -1) exit(1);
    else
    {
        return stackPtr[TREEtop --];
    }
}

int popNUM(int stackN[])
{
    if (NUMtop == -1)
    {
        exit(1);
    }
    else
    {
        return stackN[NUMtop --];
    }
}

char popOP(char stack[])
{
    if (OPtop == -1)
    {
        exit(1);
    }
    else
    {
        return stack[OPtop --];
    }
}

void cal(int stackN[], char op)
{
    switch(op)
    {
        case '+':
        {
            pushNUM(stackN, popNUM(stackN) + popNUM(stackN));
            break;
        }
        case '-':
        {
            int tmp = popNUM(stackN);
            pushNUM(stackN, popNUM(stackN) - tmp);
            break;
        }
        case '*':
        {
            pushNUM(stackN, popNUM(stackN) * popNUM(stackN));
            break;
        }
        case '/':
        {
            int tmp = popNUM(stackN);
            pushNUM(stackN, popNUM(stackN) / tmp);
            break;
        }
    }
}

void printer(Treenode *node)
{
    if (node != NULL)
    {
        if (node -> isOP)
            printf("%c ", node -> data);
        else
            printf("%d ", node -> data);
    }
}

int main()
{
    int stackN[MAXSIZE];
    char stackO[MAXSIZE];
    Treenode *stackPtr[MAXSIZE];
    Treenode rev_poland[MAXSIZE];
    int rev_index = 0;
    char ch;
    int n;
    while((ch = getchar()) != '=')
    {
        if (ch >= '0' && ch <= '9')
        {
            for (n = 0; ch >= '0' && ch <= '9'; ch = getchar())
            {
                n = n * 10 + ch - '0';
            }
            pushNUM(stackN, n);
            rev_poland[rev_index].isOP = 0;
            rev_poland[rev_index].data = n;
            rev_index ++;
            ungetc(ch, stdin);
        }
        else
        {
            char op;
            switch(ch)
            {
                case ')':
                {
                    while ((op = popOP(stackO)) != '(')
                    {
                        rev_poland[rev_index].isOP = 1;
                        rev_poland[rev_index].data = op;
                        rev_index ++;
                        cal(stackN, op);
                    }
                    break;
                }
                case '+':
                {
                    while (stackO[OPtop] == '*' || stackO[OPtop] == '/' || stackO[OPtop] == '+' || stackO[OPtop] == '-')
                    {
                        char optmp = popOP(stackO);
                        rev_poland[rev_index].isOP = 1;
                        rev_poland[rev_index].data = optmp;
                        rev_index ++;
                        cal(stackN, optmp);
                    }
                    pushOP(stackO, ch);
                    break;
                }
                case '-':
                {
                    while (stackO[OPtop] == '*' || stackO[OPtop] == '/' || stackO[OPtop] == '+' || stackO[OPtop] == '-')
                    {
                        char optmp = popOP(stackO);
                        rev_poland[rev_index].isOP = 1;
                        rev_poland[rev_index].data = optmp;
                        rev_index ++;
                        cal(stackN, optmp);
                    }
                    pushOP(stackO, ch);
                    break;
                }
                case '*':
                {
                    while (stackO[OPtop] == '*' || stackO[OPtop] == '/')
                    {
                        char optmp = popOP(stackO);
                        rev_poland[rev_index].isOP = 1;
                        rev_poland[rev_index].data = optmp;
                        rev_index ++;
                        cal(stackN, optmp);
                    }
                    pushOP(stackO, ch);
                    break;
                }
                case '/':
                {
                    while (stackO[OPtop] == '*' || stackO[OPtop] == '/')
                    {
                        char optmp = popOP(stackO);
                        rev_poland[rev_index].isOP = 1;
                        rev_poland[rev_index].data = optmp;
                        rev_index ++;
                        cal(stackN, optmp);
                    }
                    pushOP(stackO, ch);
                    break;
                }
                case '(':
                {
                    pushOP(stackO, ch);
                    break;
                }
            }
        }
    }

    while (OPtop >= 0)
    {
        char optmp = popOP(stackO);
        rev_poland[rev_index].isOP = 1;
        rev_poland[rev_index].data = optmp;
        rev_index ++;
        cal(stackN, optmp);
    }
    for (int i = 0; i < rev_index; i ++)
    {
        if (rev_poland[i].isOP == 0)
        {
            Treenode *node = (Treenode *)malloc(sizeof(Treenode));
            node -> isOP = 0;
            node -> data = rev_poland[i].data;
            node -> left = NULL;
            node -> right = NULL;
            pushPtr(stackPtr, node);
        }
        else
        {
            Treenode *node = (Treenode *)malloc(sizeof(Treenode));
            node -> isOP = 1;
            node -> data = rev_poland[i].data;
            node -> right = popPtr(stackPtr);
            node -> left = popPtr(stackPtr); 
            pushPtr(stackPtr, node);
        }
    }
    Treenode *root = popPtr(stackPtr);
    printer(root);
    printer(root -> left);
    printer(root -> right);
    printf("\n");
    printf("%d\n", popNUM(stackN));
}