#include <TKAssets.h>
#include <stdio.h>
#include <stdlib.h>

bool tkast_loadFile(const char *name, tkast_file_t *file)
{
    char *path = malloc(tkast_maxPathLength);
    snprintf(path, tkast_maxPathLength, "%s/%s/%s",
             tkast_getDirectory(file->type), name,
             tkast_getExtension(file->type));

    FILE *fileHandle = fopen(path, "r");

    fseek(fileHandle, 0, SEEK_END);
    file->size = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);

    file->content = malloc(file->size);
    long read = fread(file->content, 1, file->size, fileHandle);
    (void)read; // TODO: Implement check.

    fclose(fileHandle);
    return true;
}
