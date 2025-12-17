#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student structure
typedef struct Student {
    int id;
    char name[50];
    float marks;
    struct Student* next;
} Student;

// Insert at head
Student* insertStudent(Student* head, int id, char name[], float marks) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->marks = marks;
    newStudent->next = head;
    return newStudent;
}

// Display all students
void displayStudents(Student* head) {
    Student* temp = head;
    printf("\nID\tName\tMarks\n");
    while(temp != NULL) {
        printf("%d\t%s\t%.2f\n", temp->id, temp->name, temp->marks);
        temp = temp->next;
    }
}

// Search by ID
Student* searchByID(Student* head, int id) {
    Student* temp = head;
    while(temp != NULL) {
        if(temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Delete by ID
Student* deleteByID(Student* head, int id) {
    Student* temp = head;
    Student* prev = NULL;

    while(temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL) return head; // Not found

    if(prev == NULL) { // Delete head
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    return head;
}

// Update student
void updateStudent(Student* student, char name[], float marks) {
    if(student) {
        strcpy(student->name, name);
        student->marks = marks;
    }
}

// Merge two sorted lists
Student* mergeSorted(Student* a, Student* b, int key) {
    if(!a) return b;
    if(!b) return a;

    Student* result = NULL;

    if(key == 1 ? a->id <= b->id : 
       key == 2 ? strcmp(a->name, b->name) <= 0 :
                  a->marks <= b->marks) {
        result = a;
        result->next = mergeSorted(a->next, b, key);
    } else {
        result = b;
        result->next = mergeSorted(a, b->next, key);
    }
    return result;
}

// Split list for merge sort
void splitList(Student* source, Student** front, Student** back) {
    Student* slow = source;
    Student* fast = source->next;

    while(fast) {
        fast = fast->next;
        if(fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

// Merge sort linked list
void mergeSort(Student** headRef, int key) {
    Student* head = *headRef;
    if(!head || !head->next) return;

    Student* a;
    Student* b;

    splitList(head, &a, &b);
    mergeSort(&a, key);
    mergeSort(&b, key);

    *headRef = mergeSorted(a, b, key);
}

// Main menu
int main() {
    Student* head = NULL;
    int choice, id, key;
    char name[50];
    float marks;
    Student* temp;

    do {
        printf("\n1. Insert  2. Display  3. Search  4. Delete  5. Update  6. Sort  0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter ID, Name, Marks: ");
                scanf("%d %s %f", &id, name, &marks);
                head = insertStudent(head, id, name, marks);
                break;
            case 2:
                displayStudents(head);
                break;
            case 3:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                temp = searchByID(head, id);
                if(temp) printf("Found: %d %s %.2f\n", temp->id, temp->name, temp->marks);
                else printf("Not found.\n");
                break;
            case 4:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                head = deleteByID(head, id);
                break;
            case 5:
                printf("Enter ID to update: ");
                scanf("%d", &id);
                temp = searchByID(head, id);
                if(temp) {
                    printf("Enter new Name and Marks: ");
                    scanf("%s %f", name, &marks);
                    updateStudent(temp, name, marks);
                } else printf("Student not found.\n");
                break;
            case 6:
                printf("Sort by: 1-ID 2-Name 3-Marks: ");
                scanf("%d", &key);
                mergeSort(&head, key);
                break;
        }
    } while(choice != 0);

    return 0;
}
