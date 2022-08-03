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
#include "corn/dynamic_array/dynamic_array_T.h"

#ifndef primitiveH
#  include "corn/primitive.h"
#endif
//160208 #include <corn/file_sys/smart_filename.h>

class CORN::Ustring;
namespace CORN
{
class Scaled_color_ramp;
class Date;
}
//---------------------------------------------------------------------------
class PACKAGE TAutoProfilePlotter : public TAutoTimeSeriesPlotter
{
private:
protected:
   // Unlike a time series plotter, here there is only one variable to plot
   //160208 CORN::Smart_file_name   help_URL;                                             //021124
 public:
    std::string description;
    nat8  layers;
    CORN::Dynamic_array<float> values_array[100];
    CORN::Dynamic_array<nat8>  attributes[100];
    float32 low_value;  // This is a low values for a range of values
    float32 med_value;
    float32 high_value;

   CORN::Dynamic_array<float> layering; // Stores the unit thickness of the layer.
   bool    top_down;    // Draw layers such that layer 1 is at the top of the rectangle
   CORN::Scaled_color_ramp *color_ramp; // assigned when bound
public:
   __fastcall TAutoProfilePlotter(TComponent* Owner);
   __fastcall ~TAutoProfilePlotter();                                            //020809
   virtual void __fastcall Paint(void);
   void bind_to
   (const char * /*const CORN::Ustring  &*/i_description
   ,CORN::Date          *i_display_date  // Eventually this will be a CORN_date_time
   ,float32 i_low_value  // This is a low values for a range of values
   ,float32 i_high_value
   ,uint16  i_colors      // Number of color divisions in color ramp
   ,TColor  i_low_color   // Color of lowest value
   ,TColor  i_med_color  // Color of medium value
   ,TColor  i_high_color  // Color of highest value
   ,bool    i_top_down
   ,nat8   i_layers      // Number of layers
   ,float32 i_thickness[]  // The unit thickness of the layer
   ,const char *help_URL=0    );                                                 //021106

   void set_layer(nat8 layer
        , const CORN::Dynamic_array<float32> &values_array
         ,const CORN::Dynamic_array<nat8> &attributes);

    void set_layering
    (nat8   i_layers
    ,float32 i_thickness[]  // The unit thickness of the layer
    );

   inline virtual bool blackout_background() const { return false;};

__published:
};
//---------------------------------------------------------------------------
#endif
