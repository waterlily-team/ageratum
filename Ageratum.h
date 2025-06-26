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

/**
 * @def AGERATUM_MAJOR_VERSION
 * @brief The major (X.x.x.x) version of the library. This increments after a
 * huge overhaul or large project completion.
 * @since v0.0.0.12
 */
#define AGERATUM_MAJOR_VERSION 0

/**
 * @def AGERATUM_MINOR_VERSION
 * @brief The minor (x.X.x.x) version of the library. This increments after a
 * project completion.
 * @since v0.0.0.12
 */
#define AGERATUM_MINOR_VERSION 0

/**
 * @def AGERATUM_PATCH_VERSION
 * @brief The patch (x.x.X.x) version of the library. This increments when a
 * featureset is properly implemented.
 * @since v0.0.0.12
 */
#define AGERATUM_PATCH_VERSION 0

/**
 * @def AGERATUM_TWEAK_VERSION
 * @brief The tweak (x.x.x.X) version of the library. This increments after any
 * new code is committed.
 * @since v0.0.0.12
 */
#define AGERATUM_TWEAK_VERSION 27

/**
 * @def AGERATUM_BASE_DIRECTORY
 * @brief The base directory for project assets. This is not where external
 * files are looked for, for that see @ref AGERATUM_SYSTEM_DIRECTORY.
 * @since v0.0.0.13
 */
#define AGERATUM_BASE_DIRECTORY "./Assets/"

/**
 * @def AGERATUM_BASE_DIRECTORY_LENGTH
 * @brief The length in characters of the base asset directory filepath,
 * excluding the null terminator.
 * @since v0.0.0.17
 */
#define AGERATUM_BASE_DIRECTORY_LENGTH 9

// Allow the user/application to define their own system directory.
#ifndef AGERATUM_SYSTEM_DIRECTORY
/**
 * @def AGERATUM_SYSTEM_DIRECTORY
 * @brief The system directory for external assets like executables and
 * libraries. This is not where internal asset files are looked for, for that
 * see @ref AGERATUM_BASE_DIRECTORY.
 * @since v0.0.0.14
 */
#define AGERATUM_SYSTEM_DIRECTORY "/usr/bin/"
#endif

/**
 * @def AGERATUM_SYSTEM_DIRECTORY_LENGTH
 * @brief The length in characters of the system asset directory filepath,
 * excluding the null terminator.
 * @since v0.0.0.19
 */
#define AGERATUM_SYSTEM_DIRECTORY_LENGTH sizeof(AGERATUM_SYSTEM_DIRECTORY) - 1

/**
 * @def AGERATUM_MAX_PATH_LENGTH
 * @brief The max length in characters (plus the null terminator) a path can be
 * in order to be properly handled by the library. This is defined for
 * efficiency and performance reasons.
 * @since v0.0.0.13
 */
#define AGERATUM_MAX_PATH_LENGTH 128

/**
 * @enum ageratum_permissions
 * @brief The various permissions that a file may be opened under. This is not a
 * bitmask, each enum value corresponds to a different logic chain which is
 * entirely exclusive from the others.
 * @since v0.0.0.13
 *
 * @showenumvalues
 */
typedef enum ageratum_permissions
{
    /**
     * @var ageratum_permissions AGERATUM_READ
     * @brief Open the file in read-only mode.
     * @since v0.0.0.13
     */
    AGERATUM_READ,
    /**
     * @var ageratum_permissions AGERATUM_WRITE
     * @brief Open the file in writing mode, with the file pointer at the
     * beginning of the file. If the file doesn't exist, it will be created.
     * @since v0.0.0.13
     */
    AGERATUM_WRITE,
    /**
     * @var ageratum_permissions AGERATUM_APPEND
     * @brief Open the file in writing mode, with the file pointer at the end of
     * the file. If the file doesn't exist, it will be created.
     * @since v0.0.0.13
     */
    AGERATUM_APPEND,
    /**
     * @var ageratum_permissions AGERATUM_READWRITE
     * @brief Open the file in reading and writing mode simultaneously, with the
     * file pointer at the beginning of the file. If the file doesn't exist, it
     * will be created.
     * @since v0.0.0.13
     */
    AGERATUM_READWRITE,
    /**
     * @var ageratum_permissions AGERATUM_READAPPEND
     * @brief Open the file in reading and writing mode simultaneously, with the
     * file pointer at the end of the file. If the file doesn't exist, it will
     * be created.
     * @since v0.0.0.15
     */
    AGERATUM_READAPPEND,
} ageratum_permissions_t;

