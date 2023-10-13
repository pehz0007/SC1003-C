#include <stdio.h>

int main() {
    printf("Enter number of lines:\n");

    int lines;
    scanf("%d", &lines);

    for(int i = 0; i < lines; ++i){
        printf("Enter line %d (end with ‐1):\n", i+1);

        float average = 0;
        int size = 0;

        int value;
        while(scanf("%d[^ ]", &value) && value != -1){
            average = (size * average + value) / (size + 1);
            size++;
        }
        printf("Average = %.2f\n", average);
    }
    return 0;
}
