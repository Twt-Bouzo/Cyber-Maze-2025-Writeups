#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void win(void) {
    FILE *fp = fopen("flag.txt", "r");
    if (!fp) { perror("flag.txt"); return; }
    char buf[64];
    fgets(buf, sizeof(buf), fp);
    printf("%s", buf);
    fclose(fp);
}

int main(void) {
    srand(time(NULL));          // different seed every second

    int guess, value;
    printf("Enter the Dance Arena\n");
    printf("Follow the rhythm without missing a beat...\n\n");

    for (int i = 0; i < 4; i++) {
        value = rand();
        printf("Move: ");
        fflush(stdout);
        if (scanf("%d", &guess) != 1) {
            printf("That's not a move!\n");
            return 1;
        }
        if (guess != value) {
            printf("You lost the rhythm.\n");
            return 0;
        }
    }
    printf("You dominated the dance floor!\n");
    win();
    return 0;
}
