#ifndef LIBFS_H
#define LIBFS_H

#include <stdio.h>

int fileCreate(const char *filename);
FILE* fileOpen(const char *filename, const char *mode);
int fileWrite(FILE *file, const char *content);
int fileRead(FILE *file);
int fileClose(FILE *file);
int fileDelete(const char *filename);

#endif