/**
 * @enum ageratum_type
 * @brief The various types of files that have specific handling cases within
 * the library. This is not a bitmask.
 * @since v0.0.0.12
 *
 * @showenumvalues
 */
typedef enum ageratum_type
{
    /**
     * @var ageratum_type AGERATUM_TEXT
     * @brief A text file. This has no special handling protocols; it's treated
     * as a string of bytes. It comes with the extension ".txt".
     * @since v0.0.0.1
     */
    AGERATUM_TEXT,
    /**
     * @var ageratum_type AGERATUM_GLSL_VERTEX
     * @brief A GLSL vertex shader file. This is one of the possible inputs for
     * the GLSL->SPIRV workflow. It comes with the extension ".vert".
     * @since v0.0.0.2
     */
    AGERATUM_GLSL_VERTEX,
    /**
     * @var ageratum_type AGERATUM_GLSL_FRAGMENT
     * @brief A GLSL fragment shader file. This is one of the possible inputs
     * for the GLSL->SPIRV workflow. It comes with the extension ".frag".
     * @since v0.0.0.2
     */
    AGERATUM_GLSL_FRAGMENT,
    /**
     * @var ageratum_type AGERATUM_SPIRV_VERTEX
     * @brief A SPIRV vertex shader file. This is treated as a string of bytes,
     * and is the output for the GLSL->SPIRV workflow. It comes with the
     * extension "-vert.spv".
     * @since v0.0.0.13
     */
    AGERATUM_SPIRV_VERTEX,
    /**
     * @var ageratum_type AGERATUM_SPIRV_FRAGMENT
     * @brief A SPIRV fragment shader file. This is treated as a string of
     * bytes, and is the output for the GLSL->SPIRV workflow. It comes with the
     * extension "-frag.spv".
     * @since v0.0.0.13
     */
    AGERATUM_SPIRV_FRAGMENT,
    /**
     * @var ageratum_type AGERATUM_SYSTEM
     * @brief A system executable file. If attempted to be loaded, this is
     * handled as a string of bytes. This filetype can be used as an input for
     * the @ref ageratum_executeFile function. This comes with no file
     * extension.
     * @since v0.0.0.14
     */
    AGERATUM_SYSTEM,
} ageratum_type_t;

/**
 * @def AGERATUM_TYPE_COUNT
 * @brief The count of recognized filetypes by the library.
 * @since v0.0.0.18
 */
#define AGERATUM_TYPE_COUNT 6

/**
 * @struct ageratum_file Ageratum.h "Ageratum.h"
 * @brief The core file structure for the library. This contains all important
 * information about a generic file, including its type, filename, handle, and
 * size.
 * @since v0.0.0.1
 */
