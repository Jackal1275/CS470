#include "CS470_Lab4_libFS.h"
#include <stdio.h>
#include <stdlib.h>

void menu() {
    printf("\nUser-Level File System (libFS)\n");
    printf("1. Create File\n");
    printf("2. Write Introduction\n");
    printf("3. Read File\n");
    printf("4. Delete File\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
}

int main() {
    const char *filename = "JackSchenck_Introduction.txt";
    FILE *fp = NULL;
    int choice;
    char *intro =
        "Hello, my name is JackSchenck. I am currently pursuing studies in computer science, "
        "and I enjoy exploring systems programming, especially around operating systems.\n\n"
        "Outside of academics, I enjoy solving coding challenges and working on personal "
        "software projects. This exercise is a great opportunity to apply what I’ve learned.\n";

    while (1) {
        menu();
        scanf("%d", &choice);
        getchar();  // Consume newline

        switch (choice) {
            case 1:
                if (fileCreate(filename) == 0)
                    printf("File created: %s\n", filename);
                else
                    printf("Error creating file.\n");
                break;
            case 2:
                fp = fileOpen(filename, "w");
                if (fp == NULL) {
                    printf("File open failed.\n");
                    break;
                }
                fileWrite(fp, intro);
                fileClose(fp);
                printf("Introduction written to file.\n");
                break;
            case 3:
                fp = fileOpen(filename, "r");
                if (fp == NULL) {
                    printf("File open failed.\n");
                    break;
                }
                printf("Reading file contents:\n\n");
                fileRead(fp);
                fileClose(fp);
                break;
            case 4:
                if (fileDelete(filename) == 0)
                    printf("File deleted: %s\n", filename);
                else
                    printf("Error deleting file.\n");
                break;
            case 5:
                printf("Exiting libFS system.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
