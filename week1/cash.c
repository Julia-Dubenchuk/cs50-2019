#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void) {
    float cash;
    int count = 0;

    do {
        cash = get_float("Change owed: ");
    } while(cash < 0);

    int coins = round(cash * 100);
    printf("coins: %i\n", coins);
    do {
        if (coins >= 25) {
            coins -= 25;
            count++;
        } else if (coins >= 10) {
            coins -= 10;
            count++;
        } else if (coins >= 5) {
            coins -= 5;
            count++;
        } else {
            coins -= 1;
            count++;
        }

    } while(coins > 0);

    printf("%i\n", count);
}
