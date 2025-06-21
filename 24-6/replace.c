#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char origin[1000], new[1000];

    scanf("%s", origin);
    scanf("%s", new);
    int len_o = strlen(origin);


    FILE *in, *out;
    in = fopen("filein.txt", "r");
    out = fopen("fileout.txt", "w");
    char line[1000];
    char lowerline[1000];
    while (fgets(line, 1000, in)!= NULL)
    {
        
        int len = strlen(line);
        for (int i = 0; i < len; i ++)
        {
            lowerline[i] = tolower(line[i]);
        }
        char *ql = lowerline;
        char *q = line;

        while (q < line + len)
        {
            char *pl = strstr(ql, origin);
            char *p = q + (pl - ql);
            if (pl != NULL && pl - ql == 0) 
            {
                fputs(new, out);
                q = p + len_o;
                ql = pl + len_o;
            }
            else
            {
                fputc(*q, out);
                q ++;
                ql ++;
            }
        }
    }
    fclose(in);
    fclose(out);
    return 0;

}