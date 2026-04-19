/* Weighted Grade System (Assignment 2)

## Features
- Uses structures (struct)
- Dynamic memory allocation (malloc, realloc)
- Sorting students by grade
- Searching students by name
- Computes max, average, median
- Input validation

## Concepts Used
- Structures
- Pointers
- Dynamic memory
- Sorting algorithms
- Searching algorithms */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char name[50];
    double weight;
    double maxPoints;
    double earnedPoints;
} CourseComponent;

typedef struct {
    char name[100];
    CourseComponent *components;
    int numComponents;
    double finalGrade;
    char letterGrade[3];
} Student;

// ================= FUNCTIONS =================

double calculateFinalGrade(Student *s) {
    double total = 0;
    for (int i = 0; i < s->numComponents; i++) {
        total += (s->components[i].earnedPoints / s->components[i].maxPoints)
                 * s->components[i].weight;
    }
    return total;
}

void assignLetterGrade(Student *s) {
    int g = (int)round(s->finalGrade);

    if (g >= 90) strcpy(s->letterGrade, "A+");
    else if (g >= 85) strcpy(s->letterGrade, "A");
    else if (g >= 80) strcpy(s->letterGrade, "A-");
    else if (g >= 75) strcpy(s->letterGrade, "B+");
    else if (g >= 70) strcpy(s->letterGrade, "B");
    else if (g >= 65) strcpy(s->letterGrade, "C+");
    else if (g >= 60) strcpy(s->letterGrade, "C");
    else if (g >= 50) strcpy(s->letterGrade, "D");
    else strcpy(s->letterGrade, "F");
}

void freeStudent(Student *s) {
    free(s->components);
}

// ================= SINGLE STUDENT =================

void singleStudent() {
    Student s;
    double totalWeight;

    while (getchar() != '\n');
    printf("Enter student's full name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    do {
        printf("Enter number of course components: ");
        scanf("%d", &s.numComponents);
    } while (s.numComponents <= 0);

    s.components = malloc(s.numComponents * sizeof(CourseComponent));
    if (!s.components) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    while (getchar() != '\n');

    do {
        totalWeight = 0;

        for (int i = 0; i < s.numComponents; i++) {

            printf("\nComponent %d:\n", i + 1);

            printf("Name: ");
            fgets(s.components[i].name, 50, stdin);
            s.components[i].name[strcspn(s.components[i].name, "\n")] = 0;

            do {
                printf("Weight (as percentage): ");
                scanf("%lf", &s.components[i].weight);
            } while (s.components[i].weight <= 0 || s.components[i].weight > 100);

            totalWeight += s.components[i].weight;

            do {
                printf("Max Allocated Points: ");
                scanf("%lf", &s.components[i].maxPoints);
            } while (s.components[i].maxPoints <= 0);

            do {
                printf("Earned Points: ");
                scanf("%lf", &s.components[i].earnedPoints);

                if (s.components[i].earnedPoints < 0) {
                    printf("Error: Earned points cannot be negative.\n");
                    printf("Please re-enter.\n");
                } else if (s.components[i].earnedPoints > s.components[i].maxPoints) {
                    printf("Error: Earned points cannot exceed maximum allocated points.\n");
                    printf("Please re-enter.\n");
                }

            } while (s.components[i].earnedPoints < 0 ||
                     s.components[i].earnedPoints > s.components[i].maxPoints);
        }

        if (fabs(totalWeight - 100.0) > 0.001) {
            printf("Error: Total weight must equal 100%%! Please re-enter all components.\n");
            while (getchar() != '\n');
        }

    } while (fabs(totalWeight - 100.0) > 0.001);

    s.finalGrade = calculateFinalGrade(&s);
    assignLetterGrade(&s);

    printf("\n-- Summary of Scores --\n");
    printf("Final Weighted Grade: %.0lf%%\n", s.finalGrade);
    printf("Letter Grade: %s\n", s.letterGrade);

    freeStudent(&s);
}

// ================= MULTIPLE STUDENTS =================

