#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "tasks.txt"

struct Task {
    int id;
    char task[100];
    int completed;
};


void addTask() {
    struct Task t;
    FILE *file = fopen(FILE_NAME, "a");

    if (file == NULL) {
        printf("Error opening file!\n"); 
        return;
    }

    printf("\nEnter Task ID: ");
    scanf("%d", &t.id);

    getchar(); 

    printf("Enter Task: ");
    fgets(t.task, sizeof(t.task), stdin);

   
    t.task[strcspn(t.task, "\n")] = '\0';

    t.completed = 0;

    fprintf(file, "%d|%s|%d\n", t.id, t.task, t.completed);

    fclose(file);

    printf("Task added successfully!\n");
}


void viewTasks() {
    struct Task t;
    FILE *file = fopen(FILE_NAME, "r");

    if (file == NULL) {
        printf("\nNo tasks found.\n");
        return;
    }

    printf("\n========== DAILY TASK LIST ==========\n");

    while (fscanf(file, "%d|%99[^|]|%d\n",
                  &t.id, t.task, &t.completed) == 3) {

        printf("\nID: %d", t.id);
        printf("\nTask: %s", t.task);

        if (t.completed)
            printf("\nStatus: Completed\n");
        else
            printf("\nStatus: Pending\n");
    }

    fclose(file);
}


void completeTask() {
    struct Task t;
    int id;
    int found = 0;

    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Task ID to mark as completed: ");
    scanf("%d", &id);

    while (fscanf(file, "%d|%99[^|]|%d\n",
                  &t.id, t.task, &t.completed) == 3) {

        if (t.id == id) {
            t.completed = 1;
            found = 1;
        }

        fprintf(temp, "%d|%s|%d\n",
                t.id, t.task, t.completed);
    }

    fclose(file);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Task marked as completed!\n");
    else
        printf("Task ID not found!\n");
}


int main() {
    int choice;

    while (1) {
        printf("\n\n========== DAILY TASK MANAGER ==========\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Mark Task as Completed\n");
        printf("4. Exit\n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask();
                break;

            case 2:
                viewTasks();
                break;

            case 3:
                completeTask();
                break;

            case 4:
                printf("\nThank you for using Task Manager!\n");
                exit(0);

            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}

