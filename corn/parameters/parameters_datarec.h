#ifndef parameters_datarecH
#define parameters_datarecH
#ifndef datarecH
#  include "corn/data_source/datarec.h"
#endif
#ifndef parametersH
#  include "corn/parameters/parameters.h"
#endif
//______________________________________________________________________________
class Common_parameters_data_record
: public CORN::Data_record
, public Common_parameters
{public:
   Common_parameters_data_record
      (Associated_directory_mode         associated_directory_mode               //060620
      ,const char *primary_section_name
      ,nat32 version_code=0
      /* 180626 now using date
      ,nat8 _major   =0
      ,nat8 _release =0
      ,nat8 _minor   =0
      */
      );
   virtual bool set_start();
   // We current always write to the current version
   // set the IO version numbers to the current version.
   /*180626 obsolete, now use file conversion/upgrade utilities
   virtual bool get_end();
   // After reading, we will check if the read file version does not match the current version.
   // If not we update section and entries that may have been moved or renamed.
   */
   /*180626 now using conversion/upgrade utilities
   inline virtual Section_entry_change *get_section_entry_changes(uint16 &count) const { count = 0; return 0;}
   // If the derived class has a new version with renamed sections and entries
   // it should override this method to return the table of changes
   // The return value is the number of changes in the table.
   */
   virtual const char *get_primary_section_name()                         const;
   // Derived classes must specify the primary section name.
   virtual void setup_parameters(CORN::Data_record &data_rec,bool for_write) modification_;
   virtual bool expect_structure(bool for_write = false);                        //161023
};
//______________________________________________________________________________

#endif

