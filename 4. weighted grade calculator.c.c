#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_NAME 50

void displayMenu();
void singleStudent();
void multipleStudents();
void readComponents(int m, char names[][MAX_NAME], double weights[], double maxPoints[]);
double calculateFinalGrade(int m, double weights[], double maxPoints[], double scores[]);
char *getLetterGrade(int roundedGrade);
void computeStatistics(int n, double grades[]);
void sortArray(int n, double arr[]);

//Recursive function to calculate the sum of weighted component grades
double recursiveSum(int index, int m, double weights[], double maxPoints[], double scores[]) {
    if (index == m)
        return 0;

    double current = (scores[index] / maxPoints[index]) * (weights[index] / 100.0);
    return current + recursiveSum(index + 1, m, weights, maxPoints, scores);
}

int main() {
    int choice;

    while (1) {
        displayMenu();
        printf("Enter your choice (1/2/3): ");
        scanf("%d", &choice);

        if (choice == 1)
            singleStudent();
        else if (choice == 2)
            multipleStudents();
        else if (choice == 3) {
            printf("\n--- HAVE A GOOD DAY! ---\n");
            printf("========================\n");
            break;
        }
        else
            printf("Invalid choice. Please try again.\n");
    }

    return 0;
}

void displayMenu() {
    printf("\n======================================\n");
    printf("Weighted Grade Calculation Program\n");
    printf("======================================\n");
    printf("1. Single Student Grades\n");
    printf("2. Multiple Students Grades\n");
    printf("3. Exit\n");
}

void readComponents(int m, char names[][MAX_NAME], double weights[], double maxPoints[]) {
    double totalWeight = 0;

    for (int i = 0; i < m; i++) {
        printf("Component %d:\n", i + 1);

        printf("  Name: ");
        scanf(" %[^\n]", names[i]);

        do {
            printf("  Weight: ");
            scanf("%lf", &weights[i]);
            if (weights[i] <= 0)
                printf("  Invalid weight. Must be positive.\n");
        } while (weights[i] <= 0);

        do {
            printf("  Max Allocated Point: ");
            scanf("%lf", &maxPoints[i]);
            if (maxPoints[i] <= 0)
                printf("  Invalid max point. Must be positive.\n");
        } while (maxPoints[i] <= 0);

        totalWeight += weights[i];
    }

    if (fabs(totalWeight - 100.0) > 0.001) {
        printf("Error: Total weight must equal 100.\n");
        exit(1);
    }
}

double calculateFinalGrade(int m, double weights[], double maxPoints[], double scores[]) {
    double result = recursiveSum(0, m, weights, maxPoints, scores);
    return result * 100;
}

char* getLetterGrade(int grade) {

    if (grade >= 90 && grade <= 100)
        return "A+";
    else if (grade >= 85 && grade <= 89)
        return "A";
    else if (grade >= 80 && grade <= 84)
        return "A-";
    else if (grade >= 75 && grade <= 79)
        return "B+";
    else if (grade >= 70 && grade <= 74)
        return "B";
    else if (grade >= 65 && grade <= 69)
        return "C+";
    else if (grade >= 60 && grade <= 64)
        return "C";
    else if (grade >= 50 && grade <= 59)
        return "D";
    else
        return "F";
}

void singleStudent() {
    int m;

    printf("\nNumber of components: ");
    scanf("%d", &m);

    if (m <= 0) {
        printf("Invalid number of components.\n");
        return;
    }

    char names[m][MAX_NAME];
    double weights[m], maxPoints[m], scores[m];

    readComponents(m, names, weights, maxPoints);

    printf("-- Summary of Score--\n");

    for (int i = 0; i < m; i++) {
        do {
            printf(" Score for \"%s\": ", names[i]);
            scanf("%lf", &scores[i]);
            if (scores[i] < 0 || scores[i] > maxPoints[i])
                printf(" Invalid score.\n");
        } while (scores[i] < 0 || scores[i] > maxPoints[i]);
    }

    double finalGrade = calculateFinalGrade(m, weights, maxPoints, scores);
    int rounded = (int)round(finalGrade);
    char* letter = getLetterGrade(rounded);

printf(" Final Weighted Grade: %d%%\n", rounded);
printf(" Letter Grade: %s\n", letter);  
}

void multipleStudents() {
    int m, n;

    printf("\nNumber of components: ");
    scanf("%d", &m);

    if (m <= 0) {
        printf("Invalid number of components.\n");
        return;
    }

    char names[m][MAX_NAME];
    double weights[m], maxPoints[m];

    readComponents(m, names, weights, maxPoints);

    printf("Number of students: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of students.\n");
        return;
    }

    double finalGrades[n];

    for (int i = 0; i < n; i++) {
        printf("-- Student %d --\n", i + 1);

        double scores[m];

        for (int j = 0; j < m; j++) {
            do {
                printf(" Score for \"%s\": ", names[j]);
                scanf("%lf", &scores[j]);
                if (scores[j] < 0 || scores[j] > maxPoints[j])
                    printf(" Invalid score.\n");
            } while (scores[j] < 0 || scores[j] > maxPoints[j]);
        }

        double final = calculateFinalGrade(m, weights, maxPoints, scores);
        int rounded = (int)round(final);
        finalGrades[i] = rounded;

        printf(" Final Weighted Grade: %d%%\n", rounded);
        printf(" Letter Grade: %s\n", getLetterGrade(rounded));
    }

    computeStatistics(n, finalGrades);
}

void computeStatistics(int n, double grades[]) {
    double sum = 0, max = grades[0];

    for (int i = 0; i < n; i++) {
        sum += grades[i];
        if (grades[i] > max)
            max = grades[i];
    }

    double average = sum / n;

    sortArray(n, grades);

    double median;
    if (n % 2 == 0)
        median = (grades[n/2 - 1] + grades[n/2]) / 2;
    else
        median = grades[n/2];

    printf("\nClass Summary:\n");
    printf(" Maximum: %.2lf\n", max);
    printf(" Average: %.2lf\n", average);
    printf(" Median: %.2lf\n", median);
}

void sortArray(int n, double arr[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}