#ifndef recorder_datasrcH
#define recorder_datasrcH

#ifndef datasrcH
#  include <corn/data_source/datasrc.h>
#endif

/*
   Currently the Recorder_data_source works at daily time step.
*/


//070223  I am not sure what I was doing with this
// it doesn't seem to be viable or doing anything of significant


namespace CORN {
//______________________________________________________________________________
class Recorder_data_source
: public Data_source
{
 protected:
  Data_source &data_source;
   // In table based datasources, the target record will be determined from the
   // difference between the base_date and today.
 public:
   Recorder_data_source
      (Data_source &i_data_source)
      : data_source(i_data_source)
      {}
  // The Recorder_data_source takes the passed data_source
  // which relinquishes it to the recorder data source.
  // The recorder_data_source will delete it when done.

   inline virtual bool get(Data_record &data_rec)
      { return data_source.get(data_rec); }
   inline virtual bool set_data(Data_record &data_rec)                           //050705
      { return false; /*NYN?*/ }
   //170424 replaced with label_string inline virtual const char *label_cstr(char *buffer ) const { return data_source.label_cstr_deprecated(buffer); } //030123
   inline virtual const char *label_string(std::string &buffer )           const //170423
      { return data_source.label_string(buffer); }
};
//______________________________________________________________________________
} // namespace CORN

#endif

