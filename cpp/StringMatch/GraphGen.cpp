/**
 * This class gets a tree structure and translate it to a file 
 * ready to draw as a graph
 */

#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

/**
 * getColor
 */
char* getColor(char c)
{
	switch(c)
	{
		case 'A': return "red";
		case 'T': return "yellow";
		case 'C': return "blue";
		case 'G': return "green";
		default: return "black";
	}
}

/**
 * Print the generated set
 */
void printResultSet()
{
    /*
	char str[128];
	char strTotal[128];
	char strNode[256];
	char strNodeTotal[1024];

	cout << "The generate set:" << endl;
	cout << "Number of strings: " << setResult_num << endl;

	for(int i=0; i<setResult_num; i++)
	{
		strcpy(strTotal, "");
		strcpy(strNodeTotal, "");
		for(int j=0; j<strlen(setResult[i]); j++)
		{
			sprintf(str, "%c%01d", setResult[i][j], j); 
			strcat(strTotal, str);
			sprintf(strNode, "%s [label=\"%c\" shape=point color=%s]\n", strTotal, setResult[i][j], getColor(setResult[i][j]));
			strcat(strNodeTotal, strNode);

			//A [label="A" shape=point color=red];

			cout << strTotal;
			if(j+1 != strlen(setResult[i]))
				cout << " -- ";
		}
		cout << endl;

		cout << strNodeTotal << endl;
	}
    */
}