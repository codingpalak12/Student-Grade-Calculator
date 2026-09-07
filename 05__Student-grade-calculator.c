/* Professional Student Grade Calculator with GPA & Report Generation
   description This program calculates grades based on marks,
   computes GPA, and generates a report card.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For validation

// ==================== CONSTANTS & CONFIGURATION ====================
#define MAX_SUBJECTS 10
#define MAX_NAME_LEN 50
#define PASS_MARKS 40
#define MAX_MARKS_PER_SUBJECT 100

// ==================== DATA STRUCTURES ====================

/**
 * @struct Subject
 * @brief Holds individual subject data
 */
typedef struct {
    char name[MAX_NAME_LEN];
    int marks;
    char grade;
    float gradePoint;
} Subject;

/**
 * @struct Student
 * @brief Holds complete student academic record
 */
typedef struct {
    char name[MAX_NAME_LEN];
    int rollNo;
    int numSubjects;
    Subject subjects[MAX_SUBJECTS];
    int totalMarks;
    float percentage;
    float gpa;
    char finalGrade;
} Student;

// ==================== FUNCTION PROTOTYPES ====================
char calculateGrade(int marks);
float getGradePoint(char grade);
void inputStudentData(Student *s);
void calculateResults(Student *s);
void displayReportCard(const Student *s);
void saveToFile(const Student *s);
int validateMarks(int marks);
void clearInputBuffer();

// ==================== GRADE LOGIC ====================

/**
 * @brief Converts marks to letter grade as per standard university system
 * @param marks - Marks obtained out of 100
 * @return char - Grade letter (O, A+, A, B+, B, C, F)
 */
char calculateGrade(int marks) {
    // Using absolute grading system - 90+ O, 80+ A+, etc.
    if (marks >= 90) return 'O'; // Outstanding - using O for distinction
    else if (marks >= 80) return 'A'; // A+ category handled in display
    else if (marks >= 70) return 'B'; // B+ category
    else if (marks >= 60) return 'C'; // B category
    else if (marks >= 50) return 'D'; // C category
    else if (marks >= 40) return 'E'; // Pass
    else return 'F'; // Fail
}

/**
 * @brief Returns numerical grade point for GPA calculation (10-point scale)
 * @param grade - Letter grade
 * @return float - Grade point
 */
float getGradePoint(char grade) {
    switch (grade) {
        case 'O': return 10.0f;
        case 'A': return 9.0f; // A+
        case 'B': return 8.0f; // A
        case 'C': return 7.0f; // B+
        case 'D': return 6.0f; // B
        case 'E': return 5.0f; // C
        case 'F': return 0.0f; // Fail
        default: return 0.0f;
    }
}

/**
 * @brief Validates if marks are in valid range
 */
int validateMarks(int marks) {
    return (marks >= 0 && marks <= MAX_MARKS_PER_SUBJECT);
}

// ==================== CORE FUNCTIONS ====================

/**
 * @brief Takes student and subject details with input validation
 * @param s - Pointer to Student struct
 */
void inputStudentData(Student *s) {
    printf("========== STUDENT GRADE CALCULATOR ==========\n");

    // --- Student Info Input ---
    printf("Enter Student Name: ");
    fgets(s->name, MAX_NAME_LEN, stdin);
    // Remove trailing newline from fgets
    s->name[strcspn(s->name, "\n")] = 0;

    printf("Enter Roll Number: ");
    scanf("%d", &s->rollNo);
    clearInputBuffer(); // Clear leftover newline

    // --- Number of Subjects with Validation ---
    do {
        printf("Enter Number of Subjects (1-%d): ", MAX_SUBJECTS);
        scanf("%d", &s->numSubjects);
        clearInputBuffer();
        if (s->numSubjects < 1 || s->numSubjects > MAX_SUBJECTS) {
            printf("[Error] Invalid number! Please enter between 1 and %d\n", MAX_SUBJECTS);
        }
    } while (s->numSubjects < 1 || s->numSubjects > MAX_SUBJECTS);

    // --- Loop for each subject ---
    for (int i = 0; i < s->numSubjects; i++) {
        printf("\n--- Subject %d ---\n", i + 1);
        printf("Enter Subject Name: ");
        fgets(s->subjects[i].name, MAX_NAME_LEN, stdin);
        s->subjects[i].name[strcspn(s->subjects[i].name, "\n")] = 0;

        // Marks input with validation loop
        do {
            printf("Enter Marks for %s (0-100): ", s->subjects[i].name);
            scanf("%d", &s->subjects[i].marks);
            clearInputBuffer();
            if (!validateMarks(s->subjects[i].marks)) {
                printf("[Error] Marks must be between 0 and 100!\n");
            }
        } while (!validateMarks(s->subjects[i].marks));

        // Auto-calculate grade and gradepoint for this subject
        s->subjects[i].grade = calculateGrade(s->subjects[i].marks);
        s->subjects[i].gradePoint = getGradePoint(s->subjects[i].grade);
    }
}

