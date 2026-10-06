#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define SUBJECTS 5

// Structure to store student information
struct Student
{
    int rollNo;
    char name[50];

    float marks[SUBJECTS];

    float total;
    float percentage;

    char grade;
    char result[10];
};

// Function declarations
void addStudent(struct Student students[], int *count);
void displayAllStudents(struct Student students[], int count);
void searchStudent(struct Student students[], int count);
void updateStudent(struct Student students[], int count);
void deleteStudent(struct Student students[], int *count);
void displayResult(struct Student students[], int count);

void calculateResult(struct Student *student);
void displayStudent(struct Student student);
int findStudentByRoll(struct Student students[], int count, int rollNo);

float getValidMarks(char subject[]);
int getValidRollNumber(struct Student students[], int count);

void clearInputBuffer();


// Main function
int main()
{
    struct Student students[MAX_STUDENTS];

    int count = 0;
    int choice;

    do
    {
        printf("\n");
        printf("===============================================\n");
        printf("       STUDENT RESULT MANAGEMENT SYSTEM\n");
        printf("===============================================\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Display Student Result\n");
        printf("7. Exit\n");
        printf("===============================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addStudent(students, &count);
                break;

            case 2:
                displayAllStudents(students, count);
                break;

            case 3:
                searchStudent(students, count);
                break;

            case 4:
                updateStudent(students, count);
                break;

            case 5:
                deleteStudent(students, &count);
                break;

            case 6:
                displayResult(students, count);
                break;

            case 7:
                printf("\nThank you for using Student Result Management System!\n");
                break;

            default:
                printf("\nInvalid choice! Please enter a number from 1 to 7.\n");
        }

    } while(choice != 7);

    return 0;
}


// Function to add a new student
void addStudent(struct Student students[], int *count)
{
    int i;

    if(*count >= MAX_STUDENTS)
    {
        printf("\nStudent limit reached. Cannot add more students.\n");
        return;
    }

    printf("\n========== ADD STUDENT ==========\n");

    // Get unique roll number
    students[*count].rollNo = getValidRollNumber(students, *count);

    clearInputBuffer();

    printf("Enter student name: ");
    fgets(students[*count].name, sizeof(students[*count].name), stdin);

    // Remove newline from name
    students[*count].name[strcspn(students[*count].name, "\n")] = '\0';

    printf("\nEnter marks:\n");

    students[*count].marks[0] = getValidMarks("C Programming");
    students[*count].marks[1] = getValidMarks("Data Structures");
    students[*count].marks[2] = getValidMarks("Mathematics");
    students[*count].marks[3] = getValidMarks("Computer Organization");
    students[*count].marks[4] = getValidMarks("Operating Systems");

    // Calculate total, percentage, grade and result
    calculateResult(&students[*count]);

    (*count)++;

    printf("\nStudent added successfully!\n");
}


// Function to get valid roll number
int getValidRollNumber(struct Student students[], int count)
{
    int rollNo;
    int i;

    while(1)
    {
        printf("Enter roll number: ");
        scanf("%d", &rollNo);

        if(rollNo <= 0)
        {
            printf("Roll number must be greater than 0.\n");
            continue;
        }

        // Check duplicate roll number
        for(i = 0; i < count; i++)
        {
            if(students[i].rollNo == rollNo)
            {
                printf("Roll number already exists!\n");
                printf("Please enter a different roll number.\n");
                rollNo = -1;
                break;
            }
        }

        if(rollNo != -1)
        {
            return rollNo;
        }
    }
}


// Function to get valid marks
float getValidMarks(char subject[])
{
    float marks;

    while(1)
    {
        printf("%s (0-100): ", subject);
        scanf("%f", &marks);

        if(marks >= 0 && marks <= 100)
        {
            return marks;
        }

        printf("Invalid marks! Please enter marks between 0 and 100.\n");
    }
}


// Function to calculate result
void calculateResult(struct Student *student)
{
    int i;
    int failedSubject = 0;

    student->total = 0;

    // Calculate total marks
    for(i = 0; i < SUBJECTS; i++)
    {
        student->total += student->marks[i];

        // Check whether student failed in any subject
        if(student->marks[i] < 40)
        {
            failedSubject = 1;
        }
    }

    // Calculate percentage
    student->percentage = student->total / SUBJECTS;

    // Determine grade
    if(student->percentage >= 90)
    {
        student->grade = 'A';
    }
    else if(student->percentage >= 80)
    {
        student->grade = 'B';
    }
    else if(student->percentage >= 70)
    {
        student->grade = 'C';
    }
    else if(student->percentage >= 60)
    {
        student->grade = 'D';
    }
    else if(student->percentage >= 50)
    {
        student->grade = 'E';
    }
    else
    {
        student->grade = 'F';
    }

    // Determine pass/fail
    if(failedSubject == 1)
    {
        strcpy(student->result, "FAIL");
    }
    else
    {
        strcpy(student->result, "PASS");
    }
}


