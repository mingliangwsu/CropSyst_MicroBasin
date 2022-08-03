#include "settings.h"
#include <corn/data_source/datarec.h>
namespace CORN
{
//______________________________________________________________________________
User_settings::User_settings()
: GUI_top(0)
, GUI_left(0)
, GUI_width(0)
, GUI_height(0)
, GUI_activepageindex(0)
, GUI_active_control("")
, advanced_mode(false)
, most_recent_context_directory("")
, language()
, auto_explore_created_context(false)
{}
//______________________________________________________________________________
bool User_settings::setup_structure
(CORN::Data_record &data_rec,bool for_write) modification_
{  data_rec.expect_int16("top",    GUI_top);
   data_rec.expect_int16("left",   GUI_left);
   data_rec.expect_int16("width",  GUI_width);
   data_rec.expect_int16("height", GUI_height);
   data_rec.expect_int16("activepageindex", GUI_activepageindex);
   data_rec.expect_string("active_control", GUI_active_control,255);             //080124
   data_rec.expect_string("language", language,50);                              //100518
   data_rec.expect_bool("advanced",advanced_mode);                               //060808
   data_rec.expect_bool("auto_explore_context",auto_explore_created_context);    //101126
   if (!for_write || most_recent_context_directory.length())                     //090811
      // Only need to write the directory context if it has been set.
      data_rec.expect_string("recent_context",most_recent_context_directory,255);//090811
   return true;
}
//_2008-05-13___________________________________________________________________
};

