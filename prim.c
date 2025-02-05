#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int prim(int n  ){
    int i;
    for(i=2;i<n;i++){
        if (n % i==0){
            return 1;
        }
        else{
        return 0;
        }
    }
}
int main(){
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    if(prim(n)==1){
        printf("Prime\n");
    }
    else{
        printf("Not prime\n");
    }
    return 0;
}