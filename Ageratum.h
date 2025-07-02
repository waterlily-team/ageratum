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

#include <Primrose.h>
#define __need_size_t
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

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
#define AGERATUM_TWEAK_VERSION 36

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
     * the @ref ageratum_glslToSPIRV function. It comes with the extension
     * ".vert".
     * @since v0.0.0.2
     */
    AGERATUM_GLSL_VERTEX,
    /**
     * @var ageratum_type AGERATUM_GLSL_FRAGMENT
     * @brief A GLSL fragment shader file. This is one of the possible inputs
     * for the @ref ageratum_glslToSPIRV function. It comes with the extension
     * ".frag".
     * @since v0.0.0.2
     */
    AGERATUM_GLSL_FRAGMENT,
    /**
     * @var ageratum_type AGERATUM_SPIRV_VERTEX
     * @brief A SPIRV vertex shader file. This is treated as a string of bytes,
     * and is the output for the @ref ageratum_glslToSPIRV function. It comes
     * with the extension "-vert.spv".
     * @since v0.0.0.13
     */
    AGERATUM_SPIRV_VERTEX,
    /**
     * @var ageratum_type AGERATUM_SPIRV_FRAGMENT
     * @brief A SPIRV fragment shader file. This is treated as a string of
     * bytes, and is the output for the @ref ageratum_glslToSPIRV function. It
     * comes with the extension "-frag.spv".
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
     */
    FILE *handle;
    /**
     * @property size
     * @brief The size of the file in bytes.
     * @since v0.0.0.1
     */
    size_t size;
} ageratum_file_t;

/**
 * @fn bool ageratum_openFile(ageratum_file_t *file, ageratum_permissions_t
 * permissions)
 * @brief Open a file and store its handle in the provided structure. The file
 * must have its filename and filetype set, all other values will be ignored.
 * @since v0.0.0.13
 *
 * @remark Should a file handle have previously have been in this file
 * structure, it should be closed before calling, as it will be leaked on
 * overwrite.
 *
 * @param[in, out] file The file structure we are going to be operating on and
 * storing to.
 * @param[in] permissions The permissions to open the file under.
 *
 * @return A boolean value representing whether or not the file was opened
 * successfully. On failure, a message will be posted to @c stderr alongside the
 * current @c ERRNO value. This function usually fails because the given file
 * does not exist.
 */
[[gnu::nonnull(1)]] [[gnu::hot]] [[nodiscard("Expression result unchecked.")]]
bool ageratum_openFile(ageratum_file_t *file,
                       ageratum_permissions_t permissions);

/**
 * @fn bool ageratum_closeFile(ageratum_file_t *file)
 * @brief Close a file handle.
 * @since v0.0.0.13
 *
 * @param[in] file The file structure to be operated on. The file handle is
 * garbage after this function's completion.
 *
 * @return A boolean value representing whether or not the file was closed
 * successfully. On failure, a message will be posted to @c stderr alongside the
 * current @c ERRNO value. This function usually fails because of IO errors when
 * flushing the file's buffer.
 */
[[gnu::nonnull(1)]] [[gnu::hot]] [[nodiscard("Expression result unchecked.")]]
static inline bool ageratum_closeFile(const ageratum_file_t *const file)
{
    if (__builtin_expect(fclose(file->handle) != 0, 0))
    {
        primrose_log(ERROR, "Failed to close file '%s'.", file->basename);
        return false;
    }
    primrose_log(VERBOSE_OK, "Closed file '%s'.", file->basename);
    return true;
}

/**
 * @fn bool ageratum_loadFile(ageratum_file_t *file, char *contents)
 * @brief Load all the contents of the given file from disk. The given file
 * structure must have a valid file pointer and its size must have been polled
 * via @ref ageratum_getFileSize.
 * @since v0.0.0.1
 *
 * @remark This function does not add a terminating NUL character to the loaded
 * bytes.
 *
 * @param[in] file The file structure to be operated on.
 * @param[out] contents An array of bytes in which the file's contents will be
 * inserted. This must be large enough to store the file's entire contents.
 *
 * @return A boolean value representing whether or not the file was loaded
 * successfully. On failure, a message will be posted to @c stderr alongside the
 * current @c ERRNO value. This function typically fails because of IO errors.
 */
[[gnu::nonnull(1, 2)]] [[nodiscard("Expression result unchecked.")]]
bool ageratum_loadFile(const ageratum_file_t *const file, char *contents);

/**
 * @fn bool ageratum_writeFile(const ageratum_file_t *const file, const char
 * *const contents)
 * @brief Write the given contents to the given file. The given file must
 * contain a valid file handle, and the given file size is the count of elements
 * that are to be written.
 * @since v0.0.0.1
 *
 * @param[in] file The file structure to be operated on.
 * @param[out] contents An array of bytes which will be written to the file.
 * This must be the same length or longer than described in the provided file
 * structure's @c size property.
 *
 * @return A boolean value representing whether or not the file was written to
 * successfully. On failure, a message will be posted to @c stderr alongside the
 * current @c ERRNO value. This function typically fails because of IO errors.
 */
