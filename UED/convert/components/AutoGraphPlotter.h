//---------------------------------------------------------------------------

#ifndef AutoGraphPlotterH
#define AutoGraphPlotterH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <corn/file_sys/smart_filename.h>
#ifndef primitiveH
#  include <corn/primitive.h>
#endif
namespace CORN
{
   class Date_time;
   class Date;
//   class Smart_file_name;
}
//#include <corn/datetime/date.h>

//---------------------------------------------------------------------------
class PACKAGE TAutoGraphPlotter : public TGraphicControl
{
private:
protected:
   CORN::Date   *display_date;  // Eventually this will be a CORN_date_time

   uint16 first_valid_value;  // There may be a period of valid data
   uint16 last_valid_value;   // The part of the graph out size this range of the ordinate will be grayed out.
   CORN::Smart_file_name   help_URL;

//	Graphics::TBitmap *buffer;   

public:
   __fastcall TAutoGraphPlotter(TComponent* Owner);
	virtual void __fastcall Paint(void);
   virtual void PaintCalendar(/*TDC &drawDC,bool erase, TRect &itemRect*/);
   inline void bind_to(CORN::Date *i_display_date,const char *help_URL=0) { display_date = i_display_date; };

__published:
};
//---------------------------------------------------------------------------
#endif
 