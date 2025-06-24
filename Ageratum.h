/**
 * @file Ageratum.h
 * @authors Israfil Argos
 * @brief This file provides both the public interface and implementation for
 * the header-only Ageratum asset library. All code for the library is defined
 * within this file.
 * @since v0.0.0.1
 *
 * @copyright (c) 2025 - the Waterlily Team
 * This source file is under the GNU General Public License v3.0. For licensing
 * and other information, see the @c LICENSE.md file that should have come with
 * your copy of the source code, or https://www.gnu.org/licenses/gpl-3.0.txt.
 */
#ifndef AGERATUM_H
#define AGERATUM_H

#define AGERATUM_MAJOR_VERSION 0
#define AGERATUM_MINOR_VERSION 0
#define AGERATUM_PATCH_VERSION 0
#define AGERATUM_TWEAK_VERSION 13

#define __need_size_t
#include <stddef.h>

#define AGERATUM_BASE_DIRECTORY "./Resources/"
#define AGERATUM_MAX_PATH_LENGTH 128
#define AGERATUM_MAX_FILENAME_LENGTH 32

typedef unsigned char ageratum_byte_t;

typedef enum ageratum_permissions
{
    AGERATUM_READ = 114,
    AGERATUM_WRITE = 119,
    AGERATUM_APPEND = 97,
    AGERATUM_READWRITE = 0,
} ageratum_permissions_t;

typedef enum ageratum_type
{
    AGERATUM_UNKNOWN,
    AGERATUM_TEXT,
    AGERATUM_GLSL_VERTEX,
    AGERATUM_GLSL_FRAGMENT,
    AGERATUM_SPIRV_VERTEX,
    AGERATUM_SPIRV_FRAGMENT,
} ageratum_type_t;

typedef struct ageratum_file
{
    const char *const filename;
    ageratum_type_t type;
    void *handle;
    size_t size;
} ageratum_file_t;

bool ageratum_openFile(ageratum_file_t *file,
                       ageratum_permissions_t permissions);

bool ageratum_closeFile(ageratum_file_t *file);

bool ageratum_loadFile(ageratum_file_t *file, char *contents);

bool ageratum_writeFile(ageratum_file_t *file, const char *const contents);

bool ageratum_getFileSize(ageratum_file_t *file);

///////////////////////////////////////////////////////////////////////////////
//                              IMPLEMENTATION                               //
// ////////////////////////////////////////////////////////////////////////////
#ifdef AGERATUM_IMPLEMENTATION

#include <WLLogging.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

static const char *const ageratum_subdirectories[] = {
    [AGERATUM_UNKNOWN] = 0,
    [AGERATUM_TEXT] = 0,
    [AGERATUM_GLSL_VERTEX] = "Shaders/Source/",
    [AGERATUM_GLSL_FRAGMENT] = "Shaders/Source/",
    [AGERATUM_SPIRV_VERTEX] = "Shaders/Compiled/",
    [AGERATUM_SPIRV_FRAGMENT] = "Shaders/Compiled/",
};

static const char *const ageratum_extensions[] = {
    [AGERATUM_UNKNOWN] = 0,
    [AGERATUM_TEXT] = ".txt",
    [AGERATUM_GLSL_VERTEX] = ".vert",
    [AGERATUM_GLSL_FRAGMENT] = ".frag",
    [AGERATUM_SPIRV_VERTEX] = "-vert.spv",
    [AGERATUM_SPIRV_FRAGMENT] = "-frag.spv",
};

bool ageratum_openFile(ageratum_file_t *file,
                       ageratum_permissions_t permissions)
{
    char path[AGERATUM_MAX_PATH_LENGTH + 1] = AGERATUM_BASE_DIRECTORY;
    (void)strncat(path, ageratum_subdirectories[file->type],
                  AGERATUM_MAX_PATH_LENGTH);
    (void)strncat(path, file->filename, AGERATUM_MAX_PATH_LENGTH);
    (void)strncat(path, ageratum_extensions[file->type],
                  AGERATUM_MAX_PATH_LENGTH);

    char mode[3];
    if (__builtin_expect(permissions == AGERATUM_READWRITE, 0))
    {
        mode[0] = 'w';
        mode[1] = '+';
    }
    else mode[0] = permissions;

    file->handle = (void *)fopen(path, mode);
    if (__builtin_expect(file->handle == nullptr, 0))
    {
        waterlily_log(ERROR, "Failed to open file '%s'.", path);
        return false;
    }
    waterlily_log(VERBOSE_OK, "Opened file '%s'.", path);
    return true;
}

bool ageratum_closeFile(ageratum_file_t *file)
{
    if (__builtin_expect(fclose(file->handle) != 0, 0))
    {
        waterlily_log(ERROR, "Failed to close file '%s'.", file->filename);
        return false;
    }
    return true;
}

bool ageratum_getFileSize(ageratum_file_t *file)
{
    struct stat stats;
    // Nearly 10x faster than fseek/ftell in my tests.
    fstat(fileno(file->handle), &stats);
    file->size = stats.st_size;
    return true;
}

bool ageratum_loadFile(ageratum_file_t *file, char *contents)
{
    fread(contents, 1, file->size, file->handle);
    contents[file->size] = 0;
    return true;
}

bool ageratum_writeFile(ageratum_file_t *file, const char *const contents)
{
    if (fwrite(contents, 1, file->size, file->handle) != file->size)
    {
        waterlily_log(ERROR, "Failed to write to file '%s'.", file->filename);
        return false;
    }
    waterlily_log(VERBOSE_OK, "Wrote %zu bytes to file '%s'.", file->size,
                  file->filename);
    return true;
}

#endif
///////////////////////////////////////////////////////////////////////////////
//                            IMPLEMENTATION END                             //
// ////////////////////////////////////////////////////////////////////////////

#endif // AGERATUM_H
