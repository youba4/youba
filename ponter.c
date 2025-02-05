#include <stdio.h>

int main() {
    // Define an array of integers
    int arr[] = {10, 20, 30, 40, 50};
    
    // Declare a pointer to the array
    int *ptr = arr;  // Pointer pointing to the first element of the array

    printf("Array elements using pointer arithmetic:\n");

    // Access and print each element of the array using pointer arithmetic
    printf("First element: %d\n", *ptr);          // Equivalent to arr[0]
    printf("Second element: %d\n", *(ptr + 1));   // Equivalent to arr[1]
    printf("Third element: %d\n", *(ptr + 2));    // Equivalent to arr[2]
    printf("Fourth element: %d\n", *(ptr + 3));   // Equivalent to arr[3]
    printf("Fifth element: %d\n", *(ptr + 4));    // Equivalent to arr[4]

    // Pointer arithmetic to move through the array
    ptr++;  // Move the pointer to the next element (points to arr[1])
    printf("\nAfter ptr++:\n");
    printf("Current element: %d\n", *ptr);  // Now points to arr[1]

    ptr += 2;  // Move the pointer two elements ahead (points to arr[3])
    printf("\nAfter ptr += 2:\n");
    printf("Current element: %d\n", *ptr);  // Now points to arr[3]

    ptr--;  // Move the pointer one element back (points to arr[2])
    printf("\nAfter ptr--:\n");
    printf("Current element: %d\n", *ptr);  // Now points to arr[2]

    // Pointer subtraction (pointer difference)
    int *ptr2 = arr + 4;  // Pointer to arr[4]
    int difference = ptr2 - ptr;  // Difference between two pointers
    printf("\nDifference between ptr2 and ptr: %d\n", difference); // Should print 4

    return 0;
}
