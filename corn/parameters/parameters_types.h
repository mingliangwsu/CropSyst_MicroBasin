#ifndef parameters_typesH
#define parameters_typesH
//___________________________________________________________________________
enum Associated_directory_mode
   {NO_ASSOCIATED_DIRECTORY
   ,OPTIONAL_ASSOCIATED_DIRECTORY   // An associated directory may or may not exist
   ,REQUIRED_ASSOCIATED_DIRECTORY   // There will always be an associated directory
                                    // Required an associated directories are always the same name as the parameter file with out the extension
                                    // and are in the same parent folder.
   ,PARENT_ASSOCIATED_DIRECTORY     // The directory in which the parameters file (if these parameters are stored in a file) is the associated directory
                                    // The associated directory may have the same name as the parameter file
                                    // but generally not.
   };
//___________________________________________________________________________
#endif


