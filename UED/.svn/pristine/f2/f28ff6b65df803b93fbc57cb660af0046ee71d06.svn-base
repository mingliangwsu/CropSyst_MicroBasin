//---------------------------------------------------------------------------

#ifndef AutoProfilePlotterH
#define AutoProfilePlotterH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include "AutoGraphPlotter.h"
#include "AutoTimeSeriesPlotter.h"
#include <corn/dynamic_array/da_float32.h>
#include <corn/dynamic_array/da_uint8.h>

#ifndef primitiveH
#  include <corn/primitive.h>
#endif
#include <corn/file_sys/smart_filename.h>

class CORN::Ustring;
namespace CORN
{
//class Dynamic_float_array;
//class Dynamic_uint8_array;
class Scaled_color_ramp;
class Date;
//   class Smart_file_name;

}

//---------------------------------------------------------------------------
/*_______*/ class PACKAGE TAutoProfilePlotter : public TAutoTimeSeriesPlotter
/*_______*/ {
/*_______*/ private:
/*_______*/ protected:
/*_______*/    // Unlike a time series plotter, here there is only one variable to plot
/*021124_*/    CORN::Smart_file_name   help_URL;
/*_______*/
/*_______*/  public:
/*_______*/     CORN::Ustring description;
/*_______*/     uint8  layers;
/*_______*/     CORN::Dynamic_float_array values_array[100];
/*_______*/     CORN::Dynamic_uint8_array attributes[100];
/*_______*/     float32 low_value;  // This is a low values for a range of values
/*_______*/     float32 med_value;
/*_______*/     float32 high_value;
/*_______*/
/*_______*/    CORN::Dynamic_float_array layering; // Stores the unit thickness of the layer.
/*_______*/     bool    top_down;    // Draw layers such that layer 1 is at the top of the rectangle
/*_______*/
/*_______*/    CORN::Scaled_color_ramp *color_ramp; // assigned when bound
/*_______*/
/*_______*/ public:
/*_______*/    __fastcall TAutoProfilePlotter(TComponent* Owner);
/*020809_*/    __fastcall ~TAutoProfilePlotter();
/*_______*/	   virtual void __fastcall Paint(void);
/*_______*/
/*_______*/    void bind_to
/*_______*/    (const char * /*const CORN::Ustring  &*/i_description
/*_______*/    ,CORN::Date          *i_display_date  // Eventually this will be a CORN_date_time
/*_______*/    ,float32 i_low_value  // This is a low values for a range of values
/*_______*/    ,float32 i_high_value
/*_______*/    ,uint16  i_colors      // Number of color divisions in color ramp
/*_______*/    ,TColor  i_low_color   // Color of lowest value
/*_______*/    ,TColor  i_med_color  // Color of medium value
/*_______*/    ,TColor  i_high_color  // Color of highest value
/*_______*/    ,bool    i_top_down
/*_______*/    ,uint8   i_layers      // Number of layers
/*_______*/    ,float32 i_thickness[]  // The unit thickness of the layer
/*021106_*/    ,const char *help_URL=0
/*_______*/    );

/*_______*/    void set_layer(uint8 layer
/*_______*/         , const CORN::Dynamic_array<float32>/*101018 Dynamic_float_array*/ &values_array
/*_______*/          ,const CORN::Dynamic_array<nat8>/*101018Dynamic_uint8_array*/ &attributes
/*_______*/       );
/*_______*/
/*_______*/     void set_layering
/*_______*/     (uint8   i_layers
/*_______*/     ,float32 i_thickness[]  // The unit thickness of the layer
/*_______*/     );
/*_______*/
               inline virtual bool blackout_background() const { return false;};

/*_______*/ __published:
/*_______*/ };
//---------------------------------------------------------------------------
#endif
