#ifndef verbosityH
#define verbosityH


/* verbose
Suggested encoding bits:
Bits 4-7 indicates high verbosity which would typically be useful
for debugging and the output is written to error stream.
7 debugging
6 undefined reserved for future use, was explaination (include detailed explaination) (now use --explaination level option)
5 inline file system operations detail
3-4 call depth
Bits 0-2 indicates
0-2 level number (level 1,2,3,4)
 typical user level of logging where the

 output is written to the log file stream


Minimal progress indicator
Essentially the higher the verbose number the greater the verbosity
*/
#define VERBOSE_MASK_LEVEL        0x07
#define VERBOSE_MASK_DEPTH        0x24
#define VERBOSE_MASK_DEPTH_SHIFT     3

#define VERBOSE_FLAG_EXPLAINATION 0x40
#define VERBOSE_FLAG_FILE_SYSTEM  0x20
   // With this flag log file system operations
   // The level indicates what file system operations to
   // 0 show file/directory
   // 1 show file open for modifications
   // 2 show file open for read
   // 3 show file/directory queries (I.e. check existance)

#define VERBOSE_FLAG_DEBUG        0x80

/*170814 not currently used
#if (defined(DEBUG) || defined(_DEBUG))
#define IS_VERBOSE_DEBUG(verbose,level,depth,debug)                           \
(((verbose & VERBOSE_MASK_LEVEL) >= level )                                   \
&&((verbose & VERBOSE_MASK_DEPTH) >= depth))
#else
#define IS_VERBOSE_DEBUG(verbose,level,depth,debug) (false)
#endif
*/
#define IS_VERBOSE(verbose,level)                                             \
(verbose && !(verbose & VERBOSE_FLAG_DEBUG)                                   \
&&((verbose & VERBOSE_MASK_LEVEL) >= level))


#define IS_VERBOSE_IN_DEPTH(verbose,level,depth)                              \
( !(verbose & VERBOSE_FLAG_DEBUG)                                             \
&&((verbose & VERBOSE_MASK_LEVEL) >= level)                                   \
&&((verbose & VERBOSE_MASK_DEPTH) >= depth))

#define IS_VERBOSE_FILE_SYSTEM(verbose,level,depth)                           \
( !(verbose & VERBOSE_FLAG_DEBUG)                                             \
&&  (verbose & VERBOSE_FLAG_FILE_SYSTEM)                                      \
&& ((verbose & VERBOSE_MASK_LEVEL) >= level)                                  \
&& ((verbose & VERBOSE_MASK_DEPTH) >= depth))

namespace CORN { extern int8 global_verbosity_depth; }
// Currently the global_verbosity_depth is instanciated in arguments.cpp

#endif