/**
 * @brief Calculates total, percentage, GPA and final grade
 * @param s - Pointer to Student struct
 */
void calculateResults(Student *s) {
    s->totalMarks = 0;
    float totalGradePoints = 0.0f;
    int failedSubjects = 0;

    // Calculate total and check for fails
    for (int i = 0; i < s->numSubjects; i++) {
        s->totalMarks += s->subjects[i].marks;
        totalGradePoints += s->subjects[i].gradePoint;
        if (s->subjects[i].grade == 'F') {
            failedSubjects++;
        }
    }

    // Percentage = (Total / Max Possible) * 100
    s->percentage = ((float)s->totalMarks / (s->numSubjects * MAX_MARKS_PER_SUBJECT)) * 100.0f;

    // GPA = Total Grade Points / Number of Subjects
    s->gpa = totalGradePoints / s->numSubjects;

    // Final Grade based on percentage and fail condition
    if (failedSubjects > 0) {
        s->finalGrade = 'F'; // Fail if any subject failed
    } else {
        s->finalGrade = calculateGrade((int)s->percentage);
    }
}

/**
 * @brief Displays formatted report card
 * @param s - Const pointer to Student (read-only)
 */
void displayReportCard(const Student *s) {
    printf("\n\n");
    printf("===================================================\n");
    printf(" STUDENT REPORT CARD\n");
    printf("===================================================\n");
    printf("Name : %s\n", s->name);
    printf("Roll No : %d\n", s->rollNo);
    printf("---------------------------------------------------\n");
    printf("%-20s %-10s %-10s %-10s\n", "SUBJECT", "MARKS", "GRADE", "GP");
    printf("---------------------------------------------------\n");

    for (int i = 0; i < s->numSubjects; i++) {
        // Nicely formatted row for each subject
        printf("%-20s %-10d %-10c %-10.1f\n",
               s->subjects[i].name,
               s->subjects[i].marks,
               s->subjects[i].grade,
               s->subjects[i].gradePoint);
    }

    printf("---------------------------------------------------\n");
    printf("Total Marks : %d / %d\n", s->totalMarks, s->numSubjects * 100);
    printf("Percentage : %.2f%%\n", s->percentage);
    printf("GPA : %.2f / 10.0\n", s->gpa);
    printf("Final Grade : %c\n", s->finalGrade);
    printf("Result : %s\n", (s->finalGrade == 'F')? "FAIL" : "PASS");
    printf("===================================================\n");
}

/**
 * @brief Saves report card to a text file for record keeping
 * @param s - Student data
 */
void saveToFile(const Student *s) {
    char filename[MAX_NAME_LEN + 10];
    sprintf(filename, "%d_report.txt", s->rollNo); // e.g., 101_report.txt

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("[Error] Could not save file!\n");
        return;
    }

    // Writing same report to file
    fprintf(fp, "Report Card - %s (Roll: %d)\n", s->name, s->rollNo);
    fprintf(fp, "Total: %d, Percentage: %.2f, GPA: %.2f, Grade: %c\n",
            s->totalMarks, s->percentage, s->gpa, s->finalGrade);

    fclose(fp);
    printf("\n[Success] Report saved to file: %s\n", filename);
}

/**
 * @brief Utility to clear stdin buffer to prevent input skipping
 */
void clearInputBuffer() {
    int c;
    while ((c = getchar())!= '\n' && c!= EOF);
}

// ==================== MAIN DRIVER FUNCTION ====================
int main() {
    Student student1;

    // Step 1: Input
    inputStudentData(&student1);

    // Step 2: Process
    calculateResults(&student1);

    // Step 3: Output
    displayReportCard(&student1);

    // Step 4: Save (Professional Touch)
    char choice;
    printf("\nDo you want to save report to file? (y/n): ");
    scanf("%c", &choice);
    if (tolower(choice) == 'y') {
        saveToFile(&student1);
    }

    printf("\nThank you for using Grade Calculator!\n");
    return 0;
}
