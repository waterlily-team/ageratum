#include <TKAssets.h>
#include <stdio.h>
#include <stdlib.h>

bool tkast_loadFile(tkast_file_t *file)
{
    char *path = malloc(tkast_maxPathLength);
    snprintf(path, tkast_maxPathLength, "%s/%s/%s%s", tkast_baseDirectory,
             tkast_getDirectory(file->type), file->name,
             tkast_getExtension(file->type));

    FILE *fileHandle = fopen(path, "r");
    if (fileHandle == nullptr)
    {
        // TODO: Better handling of this.
        printf("Failed to open file '%s'.\n", path);
        return false;
    }

    fseek(fileHandle, 0, SEEK_END);
    file->size = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);

    file->content = malloc(file->size + 1);
    long read = fread(file->content, 1, file->size, fileHandle);
    (void)read; // TODO: Implement check.
    file->content[file->size] = 0;

    fclose(fileHandle);
    return true;
}

bool tkast_writeFile(tkast_file_t *file, const uint8_t *contents)
{
    char *path = malloc(tkast_maxPathLength);
    snprintf(path, tkast_maxPathLength, "%s/%s/%s%s", tkast_baseDirectory,
             tkast_getDirectory(file->type), file->name,
             tkast_getExtension(file->type));

    FILE *fileHandle = fopen(path, "w");
    if (fileHandle == nullptr)
    {
        // TODO: Better handling of this.
        printf("Failed to open file '%s'.\n", path);
        return false;
    }

    long written = fwrite(contents, 1, file->size, fileHandle);
    (void)written;

    fclose(fileHandle);
    return true;
}
