#include <Windows.h>
#include <Wininet.h>
#include <iostream>
#include <fstream>
#include "corn/Internet/HTTP.h"

namespace CORN {
namespace Internet {
//______________________________________________________________________________
HTTP::HTTP()
: session(0)
{


}
//______________________________________________________________________________
HTTP::~HTTP()
{
   if (session)
     netclose(session);
}
//______________________________________________________________________________
bool HTTP::download_file
(const CORN::OS::Uniform_resource_locator &source_URL
//const std::wstring &    source_URL
,const CORN::OS::File_name &target_filename)
{
   bool downloaded = provide_session() != 0;
   if (downloaded)
   {  std::wstring source_URL_wide; CORN::string_to_wstring(source_URL,source_URL_wide);
      const ::HINTERNET istream = netopen(session, source_URL_wide.c_str());
      if ( istream != 0 )
      {
         std::ofstream ostream(target_filename.w_str(), std::ios::binary);
         if (ostream.is_open())
            netfetch(istream, ostream);
         else downloaded = false;
         netclose(istream);
      } else downloaded = false;
   }
   return downloaded;
}
//______________________________________________________________________________
::HINTERNET HTTP::provide_session ()
{
   if (!session)
   {
      session = ::InternetOpenW(0, INTERNET_OPEN_TYPE_DIRECT, 0, 0, 0);
      if ( session == 0 )
      {
         const ::DWORD error = ::GetLastError();
           std::cerr
            << "InternetOpen(): " << error << "."
            << std::endl;
      }
   }
   return session;
}
//______________________________________________________________________________
void HTTP::netclose ( ::HINTERNET object )
{
    const ::BOOL result = ::InternetCloseHandle(object);
    if ( result == FALSE )
    {
        const ::DWORD error = ::GetLastError();
        std::cerr
            << "InternetClose(): " << error << "."
            << std::endl;
    }
}
//______________________________________________________________________________
::HINTERNET HTTP::netopen ( ::HINTERNET session, ::LPCWSTR url )
{
    const ::HINTERNET handle =
        ::InternetOpenUrlW(session, url, 0, 0, 0, 0);
    if ( handle == 0 )
    {
        const ::DWORD error = ::GetLastError();
        std::cerr
            << "InternetOpenUrl(): " << error << "."
            << std::endl;
    }
    return (handle);
}
//______________________________________________________________________________
void HTTP::netfetch ( ::HINTERNET istream, std::ostream& ostream )
{
    static const ::DWORD SIZE = 1024;
    ::DWORD error = ERROR_SUCCESS;
    ::BYTE data[SIZE];
    ::DWORD size = 0;
    do {
        ::BOOL result = ::InternetReadFile(istream, data, SIZE, &size);
        if ( result == FALSE )
        {
            error = ::GetLastError();
            std::cerr
                << "InternetReadFile(): " << error << "."
                << std::endl;
        }
        ostream.write((const char*)data, size);
    }
    while ((error == ERROR_SUCCESS) && (size > 0));
}
//______________________________________________________________________________
/*
int main ( int, char ** )
{
    const ::WCHAR URL[] = L"http://stackoverflow.com/";
    const ::HINTERNET session = ::netstart();
    if ( session != 0 )
    {
        const ::HINTERNET istream = ::netopen(session, URL);
        if ( istream != 0 )
        {
            std::ofstream ostream("output.txt", std::ios::binary);
            if ( ostream.is_open() ) {
                ::netfetch(istream, ostream);
            }
            else {
                std::cerr << "Could not open 'output.txt'." << std::endl;
            }
            ::netclose(istream);
        }
        ::netclose(session);
    }
}
*/
//______________________________________________________________________________
} // namespace CORN
} // namespace Internet
