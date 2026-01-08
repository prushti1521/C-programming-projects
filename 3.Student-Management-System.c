/*
   Student Management System 
  -------------------------------
 * Features:
  - Add student records
  - View all students
  - Search student by ID
  - Delete student records
 
  Data is stored in "test.txt" automatically.
  File is created if it does not exist.
 
 * Concepts used:
  - Arrays for student fields
  - File handling (text mode)
  - Loops & conditional statements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int ids[MAX];
char names[MAX][50];
int ages[MAX];
char courses[MAX][50];
int count = 0;


void addStudent();
void viewStudents();
void searchStudent();
void deleteStudent();
void loadFromFile();
void saveToFile();

int main() {
    int choice;

    loadFromFile(); 

    while (1) {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: saveToFile(); printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}


void loadFromFile() {
    FILE *fp = fopen("test.txt", "r");
    if (!fp) {
        // File does not exist → create empty file
        fp = fopen("test.txt", "w");
        if (!fp) {
            printf("Error creating data file!\n");
            exit(1);
        }
        fclose(fp);
        return;
    }

    count = 0;
    while (fscanf(fp, "%d %49s %d %49s", &ids[count], names[count], &ages[count], courses[count]) == 4) {
        count++;
        if (count >= MAX) break;
    }
    fclose(fp);
}


void saveToFile() {
    FILE *fp = fopen("test.txt", "w");
    if (!fp) {
        printf("Error saving data!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %d %s\n", ids[i], names[i], ages[i], courses[i]);
    }
    fclose(fp);
}


void addStudent() {
    if (count >= MAX) {
        printf("Database full!\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &ids[count]);
    getchar();

    printf("Enter Name: ");
    scanf("%49s", names[count]);

    printf("Enter Age: ");
    scanf("%d", &ages[count]);
    getchar();

    printf("Enter Course: ");
    scanf("%49s", courses[count]);

    count++;
    saveToFile();
    printf("Student added successfully!\n");
}

void viewStudents() {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("\n--- Student Records ---\n");
    for (int i = 0; i < count; i++) {
        printf("\nID: %d\n", ids[i]);
        printf("Name: %s\n", names[i]);
        printf("Age: %d\n", ages[i]);
        printf("Course: %s\n", courses[i]);
    }
}


void searchStudent() {
    int id, found = 0;
    printf("Enter Student ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (ids[i] == id) {
            printf("\nStudent Found!\n");
            printf("ID: %d\n", ids[i]);
            printf("Name: %s\n", names[i]);
            printf("Age: %d\n", ages[i]);
            printf("Course: %s\n", courses[i]);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found!\n");
}

void deleteStudent() {
    int id, found = 0;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (ids[i] == id) {
            for (int j = i; j < count - 1; j++) {
                ids[j] = ids[j + 1];
                strcpy(names[j], names[j + 1]);
                ages[j] = ages[j + 1];
                strcpy(courses[j], courses[j + 1]);
            }
            count--;
            found = 1;
            saveToFile();
            printf("Student deleted successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Student not found!\n");
}