// Function to display all students
void displayAllStudents(struct Student students[], int count)
{
    int i;

    if(count == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n================ ALL STUDENTS ================\n");

    printf("%-10s %-25s %-10s %-12s %-8s %-10s\n",
           "Roll No", "Name", "Total", "Percentage", "Grade", "Result");

    printf("--------------------------------------------------------------------------\n");

    for(i = 0; i < count; i++)
    {
        printf("%-10d %-25s %-10.2f %-12.2f %-8c %-10s\n",
               students[i].rollNo,
               students[i].name,
               students[i].total,
               students[i].percentage,
               students[i].grade,
               students[i].result);
    }
}


// Function to find student by roll number
int findStudentByRoll(struct Student students[], int count, int rollNo)
{
    int i;

    for(i = 0; i < count; i++)
    {
        if(students[i].rollNo == rollNo)
        {
            return i;
        }
    }

    return -1;
}


// Function to search student
void searchStudent(struct Student students[], int count)
{
    int rollNo;
    int index;

    if(count == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n========== SEARCH STUDENT ==========\n");

    printf("Enter roll number to search: ");
    scanf("%d", &rollNo);

    index = findStudentByRoll(students, count, rollNo);

    if(index == -1)
    {
        printf("\nStudent with roll number %d not found.\n", rollNo);
    }
    else
    {
        printf("\nStudent found!\n");
        displayStudent(students[index]);
    }
}


// Function to display individual student
void displayStudent(struct Student student)
{
    printf("\n========================================\n");
    printf("           STUDENT DETAILS\n");
    printf("========================================\n");

    printf("Roll Number          : %d\n", student.rollNo);
    printf("Name                 : %s\n", student.name);

    printf("----------------------------------------\n");

    printf("C Programming        : %.2f\n", student.marks[0]);
    printf("Data Structures      : %.2f\n", student.marks[1]);
    printf("Mathematics          : %.2f\n", student.marks[2]);
    printf("Computer Organization: %.2f\n", student.marks[3]);
    printf("Operating Systems    : %.2f\n", student.marks[4]);

    printf("----------------------------------------\n");

    printf("Total                : %.2f / 500\n", student.total);
    printf("Percentage           : %.2f%%\n", student.percentage);
    printf("Grade                : %c\n", student.grade);
    printf("Result               : %s\n", student.result);

    printf("========================================\n");
}


// Function to update student
void updateStudent(struct Student students[], int count)
{
    int rollNo;
    int index;

    if(count == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n========== UPDATE STUDENT ==========\n");

    printf("Enter roll number of student: ");
    scanf("%d", &rollNo);

    index = findStudentByRoll(students, count, rollNo);

    if(index == -1)
    {
        printf("\nStudent not found.\n");
        return;
    }

    printf("\nCurrent student information:\n");
    displayStudent(students[index]);

    clearInputBuffer();

    printf("\nEnter new name: ");
    fgets(students[index].name,
          sizeof(students[index].name),
          stdin);

    students[index].name[strcspn(students[index].name, "\n")] = '\0';

    printf("\nEnter new marks:\n");

    students[index].marks[0] = getValidMarks("C Programming");
    students[index].marks[1] = getValidMarks("Data Structures");
    students[index].marks[2] = getValidMarks("Mathematics");
    students[index].marks[3] = getValidMarks("Computer Organization");
    students[index].marks[4] = getValidMarks("Operating Systems");

    // Recalculate result
    calculateResult(&students[index]);

    printf("\nStudent information updated successfully!\n");
}


// Function to delete student
void deleteStudent(struct Student students[], int *count)
{
    int rollNo;
    int index;
    int i;

    if(*count == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n========== DELETE STUDENT ==========\n");

    printf("Enter roll number to delete: ");
    scanf("%d", &rollNo);

    index = findStudentByRoll(students, *count, rollNo);

    if(index == -1)
    {
        printf("\nStudent not found.\n");
        return;
    }

    // Shift all records after deleted record one position left
    for(i = index; i < *count - 1; i++)
    {
        students[i] = students[i + 1];
    }

    (*count)--;

    printf("\nStudent deleted successfully!\n");
}


// Function to clear input buffer
void clearInputBuffer()
{
    int character;

    while((character = getchar()) != '\n' && character != EOF)
    {
        // Clear unwanted characters
    }
}


// Function to display student result
void displayResult(struct Student students[], int count)
{
    int rollNo;
    int index;

    if(count == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n========== DISPLAY RESULT ==========\n");

    printf("Enter roll number: ");
    scanf("%d", &rollNo);

    index = findStudentByRoll(students, count, rollNo);

    if(index == -1)
    {
        printf("\nStudent not found.\n");
    }
    else
    {
        displayStudent(students[index]);
    }
}