typedef struct ageratum_file
{
    /**
     * @property basename
     * @brief The basename of the file.
     * @since v0.0.0.1
     */
    char *basename;
    /**
     * @property type
     * @brief The type of the file.
     * @since v0.0.0.13
     */
    ageratum_type_t type;
    /**
     * @property handle
     * @brief The underlying handle of the file within the filesystem.
     * @since v0.0.0.13
     *
     * @remark This is actually of the type FILE*, but in order to prevent a
     * mostly unnessecary @c stdio.h include, it's just referenced as a void
     * pointer.
     */
    void *handle;
    /**
     * @property size
     * @brief The size of the file in bytes.
     * @since v0.0.0.1
     */
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

// TODO: "Workflow" functionality, where this can be generalized into a
// process
// TODO: for many different file types.
bool ageratum_glslToSPIRV(const ageratum_file_t *const file);

///////////////////////////////////////////////////////////////////////////////
//                              IMPLEMENTATION                               //
// ////////////////////////////////////////////////////////////////////////////
#ifdef AGERATUM_IMPLEMENTATION

#include <WLLogging.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

const char *const ageratum_shaderSourcePath = "Shaders/Source/";
const char *const ageratum_shaderCompiledPath = "Shaders/Compiled/";

static const char *const ageratum_infos[AGERATUM_TYPE_COUNT][2] = {
    [AGERATUM_TEXT] = {nullptr, ".txt"},
    [AGERATUM_GLSL_VERTEX] = {ageratum_shaderSourcePath, ".vert"},
    [AGERATUM_GLSL_FRAGMENT] = {ageratum_shaderSourcePath, ".frag"},
    [AGERATUM_SPIRV_VERTEX] = {ageratum_shaderCompiledPath, "-vert.spv"},
    [AGERATUM_SPIRV_FRAGMENT] = {ageratum_shaderCompiledPath, "-frag.spv"},
    [AGERATUM_SYSTEM] = {nullptr, nullptr},
};

static inline void ageratum_strncat(char *dest, const char *const src,
                                    size_t *consumed)
{
    if (src == nullptr) return;

    char *tempSource = (char *)src;
    const size_t n = AGERATUM_MAX_PATH_LENGTH - *consumed;
    dest += *consumed;
    while (*tempSource != 0 && *consumed < n)
    {
        *dest++ = *tempSource;
        tempSource++;
        (*consumed)++;
    }
}

// Benchmarks:
// LibC strncat
// 0.000004  0.000004  0.000006
// 0.000001  0.000002  0.000001
// 0.000001  0.000001  0.000001
// 0.000004  0.000003  0.000003
// 0.000001  0.000001  0.000001
// 0.000002  0.000001  0.000001
//
// Custom strncat (old)
// - Regular inline
// 0.000003  0.000003  0.000003
// 0.000001  0.000001  0.000001
// 0.000001  0.000001  0.000001
// 0.000003  0.000003  0.000002
// 0.000002  0.000002  0.000001
// 0.000002  0.000001  0.000002
//
// Custom strncat (new)
// - Regular inline
// 0.000001  0.000001  0.000001
// 0.000001  0.000002  0.000001
// 0.000001  0.000001  0.000001
// 0.000001  0.000002  0.000002
// 0.000001  0.000001  0.000001
// 0.000001  0.000002  0.000002
static void ageratum_createFilepath(const ageratum_file_t *const file,
                                    char *path)
{
    size_t consumed = 0;
    if (__builtin_expect(file->type == AGERATUM_SYSTEM, 0))
    {
        // It's more efficient to just do this inline.
        char *baseDirectory = AGERATUM_SYSTEM_DIRECTORY;
        for (size_t i = 0; i < AGERATUM_SYSTEM_DIRECTORY_LENGTH; i++)
            path[i] = baseDirectory[i];
        consumed = AGERATUM_SYSTEM_DIRECTORY_LENGTH;
        ageratum_strncat(path, file->basename, &consumed);
    }
    else
    {
        // It's more efficient to just do this inline.
        char *baseDirectory = AGERATUM_BASE_DIRECTORY;
        for (size_t i = 0; i < AGERATUM_BASE_DIRECTORY_LENGTH; i++)
            path[i] = baseDirectory[i];
        consumed = AGERATUM_BASE_DIRECTORY_LENGTH;

        auto info = ageratum_infos[file->type];
        ageratum_strncat(path, info[0], &consumed);
        ageratum_strncat(path, file->basename, &consumed);
        ageratum_strncat(path, info[1], &consumed);
    }
}

bool ageratum_openFile(ageratum_file_t *file,
                       ageratum_permissions_t permissions)
{
    char path[AGERATUM_MAX_PATH_LENGTH];
    ageratum_createFilepath(file, path);

    char *mode;
    switch (permissions)
    {
        case AGERATUM_READ:      mode = "r"; break;
        case AGERATUM_WRITE:     mode = "w"; break;
        case AGERATUM_APPEND:    mode = "a"; break;
        case AGERATUM_READWRITE: mode = "w+"; break;
        default:                 mode = "a+"; break;
    }

    file->handle = fopen(path, mode);
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
        waterlily_log(ERROR, "Failed to close file '%s'.", file->basename);
        return false;
    }
    return true;
}

