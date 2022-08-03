#ifndef httpH
#define httpH
#include "corn/OS/directory_entry_name.h"
#include "corn/OS/uniform_resource_locator.h"
namespace CORN {
namespace Internet {
//______________________________________________________________________________
class HTTP
{
 private:
   ::HINTERNET session;
 public:
   HTTP();
   ~HTTP();
   bool download_file
      (//const std::wstring &    source_URL
       const CORN::OS::Uniform_resource_locator &    source_URL
      ,const CORN::OS::File_name &target_filename);
 protected:
   // ::HINTERNET    netstart ();
   ::HINTERNET    provide_session();
   void           netclose ( ::HINTERNET object );
   ::HINTERNET    netopen  ( ::HINTERNET session, ::LPCWSTR url );
   void           netfetch ( ::HINTERNET istream, std::ostream& ostream );

};
//______________________________________________________________________________
} // Internet
} // CORN

#endif
