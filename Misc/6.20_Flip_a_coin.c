#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CoinFlip(char* decisionString) {
    char heads[] = {"Heads"};
    char tails[] = {"Tails"};

    int coinFlip = rand() % 2;

    if(coinFlip == 1) {
        for(int i = 0; i < strlen(decisionString); i++) {
            decisionString[i] = heads[i];
        }
    }
    if(coinFlip == 0) {
        for(int i = 0; i < strlen(decisionString); i++) {
            decisionString[i] = tails[i];
        }
    }
}

int main(void) {
    int numOfFlips;
    char decisionString[] = {"Heads"};

    srand(2);

    scanf("%d", &numOfFlips);

    for(int i = 0; i < numOfFlips; i++) {
        CoinFlip(decisionString);
        printf("%s\n", decisionString);
    }

    return 0;
}
