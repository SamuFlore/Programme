#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *p = NULL;
#define MAXSIZE 32
int char_count = 1;//统计出现的字符种类个数，包括压缩文件结束符NUL

struct tnode {					//Huffman���ṹ
	char c;		
	int weight;					//���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
	// struct tnode *next;
	struct tnode *left,*right;
} ; 

//补充解压缩时huffman树的结点定义
typedef struct huffman_node
{
	char c;
	struct huffman_node *left, *right;
} Huffman;

Huffman *H_root = NULL;//Huffman树根节点初始化为零

int Ccount[128]={0};			//���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ��� 
struct tnode *Root=NULL; 		//Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE]={{0}}; //�ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ�� 
int Step=0;						//ʵ�鲽�� 
FILE *Src, *Obj;
	
void statCount();				//����1��ͳ���ļ����ַ�Ƶ��
void createHTree();				//����2������һ��Huffman�������ڵ�ΪRoot 
void makeHCode();				//����3������Huffman������Huffman����
void atoHZIP(); 				//����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�
void unHZIP();					//解压缩

void print4();					//�������4�Ľ��
/*
hzip.exe filename.txt压缩，2个参数
hzip.exe -u filename.hzip解压，3个参数
*/

int main(int argc, char *argv[])//argc传入的参数个数，argv是传入参数的数组
{
    if (argc == 2)
    {

        if((Src=fopen(argv[1],"r"))==NULL) 
        {
		    fprintf(stderr, "%s open failed!\n", argv[1]);
		    return 1;
	    }
        char outname[1000];
        strcpy(outname, argv[1]);//outname==  filename.txt'\0'
        char *token = strtok(outname, ".");//'\0',  filename'\0'txt'\0'
        strcat(outname, ".hzip");//filename.hzip
	    if((Obj=fopen(outname,"w"))==NULL) 
        {
		    fprintf(stderr, "%s open failed!\n", outname);
		    return 1;
	    }
		statCount();						//ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
	
		createHTree();						//ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
	
		makeHCode();				   		//ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
	
		atoHZIP(); 	//ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���	
    	print4();

    }
	else if (argc == 3 && strcmp(argv[1], "-u") == 0)
	{
		if((Src = fopen(argv[2], "r")) == NULL) 
        {
		    fprintf(stderr, "%s open failed!\n", argv[2]);
		    return 1;
        }
		char outname[1000];
        strcpy(outname, argv[2]);
        char *token = strtok(outname, ".");
        strcat(outname, ".txt");
	    if((Obj = fopen(outname, "w")) == NULL) 
        {
		    fprintf(stderr, "%s open failed!\n", outname);
		    return 1;
	    }

		unHZIP(); 	
	}
	else printf("Usage: hzip.exe [-u] <filename>\n");
	
	// scanf("%d",&Step);					//���뵱ǰʵ�鲽�� 
	
	
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
        if (Ccount[(int)ch] == 1) char_count ++; 
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
    //先输出码表长度
    unsigned char len = (unsigned char)char_count;
    fputc(len, Obj);
    //第一部分：按照字典序，按照格式输出每个字符的ascii，Huffman码长，及Huffman码，三个字节
    for (int i = 0; i < 128; i++) 
    {
        if (Ccount[i] > 0) 
        {
            // 写入ASCII码（1字节）
            fputc(i, Obj);//fputc把一个无符号字符写入stream中，该过程发生隐式类型转换将int的i转换为unsigned char，下同
            
            // 获取Huffman编码及其长度
            const char *code = HCode[i];
            const int code_len = strlen(code);
            
            // 写入编码长度（1字节）
            fputc(code_len, Obj);
            
            // 计算需要的字节数（向上取整）
            const int bytes_needed = (code_len + 7) / 8;
            
            // 将二进制字符串转换为字节序列
            unsigned char *bytes = (unsigned char*)calloc(bytes_needed, 1);//分配内存，并且初始化位0.calloc和malloc的区别在于calloc会把内存全部初始化为0
            for (int j = 0; j < code_len; j++) {
                const int byte_idx = j / 8;//确定正在填充的字节是第几个
                const int bit_pos = 7 - (j % 8); // 高位优先
                bytes[byte_idx] |= (code[j] - '0') << bit_pos;
            }
            
            // 写入编码字节序列
            fwrite(bytes, 1, bytes_needed, Obj);//第一个参数指向要写入的内存的地址，第二个是每个块的字节数，第三个是要写入的块个数，第四个是要被写入的文件指针
            free(bytes);
        }
    }


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

    if (bit_count > 0) 
    {
        fputc(buffer, Obj);// 缓冲区还有剩余数据，由于存储时高位优先，所以已经是有效数字在前，无需左移补零
    }
	
}


