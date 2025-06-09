#include "CS470_Lab4_libFS.h"
#include <stdio.h>
#include <stdlib.h>

int fileCreate(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) return -1;
    fclose(file);
    return 0;
}

FILE* fileOpen(const char *filename, const char *mode) {
    return fopen(filename, mode);
}

int fileWrite(FILE *file, const char *content) {
    if (file == NULL) return -1;
    fprintf(file, "%s", content);
    return 0;
}

int fileRead(FILE *file) {
    if (file == NULL) return -1;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    return 0;
}

int fileClose(FILE *file) {
    return fclose(file);
}

int fileDelete(const char *filename) {
    return remove(filename);
}
