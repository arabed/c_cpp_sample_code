/**
 * This program is computing the longest set of strings using aphabet A,T,C,G to conform
 * a number of defined pre-condiftions. The program uses Native Algorithm to identify the 
 * string set.
 * The new variation in strating with a given set and try to insert the number in, it will 
 * record the number of rejection done by already existing sets and it will eliminate them 
 * from the series.
 */

#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

//define constants
#define MAX_SIZE 255
#define STR_SIZE 8
#define ALPHA_SIZE 4
#define MAX_SET_SIZE 65535

//define the alphabet
char alphabet[ALPHA_SIZE] = {'A', 'T', 'C', 'G'};
char alphabetRC[ALPHA_SIZE] = {'T', 'A', 'G', 'C'};

//Define the DNAString type
typedef struct
{
	char str[STR_SIZE+1];
} DNAString;

//Functions declaration and implementation
/**
 * Return index of the alphabet
 * @param the char in alphabet
 * @return Returns the position of the character in the set, 
 *         retunrs -1 if couldn't found
 */
int getIndex(char ch)
{
	for(int i=0; i<ALPHA_SIZE; i++)
		if(alphabet[i]==ch)
			return i;

	return -1;
}

/**
 * Calculate the hamming distance between two fixed size strings
 * @param First string to compare
 * @param Second string to compare
 * @return Returns the calculated value between two strings
 */
int HammingDistance(char* str1, char* str2)
{	
	int cnt = 0;

	for(int i=0; i<STR_SIZE; i++)
		if(str1[i] != str2[i])
			cnt++;

	return cnt;
}

/**
 * Calculate the hamming distance between two fixed size strings
 * while the second string will trun to reverse complement before
 * the comparison
 * @param First string to compare
 * @param Second string to compare (will trun to RC)
 * @return Returns the calculated value between two strings
 */
int HammingDistanceRC(char* str1, char* str2)
{
	char str2RC[STR_SIZE+1];

	for(int i=0; i<STR_SIZE+1; i++)
	{
		int index = getIndex(str2[STR_SIZE-i-1]);
		str2RC[i] = alphabetRC[index];
	}

	return HammingDistance(str1, str2RC);
}

/**
 * Count the number of C and G characters in string
 * @param String to count the number of C and Gs
 * @return Returns the total count of C and Gs
 */
int CountGC(char* str1)
{
	int cnt = 0;

	for(int i=0; i<STR_SIZE; i++)
		if(str1[i] == 'C' || str1[i] == 'G')
			cnt++;
	
	return cnt;
}

/**
 * Validate the generated string so far
 * @return Returns true if string set passed the validation test
 */
bool ValidateStringSet(DNAString aDNAString[], int aSize)
{
	for(int i=0; i<aSize; i++)
	{
		if(CountGC(aDNAString[i].str) != 4)
		{
			cout << "FAILED! Phase1: " << aDNAString[i].str << endl;
			return false;
		}
		for(int j=0; j<aSize; j++)
		{
			if( i != j && HammingDistance(aDNAString[i].str, aDNAString[j].str) < 4)
			{
				cout << "FAILED! Phase2: " << aDNAString[i].str << " - " << aDNAString[j].str << endl;
				return false;
			}
			if( HammingDistanceRC(aDNAString[i].str, aDNAString[j].str) < 4)
			{
				cout << "FAILED! Phase3: " << aDNAString[i].str << " - " << aDNAString[j].str << endl;
				return false;
			}
		}
	}

	return true;
}

/**
 * Validate the new generated string against the string set
 * @return Returns true if string set passed the validation test
 */
bool ValidateAgainstStringSet(char* str, DNAString aDNAString[], int aSize)
{
	if(CountGC(str) != 4)
	{
		//cout << str << endl;
		return false;
	}

	if( HammingDistanceRC(str, str) < 4)
	{
		//cout << str << " - " << aDNAString[i]->str << endl;
		return false;
	}

	for(int i=0; i<aSize; i++)
	{
		if( HammingDistance(str, aDNAString[i].str) < 4)
		{
			//cout << str << " - " << aDNAString[i].str << endl;
			return false;
		}
		if( HammingDistanceRC(str, aDNAString[i].str) < 4)
		{
			//cout << str << " - " << aDNAString[i].str << endl;
			return false;
		}
	}

	return true;
}

/**
 * Generate all possible combinations of the strings set to conform to required conditions
 * Naive Algorithm
 */
