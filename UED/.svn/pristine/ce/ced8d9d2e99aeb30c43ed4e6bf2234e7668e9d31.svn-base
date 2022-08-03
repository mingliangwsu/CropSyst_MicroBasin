#ifndef import_export_engineH
#define import_export_engineH
#include "corn/container/enumlist.h"
#include "corn/chronometry/date_time_64.h"
#include "corn/quality.hpp"
#include "corn/const.h"
#include "UED/library/UED_types.h"
#include "UED/library/datasetrec.h"
namespace UED
{
class Convertor_arguments;
//______________________________________________________________________________
class Quality_import_export_engine
{
   const Convertor_arguments &parameters;
   CORN::Enumeration_list variable_quantum_lists;     // for export
   CORN::Unidirectional_list quality_spans;           // for import
   //___________________________________________________________________________
   class Quantum
   : public implements_ CORN::Enumeration
   {public:
      CORN::Date_time_clad_64 timestamp;
      CORN::Quality_clad      quality;
    public:
      inline Quantum(CORN::datetime64 timestamp_
             ,const CORN::Quality &quality_)
         : CORN::Enumeration()
         , timestamp (timestamp_)
         , quality   (quality_)
         {}
      inline virtual bool is_key_nat32(nat32 key)                  affirmation_  //180820
      { return timestamp.get_date32() == key; }
      virtual nat32 get_key_nat32()     const { return timestamp.get_date32(); }
         // Warning currently only assuming date only time steps
         // This will not work for subdaily time steps.
         // The key currently used only for compare in sorting.
   };
   //___________________________________________________________________________
   class Variable_quantum_list
   : public implements_ CORN::Enumeration       // enumerated by variable
   , public implements_ CORN::Enumeration_list  // list of quantums
   {public:  UED::Variable_code variable_code;
    public:
      inline Variable_quantum_list(Variable_code _variable_code)
         : CORN::Enumeration_list()
         , variable_code(_variable_code)
         {}

      inline virtual bool is_key_nat32(nat32 key)                  affirmation_  //180820
         { return variable_code == key; }
      inline virtual nat32 get_key_nat32()       const  { return variable_code; }
      bool add_quantum
         (datetime64           timestamp
         ,const CORN::Quality &quality);
   };
   //___________________________________________________________________________
   class Quality_span
   : public implements_ CORN::Item
   {public:
      UED::Variable_code   variable_code;
      datetime64           date_start;
      datetime64           date_end;
      const CORN::Quality_clad quality;
    public:
      Quality_span
         (UED::Variable_code   variable_code
         ,datetime64           date_start
         ,datetime64           date_end
         ,CORN::Quality_code   quality);
   };
   //___________________________________________________________________________
 public:
   Quality_import_export_engine(const Convertor_arguments &_parameters);
   int process();
 protected:
   virtual nat32 perform_import() ;
   virtual nat32 perform_export() ;
 private:
   bool identify_quality_spans(const Binary_data_record_cowl &data_rec);
   bool add_quantum
      (UED::Variable_code   variable_code
      ,datetime64           timestamp_i
      ,const CORN::Quality &quality_i
      ,CORN::Units_code     time_step_units_code_not_currently_used);
   Variable_quantum_list  &provide_variable_quantum_list(UED::Variable_code   variable_code);
 private:
   Quality_span *last_used_quality_span;
   Quality_span *find_quality_span(UED::Variable_code variable_code,CORN::datetime64 timestamp);
   Quality_span *get_quality_span(UED::Variable_code variable_code,CORN::datetime64 timestamp);
};
//_2014-06-14___________________________________________________________________
} // namespace UED
#endif
