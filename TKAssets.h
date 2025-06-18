#ifndef TKASSETS_MAIN_H
#define TKASSETS_MAIN_H

#define __need_size_t
#include <stddef.h>
#include <stdint.h>

typedef enum
{
    TKAST_TEXT_FILE,
    TKAST_SPIRV_FILE,
    TKAST_VERTEX_FILE,
    TKAST_FRAGMENT_FILE,
} tkast_file_type_t;

typedef struct
{
    const char *name;
    // size+1 (term. NUL)
    uint8_t *content;
    size_t size;
    tkast_file_type_t type;
} tkast_file_t;

static const size_t tkast_maxPathLength = 512;
static const char *const tkast_baseDirectory = "./Resources";

inline const char *tkast_getExtension(tkast_file_type_t type)
{
    switch (type)
    {
        case TKAST_SPIRV_FILE:    return ".spv";
        case TKAST_VERTEX_FILE:   return ".vert";
        case TKAST_FRAGMENT_FILE: return ".frag";
        case TKAST_TEXT_FILE:     [[fallthrough]];
        default:                  return ".txt";
    }
}

inline const char *tkast_getDirectory(tkast_file_type_t type)
{
    switch (type)
    {
        case TKAST_VERTEX_FILE:   [[fallthrough]];
        case TKAST_FRAGMENT_FILE: [[fallthrough]];
        case TKAST_SPIRV_FILE:    return "Shaders";
        case TKAST_TEXT_FILE:     [[fallthrough]];
        default:                  return ".";
    }
}

bool tkast_loadFile(tkast_file_t *file);

bool tkast_writeFile(tkast_file_t *file, const uint8_t *contents);

#endif // TKASSETS_MAIN_H
