#include <stdio.h>
#include <string.h>

#define FIXED_LENGTH 5

void encode(char input[], char output[][FIXED_LENGTH + 1], int size) {
    for (int i = 0; i < size; i++) {
        int value = input[i] - 'a'; // Calculate the index (0-25) for the character
        for (int j = FIXED_LENGTH - 1; j >= 0; j--) {
            output[i][j] = (value % 2) + '0'; // Convert to binary
            value /= 2;
        }
        output[i][FIXED_LENGTH] = '\0'; // Null-terminate the string
    }
}

void display(char input[], char output[][FIXED_LENGTH + 1], int size) {
    printf("Character | Fixed-Length Code\n");
    printf("-----------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("    %c     |     %s\n", input[i], output[i]);
    }
}

int main() {
    char input[] = "hello";
    int size = strlen(input);
    char output[size][FIXED_LENGTH + 1];

    encode(input, output, size);
    display(input, output, size);

    return 0;
}
