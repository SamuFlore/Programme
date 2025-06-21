/*
    1gram->1gram->1gram
      |      |      |
    2gram  2gram
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 419000
#define max2(a,b) ((a)>(b)?(a):(b))

 int front=0, end=0;
 char *dictionary[MAX];
 int dnum=0;

 //2gram单词
 typedef struct gram
 {
    char *word;
    int correct;
    struct gram *next;
 }gram;

 //1gram单词
 typedef struct voca
 {
    char *word;
    int correct;
    gram *link;
    struct voca *next;
 }voca;

 //错误单词
 typedef struct false
 {
    char *word;
    voca *previous;
    struct false *next;
 }false;

 //修正建议
 typedef struct correction
 {
    int weight;
    char *word;
 }correction;

 correction array[MAX];
 int arraynum=0;

 char* my_strdup(const char* s) {
    if (s == NULL) return NULL;
    size_t len = strlen(s) + 1;
    char* p = (char*)malloc(len);
    if (p) {
        memcpy(p, s, len);
    }
    return p;
 }


 //生成词典
 void readdict(FILE *fp)
 {
    char s[50];
    while(fscanf(fp, "%s", s) != EOF)
    {
        dictionary[dnum] = my_strdup(s);
        dnum++;
    }
 }

 //读入单词
 char *getword(FILE *fp)
 {
    static char word[50];
    int c, i=0;
    //有分隔符情况
    if(end==1)
    {
        front=1;
        end=0;
    }

    while((c=fgetc(fp))!=EOF && !isalpha(c))
    {
        if(c!=' '&& c!='\t')
        {
            front=1;
        }
    }

    if(c==EOF)
     return NULL;

    word[i++] = tolower(c);
    while ((c = fgetc(fp)) != EOF && isalpha(c))
    {
        word[i++] = tolower(c); 
    }
    if(c!=' '&& c!='\t')
    {
        end=1;
    }

    word[i]='\0';
    return word;
 }

 voca *insert1gram(voca **head, const char *word) 
 {
    voca *p, *q=NULL;
    for(p = *head; p != NULL; p = p->next) 
    {
        if(strcmp(p->word, word) == 0) 
        {
            return p;
        }
        q=p;
    }
    
    voca *new=malloc(sizeof(voca));
    new->word=my_strdup(word);
    new->next=NULL;
    new->link=NULL;
    
    if(*head == NULL) 
    {
        *head = new;
    } 
    else 
    {
        q->next = new;
    }
    return new;
}

 void insert2(voca *link, char *word, int correct)
 {
    gram *first=link->link, *p, *q;
    
    if(first==NULL)
    {
        q=(gram *)malloc(sizeof(gram));
        q->next=NULL;
        q->correct=correct;
        q->word = my_strdup(word);
        first=q;
        link->link=first;
    }
    else
    {
        for(p=first;p!=NULL;p=p->next)
        {
            q=p;
            if(strcmp(p->word, word)==0)
             return;
        }
        p=(gram *)malloc(sizeof(gram));
        p->next=NULL;
        p->correct=correct;
        p->word = my_strdup(word);
        q->next=p;
    }
 }

 //生成带错的链表
 false *insertfalse(false *head, char *word, voca *tem)
 {
    false *first=head, *p, *q;    
    if(first==NULL)
    {
        q=(false *)malloc(sizeof(false));
        q->word = my_strdup(word);
        q->next=NULL;
        q->previous=tem;
        first=q;
        return first;
    }
    else
    {
        for(p=first;p!=NULL;p=p->next)
        {
            q=p;
        }
        p=(false *)malloc(sizeof(false));
        p->next=NULL;
        p->word = my_strdup(word);
        p->previous=tem;
        q->next=p;
        return first;
    }
 }

 int searchfalse(false *head, char *word, voca *tem)
 {
    false *p;
    for(p=head;p!=NULL;p=p->next)
    {
        if(strcmp(p->word, word)==0 && p->previous==tem)
         return 1;
    }
    return 0;
 }

 int search(char **dict, const char *word, int size)
 {
    int left=0, right=size-1;
    while(left<=right)
    {
        int mid=left+(right-left)/2;
        int temp=strcmp(dict[mid], word);

        if(temp==0)
         return 1;
        if(temp<0)
         left=mid+1;
        else
         right=mid-1;
    }
    return 0;
 }

 int **Dp, MaxDP=3300;								//for dynamic programming
int min3(int a, int b, int c)
{
    int min = a < b ? a : b;
    return min < c ? min : c;
}
int error2(char *s)
{
    fprintf(stderr,"%s\n",s); 
    exit(-1); 
}
int initDP()
{		
    int i;
    Dp = (int **)malloc(MaxDP*sizeof(int *));
    for(i=0; i<MaxDP; i++)
    Dp[i] = (int *)malloc(MaxDP*sizeof(int));
	return 0;	
}
int editdistDP(char *str1, char *str2) 
{
    int i,j;
    int len1, len2;
    static int flag=0;
	
    (flag++) ? 1 : initDP(); 
    len1 = strlen(str1)+1; len2 = strlen(str2)+1;
    (max2(len1,len2)>=MaxDP) ? error2("DP memory error!") : len1;
    for (i=0; i<=len1; i++) {
        for (j=0; j<=len2; j++) {
            if (i==0)
                Dp[i][j] = j;
            else if (j==0)
                Dp[i][j] = i;
            else if (str1[i-1] == str2[j-1])
                Dp[i][j] = Dp[i-1][j-1];
            else
                Dp[i][j] = 1 + min3(Dp[i][j-1], Dp[i-1][j], Dp[i-1][j-1]);
        }
    }
    return Dp[len1][len2];
}

 void destroy1(voca *head)
 {
    voca *current=head, *t;
    while(current!=NULL)
    {
        t=current;
        current=current->next;

            gram *p=t->link, *q;
            while(p!=NULL)
            {
                q=p;
                p=p->next;
                free(q->word);
                free(q);
            }

        free(t);
    }
 }

 void destroy2(false *head)
 {
    false *p=head, *q;
    while(p!=NULL)
    {
        q=p;
        p=p->next;
        free(q->word);
        free(q);
    }
 }

 void free_all() {
    // 释放字典
    for(int i=0; i<dnum; i++) {
        free(dictionary[i]);
    }
    
    // 释放建议数组
    for(int i=0; i<arraynum; i++) {
        free(array[i].word);
    }
}

 int cmp(const void *pt1 ,const void *pt2)
  {
      correction *f1 = (correction *)pt1;
      correction *f2 = (correction *)pt2;
      /*if(f1->weight > f2->weight)
       return 1;
      else if(f1->weight < f2->weight)
       return -1;
      else*/
       return strcmp(f1->word, f2->word);
  }

 int main()
 {
    FILE *in, *dict;
    FILE *out;
    voca *first=NULL;
    voca *temp1=NULL;
    false *fir=NULL, *current;

    in=fopen("evaluate-in.txt", "r");
    dict=fopen("dict.txt", "r");
    out = fopen("outtext.txt", "w");
    readdict(dict);

    char *word;
    while((word=getword(in))!=NULL)
    {    
        int correct;
        correct=search(dictionary, word, dnum);
        if(temp1==NULL || front==1)
        {
            temp1=insert1gram(&first, word);
            temp1->correct=correct;
            front=0;
        }
        else
        {
            insert2(temp1, word, correct);
            if(correct==0)
            {
                if(temp1->correct==1)
                {
                    if(!searchfalse(fir, word, temp1))
                     fir=insertfalse(fir, word, temp1);
                }
            }
            temp1=insert1gram(&first, word);
            temp1->correct=correct;
        }
    }

    for(current=fir;current!=NULL;current=current->next)
    {
        gram *r=current->previous->link;
        for(;r!=NULL;r=r->next)
        {
            if(r->correct==0)
             continue;
            else
            {
                array[arraynum].word = my_strdup(r->word);
                array[arraynum].weight=editdistDP(current->word, r->word);
                arraynum++;
            }
        }
        fprintf(out, "%s: %s -> ", current->previous->word, current->word);
        // printf("%s: %s -> ", current->previous->word, current->word);
        if(arraynum==0)
        {
            fprintf(out, "No suggestion\n");
            // printf("No suggestion\n");
        }

        else
        {
            int repeat=0, wei=MAX;
            for(int i=0;i<arraynum;i++)
            {
                if(array[i].weight==wei)
                {
                    array[repeat].weight=array[i].weight;
                    free(array[repeat].word);
                    array[repeat].word=my_strdup(array[i].word);
                    repeat++;
                }
                else if(array[i].weight<wei)
                {
                    repeat=0;
                    wei=array[repeat].weight=array[i].weight;
                    free(array[repeat].word);
                    array[repeat].word=my_strdup(array[i].word);
                    repeat++;
                }
            }
            qsort(array, repeat, sizeof(array[0]), cmp);
            for(int i=0;i<repeat;i++)
            {
                if(i==repeat-1)
                fprintf(out, "%s\n", array[i].word);
                //  printf("%s\n", array[i].word);
                else
                fprintf(out, "%s,", array[i].word);
                //  printf("%s,", array[i].word);
            }
            /*qsort(array, arraynum, sizeof(array[0]), cmp);
            int h=0;
            for(int i=0;i<arraynum;i++)
            {
                if(arraynum==1)
                {
                    h=1;break;
                }                
                if(array[i].weight!=array[i+1].weight && i<arraynum-1)
                {
                    h=i+1;
                    break;
                }
                if(array[i-1].weight==array[i].weight && i==arraynum-1)
                {
                    h=i+1;
                    break;
                }
            }
            for(int i=0;i<h;i++)
            {
                if(i==h-1)
                 printf("%s\n", array[i].word);
                else
                 printf("%s,", array[i].word);
            }*/
        }

        // 释放建议内存
        for(int i = 0; i < arraynum; i++)
        {
        free(array[i].word);
        }
        arraynum=0;
    }

    destroy1(first);
    destroy2(fir);
    free_all();

    fclose(in);
    fclose(dict);

    return 0;
 }