int GenerateSet(DNAString aDNAString[])
{
	int cnt = 0;
	char candidateStr[STR_SIZE+1];

	for(int i1=0; i1<ALPHA_SIZE; i1++)
	for(int i2=0; i2<ALPHA_SIZE; i2++)
	for(int i3=0; i3<ALPHA_SIZE; i3++)
	for(int i4=0; i4<ALPHA_SIZE; i4++)
	for(int i5=0; i5<ALPHA_SIZE; i5++)
	for(int i6=0; i6<ALPHA_SIZE; i6++)
	for(int i7=0; i7<ALPHA_SIZE; i7++)
	for(int i8=0; i8<ALPHA_SIZE; i8++)
	{
		candidateStr[0] = alphabet[i1];
		candidateStr[1] = alphabet[i2];
		candidateStr[2] = alphabet[i3];
		candidateStr[3] = alphabet[i4];
		candidateStr[4] = alphabet[i5];
		candidateStr[5] = alphabet[i6];
		candidateStr[6] = alphabet[i7];
		candidateStr[7] = alphabet[i8];
		candidateStr[STR_SIZE] = 0;

		//Add onlt the ones that are passing the initial criteria
		if( CountGC(candidateStr)==4 && HammingDistanceRC(candidateStr,candidateStr)>=4)
		{
			strcpy_s(aDNAString[cnt].str, candidateStr);
			cnt++;
		}
	}

    return cnt;
}

/**
 * Harvest the strings set to conform to required conditions
 * Naive Algorithm
 */
int HarvestStringSet(DNAString aDNAString[], DNAString aResultDNAString[], int aSize)
{
	int maxSetSize = -1; //Try to find the maximum set size
	int maxSetSizeSeed = -1; //Try to find the maximum set size seed
	int maxSetSizeHop = -1; //Try to find the maximum set size seed
    int resultSetSize = 0;
	int counter = 0;
	int index = 0;

	// Seed the random-number generator with current time so that
	// the numbers will be different every time we run.
	//
	srand( (unsigned)time( NULL ) );

	for(int j=1; j<=100; j++)
	{
	for(int i=0; i<aSize; i++)
	{
		//start from this position to see if we can get more string in to the set
		counter = 0;
        resultSetSize = 0;
        index = i;
		maxSetSizeSeed = rand();
        maxSetSizeHop = j;

		while(counter<aSize)
		{
			if( ValidateAgainstStringSet(aDNAString[index].str, aResultDNAString, resultSetSize) )
			{
    			strcpy_s( aResultDNAString[resultSetSize].str, aDNAString[index].str);
	    		resultSetSize++;
		    	//cout << "Add to set:" << aDNAString[index].str << endl;
			}
			index = (index + maxSetSizeHop) % aSize;
			counter++;
		}

		//cout << "Iteration: " << i << " completed; the set size: " << resultSetSize << " max size: " << maxSetSize << endl; 
		//cout << "."; 

		if(resultSetSize > maxSetSize)
		{
			//CopyToResultSet();
			maxSetSize = resultSetSize;
			cout << "Iteration: " << i << " maximum index/size/seed/hop: "
                << i << "/" << maxSetSize << "/" << maxSetSizeSeed << "/" << maxSetSizeHop << endl; 
            
            if( maxSetSize > 150) break;
		}
	}
    }
	
	cout << endl; 
	if( ValidateStringSet(aResultDNAString, resultSetSize) )
		cout << "Set passed." << endl; 
	else
		cout << "Set failed." << endl; 

    return resultSetSize;
}

/**
 * Main entry point for this program
 * The input arguments shall ignored
 * @return negative if an error happened
 */
int main(int argc, char* argv[])
{
	//record elapsed time 
	clock_t start, finish;
	
	//Record the starting time
	start = clock();
	
	//reset the generated set number to 0
	int set_num = 0;
	int setResult_num = 0;
	
	//generate all possible strings
    DNAString allSet[MAX_SET_SIZE/2];
    int cnt = GenerateSet(allSet);
	cout << "Number of possible generated strings: " << cnt << endl;

	//harvest the longest string set
    DNAString resultSet[500];
	cnt = HarvestStringSet(allSet, resultSet, cnt);
	cout << "The max string: " << cnt << endl;

	//record the finish time
	finish = clock();
	
	double duration = (double)(finish - start) /*/ CLOCKS_PER_SEC*/;
	printf( "%2.1f seconds\n", duration );

	return 0;
}

