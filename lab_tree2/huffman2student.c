//�ļ�ѹ��-Huffmanʵ��
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *p = NULL;
#define MAXSIZE 32

struct tnode {					//Huffman���ṹ
	char c;		
	int weight;					//���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
	// struct tnode *next;
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ��� 
struct tnode *Root=NULL; 		//Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE]={{0}}; //�ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ�� 
int Step=0;						//ʵ�鲽�� 
FILE *Src, *Obj;
	
void statCount();				//����1��ͳ���ļ����ַ�Ƶ��
void createHTree();				//����2������һ��Huffman�������ڵ�ΪRoot 
void makeHCode();				//����3������Huffman������Huffman����
void atoHZIP(); 				//����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�

void print1();					//�������1�Ľ��
void print2(struct tnode *p);	//�������2�Ľ�� 
void print3();					//�������3�Ľ��
void print4();					//�������4�Ľ��

int main()
{
	if((Src=fopen("input.txt","r"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);					//���뵱ǰʵ�鲽�� 
	
	statCount();						//ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
	if(Step==1) 
		print1(); 			//���ʵ�鲽��1���	
	createHTree();						//ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
	if(Step==2) 
		print2(Root); 		//���ʵ�鲽��2���	
	makeHCode();				   		//ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
	if(Step==3) 
		print3(); 			//���ʵ�鲽��3���
	if(Step>=4) 
		atoHZIP(),print4(); 	//ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//��ʵ�鲽��1����ʼ 

void statCount()
{
	Ccount[0] = 1; //NUL�ַ����ִ���Ϊ1 
	char ch;
	while ((ch = fgetc(Src)) != EOF)
	{
		Ccount[(int)ch]++;
	}
}

//��ʵ�鲽��1������

//��ʵ�鲽��2����ʼ

int cmp(const void *a, const void *b) 
{
    const struct tnode *nodeA = *(const struct tnode **)a;
    const struct tnode *nodeB = *(const struct tnode **)b;

    if (nodeA -> weight > nodeB -> weight) 
	{
        return 1;//����
    } 
	else if (nodeA -> weight < nodeB -> weight) 
	{
        return -1;//������
    } 
	else 
	{
        if (nodeA -> c > nodeB -> c) 
		{
            return 1;
        } 
		else if (nodeA -> c < nodeB -> c) 
		{
            return -1;
        } 
		else 
		{
            return 0;
        }
    }
}


void createHTree()
{
	int cnt = 0;
	struct tnode *list[128];
	for (int i = 0; i < 128; i ++)
	{
		if(Ccount[i] > 0)
		{
			list[cnt] = (struct tnode *)malloc(sizeof(struct tnode));
			list[cnt] -> c = i;
            list[cnt] -> weight = Ccount[i];
            list[cnt] -> left = NULL;
            list[cnt] -> right = NULL;
            cnt ++;
		}
	}

	qsort(list, cnt, sizeof(struct tnode *), cmp);

	while (cnt > 1)//cnt�ǽṹ��ָ�������Ԫ�ظ���
	{
		struct tnode *tmp_root = (struct tnode *)malloc(sizeof(struct tnode));
		tmp_root -> weight = 0;
		tmp_root -> left = list[0];
		tmp_root -> right = list[1];
		tmp_root -> weight = list[0] -> weight + list[1] -> weight;
		for (int i = 2; i < cnt; i ++)
		{
			list[i - 2] = list[i];
		}
		cnt = cnt - 2;
		int i;
		for (i = 0; i < cnt; i ++)
		{
			if (list[i] -> weight > tmp_root -> weight)
			{
				break;
			}
		}
		for (int j = cnt; j > i; j --)
		{
			list[j] = list[j - 1];
		}
		list[i] = tmp_root;
		cnt ++;
	}
	Root = list[0];
}

//��ʵ�鲽��2������

//��ʵ�鲽��3����ʼ

char HuffmanCode[MAXSIZE] = {0};

void pre_order(struct tnode *node, char code, int level)//���ʸ��ڵ�->����������->����������
{
    if (level > 1)
	{
		HuffmanCode[level - 2] = code;
	}
	if (node -> left == NULL && node -> right == NULL)//Ҷ�ڵ�
	{
		HuffmanCode[level - 1] = '\0';
		strcpy(HCode[(int)node -> c], HuffmanCode);
	}
	else
	{
		pre_order(node -> left, '0', level + 1);
		pre_order(node -> right, '1', level + 1);
	}
}

void makeHCode()
{
	pre_order(Root, '0', 1);
} 

//��ʵ�鲽��3������

//��ʵ�鲽��4����ʼ



void atoHZIP()
{
	unsigned char buffer = 0;  // 位缓冲
    int bit_count = 0;         // 当前缓冲位数
	fseek(Src, 0, SEEK_SET);//光标移动到文件头
	char ch;
	while ((ch = fgetc(Src)) != EOF)
	{
		const char *code = HCode[(int)ch];
        const int code_len = strlen(code);
        
        // 逐位填充缓冲区
        for (int i = 0; i < code_len; i++) 
        {
            buffer |= (code[i] - '0') << (7 - bit_count);
            bit_count++;
            
            // 缓冲区满时写入文件
            if (bit_count == 8) 
            {
                fputc(buffer, Obj);
                buffer = 0;
                bit_count = 0;
            }
        }
    }

    // 处理结束符NUL（ASCII 0）
    const char *end_code = HCode[0];
    const int end_len = strlen(end_code);
    for (int i = 0; i < end_len; i++) 
    {
        buffer |= (end_code[i] - '0') << (7 - bit_count);
        bit_count++;
        if (bit_count == 8) 
        {
            fputc(buffer, Obj);
            buffer = 0;
            bit_count = 0;
        }
    }

    if (bit_count > 0) // 缓冲区还有剩余数据，由于存储时高位优先，所以已经是有效数字在前，无需左移补零
    {
        fputc(buffer, Obj);
    }
	
}
//��ʵ�鲽��4������

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

void print4()
{
	long int in_size, out_size;
	
	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);
	
	printf("\nSize of input file: %ldB\n",in_size);
	printf("After compression, size of output file: %ldB\n",out_size);
	printf("Compression rate: %.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
