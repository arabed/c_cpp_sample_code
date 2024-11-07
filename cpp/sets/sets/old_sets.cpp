/**
 * cics510 Advanced Algorithms - Find the longest string set possible
 * Assignment #10
 * Author: Ara Bedrossian
 * Student#: 68157056
 *
 * This program is computing the longest set of strings using aphabet A,T,C,G to conform
 * a number of defined pre-condiftions. The program uses Native Algorithm to identify the 
 * string set.
 * Example: The following command line will run the program (expect ~20min time to finish the calculation)
 *                
 *     Assignment10
 *                
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
#define MAX_ALL_SET_SIZE 65535

//define the alphabet
char alphabet[4] = {'A', 'T', 'C', 'G'};
char alphabetRC[4] = {'T', 'A', 'G', 'C'};

//All Possible strings
char all_set[MAX_ALL_SET_SIZE][STR_SIZE+1];
int all_set_num = 0;

//Generated string set
char set[MAX_SIZE][STR_SIZE+1];
int set_num = 0;
char setResult[MAX_SIZE][STR_SIZE+1];
int setResult_num = 0;

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
int hamming_distance(char* str1, char* str2)
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
int hamming_distance_rc(char* str1, char* str2)
{
	char str2RC[STR_SIZE+1];

	for(int i=0; i<STR_SIZE+1; i++)
	{
		int index = getIndex(str2[STR_SIZE-i-1]);
		str2RC[i] = alphabetRC[index];
	}
	//cout << "RC: " << str2 << " - " << str2RC << endl;

	return hamming_distance(str1, str2RC);
}

/**
 * Count the nuber of C and G characters in string
 * @param String to count the number of C and Gs
 * @return Returns the total count of C and Gs
 */
int count_GC(char* str1)
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
bool validateStringSet()
{
	for(int i=0; i<set_num; i++)
	{
		if(count_GC(set[i]) != 4)
		{
			cout << "FAILED! Phase1: " << set[i] << endl;
			return false;
		}
		for(int j=0; j<set_num; j++)
		{
			if( i != j && hamming_distance(set[i], set[j]) < 4)
			{
				cout << "FAILED! Phase2: " << set[i] << " - " << set[j] << endl;
				return false;
			}
			if( hamming_distance_rc(set[i], set[j]) < 4)
			{
				cout << "FAILED! Phase3: " << set[i] << " - " << set[j] << endl;
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
bool validateAgainstStringSet(char* str)
{
	if(count_GC(str) != 4)
	{
		//cout << str << endl;
		return false;
	}

	if( hamming_distance_rc(str, str) < 4)
	{
		//cout << str << " - " << set[j] << endl;
		return false;
	}

	for(int j=0; j<set_num; j++)
	{
		if( hamming_distance(str, set[j]) < 4)
		{
			//cout << str << " - " << set[j] << endl;
			return false;
		}
		if( hamming_distance_rc(str, set[j]) < 4)
		{
			//cout << str << " - " << set[j] << endl;
			return false;
		}
	}
	return true;
}
/**
 * Generate all possible combinations of the strings set to conform to required conditions
 * Naive Algorithm
 */
void generateAllPosibleStringSet()
{
	all_set_num = 0;
	char candidate_str[STR_SIZE+1];

	for(int i1=0; i1<ALPHA_SIZE; i1++)
	for(int i2=0; i2<ALPHA_SIZE; i2++)
	for(int i3=0; i3<ALPHA_SIZE; i3++)
	for(int i4=0; i4<ALPHA_SIZE; i4++)
	for(int i5=0; i5<ALPHA_SIZE; i5++)
	for(int i6=0; i6<ALPHA_SIZE; i6++)
	for(int i7=0; i7<ALPHA_SIZE; i7++)
	for(int i8=0; i8<ALPHA_SIZE; i8++)
	{
		candidate_str[0] = alphabet[i1];
		candidate_str[1] = alphabet[i2];
		candidate_str[2] = alphabet[i3];
		candidate_str[3] = alphabet[i4];
		candidate_str[4] = alphabet[i5];
		candidate_str[5] = alphabet[i6];
		candidate_str[6] = alphabet[i7];
		candidate_str[7] = alphabet[i8];
		candidate_str[STR_SIZE] = 0;

		//Add onlt the ones that are passing the initial criteria
		if( count_GC(candidate_str)==4 && hamming_distance_rc(candidate_str,candidate_str)>=4)
		{
			strcpy_s(all_set[all_set_num], candidate_str);
			all_set_num++;
		}
	}
}

/**
 * Copy the generated set to result set
 */
void copyToResultSet()
{
	for(int i=0; i<set_num; i++)
	{
		strcpy_s(setResult[i], set[i]);
	}
	setResult_num = set_num;
}

/**
 * Harvest the strings set to conform to required conditions
 * Naive Algorithm
 */
void harvestStringSet()
{
	int max_set_size = -1; //Try to find the maximum set size
	int counter = 0;
	int index = 0;

	for(int i=0; i<all_set_num; i++)
	{
		//start from this position to see if we can get more string in to the set
		index = i;
		set_num = 0;
		counter = 0;
		
		while(counter<all_set_num)
		{
			if( validateAgainstStringSet(all_set[index]) )
			{
			strcpy_s( set[set_num], all_set[index]);
			set_num++;
			//cout << "Add to set:" << all_set[index] << endl;
			}
			index = (index + 1) % all_set_num;
			counter++;
		}

		//cout << "Iteration: " << i << " completed; the set size: " << set_num << " max size: " << max_set_size << endl; 
		cout << "."; 

		if(set_num > max_set_size)
		{
			copyToResultSet();
			max_set_size = set_num;
			cout << endl; 
			cout << "Iteration: " << i << " maximum string set size: " << max_set_size << endl; 
		}
	}
	
	cout << endl; 
	if( validateStringSet() )
		cout << "Set passed." << endl; 
	else
		cout << "Set failed." << endl; 
}

/**
 * Print the generated set
 */
void printResultSet()
{
	cout << "The generate set:" << endl;
	cout << "Number of strings: " << setResult_num << endl;
	for(int i=0; i<setResult_num; i++)
	{
		cout << setResult[i] << endl;
	}
}

/**
 * Main entry point for this program
 * The input arguments shall ignored
 * @return negative if an error happened
 */
int mainXXX(int argc, char* argv[])
{
	//record elapsed time 
	clock_t start, finish;
	
	//Record the starting time
	start = clock();
	
	//reset the generated set number to 0
	int set_num = 0;
	int setResult_num = 0;
	
	//generate all possible strings
	generateAllPosibleStringSet();
	cout << "Number of possible generated strings: " << all_set_num << endl;

	//harvest the longest string set
	harvestStringSet();

	//record the finish time
	finish = clock();
	
	//print the result set
	printResultSet();
	
	double duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf( "%2.1f seconds\n", duration );

	return 0;
}
