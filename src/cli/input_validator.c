#include "input_validator.h"

static void flush() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

unsigned long long positive_integer_input() {
    int num = integer_input();
    while (num < 0) {
        printf("No negative numbers! Enter again: ");
        num = integer_input();
    }
    return num;
}

float positive_float_input() {
    float num = float_input();
    while (num < 0) {
        printf("No negative numbers! Enter again: ");
        num = float_input();
    }
    return num;
}


int integer_input() {
    int num;
    while (scanf("%d", &num) != 1) {
        flush();
        printf("Invalid input! Enter again: ");
    }
    flush();
    return num;
}

float float_input() {
    float num;
    while (scanf("%f", &num) != 1) {
        flush();
        printf("Invalid input! Enter again: ");
    }
    flush();
    return num;
}

char* string_input() {
    char* buffer = malloc(sizeof(char) * PRODUCT_STRING_BUFFER_SIZE);
    fgets(buffer, PRODUCT_STRING_BUFFER_SIZE, stdin);
    char* new_line = strchr(buffer, '\n');
    if (new_line != NULL) new_line = '\0';

    return buffer;
}