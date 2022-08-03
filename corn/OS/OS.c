#include <stdio.h>
#include "corn/OS/OS.h"

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
#include <alloc.h>
struct ffblk FIB;

#endif
/* obsolete, use CORN_filename
int OS_file_exists(const char *filename)
{
	FILE *f;
   if ((f = fopen(filename,"rt")) != NULL)
	{
		fclose(f);
      return(1);
   }
   else
      return(0);
};
*/
bool OS_get_first_file_in_dir(const char *directory, char *first_filename)
/* first_filename is returned */
{
#ifdef AMIGADOS
	if(directory[0])
	dirlock = Lock(directory, ACCESS_READ);
	else
   {
	BPTR ram;
	ram = Lock("RAM:", ACCESS_READ);
	dirlock = CurrentDir(ram);
	CurrentDir(dirlock);
	UnLock(ram);
	}
   if(dirlock==0)
	return 0;
	if((FIB = AllocMem(sizeof(struct FileInfoBlock), MEMF_PUBLIC)) == 0)
   {
	UnLock(dirlock);
	return 0;
   }
   if(!Examine(dirlock, FIB)) 
   {
	UnLock(dirlock);
	FreeMem(FIB, sizeof(struct FileInfoBlock));
	return 0;
   }
   if(FIB->fib_DirEntryType < 0) 
   {
	UnLock(dirlock);
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
  while ((find_status == 0) && (FIB.ff_attrib & (FA_HIDDEN | FA_SYSTEM | FA_LABEL | FA_DIREC )))
    /* While it is a special file */
    find_status = findnext(&FIB);

  if (find_status == 0)  /* A file was found */
  {
//    strcpy(first_filename,directory);
//    strcat(first_filename,"\\");
    strcpy(first_filename,FIB.ff_name);
	 return(1);
  }
  else
    return(0);
#endif
};

bool OS_get_next_file_in_dir(const char *directory, char *next_filename)
/* next_filename is returned */
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
#ifdef __MSDOS__
  int find_status;
  find_status = findnext(&FIB);
  while ((find_status == 0) && (FIB.ff_attrib & (FA_HIDDEN | FA_SYSTEM | FA_LABEL | FA_DIREC )))
    /* While it is a special file */
    find_status = findnext(&FIB);

  if (find_status == 0)  /* A file was found */
  {
//    strcpy(next_filename,directory);
//    strcat(next_filename,"\\");
    strcpy(next_filename,FIB.ff_name);
    return(1);
  }
  else
    return(0);

#endif
};

void OS_end_get_file_in_dir()
{
#ifdef AMIGADOS
	FreeMem(FIB, sizeof(struct FileInfoBlock));
   UnLock(dirlock);
#endif
/* For MSDOS we don't need to end or close anything */
};
#ifdef __MSDOS__
void MSDOS_filename(char *fname)
{
  int i;
  for (i = 0 ;i < strlen(fname) ; i++)
     if (fname[i] == '/') fname[i] = 92;
};
#endif

/*obsolete, use CORN_filename

int OS_has_extension(char *filename,char *extension)
{
	return (strstr(filename,extension)? 1 : 0);
};

// Get a unique filename in the specified directory with the specified extension
   returns only the filename part, not a full path.

char *OS_unique_name(char *name,char *directory, char *desired, char *extension)
{
  int cnt = 0;
  char buffer[255];
  char prefix[32];
  strncpy(prefix,desired,8);
  sprintf(buffer,"%s%c%s%s",directory,OS_DIRECTORY_SEPARATOR,prefix,extension);
  while (OS_file_exists(buffer))
	{ strncpy(prefix,desired,6);
	  prefix[6] = 0;
	  sprintf(buffer,"%s%c%s%s",directory,OS_DIRECTORY_SEPARATOR,prefix,extension);
	};
  strcpy(name,prefix);
  return(name);
};

char *OS_extract_filename(const char *full_filename,char *filename)
{
#ifdef __MSDOS__
  char drive[MAXDRIVE];
  char path[MAXPATH];
  char ext[MAXEXT];
  fnsplit(full_filename,drive,path,filename,ext);
#endif
#ifdef AMIGADOS
  need to define this
#endif
  return(filename);
}
char *OS_extract_path(char *full_filename,char *full_path)
{
#ifdef __MSDOS__

  char drive[MAXDRIVE];
  char path[MAXPATH];
  char filename[MAXFILE];
  char ext[MAXEXT];

  fnsplit(full_filename,drive,path,filename,ext);
  strcpy(full_path,drive);
  strcat(full_path,path);

#endif
#ifdef AMIGADOS
  need to define this
#endif
  return(filename);
};
*/
/* Creates the specified directory if it doesn't already exist.*/

