#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000

int NUMtop = -1;
int OPtop = -1;


void pushNUM(double stackN[], double data)
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

double popNUM(double stackN[])
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

void cal(double stackN[], char op)
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
            double tmp = popNUM(stackN);
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
            double tmp = popNUM(stackN);
            pushNUM(stackN, popNUM(stackN) / tmp);
            break;
        }
    }
}

int main()
{
    double stackN[MAXSIZE];
    char stackO[MAXSIZE];
    char ch;
    double n;
    while((ch = getchar()) != '=')
    {
        if (ch >= '0' && ch <= '9')
        {
            for (n = 0; ch >= '0' && ch <= '9'; ch = getchar())
            {
                n = n * 10 + ch - '0';
            }
            pushNUM(stackN, n);
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
                        cal(stackN, op);
                    }
                    break;
                }
                case '+':
                {
                    while (stackO[OPtop] == '*' || stackO[OPtop] == '/' || stackO[OPtop] == '+' || stackO[OPtop] == '-')
                    {
                        cal(stackN, popOP(stackO));
                    }
                    pushOP(stackO, ch);
                    break;
                }
                case '-':
                {
                    while (stackO[OPtop] == '*' || stackO[OPtop] == '/' || stackO[OPtop] == '+' || stackO[OPtop] == '-')
                    {
                        cal(stackN, popOP(stackO));
                    }
                    pushOP(stackO, ch);
                    break;
                }
                case '*':
                {
                    while (stackO[OPtop] == '*' || stackO[OPtop] == '/')
                    {
                        cal(stackN, popOP(stackO));
                    }
                    pushOP(stackO, ch);
                    break;
                }
                case '/':
                {
                    while (stackO[OPtop] == '*' || stackO[OPtop] == '/')
                    {
                        cal(stackN, popOP(stackO));
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
        cal(stackN, popOP(stackO));
    }
    printf("%.2f\n", popNUM(stackN));
}