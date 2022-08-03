#include "CS_inspector.h"
#include <algorithm>
#include "corn/measure/unitconv.h"
#include "corn/math/statistical/statistics_types.hpp"
#ifndef Data_type_enumH
#  include "corn/data_type_enum.h"
#endif
namespace CS {
nat16 inspector_count = 0;
// Used to produce unique variable code.
// It is only 16bit because will need to reserve high word for stat descriptor
// Eventually variable the code may be composed from property ontology

CORN::Units_convertor units_convertor;

//______________________________________________________________________________
Inspector_abstract::Inspector_abstract
(CORN::Units_code                          value_units_code_
,const Emanator                           &context_
,const char                               *ontology_
,CORN::Statistic                           already_statistic_
,UED::Variable_code                        preferred_variable_code)
: CORN::Item()
, variable_code_clad(preferred_variable_code ? preferred_variable_code : ++inspector_count,0,true)
, value_units_code   (value_units_code_)
, context            (context_)
, ontology           (ontology_)
, already_statistic  (already_statistic_)
, instance_name_qualified()
, instance_qualification_list(0)
{ set_variable_code(preferred_variable_code); }
//_2017-03-14__________________________________________________________________/
Inspector_scalar::Inspector_scalar
(const float64                            &value_
,CORN::Units_code                          value_units_code_
,const Emanator                           &context_
,const char                               *ontology_
,CORN::Statistic                           already_statistic_
,UED::Variable_code                        preferred_variable_code)
: Inspector_abstract                                                             //170313
   (value_units_code_,context_,ontology_,already_statistic_,preferred_variable_code)
, CORN::Number_keyed(value_)
{}
//_2013-07-30__________________________________________________________________/
Inspector_scalar::Inspector_scalar
(const float32                            &value_
,CORN::Units_code                          value_units_code_
,const Emanator                           &context_
,const char                               *ontology_
,CORN::Statistic                           already_statistic_
,UED::Variable_code                        preferred_variable_code)
: Inspector_abstract
   (value_units_code_,context_,ontology_,already_statistic_,preferred_variable_code)
, CORN::Number_keyed(value_)
{}
//_2013-07-30__________________________________________________________________/
Inspector_scalar::Inspector_scalar
(const int32                              &value_
,CORN::Units_code                          value_units_code_
,const Emanator                           &context_
,const char                               *ontology_
,CORN::Statistic                           already_statistic_                    //171031
,UED::Variable_code                        preferred_variable_code)
: Inspector_abstract
   (value_units_code_,context_,ontology_,already_statistic_/*CORN::value_statistic*/,preferred_variable_code)
, CORN::Number_keyed(value_)
{}
//_2013-09-18__________________________________________________________________/
Inspector_scalar::Inspector_scalar
(const nat16                              &value_
,CORN::Units_code                          value_units_code_
,const Emanator                           &context_
,const char                               *ontology_
,CORN::Statistic                           already_statistic_                    //171031
,UED::Variable_code                        preferred_variable_code)
: Inspector_abstract
   (value_units_code_,context_,ontology_,already_statistic_,preferred_variable_code) //171031
, CORN::Number_keyed(value_)
{}
//_2013-09-18__________________________________________________________________/
Inspector_scalar::Inspector_scalar
(const Physical::Measure_datum &datum
,const Emanator                &context_
,const char                    *ontology_
,CORN::Statistic                already_statistic_
,UED::Variable_code             preferred_variable_code)
: Inspector_abstract
   (datum.units,context_,ontology_,already_statistic_,preferred_variable_code)
, CORN::Number_keyed (datum.amount) //(parameter_.ref_amount())
{}
//_2016-06-26__________________________________________________________________/
/*NYI
Inspector::Inspector
(const Inspector &copy_from)
: CORN::Item()
, CORN::Parameter_number               (copy_from.current,copy_from.properties,copy_from.range,copy_from.format)
//151111, CORN::Statistical_sample_cumulative<float64,float64>(copy_from.applicable) // Note do not copy the tally values or data elements
, record(0)
, context                (copy_from.context)                                     //150818
, display_units_code                   (copy_from.display_units_code)
, already_statistic                    (copy_from.already_statistic)
, qualification_list(0)
{
   //NYI    record = copy_from.clone();
   assert(false);
}
*/
//_2013-09-13_________________________________________________copy_constructor_/
void Inspector_abstract::set_variable_code(UED::Variable_code preferred_variable_code)
{
   if (preferred_variable_code)
   {
      if ((preferred_variable_code & 0xFF000000) == 0)// This appears to be a CropSyst property (CSVP)
      {
         UED::Variable_code_cowl var_prop_cowled(preferred_variable_code);
         if (var_prop_cowled.is_layered_V2())
         {  // variable property is setup already we only need to indicate non-standard
            variable_code_clad.set(preferred_variable_code);
         } else
         {  // Convert variable code to V2
            variable_code_clad.set(var_prop_cowled.get_without_layer_V1());
            variable_code_clad.set_layer_V2(var_prop_cowled.get_layer_V1());
         }
         variable_code_clad.set_non_standard();
      } else
      {  // This is a fully composed variable code UED standard or CropSyst
         variable_code_clad.set(preferred_variable_code);
      }
   } else
   {  variable_code_clad.set(++inspector_count);
      variable_code_clad.set_non_standard();
   }
}
//_2016-06-27___________________________________________________________________
int  Inspector_scalar::compare(const CORN::Item &other_item)               const
{
   const Inspector_scalar *other_as_scalar
      = dynamic_cast<const Inspector_scalar *>(&other_item);                     //170303
   if (!other_as_scalar) return 1;                                               //170303
   const Inspector_scalar &other = dynamic_cast<const Inspector_scalar &>(other_item);
   const CORN::Number_keyed::Value *other_value_ref = &other.value;
   const CORN::Number_keyed::Value *this_value_ref = &this->value;
   int comparison = 0;
   if (other_value_ref == this_value_ref)
        comparison = 0;
   else comparison = -1;
   return comparison;
}
//_2016-06-18___________________________________________________________________
bool Inspector_abstract::write(std::ostream &strm)                    stream_IO_
{  strm << provide_instance_name_qualified();
   return true;
}
//_2015-01-02___________________________________________________________________
/*180820
const char *Inspector_abstract::get_key()                                  const
{  return provide_instance_name_qualified().c_str();
}
//_2015-08-27__________________________________________________________________/
*/
const char *Inspector_abstract::key_string (std::string &buffer)          const
{  buffer = provide_instance_name_qualified(); }
//_key_string_______________________________________________________2018-08-23_/
/* check still needed  (rework using  instance if still needed */
const std::string &Inspector_abstract::provide_instance_name_qualified
(char qualification_separator)                                        provision_
{  if (!instance_name_qualified.length())
   {
      CORN::Text_list instance_path;
      list_instance_qualification(instance_path);
      instance_path.string_items(instance_name_qualified,qualification_separator);
      // Part of the instance name may be ontological so replace / with .
      std::replace(instance_name_qualified.begin(),instance_name_qualified.end(),'/','.');
   }
   return instance_name_qualified;
}
//_2015-08-27__________________________________________________________________/
nat16 Inspector_abstract::list_instance_qualification
(CORN::Text_list &append_to_qualification_list)                            const
{  context.list_instance_path(append_to_qualification_list);
   append_to_qualification_list.add_string(ontology);
      // At this point the variable instance is the ontology
      // Eventually this will be final name in the string
      // returns a list of the qualified descriptive labels for the listener.
      // List the recorder contexts and append this instance's variable name
   if (already_statistic)                                                        //160626
      append_to_qualification_list.add_cstr
         (CORN::statistic_label_table[already_statistic]);
   return true;
}
//_2015-08-28___________________________________________________________________
const CORN::Text_list &Inspector_abstract::provide_instance_qualification_list() provision_
{  if (!instance_qualification_list)
   {  instance_qualification_list = new CORN::Text_list;
      list_instance_qualification(*instance_qualification_list);
   }
   return *instance_qualification_list;
}
//_2015-08-28___________________________________________________________________
const std::string &Inspector_abstract::provide_ontology_qualified
(char qualification_separator)                                        provision_
{  if (!ontology_qualified.length())
   {
      CORN::Text_list ontology_path;
      context.append_ontology_domain_name_to(ontology_qualified,':');            //170322
      nat32 appended_count = ontology_path.string_items(ontology_qualified,qualification_separator);
      if (appended_count)
         ontology_qualified += qualification_separator;
      ontology_qualified.append(ontology);
          // Eventually this will be final name in the string
   }
   return ontology_qualified;
}
//_2016-06-14___________________________________________________________________
nat16 Inspector_abstract::list_ontology_qualification
(CORN::Text_list &append_to_qualification_list)                            const
{
      // returns a list of the qualified descriptive labels for the inspector.
      // List the recorder contexts and append this instance's variable name

//170322  context.list_ontology_path(append_to_qualification_list);
  append_to_qualification_list.add_string(ontology);
   if (already_statistic)                                                        //160626
      append_to_qualification_list.add_cstr
         (CORN::statistic_label_table[already_statistic]);
   return true;
}
//_2016-06-14___________________________________________________________________
const CORN::Text_list &Inspector_abstract
::provide_ontology_qualification_list()                               provision_
{  if (!ontology_qualification_list)
   {  ontology_qualification_list = new CORN::Text_list;
      list_ontology_qualification(*ontology_qualification_list);
   }
   return *ontology_qualification_list;
}
//_2016-06-14___________________________________________________________________
nat32 Inspector_abstract::get_variable_code()                              const
{
   //NYI assert(false);
   // I am not sure yet how to derive the variable code
   // I could continue to use the current coding mechansim
   // But I in V5 would like a more automated method to compose these codes.
   return variable_code_clad.get();
}
//_2016-06-09___________________________________________________________________
const char *Inspector_abstract
::get_units_label(std::string &units_description)                          const
{  char component_description [256];
   char component_abbr        [100];
   CORN::Units_clad smart_units(value_units_code);
   smart_units.compose_description(component_description, component_abbr);
   units_description.assign(component_abbr);
   return  units_description.c_str();
}
//______________________________________________________________________________
//______________________________________________________________________________
Inspector_vector::Inspector_vector
(const float64   *values_
,nat8             count_
,CORN::Units_code value_units_code_
,const Emanator   &context_
,const char       *ontology_
,CORN::Statistic  already_statistic_
,UED::Variable_code preferred_variable_code_)
: Inspector_abstract
   (value_units_code_,context_,ontology_
   ,already_statistic_,preferred_variable_code_)
, values    (values_)
, count     (count_)
{}
//_2017-03-26___________________________________________________________________
} // namespace CS

