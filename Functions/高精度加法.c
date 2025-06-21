#include<stdio.h>
#include<string.h>
char s[40000];
char a[20000];
char b[20000];
int w[40000];
char sum[40000];
int main()
{
	gets(s);
	int l=strlen(s);
	int t=0;
	int m=0;
	for(int i=0;i<l;i++)
	{
		if(s[i]!='+')
		{
			a[t]=s[i];
			t++;
		}
		else
		{
			t=i;
			break;
		}
	}
	for(int i=t+1;i<l;i++)
	{
		if(s[i]!='=')
		{
			b[m]=s[i];
			m++;
		}
	}
	int la=strlen(a);
	int lb=strlen(b);
	int k;
	if(la>lb)
	{
		for(int i=0;i<lb;i++)
		{
			w[i]+=b[lb-1-i]-'0'+a[la-1-i]-'0';
			if(w[i]>=10)
			{
				w[i+1]++;
				w[i]-=10;
			}
		}
		for(int i=lb;i<la;i++)
		{
			w[i]+=a[la-1-i]-'0';
			if(w[i]>=10)
			{
				w[i+1]++;
				w[i]-=10;
			}
		}
		if(w[la]==0)
		k=la-1;
		else
		k=la;
	}
	else if(lb>la)
	{
		for(int i=0;i<la;i++)
		{
			w[i]+=b[lb-1-i]-'0'+a[la-1-i]-'0';
			if(w[i]>=10)
			{
				w[i+1]++;
				w[i]-=10;
			}
		}
		for(int i=la;i<lb;i++)
		{
			w[i]+=b[lb-1-i]-'0';
			if(w[i]>=10)
			{
				w[i+1]++;
				w[i]-=10;
			}
		}
		if(w[lb]==0)
		k=lb-1;
		else
		k=lb;
	}
	else
	{
		for(int i=0;i<la;i++)
		{
			w[i]+=b[lb-1-i]-'0'+a[la-1-i]-'0';
			if(w[i]>=10)
			{
				w[i+1]++;
				w[i]-=10;
			}
		}
		if(w[lb]==0)
		k=lb-1;
		else
		k=lb;
	}
	for(int i=0;i<=k;i++)
	{
		sum[i]='0'+w[k-i];
	}
	puts(sum);
	return 0;
}