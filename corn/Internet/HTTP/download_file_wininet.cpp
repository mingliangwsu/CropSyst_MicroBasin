#include <Windows.h>
#include <Wininet.h>
#include <iostream>
#include <fstream>

namespace CORN {
namespace Internet {
//______________________________________________________________________________


    ::HINTERNET netstart ()
    {
        const ::HINTERNET handle =
            ::InternetOpenW(0, INTERNET_OPEN_TYPE_DIRECT, 0, 0, 0);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            std::cerr
                << "InternetOpen(): " << error << "."
                << std::endl;
        }
        return (handle);
    }

    void netclose ( ::HINTERNET object )
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

    ::HINTERNET netopen ( ::HINTERNET session, ::LPCWSTR url )
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

    void netfetch ( ::HINTERNET istream, std::ostream& ostream )
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

}

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
//______________________________________________________________________________
} // namespace CORN
} // namespace Internet
