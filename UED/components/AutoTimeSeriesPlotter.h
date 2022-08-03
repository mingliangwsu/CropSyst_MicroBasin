//---------------------------------------------------------------------------

#ifndef AutoTimeSeriesPlotterH
#define AutoTimeSeriesPlotterH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include "AutoGraphPlotter.h"

#include <corn/container/association.h>
//101018#include <corn/dynamic_array/da_float32.h>
#include <corn/dynamic_array/dynamic_array_T.h>
#include <corn/string/ustring.h>
#ifndef primitiveH
#  include <corn/primitive.h>
#endif

class CORN::Ustring;

//---------------------------------------------------------------------------
class PACKAGE TAutoTimeSeriesPlotter : public TAutoGraphPlotter
{
public:
   class Plot : public CORN::Association
   {
   public:
      // association key is the description
      CORN::Ustring description;
      uint32   variable_code;  // 980801 I am not sure how this can be used here
      int16    num_values;
      CORN::Dynamic_array<float32>/*101018CORN::Dynamic_float_array */ values_array;
      float32 min;  // because different variable sets may have different range of value
      float32 max;  // These are references to the max and min
      bool     connect_points;   // If true will draw lines between points
      TColor   color;
      bool     inverse_axis; // I.e. values are draw from top (min value) to bottom (max value)
      bool     &enabled;
   protected:
      bool     is_a_range_plot;
   public:
      Plot(nat32  variable_code_
      ,int16      num_values_
      ,const CORN::Dynamic_array<float32> &values_
      ,float32    min_
      ,float32    max_
      ,bool       connect_points_
      ,bool       inverse_axis_
      ,TColor     color_
      ,const char *description_
      ,bool       &enabled_
      )
      : CORN::Association()
      , variable_code(variable_code_)
      ,num_values(num_values_)
      ,values_array(values_)
      ,min(min_)
      ,max(max_)
      ,connect_points(connect_points_)
      ,inverse_axis(inverse_axis_)
      ,color(color_)
      ,description(description_)
      ,enabled(enabled_)
      ,is_a_range_plot(false)
         {}
      virtual void draw(TCanvas *on_canvas,int height,int days_in_year);
      inline void set(const CORN::Dynamic_array<float32>/*101018Dynamic_float_array*/ &i_values)
         {  values_array.copy(i_values); }
      inline virtual bool is_range_plot() const { return is_a_range_plot; }
      inline virtual bool is_key_string(const std::string &key)              affirmation_  //180820
         { return description == key; }
/*180820  was probably only used for find_cstr now using is_key
      inline virtual const char *get_key() const { return description.c_str(); };
*/      
   };
   // --------------------------------------------------------------
   class Range_plot : public Plot
   {
      // min values array will be RUI_time_series_plotter::values_array
      CORN::Dynamic_array<float32>/*101018Dynamic_float_array*/ max_values_array;
   public:
      Range_plot
      (uint32     i_variable_code
      ,int16      i_num_values
      ,const CORN::Dynamic_array<float32>/*101018Dynamic_float_array*/ &i_values
      ,const CORN::Dynamic_array<float32>/*101018Dynamic_float_array*/ &i_max_values
      ,float32   i_min
      ,float32   i_max
      ,bool       i_connect_points
      ,bool       i_inverse_axis
      ,TColor     i_color
      ,const char * /*CORN::Ustring &*/i_description
      ,bool &i_enabled
      );

      virtual void draw(TCanvas *on_canvas,int height,int days_in_year);

      void set
      (const CORN::Dynamic_array<float32>/*101018Dynamic_float_array*/ &i_min_values
      ,const CORN::Dynamic_array<float32>/*101018Dynamic_float_array*/ &i_max_values)
      {  values_array.copy(i_min_values);
         max_values_array.copy(i_max_values);
      };
//      inline virtual bool is_range_plot() { return true; };
   };
   // --------------------------------------------------------------
protected:
//   bool blackouts_background;
public:
   CORN::Association_list time_series_plots;
public:
   __fastcall TAutoTimeSeriesPlotter(TComponent* Owner);

	virtual void __fastcall Paint(void);

   void add_time_series_plot(Plot *new_plot)
   { time_series_plots.append(new_plot); };
   // The plot is reliquished to the plotter.
   // which will delete it when finished

   void set
      (uint32   variable_code
      ,const CORN::Dynamic_array<float32>/*101018Dynamic_float_array*/ &i_values);

   // Range plot
   void set
      (uint32  variable_code
      ,const CORN::Dynamic_array<float32>/*101018Dynamic_float_array*/ &i_min_values
      ,const CORN::Dynamic_array<float32>/*101018Dynamic_float_array*/ &i_max_values);

   inline virtual bool blackout_background() const { return true /*blacksout_background*/;};

__published:
};
//---------------------------------------------------------------------------
#endif