bool ageratum_getFileSize(ageratum_file_t *file)
{
    struct stat stats;
    // Nearly 10x faster than fseek/ftell in my tests.
    if (__builtin_expect(fstat(fileno(file->handle), &stats) == -1, 0))
    {
        waterlily_log(ERROR, "Failed to stat file '%s'.", file->basename);
        return false;
    }
    waterlily_log(VERBOSE_OK, "Got stats of file '%s'.", file->basename);
    file->size = stats.st_size;
    return true;
}

bool ageratum_loadFile(ageratum_file_t *file, char *contents)
{
    if (__builtin_expect(
            fread(contents, 1, file->size, file->handle) != file->size, 0))
    {
        waterlily_log(ERROR, "Failed to properly read file '%s'.",
                      file->basename);
        return false;
    }
    contents[file->size] = 0;
    return true;
}

bool ageratum_writeFile(ageratum_file_t *file, const char *const contents)
{
    if (__builtin_expect(
            fwrite(contents, 1, file->size, file->handle) != file->size, 0))
    {
        waterlily_log(ERROR, "Failed to write to file '%s'.", file->basename);
        return false;
    }
    waterlily_log(VERBOSE_OK, "Wrote %zu bytes to file '%s'.", file->size,
                  file->basename);
    return true;
}

bool ageratum_executeFile(const ageratum_file_t *const file,
                          const char *const *const argv, size_t argc,
                          int *status)
{
    char path[AGERATUM_MAX_PATH_LENGTH];
    ageratum_createFilepath(file, path);

    if (__builtin_expect(access(path, X_OK) == -1, 0))
    {
        waterlily_log(ERROR, "Cannot execute file '%s'.", path);
        return false;
    }

    pid_t pid = fork();
    if (__builtin_expect(pid == -1, 0))
    {
        waterlily_log(ERROR, "Failed to fork process.");
        return false;
    }

    char *trueArgv[argc + 2];
    trueArgv[0] = path;
    for (size_t i = 0; i < argc; i++) trueArgv[i + 1] = (char *)argv[i];
    trueArgv[argc + 1] = nullptr;

    // This is executed within the new process.
    if (__builtin_expect(
            pid == 0 && execve(path, (char *const *)trueArgv, nullptr) == -1,
            0))
    {
        waterlily_log(ERROR, "Failed to execute file '%s'.", path);
        return false;
    }

    int processStatus = 0;
    pid_t waitStatus = waitpid(pid, &processStatus, 0);
    if (__builtin_expect(waitStatus == (pid_t)-1, 0))
    {
        waterlily_log(WARNING, "Execution of '%s' interrupted by a signal.",
                      path);
        return false;
    }

    // This could very likely happen or not happen. Don't expect anything.
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

// Benchmarks:
// Full (original):
// 0.103485 0.107282 0.106701
// 0.098565 0.106067 0.099129
bool ageratum_glslToSPIRV(const ageratum_file_t *const file)
{
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
    ageratum_file_t glslangFile = {.filename = "glslang",
                                   .type = AGERATUM_SYSTEM};
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
//                            IMPLEMENTATION END //
// ////////////////////////////////////////////////////////////////////////////

#endif // AGERATUM_H
