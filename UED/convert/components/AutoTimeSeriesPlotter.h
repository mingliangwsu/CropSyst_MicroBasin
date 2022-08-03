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
#include <corn/dynamic_array/dynamic_array_T.h>
#ifndef primitiveH
#  include <corn/primitive.h>
#endif

//---------------------------------------------------------------------------
class PACKAGE TAutoTimeSeriesPlotter : public TAutoGraphPlotter
{
public:
   class Plot : public CORN::Association
   {
   public:
      // association key is the description
      std::string description;
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
      Plot(uint32     i_variable_code
      ,int16      i_num_values
      ,const CORN::Dynamic_array<float32> &i_values
      ,float32   i_min
      ,float32   i_max
      ,bool       i_connect_points
      ,bool       i_inverse_axis
      ,TColor     i_color
      ,const char *i_description
      ,bool &i_enabled
      )
      : CORN::Association()
      , variable_code(i_variable_code)
      ,num_values(i_num_values)
      ,values_array(i_values)
      ,min(i_min)
      ,max(i_max)
      ,connect_points(i_connect_points)
      ,inverse_axis(i_inverse_axis)
      ,color(i_color)
      ,description(i_description)
      ,enabled(i_enabled)
      ,is_a_range_plot(false)
      {}

      virtual void draw(TCanvas *on_canvas,int height,int days_in_year);

      inline void set(const CORN::Dynamic_array<float32> &i_values)
         {  values_array.copy(i_values); }

      inline virtual bool is_range_plot() const { return is_a_range_plot; }
   inline virtual bool is_key_string(const std::string &key)              affirmation_  //180820
      { return description == key; }

/*180820  was probably only used for find_cstr now using is_key
      inline virtual const char *get_key() const { return description.c_str(); }
*/      
   };
   // --------------------------------------------------------------
   class Range_plot : public Plot
   {
      // min values array will be RUI_time_series_plotter::values_array
      CORN::Dynamic_array<float32> max_values_array;
   public:
      Range_plot
      (uint32     i_variable_code
      ,int16      i_num_values
      ,const CORN::Dynamic_array<float32> &i_values
      ,const CORN::Dynamic_array<float32> &i_max_values
      ,float32   i_min
      ,float32   i_max
      ,bool       i_connect_points
      ,bool       i_inverse_axis
      ,TColor     i_color
      ,const char *i_description
      ,bool &i_enabled
      );

      virtual void draw(TCanvas *on_canvas,int height,int days_in_year);

      void set
      (const CORN::Dynamic_array<float32> &i_min_values
      ,const CORN::Dynamic_array<float32> &i_max_values)
      {  values_array.copy(i_min_values);
         max_values_array.copy(i_max_values);
      }
//      inline virtual bool is_range_plot() { return true; }
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
   { time_series_plots.append(new_plot); }
   // The plot is reliquished to the plotter.
   // which will delete it when finished
   void set
      (nat32   variable_code
      ,const CORN::Dynamic_array<float32> &_values);
   // Range plot
   void set
      (nat32  variable_code
      ,const CORN::Dynamic_array<float32> &_min_values
      ,const CORN::Dynamic_array<float32> &_max_values);
   inline virtual bool blackout_background() const { return true /*blacksout_background*/;}
__published:
};
//---------------------------------------------------------------------------
#endif

