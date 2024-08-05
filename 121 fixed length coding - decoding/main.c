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

void decode(char output[][FIXED_LENGTH + 1], char decoded[], int size) {
    for (int i = 0; i < size; i++) {
        int value = 0;
        for (int j = 0; j < FIXED_LENGTH; j++) {
            value = value * 2 + (output[i][j] - '0');
        }
        decoded[i] = value + 'a';
    }
    decoded[size] = '\0'; // Null-terminate the decoded string
}

void display_encoded(char input[], char output[][FIXED_LENGTH + 1], int size) {
    printf("Character | Fixed-Length Code\n");
    printf("-----------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("    %c     |     %s\n", input[i], output[i]);
    }
}

void display_decoded(char decoded[]) {
    printf("Decoded message: %s\n", decoded);
}

int main() {
    char input[] = "hello";
    int size = strlen(input);
    char output[size][FIXED_LENGTH + 1];
    char decoded[size + 1];

    encode(input, output, size);
    decode(output, decoded, size);

    display_encoded(input, output, size);
    display_decoded(decoded);

    return 0;
}
