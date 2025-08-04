#include <stdio.h>
#include <string.h>



// Define the structure
struct Student {
    char name[50];
    int roll;
    float totalMarks;
};

int main() {
    struct Student students[101];
    int n, i, topIndex = 0;

    // Read the number of students
    printf("Enter the number of students: ");
    scanf("%d", &n);

    // Read student information
    for (i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]", students[i].name);  // Read string with spaces
        printf("Roll Number: ");
        scanf("%d", &students[i].roll);
        printf("Total Marks: ");
        scanf("%f", &students[i].totalMarks);
    }

    // Find the student with the highest marks
    for (i = 1; i < n; i++) {
        if (students[i].totalMarks > students[topIndex].totalMarks) {
            topIndex = i;
        }
    }

    // Print the student with the highest marks
    printf("\nStudent with the highest marks:\n");
    printf("Name: %s\n", students[topIndex].name);
    printf("Roll Number: %d\n", students[topIndex].roll);
    printf("Total Marks: %.2f\n", students[topIndex].totalMarks);

    return 0;
}