//---------------------------------------------------------------------------

#ifndef AgWeatherNet_convertorH
#define AgWeatherNet_convertorH
//---------------------------------------------------------------------------
#include <UED/convert/convertor.h>
//______________________________________________________________________________
namespace CORN
{
   class SDF_List;
   class Ustring;
};
namespace UED
{
   class Database_file_indexed;
   class Geolocation_record;
};
//_______________________________________________________forward_declarations__/
class AgWeatherNet_format_convertor
: public UED_convertor
{
public:
   AgWeatherNet_format_convertor(int argc,const char *argv[]);
   virtual uint32 perform_import() ;
   virtual uint32 perform_export() ;

   virtual uint16 get_version()           const { return 0x0100; };
   virtual const char *get_application_name()  const { return "AgWeatherNet UED import utility (Roger Nelson rnelson@wsu.edu)"; };

public: // virtual method implementations
   virtual Geolocation *render_geolocation(const CORN::Ustring &station_ID) const; // renders
private:
   Station_database *curr_station_database;
   contribute_ UED::Geolocation_record    *curr_geo_location_record;
//091027   contribute_ UED::Database_file_indexed *curr_UED;
   contribute_ bool           metric_units;
   contribute_ float32        elevation_arbitrary_units;
   contribute_ CORN::SDF_List *curr_column_headers;
   void read_header           (ifstream &input_file);
   void parse_column_headers  (const CORN::Ustring  &buffer_str);
   void parse_detail_line     (const CORN::Ustring &buffer_str,CORN::Ustring &detail_line_validation_description);
};
#endif