[[gnu::nonnull(1, 2)]] [[nodiscard("Expression result unchecked.")]]
bool ageratum_writeFile(const ageratum_file_t *const file,
                        const char *const contents);

/**
 * @fn bool ageratum_getFileSize(ageratum_file_t *file)
 * @brief Get the size of the given file in bytes. The given file's handle must
 * be valid.
 * @since v0.0.0.13
 *
 * @param[in, out] file The file structure to be operated on. The file's @c size
 * property is set by this function.
 *
 * @return A boolean value representing whether or not the file's size was
 * polled successfully. On failure, a message will be posted to @c stderr
 * alongside the current @c ERRNO value. This function typically fails because
 * of IO errors.
 */
[[gnu::nonnull(1)]] [[nodiscard("Expression result unchecked.")]]
bool ageratum_getFileSize(ageratum_file_t *file);

/**
 * @fn bool ageratum_executeFile(const ageratum_file_t *const file, const char
 * *const *const argv, size_t argc, int *status)
 * @brief Execute the given file as a child process. The given file must have a
 * valid basename and point to a file which the process has execution rights
 * over.
 * @since v0.0.0.14
 *
 * @param[in] file The file structure to be operated on.
 * @param[in] argv Command-line arguments to be provided to the executable.
 * @param[in] argc The count of arguments provided.
 * @param[out] status The return status of the child process, should it return
 * from execution properly.
 *
 * @return A boolean value representing whether or not the file was executed
 * successfully. On failure, a message will be posted to @c stderr alongside the
 * current @c ERRNO value. This function typically fails because of child
 * process-related errors.
 */
[[gnu::nonnull(1, 2, 4)]] [[nodiscard("Expression result unchecked.")]]
bool ageratum_executeFile(const ageratum_file_t *const file,
                          const char *const *const argv, size_t argc,
                          int *status);

/**
 * @fn bool ageratum_glslToSPIRV(const ageratum_file_t *const file)
 * @brief Compile a given GLSL shader file to a SPIRV output utilizing the @c
 * glslang executable. This function will throw errors unless the @c glslang
 * executable is available on the current system. The given GLSL shader file
 * must have a valid basename.
 * @since v0.0.0.14
 *
 * @param[in] file The file structure to be operated on.
 *
 * @return A boolean value representing whether or not the file was compiled
 * successfully. On failure, a message will be posted to @c stderr alongside the
 * current @c ERRNO value. This function typically fails because of GLSL
 * validation errors or missing files.
 */
[[gnu::nonnull(1)]] [[gnu::cold]] [[nodiscard("Expression result unchecked.")]]
bool ageratum_glslToSPIRV(const ageratum_file_t *const file);

/**
 * @fn void ageratum_createFilepath(const ageratum_file_t *const file, char
 * *path)
 * @brief A function to generate a full file path from the filetype and basename
 * of the given file. The given file must have a valid basename and type.
 * @since v0.0.0.14
 *
 * @param[in] file The file structure to operate on.
 * @param[out] path The generated path. This buffer should be at least as large
 * as specified in @ref AGERATUM_MAX_PATH_LENGTH.
 */
[[gnu::nonnull(1, 2)]] [[gnu::flatten]]
void ageratum_createFilepath(const ageratum_file_t *const file, char *path);

[[gnu::nonnull(1)]] [[gnu::hot]] [[nodiscard("Expression result unchecked.")]]
static inline bool ageratum_fileExists(const ageratum_file_t *const file)
{
    char path[AGERATUM_MAX_PATH_LENGTH];
    ageratum_createFilepath(file, path);
    return access(path, F_OK) == 0;
}

[[gnu::nonnull(1)]]
void ageratum_splitStem(const char *const original, char *filename,
                        char *extension);

///////////////////////////////////////////////////////////////////////////////
//                              IMPLEMENTATION                               //
// ////////////////////////////////////////////////////////////////////////////
#ifdef AGERATUM_IMPLEMENTATION

#include <sys/stat.h>
#include <sys/wait.h>

/**
 * @var const char *const ageratum_shaderSourcePath
 * @brief The path to the local shader source directory, kept separate from
 * the rest of the paths for deduplication reasons.
 * @since v0.0.0.13
 */
static const char *const ageratum_shaderSourcePath = "Shaders/Source/";

/**
 * @var const char *const ageratum_shaderCompiledPath
 * @brief The path to the local shader compiled output directory, kept separate
 * from the rest of the paths for deduplication reasons.
 * @since v0.0.0.13
 */
static const char *const ageratum_shaderCompiledPath = "Shaders/Compiled/";

/**
 * @var const char *const ageratum_infos[AGERATUM_TYPE_COUNT][2]
 * @brief A list of subdirectory and extensions for each file type recognized by
 * the library.
 * @since v0.0.0.18
 */