void unHZIP()
{
	fseek(Src, 0, SEEK_SET);
	//读取码表长度
	unsigned char len = fgetc(Src);
	//第一部分：按照字典序，按照格式读取每个字符的ascii，Huffman码长，及Huffman码，三部分，构建Huffman树
	H_root = (Huffman *)calloc(1, sizeof(Huffman));//calloc(1, sizeof(Huffman))分配一个Huffman结构体，并初始化为0
	for (int i = 0; i < len; i ++)
	{
		unsigned char ascii = fgetc(Src);
		// printf("%d ", ascii);
		unsigned char code_len = fgetc(Src);
		// printf("%d ", code_len);
		int bytes_needed = (code_len + 7) / 8;
		unsigned char *bytes = (unsigned char *)malloc(bytes_needed);//先将字节读入bytes，再转换成二进制放到huffcode中，此时bytes是一个unsigned char数组
		fread(bytes, 1, bytes_needed, Src);
		char *huffcode = (char *)malloc(code_len + 1);
		
		for (int j = 0; j < code_len; j ++)
		{
			const int byte_idx = j / 8;
			const int bit_pos = 7 - (j % 8);//高位优先
			huffcode[j] = (bytes[byte_idx] >> bit_pos) & 1 ? '1' : '0';//从高到低取出字节里的位，并转换成'0'或'1'放到huffcode中
		}
		huffcode[code_len] = '\0';
		//构建Huffman树
		printf("Char %d (ASCII %d) CODE: %s\n", ascii, ascii, huffcode);
		Huffman *cur = H_root;
		for (int j = 0; j < code_len; j++) 
		{
            if (huffcode[j] == '0') 
			{
                if (!cur->left) cur -> left = (Huffman *)calloc(1, sizeof(Huffman));
                cur = cur -> left;
            } 
			else
			{
                if (!cur->right) cur -> right = (Huffman *)calloc(1, sizeof(Huffman));
                cur = cur -> right;
            }
        }
		cur -> c = ascii;
		// printf("%c ", cur -> c);
		cur -> left = NULL;
		cur -> right = NULL;
		free(bytes);
		free(huffcode);
	}
	//第二部分按照Huffman树解压缩
	unsigned char buffer = 0;
	Huffman *cur = H_root;
	int bit_count = 0;

	while (1)
	{
		if (bit_count % 8 == 0)//读取下一个字节
		{
			int ch = fgetc(Src);
			if (ch == EOF) 
			{
				break;
			}
			buffer = (unsigned char)ch;
			bit_count = 0;
		}

		int bit = (buffer >> (7 - (bit_count % 8))) & 1;//每轮循环，从高到低读一位
		bit_count ++;

		cur = bit ? cur -> right : cur -> left;//1则向右，0则向左

		if (cur -> left == NULL && cur -> right == NULL)
		{
			if (cur -> c == 0) 
			{
				printf("Over\n");
				break;//NUL
			}
			printf("%c", cur -> c);
			fputc(cur -> c, Obj);
			cur = H_root;
		}

	}
	printf("\nDecompress successfully!\n");
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
