#include<stdio.h>

int powre(int x, int y) {
     for(int i = 0; i < y; i++) {
         x *= x;
     }
        return x;

}

int main() {
    int x, y;
    printf("Enter powre and number: ");
    scanf("%d %d", &x, &y);
    printf("Powre: %d\n", powre(x, y));
    return 0;
}