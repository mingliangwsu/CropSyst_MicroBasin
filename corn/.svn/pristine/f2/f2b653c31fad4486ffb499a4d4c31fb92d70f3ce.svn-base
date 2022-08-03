#ifndef contextualizationH
#define contextualizationH
#include "corn/data_source/datarec.h"
namespace CORN {
//______________________________________________________________________________
class Directory_record // saved in .directory file  section [context]
: public extends_ CORN::Data_record
{
 public:
   std::string context;
 public:
   inline Directory_record()
      : CORN::Data_record("explorer")
      {}
   virtual bool expect_structure(bool for_write);                                //161022_980405
};
//_class Directory_record___________________________________________2017-12-30_/
class Contextualization
{
 protected:
   CORN::OS::Directory_name     *active_directory;                               //180723_130123
      // was moved from Explorer_engine_abstract:: directory_name_qualified
   provided_ CORN::Directory_record *directory_record;                           //171230

 public:
   Contextualization();
   virtual ~Contextualization();
 public:
   virtual CORN::Directory_record *provide_directory_context()       provision_; //171231
 public:
   virtual bool is_within                                                        //180330
      (const char *monument
      ,const CORN::OS::Directory_name *dir = 0)                    affirmation_;
      ///< landmark name is unqualified (typically a name)
      /// If the dir is omitted the CWD directory_name_qualified is used.
      /// \return true if the specified directory the landmark.

   virtual bool is_beneath                                                       //171227
      (const char *monument
      ,const CORN::OS::Directory_name *dir = 0)                    affirmation_;
      ///< landmark name is unqualified (typically a name)
      /// If the dir is omitted the CWD directory_name_qualified is used.
      /// \return true if the specified directory is or is under the landmark (inclusively).
   virtual bool is_underneath                                                    //171227
      (const char *monument
      ,const CORN::OS::Directory_name *dir = 0)                    affirmation_;
      ///< landmark name is unqualified (typically a name)
      /// If the dir is omitted the CWD directory_name_qualified is used.
      /// \return true if the specified directory is under the landmark (exclusively).
   virtual bool has_monument
      (const char                      *monument
      ,const CORN::OS::Directory_name  *dir = 0)                   affirmation_;
      ///< landmark name is unqualified (typically a name)
      /// I.e. has_landmark("Output");
      /// If the dir is omitted the CWD directory_name_qualified is used.
      /// \return true if the specified directory contains the landmark dir.

 public:
   inline virtual const CORN::OS::Directory_name &get_active_directory()  const
      { return *active_directory; }
 public:
   virtual bool get_specified_context(std::string &context)               const;
      ///< The derived class should override to set context ID . (Currently this codes in the desktop infotip).
      ///  By default no description is assigned.
      ///\return false if this folder does not need or should not have a description. (arbitrary)

      // currently context_ID is string, but should be wstring 171227

   bool directory_context_save(bool if_modified = true)              stream_IO_;
   bool change_active_directory(const wchar_t *directory_name_fully_qualified);
   bool change_active_directory(const char *directory_name_fully_qualified) ;
   bool change_active_directory(const CORN::OS::Directory_name &directory_name);


};
//_class_Contextualization__________________________________________2018-07-18_/
} // namespace CORN
#endif

