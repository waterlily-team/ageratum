#ifndef WLASSETS_MAIN_H
#define WLASSETS_MAIN_H

#define __need_size_t
#include <stddef.h>
#include <stdint.h>

typedef enum
{
    WATERLILY_TEXT_FILE,
    WATERLILY_SPIRV_FILE,
    WATERLILY_VERTEX_FILE,
    WATERLILY_FRAGMENT_FILE,
} waterlily_file_type_t;

typedef struct
{
    const char *name;
    // size+1 (term. NUL)
    uint8_t *content;
    size_t size;
    waterlily_file_type_t type;
} waterlily_file_t;

static const size_t waterlily_maxPathLength = 512;
static const char *const waterlily_baseDirectory = "./Resources";

inline const char *waterlily_getExtension(waterlily_file_type_t type)
{
    switch (type)
    {
        case WATERLILY_SPIRV_FILE:    return ".spv";
        case WATERLILY_VERTEX_FILE:   return ".vert";
        case WATERLILY_FRAGMENT_FILE: return ".frag";
        case WATERLILY_TEXT_FILE:     [[fallthrough]];
        default:                      return ".txt";
    }
}

inline const char *waterlily_getDirectory(waterlily_file_type_t type)
{
    switch (type)
    {
        case WATERLILY_VERTEX_FILE:   [[fallthrough]];
        case WATERLILY_FRAGMENT_FILE: [[fallthrough]];
        case WATERLILY_SPIRV_FILE:    return "Shaders";
        case WATERLILY_TEXT_FILE:     [[fallthrough]];
        default:                      return ".";
    }
}

bool waterlily_loadFile(waterlily_file_t *file);

bool waterlily_writeFile(waterlily_file_t *file, const uint8_t *contents);

#ifdef WLASSETS_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>

bool waterlily_loadFile(waterlily_file_t *file)
{
    char *path = malloc(waterlily_maxPathLength);
    snprintf(path, waterlily_maxPathLength, "%s/%s/%s%s",
             waterlily_baseDirectory, waterlily_getDirectory(file->type),
             file->name, waterlily_getExtension(file->type));

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

bool waterlily_writeFile(waterlily_file_t *file, const uint8_t *contents)
{
    char *path = malloc(waterlily_maxPathLength);
    snprintf(path, waterlily_maxPathLength, "%s/%s/%s%s",
             waterlily_baseDirectory, waterlily_getDirectory(file->type),
             file->name, waterlily_getExtension(file->type));

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

#endif // WLASSETS_MAIN_H
