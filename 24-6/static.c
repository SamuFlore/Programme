#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct Words
{
    char word[32];
    int num;
    struct Words *next;
} WD;

WD *head = NULL;

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

int insertNode(WD *prev, char wordin[])
{
    WD *q = (WD *)malloc(sizeof(WD));
    q -> next = NULL;
    strcpy(q -> word, wordin);
    q -> num = 1;
    if (head == NULL)
    {
        head = q;
    }
    else if (head != NULL && prev == NULL)
    {
        q -> next = head;
        head = q;
    }
    else
    {
        q -> next = prev -> next;
        prev -> next = q;
    }
    return 0;
}

int searchWord(char wordin[])
{
    WD *prev = NULL, *cur;
    for (cur = head; cur != NULL; prev = cur, cur = cur -> next)
    {
        if (strcmp(cur -> word, wordin) > 0)
        {
            break;
        }
        else if (strcmp(cur -> word, wordin) == 0)
        {
            cur -> num ++;
            return 0;
        }
    }
    return insertNode(prev, wordin);
    
}


int main()
{
    FILE *in;
    WD *cur = NULL;
    in = fopen("article.txt", "r");
    char word[32];
    while (getWord(in, word) != EOF)
    {
        searchWord(word);
        // printf("%s\n", word);
    }
    for (cur = head; cur != NULL; cur = cur -> next)
    {
        printf("%s %d\n", cur -> word, cur -> num);
    }
    fclose(in);
    return 0;
}