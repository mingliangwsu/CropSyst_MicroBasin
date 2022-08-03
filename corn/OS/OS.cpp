#include <stdio.h>
#include <corn/OS/OS.h>
#ifndef USE_OS_FS

#ifdef AMIGADOS
#include <libraries/dos.h>
#include <exec/memory.h>
char *malloc();
  struct FileLock *dirlock;
  struct FileInfoBlock *FIB;
#endif

#if (defined(_WIN32) || defined(_WIN64) || defined (__MSDOS__))
#include <dir.h>
#include <dos.h>
#include <string.h>
//131115 #include <corn/file_sys/filename.h>
struct ffblk FIB;
#if (defined(_WIN32) || defined(_WIN64) )
   // for WinExec
#     include <windows.h>
#  endif
#endif
//______________________________________________________________________________
bool OS_file_exists(const char *filename)
{  FILE *f;
   if ((f = fopen(filename,"rt")) != NULL)
   {  fclose(f);
      return(1);
   } else
      return(0);
}
//______________________________________________________________________________
bool OS_get_first_file_in_dir(const char *directory, char *first_filename)
/* first_filename is returned */
{
#ifdef AMIGADOS
   if (directory[0])
      dirlock = Lock(directory, ACCESS_READ);
   else
   {  BPTR ram;
      ram = Lock("RAM:", ACCESS_READ);
      dirlock = CurrentDir(ram);
      CurrentDir(dirlock);
      UnLock(ram);
   }
   if(dirlock==0)
	return 0;
   if((FIB = AllocMem(sizeof(struct FileInfoBlock), MEMF_PUBLIC)) == 0)
   {  UnLock(dirlock);
      return 0;
   }
   if(!Examine(dirlock, FIB))
   {  UnLock(dirlock);
      FreeMem(FIB, sizeof(struct FileInfoBlock));
      return 0;
   }
   if(FIB->fib_DirEntryType < 0)
   {  UnLock(dirlock);
      FreeMem(FIB, sizeof(struct FileInfoBlock));
      return 0;
   };
  dirlock = Lock(directory,ACCESS_READ);
  if (!Examine(dirlock,FIB)) return(0);
  while (FIB->fib_DirEntryType > 0)
	  if (!ExNext(dirlock,FIB)) return(0);
  if (FIB->fib_DirEntryType == 0)
	  return(0);
  else
  {  strcpy(first_filename,FIB->fib_FileName);
     return(1);
  };
#endif

#if (defined(_WIN32) || defined(_WIN64) || defined (__MSDOS__))
  int find_status;
  char path_wildcard[MAXPATH];
  strcpy(path_wildcard,directory);
  strcat(path_wildcard,"\\*.*");

  find_status = findfirst(path_wildcard,&FIB,0);
  /* While it is a special file */
  while ((find_status == 0) &&
         (FIB.ff_attrib & (FA_HIDDEN | FA_SYSTEM | FA_LABEL | FA_DIREC )))
    find_status = findnext(&FIB);

  if (find_status == 0)  /* A file was found */
  {
    strcpy(first_filename,FIB.ff_name);
    return(1);
  }
  else
    return(0);
#endif
#ifdef unix
  // 060711 NYI for UNIX
  return false;
#endif
}
//______________________________________________________________________________
/* next_filename is returned */
bool OS_get_next_file_in_dir(const char *directory, char *next_filename)
{
#ifdef AMIGADOS
  if (!ExNext(dirlock,FIB)) return(0);
  while (FIB->fib_DirEntryType > 0)
     if (!ExNext(dirlock, FIB)) return(0);
  if (FIB->fib_DirEntryType == 0)
     return(0);
  else
  {  strcpy(next_filename,FIB->fib_FileName);
     return(1);
  };
#endif
#if (defined(_WIN32) || defined(_WIN64) || defined (__MSDOS__))
  int find_status;
  find_status = findnext(&FIB);
  /* While it is a special file */
  while ((find_status == 0) && (FIB.ff_attrib & (FA_HIDDEN | FA_SYSTEM | FA_LABEL | FA_DIREC )))
    find_status = findnext(&FIB);

  if (find_status == 0)  /* A file was found */
  {
    strcpy(next_filename,FIB.ff_name);
    return(1);
  }
  else
    return(0);

#endif
#ifdef unix
  // 060711 NYI for UNIX
  return false;
#endif
}
//______________________________________________________________________________
void OS_end_get_file_in_dir()
{
#ifdef AMIGADOS
	FreeMem(FIB, sizeof(struct FileInfoBlock));
   UnLock(dirlock);
#endif
/* For MSDOS we don't need to end or close anything */
}
//______________________________________________________________________________
#ifdef __MSDOS__
void MSDOS_filename(char *fname)
{
  int i;
  for (i = 0 ;i < strlen(fname) ; i++)
     if (fname[i] == '/') fname[i] = 92;
}
#endif
//______________________________________________________________________________
/*000203 obsolete, use CORN_filename class
int OS_has_extension(char *filename,char *extension)
{
   return (strstr(filename,extension)? 1 : 0);
};


char *OS_extract_filename(char *full_filename)
{
  char drive[MAXDRIVE];
  char path[MAXPATH];
  static char filename[MAXFILE];
  char ext[MAXEXT];
  fnsplit(full_filename,drive,path,filename,ext);
  return(filename);
}
*/
//______________________________________________________________________________
/* Copies a directory and all subdirectories*/
void OS_copy_file(const char *from_file, const char *to_file_or_directory)
{

	/* We will copy the file directly instead of starting another process */
   {
      FILE *infile =fopen(from_file,"rb");
      FILE *outfile = fopen(to_file_or_directory,"wb");
      unsigned char *buffer = (unsigned char *)malloc(512);
      int bytes_read =0;
      if (infile && outfile)
      {
        do
        {
          bytes_read = fread(buffer,1,512,infile);
          fwrite(buffer,1,bytes_read,outfile);
        }
        while (bytes_read);
      }
      fclose(infile);
      fclose(outfile);

      free(buffer);
   }
}
//______________________________________________________________________________
void OS_rename_file(const char *from_file, const char *to_file)
{
#if (defined(_WIN32) || defined(_WIN64) || defined (__MSDOS__))
   rename(from_file, to_file);
#endif
//#ifdef
//    rename(from_file,to_file);
//#endif
}
//______________________________________________________________________________
//#ifndef __cplusplus
//This is obsolete for C++ use file_system/directory class
void OS_make_directory(const char *directory_name)
{
   /*980902 we now create directories along the path if the don't already exist
   */
#if (defined(_WIN32) || defined(_WIN64) || defined (__MSDOS__))
   char parent_dir[255];
   for (size_t i = 0; i <= strlen(directory_name); i++)
   {  char next_dir_char = directory_name[i];
      if (next_dir_char == OS_DIRECTORY_SEPARATOR)
         mkdir(parent_dir);
      parent_dir[i] = next_dir_char;
      parent_dir[i+1] = 0;
   };
   mkdir(directory_name);
#endif
#ifdef unix
//NYI need something for unix
#endif
   /* This is OK for DOS*/
   /* Unix takes an additional parameter, but I don't know what it is now.*/
}
//#endif
//______________________________________________________________________________
void OS_copy_directory(const char *from_directory, const char *to_directory)
{
#ifdef AMIGADOS
   xxx
   if no system function then
   COPY /ALL from_directory to_directory
#endif

#if (defined(_WIN32) || defined(_WIN64) || defined (__MSDOS__))
   OS_make_directory(to_directory); /* We have to first make the directory*/
                              /* or the stupid XCOPY command will prompt*/
                              /* if it is a file or a directory.*/
   char *copy_cmnd = (char *)malloc(256);
   strcpy(copy_cmnd,"XCOPY /Y/S/E ");
   #if (!defined(__MSDOS__) )
   // 060627 Windows allows spaces in file names, we need to quote in this case
   strcat(copy_cmnd, "\"");
   #endif
   strcat(copy_cmnd,from_directory);
   #if (!defined(__MSDOS__) )
   strcat(copy_cmnd, "\"");
   #endif

   strcat(copy_cmnd," ");
   #if (!defined(__MSDOS__) )
   strcat(copy_cmnd, "\"");
   #endif
   strcat(copy_cmnd,to_directory);
   #if (!defined(__MSDOS__) )
   strcat(copy_cmnd, "\"");
   #endif

   #if (defined(_WIN32) || defined(_WIN64) )
     WinExec(copy_cmnd,SW_MINIMIZE	);
   #else
     system(copy_cmnd);
   #endif
   free(copy_cmnd);
#else
//NYI  need to define for UNIX
#endif
}
/* Copies a directory and all subdirectories*/
//______________________________________________________________________________

#endif
