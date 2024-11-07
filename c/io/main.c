#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main()
{
    int i;
    float f;
    char c;

    scanf( "%d", &i );
    printf( "i:%d\n", i );
    scanf( "%f", &f );
    printf( "f:%f\n", f );
    scanf( "%c", &c );
    printf( "c:%c\n", c );

    char str[50];
    // Input the Word
    printf("Enter the Word: ");
    scanf("%s\n", str);
    printf("Word:%s\n", str);
    // Input the Sentence
    printf("\n\nEnter the Sentence: ");
    scanf("%[^\n]s", str);
   printf("Sentence:%s\n", str);
 
    return 0;
}