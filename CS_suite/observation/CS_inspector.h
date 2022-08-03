#ifndef CS_inspectorH
#define CS_inspectorH

#include "corn/math/statistical/statistics_types.hpp"
#include "corn/container/enumlist.h"
//180103 #include "corn/container/association.h"
#include "corn/parameters/parameter.h"
#include "CS_suite/observation/CS_emanator.h"
#include "UED/library/varcodes.h"
#include "common/CS_parameter_float64.h"
#define CS_compose_var_code(CSCV,CSV)   (((nat32)1 << 31) | ((nat32)(((nat32)CSCV << 16) | (nat32)CSV)))

namespace CS {
#define GENERATE_VARIABLE_CODE 0
//______________________________________________________________________________
class Inspector_abstract
: public extends_ CORN::Item    // may want this to be Enumeration item
{public:
   UED::Variable_code_clad variable_code_clad; // provided for UED record identification
   CORN::Units_clad        value_units_code;
   const Emanator         &context;
   std::string             ontology; // definition (usually property)
      // Optional partial path to compose ontology property description.
      // Typically this will be a single word representing a specific
      // element with emanator's context
      // An emanator may actually have multiple element's
      // which may logically share a common ontology (domain) but there
      // is not a specific emanator to represent that ontology.
      // In this case forward slash may be used in the ontology label
      // to distinguish this structure.
   CORN::Statistic         already_statistic;
      // An object may have variables which are already some form of statistic
      // such as a cumulative value (summation).
      // Or maximum or minimum encountered value.
      // In such cases while the desired statistic would have been calculated,
      // futher statistical analysis would not likely be appropriate.
      // The user of the listeners can use this indicator to identify
      // variables for which further statistical analysis might not be appropriate.
 private:
   provided_ std::string      instance_name_qualified; // rename to just instance?
   provided_ CORN::Text_list *instance_qualification_list;
   provided_ std::string      ontology_qualified;
   provided_ CORN::Text_list *ontology_qualification_list;
 public: // structors
   Inspector_abstract
      (CORN::Units_code value_units_code
      ,const Emanator   &context
      ,const char       *ontology
      ,CORN::Statistic  already_statistic
      ,UED::Variable_code preferred_variable_code = 0);
   // The preferred variable code is used in CropSyst to
   // produce CropSyst UED output files compatible with V4
   // utilities but it should be considered deprecated
   // (0 indicates generate a unique code).

   void set_variable_code(UED::Variable_code preferred_variable_code);
   // Constructor notes:
   inline virtual bool is_key_string(const std::string &key)       affirmation_  //180820
      { return provide_instance_name_qualified() == key; }

/*180820  was probably only used for find_cstr now using is_key
   virtual const char *get_key()                                          const;
*/
   virtual const char *key_string (std::string &buffer)                   const; //180823

 public:
   const std::string &provide_instance_name_qualified
      (char qualification_separator='.')                             provision_;
   nat16 list_instance_qualification(CORN::Text_list &append_to_qual_list)const;
      // returns a list of the qualified descriptive labels for the inspector.
      // List the recorder contexts and append this instance's variable name
   const CORN::Text_list &provide_instance_qualification_list()      provision_;
   const std::string &provide_ontology_qualified
      (char qualification_separator='/')                             provision_;
   nat16 list_ontology_qualification(CORN::Text_list &append_to_qual_list)const;
      // returns a list of the qualified descriptive labels for the inspector.
      // List the recorder contexts and append this instance's variable name
   const CORN::Text_list &provide_ontology_qualification_list()      provision_;
   nat32 get_variable_code()                                              const;
   const char *get_units_label(std::string &units_description)            const;
   virtual bool write(std::ostream &)                                stream_IO_;
      // Currently this write simply identifies the qualified string
      // Eventually I may have a write 'mode'
      // to optionally write the observed value (or values) and statistics.
   virtual CORN::Data_type get_mode() const = 0;
          virtual bool is_vector()                               affirmation_=0; //170330
   inline virtual bool is_scalar()         affirmation_ { return !is_vector(); } //170330
};
// Template for instanciation of listener (in render_inspectors):
// CS::Inspector( XXXX.ref_amount() ,*reporter,XXXX_meta,UC_units,inspector.desired_descriptive_summary_elements,CORN::STAT_ALL_bits)

//__2017-03-14__2016-06-09__2013-07-30_________________________________________/
class Inspector_scalar // eventually rename to Inspector_scalar
: public extends_ Inspector_abstract
, public extends_ CORN::Number_keyed
{
   // Inspection of a single value
 public:
   Inspector_scalar
      (const float64    &value
      ,CORN::Units_code value_units_code
      ,const Emanator   &context
      ,const char       *ontology
      ,CORN::Statistic  already_statistic
      ,UED::Variable_code preferred_variable_code = 0);
   Inspector_scalar
      (const float32    &value
      ,CORN::Units_code value_units_code
      ,const Emanator   &context
      ,const char       *ontology
      ,CORN::Statistic  already_statistic
      ,UED::Variable_code preferred_variable_code = 0);
   Inspector_scalar
      (const int32      &value
      ,CORN::Units_code value_units_code
      ,const Emanator   &context
      ,const char       *ontology
      ,CORN::Statistic   already_statistic_                                      //171031
      ,UED::Variable_code preferred_variable_code = 0);
   Inspector_scalar
      (const nat16      &value
      ,CORN::Units_code value_units_code
      ,const Emanator   &context
      ,const char       *ontology
      ,CORN::Statistic  already_statistic                                        //171031
      ,UED::Variable_code preferred_variable_code = 0);
   Inspector_scalar
      (const Physical::Measure_datum &datum
      ,const Emanator   &context
      ,const char       *ontology
      ,CORN::Statistic  already_statistic = CORN::value_statistic
      ,UED::Variable_code preferred_variable_code = 0);
 public:
   inline virtual CORN::Data_type get_mode()                               const
      { return CORN::Number_keyed::mode; }
   virtual int   compare(const CORN::Item &)                              const;
   inline virtual bool is_vector()                affirmation_ { return false; }
};
//_2017-03-14__2016-06-04______________________________________________________/
class Inspector_vector
: public extends_ Inspector_abstract
{
   const float64   *values;
   nat8             count;
 public:
   Inspector_vector
      (const float64   *values_
      ,nat8             count_
      ,CORN::Units_code value_units_code
      ,const Emanator   &context
      ,const char       *ontology
      ,CORN::Statistic  already_statistic
      ,UED::Variable_code preferred_variable_code = 0);
   inline virtual CORN::Data_type get_mode()                               const
      { return CORN::DT_float64; }
   inline virtual bool is_vector()                 affirmation_ { return true; }
   inline virtual int compare(const CORN::Item &)                          const
      { return 1; }
      // Not currently needed assuming all Inspector_vector intances
      // are unique. Could return 00 if pointing to the same values.

};
//_2017-03-14__________________________________________________________________/
} // namespace CS
#endif

