#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int roll_number;
    char name[50];
    float marks[5]; // 5 subjects
} Student;

void menu();
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;

    while (1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                exit(0);
            default:
                printf("\nInvalid Choice");
        }
    }
}

void addStudent() {
    FILE *fp = fopen("students.txt", "a");

    if(fp == NULL) {
        perror("File Not Found");
    }

    Student std;

    printf("\n--- Add Student ---\n");
    printf("Enter Roll Number: ");
    scanf("%d", &std.roll_number);
    getchar();

    printf("Enter Name: ");
    fgets(std.name, sizeof(std.name), stdin);
    std.name[strcspn(std.name, "\n")] = '\0';

    printf("Enter marks for 5 subjects:\n");
    for (int i = 0; i < 5; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%f", &std.marks[i]);
    }

    // Save in text format: rollNumber,name,mark1,mark2,mark3,mark4,mark5
    fprintf(fp, "%d,%s,%.2f,%.2f,%.2f,%.2f,%.2f\n",
            std.roll_number, std.name,
            std.marks[0], std.marks[1], std.marks[2], std.marks[3], std.marks[4]);

    fclose(fp);

    printf("Student record added successfully.\n");
}

void viewStudents() {
    FILE *fp = fopen("students.txt", "r");

    if(fp == NULL) {
        perror("File Not Found");
    }

    Student std;
    int count = 0;

    printf("\n--- View Student ---\n");

    while (fscanf(fp, "%d,%49[^,],%f,%f,%f,%f,%f\n",
                  &std.roll_number, std.name,
                  &std.marks[0], &std.marks[1], &std.marks[2], &std.marks[3], &std.marks[4]) == 7) {
        printf("\nStudent #%d\n", ++count);
        printf("Roll Number: %d\n", std.roll_number);
        printf("Name: %s\n", std.name);
        printf("Marks: ");
        for (int i = 0; i < 5; i++) {
            printf("%.2f ", std.marks[i]);
        }
        printf("\n");
    }

    if (count == 0) {
        printf("No records found.\n");
    }
    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen("students.txt", "r");

    if(fp == NULL) {
        perror("File Not Found");
    }

    Student std;
    int found = 0;
    int target;

    printf("\n--- Search Student ---\n");
    printf("Enter Roll Number to search: ");
    scanf("%d", &target);

    while (fscanf(fp, "%d,%49[^,],%f,%f,%f,%f,%f\n",
        &std.roll_number, &std.name,
        &std.marks[0], &std.marks[1], &std.marks[2], &std.marks[3], &std.marks[4]) == 7) {
        if (std.roll_number == target) {
            printf("\nStudent Found:\n");
            printf("Roll Number: %d\n", std.roll_number);
            printf("Name: %s\n", std.name);
            printf("Marks: ");
            for (int i = 0; i < 5; i++) {
                printf("%.2f ", std.marks[i]);
            }
            printf("\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        perror("No records found.\n");
    }
    fclose(fp);

}

void updateStudent() {
    FILE *fp = fopen("students.txt", "a");
    FILE *temp = fopen("temp.txt", "a");

    if (fp == NULL || temp == NULL) {
        perror("Error opening files");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
    }

    int target;
    int found = 0;
    Student std;

    printf("\n--- Update Student ---\n");
    printf("Enter Roll Number to update: ");
    scanf("%d", &target);

    while (fscanf(fp, "%d,%49[^,],%f,%f,%f,%f,%f\n",
                  &std.roll_number, std.name,
                  &std.marks[0], &std.marks[1], &std.marks[2], &std.marks[3], &std.marks[4]) == 7) {
        if (std.roll_number == target) {
            printf("\nStudent found. Enter new details:\n");

            printf("Enter Name: ");
            getchar(); // Clear buffer
            fgets(std.name, sizeof(std.name), stdin);
            std.name[strcspn(std.name, "\n")] = '\0';

            printf("Enter marks for 5 subjects:\n");
            for (int i = 0; i < 5; i++) {
                printf("Subject %d: ", i + 1);
                scanf("%f", &std.marks[i]);
            }

            found = 1;
        }

        fprintf(temp, "%d,%s,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                std.roll_number, std.name,
                std.marks[0], std.marks[1], std.marks[2], std.marks[3], std.marks[4]);
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        printf("Student record updated successfully.\n");
    } else {
        printf("Student with Roll Number %d not found.\n", target);
    }

}

void deleteStudent() {
    FILE *fp = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        perror("Error opening files");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
    }

    int target;
    int found = 0;
    Student std;

    printf("\n--- Delete Student ---\n");
    printf("Enter Roll Number to delete: ");
    scanf("%d", &target);

    while (fscanf(fp, "%d,%49[^,],%f,%f,%f,%f,%f\n",
              &std.roll_number, std.name,
              &std.marks[0], &std.marks[1], &std.marks[2], &std.marks[3], &std.marks[4]) == 7) {
        if (std.roll_number == target) {
            found = 1;
            continue;
        }
        fprintf(temp, "%d,%s,%.2f,%.2f,%.2f,%.2f\n",
            std.roll_number, std.name,
            std.marks[0], std.marks[1], std.marks[2], std.marks[3], std.marks[4]);
    }
    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found) {
        printf("Student record deleted successfully.\n");
    } else {
        printf("Student with Roll Number %d not found.\n", target);
    }
}