static const char *const ageratum_infos[AGERATUM_TYPE_COUNT][2] = {
    [AGERATUM_TEXT] = {nullptr, ".txt"},
    [AGERATUM_GLSL_VERTEX] = {ageratum_shaderSourcePath, ".vert"},
    [AGERATUM_GLSL_FRAGMENT] = {ageratum_shaderSourcePath, ".frag"},
    [AGERATUM_SPIRV_VERTEX] = {ageratum_shaderCompiledPath, "-vert.spv"},
    [AGERATUM_SPIRV_FRAGMENT] = {ageratum_shaderCompiledPath, "-frag.spv"},
    [AGERATUM_SYSTEM] = {nullptr, nullptr},
};

/**
 * @fn void ageratum_strncat(char *dest, const char *const src, size_t
 * *consumed)
 * @brief A custom @c strncat implementation to fit the specific needs of
 * filepath generation within the open/close/load/execute functions of the
 * library.
 * @since v0.0.0.17
 *
 * @param[out] dest The buffer into which to copy the string data.
 * @param[in] src The data to be copied into the destination buffer.
 * @param[in, out] consumed The amount of characters that have been consumed
 * within @c dest already.
 */
[[gnu::nonnull(1, 3)]]
void ageratum_strncat(char *dest, const char *const src, size_t *consumed)
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

void ageratum_createFilepath(const ageratum_file_t *const file, char *path)
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
        primrose_log(ERROR, "Failed to open file '%s'.", path);
        return false;
    }
    primrose_log(VERBOSE_OK, "Opened file '%s'.", path);
    return true;
}

bool ageratum_getFileSize(ageratum_file_t *file)
{
    struct stat stats;
    // Nearly 10x faster than fseek/ftell in my tests.
    if (__builtin_expect(fstat(fileno(file->handle), &stats) == -1, 0))
    {
        primrose_log(ERROR, "Failed to stat file '%s'.", file->basename);
        return false;
    }
    file->size = stats.st_size;
    primrose_log(VERBOSE_OK, "Got size of file '%s': %zu.", file->basename,
                 file->size);
    return true;
}

bool ageratum_loadFile(const ageratum_file_t *const file, char *contents)
{
    if (__builtin_expect(
            fread(contents, 1, file->size, file->handle) != file->size, 0))
    {
        primrose_log(ERROR, "Failed to properly read file '%s'.",
                     file->basename);
        return false;
    }
    primrose_log(VERBOSE_OK, "Loaded %zu bytes of file '%s'.", file->size,
                 file->basename);
    return true;
}

bool ageratum_writeFile(const ageratum_file_t *const file,
                        const char *const contents)
{
    if (__builtin_expect(
            fwrite(contents, 1, file->size, file->handle) != file->size, 0))
    {
        primrose_log(ERROR, "Failed to write to file '%s'.", file->basename);
        return false;
    }
    primrose_log(VERBOSE_OK, "Wrote %zu bytes to file '%s'.", file->size,
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
        primrose_log(ERROR, "Cannot execute file '%s'.", path);
        return false;
    }

    pid_t pid = fork();
    if (__builtin_expect(pid == -1, 0))
    {
        primrose_log(ERROR, "Failed to fork process.");
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
        primrose_log(ERROR, "Failed to execute file '%s'.", path);
        return false;
    }

    int processStatus = 0;
    pid_t waitStatus = waitpid(pid, &processStatus, 0);
    if (__builtin_expect(waitStatus == (pid_t)-1, 0))
    {
        primrose_log(WARNING, "Execution of '%s' interrupted by a signal.",
                     path);
        return false;
    }

    // This could very likely happen or not happen. Don't expect anything.
    if (!WIFEXITED(processStatus))
    {
        primrose_log(WARNING,
                     "File '%s' ended execution with an unexpected result.",
                     path);
        return false;
    }
    *status = WEXITSTATUS(processStatus);
    primrose_log(VERBOSE_OK, "Executed file '%s'. Exited with status code %d.",
                 file->basename, *status);
    return true;
}

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
    ageratum_file_t glslangFile = {.basename = "glslang",
                                   .type = AGERATUM_SYSTEM};
    if (!ageratum_executeFile(&glslangFile, argv, 14, &status))
    {
        primrose_log(ERROR, "Couldn't compile shader '%s'. Code %d.", path,
                     status);
        return false;
    }
    primrose_log(VERBOSE_OK, "Compiled shader '%s'.", path);
    return true;
}

void ageratum_splitStem(const char *const original, char *filename,
                        char *extension)
{
    char *originalCopy = (char *)original;
    size_t written = 0;
    while (*originalCopy != '.' && written < AGERATUM_MAX_PATH_LENGTH)
    {
        *filename = *originalCopy;
        filename++;
        originalCopy++;
        written++;
    }
    filename[written] = 0;

    while (*originalCopy++ != 0)
    {
        *extension = *originalCopy;
        extension++;
    }
}

#endif // AGERATUM_IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////
//                            IMPLEMENTATION END                             //
// ////////////////////////////////////////////////////////////////////////////

#endif // AGERATUM_H
