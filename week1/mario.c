#include <cs50.h>
#include <stdio.h>

void spaces(int n);
void hashtags(int n);

int main(void) {
    int height;

    do {
        height = get_int("Height: ");
    } while(height < 1 || height > 8);

    for (int i = 1; i <= height; i++) {
        spaces(height - i);
        hashtags(i);

        printf("  ");

        hashtags(i);
        spaces(height - i);

        printf("\n");
    }
}

void spaces(int n) {
    for (int i = 0; i < n; i++) {
            printf(" ");
    }
}

void hashtags(int n) {
    for (int j = 0; j < n; j++) {
        printf("#");
    }
}
