#include <stdio.h>
#include <stdlib.h>

void swap_numbers(int *a,int  *b) {
    printf("bfore change:\n");
    printf("number one :%d\n", *a);
    printf("number tow:%d\n", *b);
    *a = *a + *b ;
    *b = *a - *b ;
    *a = *a - *b ;
    printf(" after change:\n");
   printf("number one :%d\n", *a);
    printf("number tow:%d\n", *b);
}
int main() {
 int a , b ;
    printf("enter the first number:\n");
    scanf("%d", &a);
    printf("enter the second number:\n");
    scanf("%d", &b);

   swap_numbers(&a , &b);
    return 0;
}