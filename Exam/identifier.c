#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LETTER 1
#define DIGIT 0
#define UNDERLINE 2
#define MAXWORD 36

typedef struct Word
{
    char word[MAXWORD];
    struct Word *next;
} Word;

Word *head = NULL;

int type(int ch)
{
    if (ch >= '0' && ch <= '9') return DIGIT;
    else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) return LETTER;
    else if (ch == '_') return UNDERLINE;
    else return ch;
}

int getWord(char word[])
{
    int ch, t;
    int index = 0;
    if (type(ch = getchar()) != LETTER && type(ch = getchar()) != UNDERLINE)
    {
        word[index] = '\0';
        ungetc(ch, stdin);
        return ch;
    }
    else if (type(ch) == LETTER || type(ch) == DIGIT || type(ch) == UNDERLINE)
    {
        word[index] = ch;
        index ++;
    }
    else if ((ch = getchar()) == EOF)
    {
        return ch;
    }
    while ((ch = getchar()))
    {
        t = type(ch);
        word[index] = ch;
        index ++;
        if (t != LETTER && t != DIGIT && t != UNDERLINE)
        {
            break;
        }
    }
    word[index - 1] = '\0';
    return LETTER;
}

int insertWord(Word *r, char *w)
{
    Word *p = NULL;
    p = (Word *)malloc(sizeof(Word));
    strcpy(p -> word, w);
    p -> next = NULL;
    if (head == NULL)
    {
        head = p;
    }
    else if (r == NULL)
    {
        p -> next = head;
        head = p;
    }
    else
    {
        p -> next = r -> next;
        r -> next = p;
    }
    return 0;
}

int searchWord(char *w)
{
    Word *p, *q = NULL;//q是p前一个
    for (p = head; p != NULL; q = p, p = p -> next)
    {
        if (strcmp(w, p -> word) < 0)
        {
            break;
        }
        if (strcmp(w, p -> word) == 0)
        {
            return 0;
        }
    }
    return insertWord(q, w);
}



int main()
{
    char word[MAXWORD];
    Word *cur;
    int t;
    while ((t = getWord(word)) != EOF)
    {
        if (t == LETTER)
            searchWord(word);
    }
    for (cur = head; cur != NULL; cur = cur -> next)
        printf("%s ", cur -> word);
    return 0;
}