void OS_copy_file(const char *from_file, const char *to_file_or_directory)
{
#ifdef obsolete
#if (defined(_WIN32) || defined(_WIN64) || defined (__MSDOS__))
	bool has_wildcard = strchr(from_file,'*') || strchr(from_file,'?');
	if (has_wildcard)
#endif
	{
	char *copy_cmnd = (char *)malloc(256);
	strcpy(copy_cmnd,
#if defined(__MSDOS__) || defined(_Windows)
		 "XCOPY  "
#endif
#ifdef AMIGADOS
		 "COPY "
#endif
#ifdef UNIX
		 "cp "
#endif
		 ); /* /y option not in NT       Xcopy doesn't always work right in NT.*/
	strcat(copy_cmnd,from_file);
	strcat(copy_cmnd," ");
	strcat(copy_cmnd,to_file_or_directory);
   #if (defined(_WIN32) || defined(_WIN64) || defined (__MSDOS__))
	  WinExec(copy_cmnd,SW_MINIMIZE	);
	#else
	  system(copy_cmnd);
	#endif
	free(copy_cmnd);
	}
//#ifdef _Windows
   else
#endif
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
   };
//#endif
};

// Copies a file to the specified file or directory

void OS_make_link(const char *from_file, const char *link_name)
{
#if (defined(_WIN32) || defined(_WIN64) || defined (__MSDOS__))
	// We'll have to do a xcopy because
	// DOS doesn't have links and windows
	// links are half baked.
//110131 now use FSUTIL OS_copy_directory(from_file,link_name);
   // Note that the fsutil command lists the link name
   // first not last as in the Unix ln command!
   char fsutil_command[2000];
   strcpy(fsutil_command,"fsutil hardlink create \"");
   strcat(fsutil_command,link_name);
   strcat(fsutil_command,"\" \"");
   strcat(fsutil_command,from_file);
   strcat(fsutil_command,"\"");
   WinExec(fsutil_command,SW_NORMAL);
#else
#ifdef unix
   char ln_command[2000];
   strcpy(ln_command,"ln -f \"")
   strcat(fsutil_command,from_file);
   strcat(fsutil_command,"\" \"");
   strcat(fsutil_command,link_name);
   strcat(fsutil_command,"\"");
   system(fsutil_command);
#endif
#endif
};


#ifdef __cplusplus
//020424 obs void OS_make_dir(string &directory_name)
//020424 obs { OS_make_dir(directory_name.c_str()); };
//020424 obs void OS_copy_dir(string &from_directory, string &to_directory)
//020424 obs { OS_copy_dir(from_directory.c_str(),to_directory.c_str()); };
//020424 obs void OS_copy_file(string &from_file, string &to_file_or_directory)
//020424 obs { OS_copy_file(from_file.c_str(),to_file_or_directory.c_str());};
//020424 obs void OS_make_link(string &from_file, string &link_name)
//020424 obs { OS_make_link(from_file.c_str(),link_name.c_str()); };

//020424 obs void OS_delete_file(const CORN::__filename &delete_filename)
//020424 obs {  unlink (delete_filename.c_str()); };
#endif

#ifndef __cplusplus
// This is obsolete for C++, now use Directory_name.delete_irrevocably()
/*970630*/void OS_remove_full_directory(const char *dirname)
/*______*/{
/*990612*/    if (chdir(dirname) == 0) // donot delete anything if we done change directory!!!
/*990612*/    {
/*______*/    ffblk fileblck;
/*______*/    const unsigned findAttr = FA_RDONLY | FA_ARCH;
/*______*/    int result = findfirst("*.*",&fileblck,findAttr);
/*______*/    while (result == 0)
/*______*/    { // There was a matching file
/*______*/         if ((fileblck.ff_attrib &FA_DIREC) == 0)
/*______*/         {   CORN_filename del_filename(fileblck.ff_name);

del_filename.to_lower();
bool keep_file = false;
if (del_filename == "annual.xls")
   keep_file = true;
if (del_filename == "harvest.xls")
   keep_file = true;

if (!keep_file)
/*______*/             unlink(del_filename.c_str());
/*______*/         };
/*______*/         result = findnext(&fileblck);
/*______*/    };
/*971015*/    chdir("\\"); //Can't be in the directory
/*______*/    rmdir(dirname);
/*990612*/    };
/*______*/};
#endif

