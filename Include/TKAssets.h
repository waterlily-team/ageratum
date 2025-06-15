#ifndef TKAST_MAIN_H
#define TKAST_MAIN_H

#define __need_size_t
#include <stddef.h>
#include <stdint.h>

typedef enum
{
    TKAST_TEXT_FILE,
    TKAST_SPIRV_FILE
} tkast_file_type_t;

typedef struct
{
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
        case TKAST_SPIRV_FILE: return ".spv";
        case TKAST_TEXT_FILE:  [[fallthrough]];
        default:               return ".txt";
    }
}

inline const char *tkast_getDirectory(tkast_file_type_t type)
{
    switch (type)
    {
        case TKAST_SPIRV_FILE: return "Shaders";
        case TKAST_TEXT_FILE:  [[fallthrough]];
        default:               return ".";
    }
}

bool tkast_loadFile(const char *name, tkast_file_t *file);

#endif // TKAST_MAIN_H
