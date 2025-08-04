#include <stdio.h>

void to_upper(char *str) {
    while (*str != '\0') {
        if (*str >= 'a' && *str <= 'z') {
            *str = *str - 32;  // Convert to uppercase by subtracting ASCII difference
        }
        str++;
    }
}

void to_lower(char *str) {
    while (*str != '\0') {
        if (*str >= 'A' && *str <= 'Z') {
            *str = *str + 32;  // Convert to lowercase by adding ASCII difference
        }
        str++;
    }
}

int main() {
    char str[100];
    char choice;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    printf("Convert to (U)ppercase or (L)owercase? ");
    scanf(" %c", &choice);

    if (choice == 'U' || choice == 'u') {
        to_upper(str);
        printf("Uppercase: %s", str);
    } else if (choice == 'L' || choice == 'l') {
        to_lower(str);
        printf("Lowercase: %s", str);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}