#ifndef OSh
#define OSh
#ifndef USE_OS_FS

#ifdef __cplusplus
//131114 #include <corn/file_sys/filename.h>
#else
#define const
#endif

#if (defined(_WIN32) || defined(_WIN64) || defined (__MSDOS__))
#define OS_DIRECTORY_SEPARATOR '\\'
#define OS_DIRECTORY_SEPARATOR_CSTR "\\"
extern void MSDOS_filename(char *fname);
#else
#define OS_DIRECTORY_SEPARATOR '/'
#define OS_DIRECTORY_SEPARATOR_CSTR "/"
#endif
//______________________________________________________________________________
extern bool OS_file_exists(const char *filename);
//extern int OS_directory_exists(char *filename);
extern bool OS_get_first_file_in_dir(const char *directory, char *first_filename);
/* first_filename is returned */
extern bool OS_get_next_file_in_dir(const char *directory, char *next_filename);
/* next_filename is returned */
extern void OS_end_get_file_in_dir();

extern int OS_has_extension(char *filename,char *extension);

// extern char *OS_unique_name(char *buffer, char *directory, char *prefix, char *extension);

/* returns just the filename part of a fully qualified filename (no path no ext) */
char *OS_extract_filename(const char *full_filename,char *buffer);
char *OS_extract_path(char *full_filename,char *buffer);

#ifndef __cplusplus
//This is obsolete for C++ use file_system/directory class
void OS_make_directory(const char *directory_name);
// Creates the specified directory if it doesn't already exist.
#endif
void OS_copy_directory(const char *from_directory, const char *to_directory);
// Copies a directory and all subdirectories


void OS_copy_file(const char *from_file, const char *to_file_or_directory);
// Copies a file to the specified file or directory

void OS_make_link(const char *from_file, const char *link_name);
// Make a symbolic link from the from_file

void OS_rename_file(const char *from_file, const char *to_file);

#ifdef __cplusplus
//#include <corn/cstring.h>
// The following are if we have a C++ string class
//020424 obs void OS_make_dir(CORN_string &directory_name);
// Creates the specified directory if it doesn't already exist.
// Creates directories recursively
//020424 obs void OS_copy_file(const char */*CORN_string &*/from_file, const char */*string &*/to_file_or_directory);
// Copies a file to the specified file or directory
//020424 obs void OS_make_link(CORN_string &from_file, string &link_name);
// Make a symbolic link from the from_file
//020424 obs void OS_copy_dir(CORN_string &from_directory, string &to_directory);
// Copies a directory and all subdirectories
#endif
#ifndef __cplusplus
//020424 obs void OS_delete_file(const CORN_string &delete_file);
// Deletes the specified file.

void OS_list_directories(const CORN_string &in_directory,CORN_bidirectional_list &directories_list);
#endif

#ifndef __cplusplus
//If you are using C++ classes, please use CORN::Directory_name and delete_irrevocably()
extern void OS_remove_full_directory(const char *dirname);
#define remove_full_directory(x) OS_remove_full_directory(x)
#endif
#endif
#endif
//os