void multipleStudents(Student **students, int *count) {
    int numComponents;
    double totalWeight;

    do {
        printf("Enter number of course components: ");
        scanf("%d", &numComponents);
    } while (numComponents <= 0);

    CourseComponent *templ = malloc(numComponents * sizeof(CourseComponent));
    if (!templ) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    do {
        totalWeight = 0;

        for (int i = 0; i < numComponents; i++) {
            while (getchar() != '\n');
            printf("\nComponent %d:\n", i + 1);

            printf("Name: ");
            fgets(templ[i].name, 50, stdin);
            templ[i].name[strcspn(templ[i].name, "\n")] = 0;

            do {
                printf("Weight (as percentage): ");
                scanf("%lf", &templ[i].weight);
            } while (templ[i].weight <= 0 || templ[i].weight > 100);

            totalWeight += templ[i].weight;

            do {
                printf("Max Allocated Points: ");
                scanf("%lf", &templ[i].maxPoints);
            } while (templ[i].maxPoints <= 0);
        }

        if (fabs(totalWeight - 100.0) > 0.001) {
            printf("Error: Total weight must equal 100%%! Please re-enter all components.\n");
        }

    } while (fabs(totalWeight - 100.0) > 0.001);

    char name[100];

    while (1) {
        while (getchar() != '\n');
        printf("\nEnter student's full name (or type DONE to stop): ");
        fgets(name, 100, stdin);
        name[strcspn(name, "\n")] = 0;

        if (strcmp(name, "DONE") == 0)
            break;

        Student *tmp = realloc(*students, (*count + 1) * sizeof(Student));
        if (!tmp) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        *students = tmp;

        Student *s = &(*students)[*count];
        strcpy(s->name, name);
        s->numComponents = numComponents;
        s->components = malloc(numComponents * sizeof(CourseComponent));
        if (!s->components) {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        for (int i = 0; i < numComponents; i++) {
            s->components[i] = templ[i];

            do {
                printf("Score for \"%s\": ", templ[i].name);
                scanf("%lf", &s->components[i].earnedPoints);

                if (s->components[i].earnedPoints < 0) {
                    printf("Error: Earned points cannot be negative.\n");
                    printf("Please re-enter.\n");
                } else if (s->components[i].earnedPoints > templ[i].maxPoints) {
                    printf("Error: Earned points cannot exceed maximum allocated points.\n");
                    printf("Please re-enter.\n");
                }

            } while (s->components[i].earnedPoints < 0 ||
                     s->components[i].earnedPoints > templ[i].maxPoints);
        }

        s->finalGrade = calculateFinalGrade(s);
        assignLetterGrade(s);

        (*count)++;
    }

    if (*count == 0) {
        printf("\nNo students entered.\n");
        free(templ);
        return;
    }

    printf("\n-- Class Summary --\n");

    double sum = 0;
    double max = (*students)[0].finalGrade;

    for (int i = 0; i < *count; i++) {
        printf("%-20s - %3.0lf%% (%s)\n",
               (*students)[i].name,
               (*students)[i].finalGrade,
               (*students)[i].letterGrade);

        sum += (*students)[i].finalGrade;

        if ((*students)[i].finalGrade > max)
            max = (*students)[i].finalGrade;
    }

    printf("\nMaximum: %.0lf%% (Students: ", round(max));
    for (int i = 0; i < *count; i++) {
        if ((int)round((*students)[i].finalGrade) == (int)round(max)) {
            printf("%s ", (*students)[i].name);
        }
    }
    printf(")\n");

    printf("Average: %.0lf%%\n", round(sum / (*count)));

    // MEDIAN
    double *grades = malloc(*count * sizeof(double));
    if (!grades) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < *count; i++)
        grades[i] = (*students)[i].finalGrade;

    for (int i = 0; i < *count - 1; i++) {
        for (int j = i + 1; j < *count; j++) {
            if (grades[i] > grades[j]) {
                double temp = grades[i];
                grades[i] = grades[j];
                grades[j] = temp;
            }
        }
    }

    double median;
    if (*count % 2 == 0)
        median = (grades[*count/2 - 1] + grades[*count/2]) / 2.0;
    else
        median = grades[*count/2];

    printf("Median: %.0lf%%\n", round(median));

    free(grades);
    free(templ);
}

// ================= SORT =================

void sortStudents(Student *students, int count) {
    if (count == 0) {
        printf("\nNo students to sort. Please use option 2 first.\n");
        return;
    }

    Student *copy = malloc(count * sizeof(Student));
    if (!copy) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    memcpy(copy, students, count * sizeof(Student));

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (copy[i].finalGrade < copy[j].finalGrade) {
                Student temp = copy[i];
                copy[i] = copy[j];
                copy[j] = temp;
            }
        }
    }

    printf("\n======================================\n");
    printf("Sorting students by final grade...\n");
    printf("======================================\n");
    printf("Class Ranking:\n");

    for (int i = 0; i < count; i++) {
        printf("%d. %-20s - %3.0lf%% (%s)\n",
               i + 1,
               copy[i].name,
               copy[i].finalGrade,
               copy[i].letterGrade);
    }

    free(copy);
}

// ================= SEARCH =================

void searchStudent(Student *students, int count) {
    if (count == 0) {
        printf("\nNo students available. Please use option 2 first.\n");
        return;
    }

    char name[100];

    while (getchar() != '\n');
    printf("Enter student name to search: ");
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = 0;

    for (int i = 0; i < count; i++) {
        if (strcasecmp(name, students[i].name) == 0) {
            printf("Result: %-20s - %3.0lf%% (%s)\n",
                   students[i].name,
                   students[i].finalGrade,
                   students[i].letterGrade);
            return;
        }
    }

    printf("Student not found.\n");
}

// ================= MAIN =================

int main() {
    int choice;
    Student *students = NULL;
    int count = 0;

    do {
        printf("\n======================================\n");
        printf("  Weighted Grade Calculation Program\n");
        printf("======================================\n");
        printf("1. Single Student Grades\n");
        printf("2. Multiple Students Grades\n");
        printf("3. Sort Students by Grade\n");
        printf("4. Search for a Student\n");
        printf("5. Exit\n");
        printf("Enter your choice (1/2/3/4/5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: singleStudent(); break;
            case 2: multipleStudents(&students, &count); break;
            case 3: sortStudents(students, count); break;
            case 4: searchStudent(students, count); break;
            case 5: break;
            default: printf("Invalid choice. Please enter 1-5.\n"); break;
        }

    } while (choice != 5);

    for (int i = 0; i < count; i++)
        freeStudent(&students[i]);

    free(students);

    return 0;
}
