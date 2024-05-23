
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct GameArea {
    int playerCount;
    int areaSize;
    int roundCount;
};

void randomPlayerPositions(int playerCount, int areaSize, int matris[][areaSize]) {
    srand(time(NULL));

    for (int i = 0; i < areaSize; i++) {
        for (int j = 0; j < areaSize; j++) {
            matris[i][j] = 0;
        }
    }

    printf("Coordinates of the players are chosen randomly\n");
    for (int i = 1; i <= playerCount; i++) {
        int x, y;

        do {
            x = rand() % areaSize;
            y = rand() % areaSize;
        } while (matris[x][y] != 0);

        matris[x][y] = i;
        if(i > 1) {
            printf(" ");
        }
        printf("player%d: [%d,%d]", i, x, y);
        if(i < playerCount) {
            printf(" ,");
        }
    }
    printf("\n");
}

void printBorders(int areaSize) {
    for(int i=0; i<areaSize+2; i++) {
        printf(" -");
    }
    printf("\n");
}

void printMatrices(int areaSize, int playersLoc[][areaSize]) {
    for(int i=0; i<areaSize; i++) {
        printf(" |");
        for(int j=0; j<areaSize; j++) {
            if(playersLoc[i][j] != 0) {
                printf(" %d", playersLoc[i][j]);
            } else {
                printf("  ");
            }
        }
        printf(" |\n");
    }
}

int printDistances(int row, int col, int areaSize, int playersLoc[][areaSize], int currentPlayer) {
    printf("\n");
    for (int i = 0; i < areaSize; i++) {
        for (int j = 0; j < areaSize; j++) {
            if (playersLoc[i][j] != currentPlayer && playersLoc[i][j] != 0) {
                int distance = abs(i - row) + abs(j - col);
                printf("The distance with player%d: %d\n", playersLoc[i][j], distance);

                if (distance == 0) {
                    return currentPlayer;
                }
            }
        }
    }
    return 999;
}

void findClosestGuessWinners(int areaSize, int playersLoc[][areaSize], int closestGuessCount) {
    printf("\nThe winner with the closest guess of 1-distance:\n");

    for (int currentPlayer = 1; currentPlayer <= closestGuessCount; currentPlayer++) {
        int closestDistance = INT_MAX;

        for (int i = 0; i < areaSize; i++) {
            for (int j = 0; j < areaSize; j++) {
                if (playersLoc[i][j] != currentPlayer && playersLoc[i][j] != 0) {
                    int distance = abs(i - playersLoc[currentPlayer - 1][0]) + abs(j - playersLoc[currentPlayer - 1][1]);

                    if (distance < closestDistance) {
                        closestDistance = distance;
                    }
                }
            }
        }

        printf("player%d", currentPlayer);

        if (currentPlayer != closestGuessCount) {
            printf(", ");
        }
    }
}

void gameProcess(struct GameArea firstArena, int areaSize, int definedPlayersLoc[][areaSize]) {
    randomPlayerPositions(firstArena.playerCount, firstArena.areaSize, definedPlayersLoc);
    printBorders(firstArena.areaSize);
    printMatrices(firstArena.areaSize, definedPlayersLoc);
    printBorders(firstArena.areaSize);

    int gameWon = 0;
    int closestGuessCount = firstArena.playerCount;

    printf("Game launches -->\n");
    for(int i = 0; i < firstArena.roundCount; i++) {
        printf("---------- Round-%d ----------\n", i + 1);
        for(int k = 0; k < firstArena.playerCount; k++) {
            int row, col, result;
            printf("\n");
            printf("Enter the guess with space character (ex. 9 9): ");
            scanf("%d %d", &row, &col);
            printf("%d.guess of player%d: [%d,%d]", i + 1, k + 1, row, col);
            result = printDistances(row, col, firstArena.areaSize, definedPlayersLoc, k + 1);
            if(result != 999) {
                printf("******************************************\n");
                printf("player%d won the game!!!\n", result);
                printf("******************************************");

                gameWon = 1;
                break;
            }
        }

        if (i == firstArena.roundCount - 1) {
            findClosestGuessWinners(firstArena.areaSize, definedPlayersLoc, closestGuessCount);
        }

        if (gameWon) {
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    struct GameArea firstArena;

    if (argc != 3) {
        printf("Usage: %s <areaSize> <playerCount>\n", argv[0]);
        return 1;
    }

    int areaSize = atoi(argv[1]);
    int playerCount = atoi(argv[2]);

    if (areaSize <= 0 || playerCount <= 0) {
        printf("Invalid arguments. Usage: %s <areaSize> <playerCount>\n", argv[0]);
        return 1;
    }

    firstArena.playerCount = playerCount;
    firstArena.areaSize = areaSize;
    firstArena.roundCount = 1;

    int definedPlayersLoc[firstArena.areaSize][firstArena.areaSize];

    gameProcess(firstArena, firstArena.areaSize, definedPlayersLoc);
}
