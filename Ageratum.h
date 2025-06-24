#ifndef AGERATUM_H
#define AGERATUM_H

#define __need_size_t
#include <stddef.h>
#include <stdint.h>

typedef enum
{
    AGERATUM_TEXT_FILE,
    AGERATUM_SPIRV_FILE,
    AGERATUM_VERTEX_FILE,
    AGERATUM_FRAGMENT_FILE,
} ageratum_file_type_t;

typedef struct
{
    const char *name;
    // size+1 (term. NUL)
    uint8_t *content;
    size_t size;
    ageratum_file_type_t type;
} ageratum_file_t;

static const size_t ageratum_maxPathLength = 512;
static const char *const ageratum_baseDirectory = "./Resources";

inline const char *ageratum_getExtension(ageratum_file_type_t type)
{
    switch (type)
    {
        case AGERATUM_SPIRV_FILE:    return ".spv";
        case AGERATUM_VERTEX_FILE:   return ".vert";
        case AGERATUM_FRAGMENT_FILE: return ".frag";
        case AGERATUM_TEXT_FILE:     [[fallthrough]];
        default:                     return ".txt";
    }
}

inline const char *ageratum_getDirectory(ageratum_file_type_t type)
{
    switch (type)
    {
        case AGERATUM_VERTEX_FILE:   [[fallthrough]];
        case AGERATUM_FRAGMENT_FILE: [[fallthrough]];
        case AGERATUM_SPIRV_FILE:    return "Shaders";
        case AGERATUM_TEXT_FILE:     [[fallthrough]];
        default:                     return ".";
    }
}

bool ageratum_loadFile(ageratum_file_t *file);

bool ageratum_writeFile(ageratum_file_t *file, const uint8_t *contents);

#ifdef AGERATUM_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>

bool ageratum_loadFile(ageratum_file_t *file)
{
    char *path = malloc(ageratum_maxPathLength);
    snprintf(path, ageratum_maxPathLength, "%s/%s/%s%s", ageratum_baseDirectory,
             ageratum_getDirectory(file->type), file->name,
             ageratum_getExtension(file->type));

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

bool ageratum_writeFile(ageratum_file_t *file, const uint8_t *contents)
{
    char *path = malloc(ageratum_maxPathLength);
    snprintf(path, ageratum_maxPathLength, "%s/%s/%s%s", ageratum_baseDirectory,
             ageratum_getDirectory(file->type), file->name,
             ageratum_getExtension(file->type));

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

#endif

#endif // AGERATUM_H
