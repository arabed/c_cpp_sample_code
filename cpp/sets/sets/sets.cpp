/**
* generate and refine the longest set of ATCGs
* 
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define A_BIT     0x00
#define C_BIT     0x01
#define G_BIT     0x02
#define T_BIT     0x03

// reverse complement
#define A_RC_BIT  0x03
#define C_RC_BIT  0x02
#define G_RC_BIT  0x01
#define T_RC_BIT  0x00

#define C_BIT_MASK 0x5555u
#define G_BIT_MASK 0xAAAAu

#define MAX_NUM_SETS    0xFFFFu

unsigned int set[MAX_NUM_SETS+1];
unsigned int setSize = 0;
unsigned int rsltSet[MAX_NUM_SETS+1];
unsigned int rsltSetSize = 0;

#define _PRINT_DEBUG_
//#undef _PRINT_DEBUG_
/**
* Functions prototype
*/
int countCBits(unsigned int n);
int countGBits(unsigned int n);
int countCGBits(unsigned int n);
int hammingDist(unsigned int n, unsigned int m);
unsigned int reverseRC(unsigned int n);
int bitCount(unsigned int n);
char *int2bin(unsigned int n);
char *int2ATCG(unsigned int n);
int generateSet();
bool validateAgainstRsltSet(unsigned int n);
void printRsltSet(FILE *fh);

/**
* Functions implementation
*/ 
int countCBits(unsigned int n)
{
	int ret = 0;
	int cnt = 8;
	while (cnt>0)
	{
		if ((n & 0x03) == C_BIT)
		{
			ret++;
		}
		n = n >> 2;
		cnt--;
	}
	return ret;
}

int countGBits(unsigned int n)
{
	int ret = 0;
	int cnt = 8;
	while (cnt>0)
	{
		if ((n & 0x03) == G_BIT)
		{
			ret++;
		}
		n = n >> 2;
		cnt--;
	}
	return ret;
}

int countCGBits(unsigned int n)
{
	return countCBits(n) + countGBits(n);
}

int hammingDist(unsigned int n, unsigned int m)
{
	return bitCount(n ^ m);
}

unsigned int reverseRC(unsigned int n)
{
	unsigned int ret = 0x0000;
	unsigned char i;

	for (i=0; i<8; i++)
	{
		ret = ret >> 2;
		ret |= n & 0xC000u;
		n = n << 2;
	}
	// do the reverse complement
	ret = ret ^ 0xFFFFu;

	return ret;
}

int bitCount(unsigned int n)
{    
	n -= ((n >> 1) & 0x55555555);
	n = (n & 0x33333333) + ((n>> 2) & 0x33333333);
	return ((n + (n >> 4) & 0xF0F0F0F) * 0x1010101) >> 24;
}

char *int2bin(unsigned int n)
{
	int cnt = 15;
	char* str = (char *)malloc(17);

	strcpy(str, "0000000000000000");

	while (n > 0)
	{
		if (n%2==1)
		{
			str[cnt] = '1';
		}
		cnt--;
		n = n/2 ;
	}
	return str;   
} 

char *int2ATCG(unsigned int n)
{
	int i;
	char c;
	char* str = (char *)malloc(9);

	strcpy(str, "");

	for (i=0; i<8; i++)
	{
		switch (n & 0x03)
		{
		case A_BIT: strcat(str, "A"); break;
		case T_BIT: strcat(str, "T"); break;
		case C_BIT: strcat(str, "C"); break;
		case G_BIT: strcat(str, "G"); break;
		}
		n = n >> 2;
	}
	return str;
}

int generateSet()
{
	int cnt = 0;
	unsigned int i;
	setSize = 0;

	for (i=0; i<=0xFFFFu; i++)
	{
		if (countCGBits(i) == 4 && hammingDist(i, reverseRC(i)) >= 4)
		{
			set[cnt] = i;
			cnt++;
#if defined(_PRINT_DEBUG_)
			printf("i=%05d cnt=%05d [%s - %s] -> ![%s - %s] Bits:%02d C:%02d G:%02d HammDist:%02d\n", 
				i, cnt, 
				int2bin(i), int2bin(reverseRC(i)),
				int2ATCG(i), int2ATCG(reverseRC(i)),
				bitCount(i),
				countCBits(i), countGBits(i),
				hammingDist(i,reverseRC(i)));
#endif
		}           
	}

	return cnt;
}

int generateRsltSet()
{
	unsigned int ret = 0;
	unsigned int index = 0;
	unsigned int i;

	rsltSetSize = 0;

	index = rand() % setSize;
#if defined(_PRINT_DEBUG_)
	printf("setSize=%05d index=%05d\n", setSize, index);
#endif

	for (i=0; i<setSize; i++)
	{
		if (validateAgainstRsltSet(set[index]))
		{
			rsltSet[ret] = set[index];
			ret++;
			rsltSetSize++;
		}
		index++;
		if (index >= setSize)
		{
			index = 0;
		}
	}

	return ret;
}

bool validateAgainstRsltSet(unsigned int n)
{
	unsigned int i;

	for (i=0; i<rsltSetSize; i++)
	{
		if (n == rsltSet[i] || 
			hammingDist(n, rsltSet[i]) < 4 || 
			hammingDist(n, reverseRC(rsltSet[i])) < 4)
		{
			return false;
		}
	}
	return true;
}

void printRsltSet(FILE *fh)
{
	unsigned int i,j,rslt;
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	if (fh != NULL)
	{
		fprintf(fh, "\n");
		fprintf(fh, "%s\n", asctime(timeinfo));
		fprintf(fh, "----------------\n");
	}
	else
	{
		printf("\n");
		printf("%s\n", asctime(timeinfo));
		printf("----------------\n");
	}

	for (i=0; i<rsltSetSize; i++)
	{
		if (fh != NULL)
		{
			fprintf(fh, "%s\n", int2ATCG(rsltSet[i]));
		}
		else
		{
			printf("%s\n", int2ATCG(rsltSet[i]));
		}
	}
}

int main()
{
	int i;
	int maxRsltSetSize = 0;

	srand((unsigned int)time(NULL));

	printf("Generating the set...\n");
	setSize = generateSet();
	printf("Set size: %d\n", setSize);

	printf("Generating the result set...\n");
	for (i=0; i<100; i++)
	{
		rsltSetSize = generateRsltSet();
		if (rsltSetSize > maxRsltSetSize)
		{
			maxRsltSetSize = rsltSetSize;
			printf("Iter:[%05d] Max result set size: %d\n", i, maxRsltSetSize);
			FILE* fh = fopen("out.txt", "w+");
			printRsltSet(fh);
			fclose(fh);
		}
	}
	printf("\n");
	printRsltSet(NULL);
	printf("done.\n");

	printf("Press any key to continue...\n");
	getch();

	return 0;
}
