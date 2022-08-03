
#include "USGS_elevation_service.h"
#include "corn/string/strconv.hpp"
#include "corn/Internet/HTTP/request.hpp"

// http://gisdata.usgs.gov/xmlwebservices2/elevation_service.asmx?op=getElevation

/* See also
http://www.earthtools.org/webservices.htm

http://developer.mapquest.com/web/products/open/elevation-service
*/

/* HTTP request using wininet
http://softwaredevelopment.gr/1823/http-post-and-get-requests-with-wininet-and-c/
http://www.cpp-home.com/archives/118.html
*/


#ifdef _Windows
#include <Windows.h>
#include <WinInet.h>
#else
#error not yet implemented for Linux
#endif

#include <iostream>


namespace CS
{
//______________________________________________________________________________
Elevation_service_USGS::Elevation_service_USGS(nat8 _service)
: service(_service)
,host((_service == USGS_Elevation_Web_service)
    ? "gisdata.usgs.gov"
    : "epqsl.er.usgs.gov")
{}
//______________________________________________________________________________
/*140804 moved to corn/Internet/HTTP/request.c_cpp
// This request function is generic It could be moved to it's own class

bool request(int Method, LPCSTR Host, LPCSTR url, LPCSTR header, LPSTR data
,std::string &result)

{
try{
	//Retrieve default http user agent
	char httpUseragent[512];
	DWORD szhttpUserAgent = sizeof(httpUseragent);
	ObtainUserAgentString( 0, httpUseragent, &szhttpUserAgent );

	char m[5];

	if(Method == GET)
		strcpy(m, "GET\0");
	else
		strcpy(m, "POST\0");

	//http://msdn.microsoft.com/en-us/library/windows/desktop/aa385096%28v=vs.85%29.aspx
	HINTERNET internet = InternetOpenA(httpUseragent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(internet != NULL)
	{
		//http://msdn.microsoft.com/en-us/library/windows/desktop/aa384363%28v=vs.85%29.aspx
		HINTERNET connect = InternetConnectA(internet, Host, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
		if(connect != NULL)
		{
			//http://msdn.microsoft.com/en-us/library/windows/desktop/aa384233%28v=vs.85%29.aspx
			HINTERNET request = HttpOpenRequestA(connect, m, url, "HTTP/1.1", NULL, NULL,
				INTERNET_FLAG_HYPERLINK | INTERNET_FLAG_IGNORE_CERT_CN_INVALID |
					INTERNET_FLAG_IGNORE_CERT_DATE_INVALID |
					INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP  |
					INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS |
					INTERNET_FLAG_NO_AUTH |
					INTERNET_FLAG_NO_CACHE_WRITE |
					INTERNET_FLAG_NO_UI |
					INTERNET_FLAG_PRAGMA_NOCACHE |
					INTERNET_FLAG_RELOAD, NULL);

			if(request != NULL)
			{
				int datalen = 0;
				if(data != NULL) datalen = strlen(data);
				int headerlen = 0;
				if(header != NULL) headerlen = strlen(header);

				//http://msdn.microsoft.com/en-us/library/windows/desktop/aa384247%28v=vs.85%29.aspx
				HttpSendRequestA(request, header, headerlen, data, datalen);

             CHAR szBuffer[1025];
             DWORD dwRead=0;
             while(::InternetReadFile(request, szBuffer, sizeof(szBuffer)-1, &dwRead) && dwRead) {
               result.append(szBuffer);
               szBuffer[dwRead] = 0;
               OutputDebugStringA(szBuffer);
               dwRead=0;
             }

				//http://msdn.microsoft.com/en-us/library/windows/desktop/aa384350%28v=vs.85%29.aspx
				InternetCloseHandle(request);
			}
		}
		InternetCloseHandle(connect);
	}
	InternetCloseHandle(internet);
}
catch(...) {}
   return true;
}
*/
/* http://stackoverflow.com/questions/10106816/how-to-contruct-httpsendrequest-method-of-wininet

#include <wininet.h>

    /// ....

    HINTERNET hIntSession =
      ::InternetOpen(_T("MyApp"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

    HINTERNET hHttpSession =
      InternetConnect(hIntSession, _T("api.twitter.com"), 80, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);

    HINTERNET hHttpRequest = HttpOpenRequest(
      hHttpSession,
      _T("GET"),
      _T("1/statuses/user_timeline.xml?screen_name=twitterapi"),
      0, 0, 0, INTERNET_FLAG_RELOAD, 0);

    TCHAR* szHeaders = _T("Content-Type: text/html\nMySpecialHeder: whatever");
    CHAR szReq[1024] = "";
    if( !HttpSendRequest(hHttpRequest, szHeaders, _tcslen(szHeaders), szReq, strlen(szReq))) {
      DWORD dwErr = GetLastError();
      /// handle error
    }

    CHAR szBuffer[1025];
    DWORD dwRead=0;
    while(::InternetReadFile(hHttpRequest, szBuffer, sizeof(szBuffer)-1, &dwRead) && dwRead) {
      szBuffer[dwRead] = 0;
      OutputDebugStringA(szBuffer);
      dwRead=0;
    }

    ::InternetCloseHandle(hHttpRequest);
    ::InternetCloseHandle(hHttpSession);
    ::InternetCloseHandle(hIntSession);
*/

//______________________________________________________________________________
bool Elevation_service_USGS::lookup_elevation(modifiable_ Geocoordinate &geocoordinate)
{  bool succeeded = false;
   std::string get_request;
   if (service == USGS_Elevation_Point_Query_Service)
   {
      get_request.append("pgs.php?");
      get_request.append("x=");
      get_request.append(CORN::float64_to_cstr(geocoordinate.get_longitude_dec_deg(),10));
      get_request.append("&y=");
      get_request.append(CORN::float64_to_cstr(geocoordinate.get_latitude_dec_deg(),10));
      get_request.append("&units=METERS&output=XML HTTP/1.1");   //omitted
      /* response:
<USGS_Elevation_Point_Query_Service>
<Elevation_Query x="46.5" y="-117">
<Data_Source>NED 1/3 arc-second</Data_Source>
<Elevation>0</Elevation>
<Units>Meters</Units>
</Elevation_Query>
</USGS_Elevation_Point_Query_Service>
      */
   } else // USGS_Elevation_Web_service
   {
      get_request.append("/xmlwebservices2/elevation_service.asmx/getElevation?");
      get_request.append("X_Value=");
      get_request.append(CORN::float64_to_cstr(geocoordinate.get_longitude_dec_deg(),10));
      get_request.append("&Y_Value=");
      get_request.append(CORN::float64_to_cstr(geocoordinate.get_latitude_dec_deg(),10));
      get_request.append("&Elevation_Units=METERS&Source_Layer=NED.CONUS_NED_13W&Elevation_Only=FALSE HTTP/1.1");   //omitted
      /*
      Reponse:
<USGS_Elevation_Web_Service_Query>
<Elevation_Query x="-116.95" y="46.588">
<Data_Source>NED 1/3rd arc-second: Western United States</Data_Source>
<Data_ID>NED.CONUS_NED_13W</Data_ID>
<Elevation>855.983154296875</Elevation>
<Units>METERS</Units>
</Elevation_Query>
</USGS_Elevation_Web_Service_Query>
      */
   }

   std::string response;
   succeeded = CORN::Internet::request(GET,host.c_str(),get_request.c_str(),NULL,NULL,response);
   float32 elevation = 0; //meter
   if (succeeded)
   {

   // parse response
      size_t start_elevation_pos = response.find("<Elevation>");
      size_t end_elevation_pos = response.find("</Elevation>");
      if ( (start_elevation_pos != std::string::npos)
         &&(end_elevation_pos   != std::string::npos))
      {
         std::string elevation_value(response,start_elevation_pos+11,end_elevation_pos-start_elevation_pos-11);
         elevation = geocoordinate.set_elevation_meter_cstr(elevation_value.c_str());
         succeeded = true;
      } else
      {
         std::string geocoordinate_str;
         geocoordinate.label_decimal_degrees_with_format
            (geocoordinate_str,true,5,' ',"\n",UC_meter);
         std::cerr << "USGS elevation site:" << host << std::endl;
         std::cerr << "Failed to return elevation for geocoordinate:" << std::endl;
         std::cerr <<  geocoordinate_str << std::endl;
         succeeded = false;
      }
   }
   if (!succeeded)
   {  elevation = 400.0;
      std::cerr
         << "Unable to connect to USGS elevation site:" << host << std::endl
         << "Using default mean elevation of Columbia basin and Palouse: 400 meter" <<std::endl;
      geocoordinate.set_elevation_meter(elevation);
   }
   return succeeded;
};
//______________________________________________________________________________
}

