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

#define __need_size_t
#include <stddef.h>

#define AGERATUM_MAJOR_VERSION 0
#define AGERATUM_MINOR_VERSION 0
#define AGERATUM_PATCH_VERSION 0
#define AGERATUM_TWEAK_VERSION 15

#ifndef AGERATUM_BASE_DIRECTORY
#define AGERATUM_BASE_DIRECTORY "./Resources/"
#endif

#ifndef AGERATUM_SYSTEM_DIRECTORY
#define AGERATUM_SYSTEM_DIRECTORY "/usr/bin/"
#endif

#define AGERATUM_MAX_PATH_LENGTH 128
#define AGERATUM_MAX_FILENAME_LENGTH 32

typedef enum ageratum_permissions
{
    AGERATUM_READ,
    AGERATUM_WRITE,
    AGERATUM_APPEND,
    AGERATUM_READWRITE,
    AGERATUM_APPENDWRITE,
} ageratum_permissions_t;

typedef enum ageratum_type
{
    AGERATUM_UNKNOWN,
    AGERATUM_TEXT,
    AGERATUM_GLSL_VERTEX,
    AGERATUM_GLSL_FRAGMENT,
    AGERATUM_SPIRV_VERTEX,
    AGERATUM_SPIRV_FRAGMENT,
    AGERATUM_SYSTEM,
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

[[gnu::always_inline]]
inline bool ageratum_closeFile(ageratum_file_t *file);

bool ageratum_loadFile(ageratum_file_t *file, char *contents);

bool ageratum_writeFile(ageratum_file_t *file, const char *const contents);

bool ageratum_getFileSize(ageratum_file_t *file);

bool ageratum_executeFile(const ageratum_file_t *const file,
                          const char *const *const argv, size_t argc,
                          int *status);

// TODO: "Workflow" functionality, where this can be generalized into a process
// TODO: for many different file types.
bool ageratum_glslToSPIRV(const ageratum_file_t *const file);

///////////////////////////////////////////////////////////////////////////////
//                              IMPLEMENTATION                               //
// ////////////////////////////////////////////////////////////////////////////
#ifdef AGERATUM_IMPLEMENTATION

#include <WLLogging.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

static const char *const ageratum_subdirectories[] = {
    [AGERATUM_UNKNOWN] = 0,
    [AGERATUM_TEXT] = 0,
    [AGERATUM_GLSL_VERTEX] = "Shaders/Source/",
    [AGERATUM_GLSL_FRAGMENT] = "Shaders/Source/",
    [AGERATUM_SPIRV_VERTEX] = "Shaders/Compiled/",
    [AGERATUM_SPIRV_FRAGMENT] = "Shaders/Compiled/",
    [AGERATUM_SYSTEM] = "",
};

static const char *const ageratum_extensions[] = {
    [AGERATUM_UNKNOWN] = 0,
    [AGERATUM_TEXT] = ".txt",
    [AGERATUM_GLSL_VERTEX] = ".vert",
    [AGERATUM_GLSL_FRAGMENT] = ".frag",
    [AGERATUM_SPIRV_VERTEX] = "-vert.spv",
    [AGERATUM_SPIRV_FRAGMENT] = "-frag.spv",
    [AGERATUM_SYSTEM] = "",
};

static void ageratum_createFilepath(const ageratum_file_t *const file,
                                    char *path)
{
    if (file->type != AGERATUM_SYSTEM)
        (void)strncat(path, AGERATUM_BASE_DIRECTORY, AGERATUM_MAX_PATH_LENGTH);
    else
        (void)strncat(path, AGERATUM_SYSTEM_DIRECTORY,
                      AGERATUM_MAX_PATH_LENGTH);
    (void)strncat(path, ageratum_subdirectories[file->type],
                  AGERATUM_MAX_PATH_LENGTH);
    (void)strncat(path, file->filename, AGERATUM_MAX_PATH_LENGTH);
    (void)strncat(path, ageratum_extensions[file->type],
                  AGERATUM_MAX_PATH_LENGTH);
}

bool ageratum_openFile(ageratum_file_t *file,
                       ageratum_permissions_t permissions)
{
    char path[AGERATUM_MAX_PATH_LENGTH];
    ageratum_createFilepath(file, path);

    char *mode;
    switch (permissions)
    {
        case AGERATUM_READ:        mode = "r"; break;
        case AGERATUM_WRITE:       mode = "w"; break;
        case AGERATUM_APPEND:      mode = "a"; break;
        case AGERATUM_READWRITE:   mode = "w+"; break;
        case AGERATUM_APPENDWRITE: mode = "a+"; break;
    }

    file->handle = (void *)fopen(path, mode);
    if (__builtin_expect(file->handle == nullptr, 0))
    {
        waterlily_log(ERROR, "Failed to open file '%s'.", path);
        return false;
    }
    waterlily_log(VERBOSE_OK, "Opened file '%s'.", path);
    return true;
}

inline bool ageratum_closeFile(ageratum_file_t *file)
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

bool ageratum_executeFile(const ageratum_file_t *const file,
                          const char *const *const argv, size_t argc,
                          int *status)
{
    char path[AGERATUM_MAX_PATH_LENGTH];
    ageratum_createFilepath(file, path);

    if (access(path, X_OK) == -1)
    {
        waterlily_log(ERROR, "Cannot execute file '%s'.", path);
        return false;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        waterlily_log(ERROR, "Failed to fork process.");
        return false;
    }

    char *trueArgv[argc + 2];
    trueArgv[0] = path;
    for (size_t i = 0; i < argc; i++) trueArgv[i + 1] = (char *)argv[i];
    trueArgv[argc + 1] = nullptr;

    // This is executed within the new process.
    if (pid == 0 && execve(path, (char *const *)trueArgv, nullptr) == -1)
    {
        waterlily_log(ERROR, "Failed to execute file '%s'.", path);
        return false;
    }

    int processStatus = 0;
    pid_t waitStatus = waitpid(pid, &processStatus, 0);
    if (waitStatus == (pid_t)-1)
    {
        waterlily_log(WARNING, "Unable to wait for execution of '%s'.", path);
        return false;
    }

    if (!WIFEXITED(processStatus))
    {
        waterlily_log(WARNING,
                      "File '%s' ended execution with an unexpected result.",
                      path);
        return false;
    }
    *status = WEXITSTATUS(processStatus);
    return true;
}

bool ageratum_glslToSPIRV(const ageratum_file_t *const file)
{
    ageratum_file_t glslangFile = {.filename = "glslang",
                                   .type = AGERATUM_SYSTEM};

    char path[AGERATUM_MAX_PATH_LENGTH];
    ageratum_createFilepath(file, path);

    char outputPath[AGERATUM_MAX_PATH_LENGTH];
    ageratum_file_t outputFile = *file;
    outputFile.type =
        (file->type == AGERATUM_GLSL_FRAGMENT ? AGERATUM_SPIRV_FRAGMENT
                                              : AGERATUM_SPIRV_VERTEX);
    ageratum_createFilepath(&outputFile, outputPath);

    const char *const argv[] = {
        "--target-env",   "vulkan1.3", "-e",          "main",  "-g0",     "-t",
        "--glsl-version", "460",       "--spirv-val", "--lto", "--quiet", "-o",
        outputPath,       path,
    };
    int status = 0;
    if (!ageratum_executeFile(&glslangFile, argv, 14, &status))
    {
        waterlily_log(ERROR, "Couldn't compile shader '%s'. Code %d.", path,
                      status);
        return false;
    }

    return true;
}

#endif
///////////////////////////////////////////////////////////////////////////////
//                            IMPLEMENTATION END                             //
// ////////////////////////////////////////////////////////////////////////////

#endif // AGERATUM_H
