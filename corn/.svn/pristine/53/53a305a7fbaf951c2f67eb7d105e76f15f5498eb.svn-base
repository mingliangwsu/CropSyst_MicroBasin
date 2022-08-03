#ifndef validtypH
#define validtypH
#ifdef _MSC_VER
//    I don't know why MS VC++ does not have values.h!
#   include "corn/values_MSC.h"
#else
#ifdef __BCPLUSPLUS__
#   include <values.h>  // for MINFLOAT MAXFLOAT
#endif
#endif

#include <limits>

#ifndef MINFLOAT
#define MINFLOAT std::numeric_limits<float32>::min()
//170725 1.17549435E-38
#endif
#ifndef MAXFLOAT
#define MAXFLOAT std::numeric_limits<float32>::max()
//170725 3.4028237E+38
#endif
#ifndef MAXSHORT
#define MAXSHORT 0x7FFF
#endif
#ifndef MINSHORT
#define MINSHORT 0x8000
#endif
#ifndef MINLONG
#define MINLONG 0x80000000
#endif
#ifndef MAXLONG
#define MAXLONG 0x7FFFFFFF
#endif
#ifndef unitsH
#  include "corn/measure/units.h"
#endif

#define Phrase_label  const char *
#define OPTIONAL_PHRASE 0
#define MESSAGE_TEXT_SIZE 3000

//______________________________________________________________________________
namespace CORN {

   enum Validation_status
   { unavailable_status
   , missing_status
   , error_low_status
   , error_status
   , error_high_status
   , pot_error_low_status
   , pot_error_status
   , pot_error_high_status
   , warning_low_status
   , warning_status
   , warning_high_status
   , ready_status
   , good_status
   , disabled_status
   , STATUS_COUNT
   };

   extern int RUI_colored_resource_index[];
//170319 #define unknown_status unavailable_status

extern const char *HTML_validation_colors[];

enum RUI_validation_stage                                                        //990310
{RUI_valid_cleanup,RUI_valid_allow_error_display,RUI_valid_error_displayed,RUI_valid_stop_error_display};
//          OWL calls the validator many many times, we actually only want to display the error message once
//          also we don't wan't some little precision loss to indicate a modification.

#define NO_KEY 0
//______________________________________________________________________________
class Valid_type          // abstract class
{
public:
   char *key;                  // The key is optional                            //020129
   Phrase_label description1;  // Description of the value
   Phrase_label description2;
   Validation_status status;                                                     //000305
public:
   Valid_type
      (const char     *i_key
      , Phrase_label i_description1=0
      , Phrase_label i_description2=0);
      //  This constructor is for use with common translator
   Valid_type(const Valid_type &from);
   virtual ~Valid_type();                                                        //980508
   virtual Validation_status validate                                            //980401
      (char *message_text,bool HTML_format) = 0; // pure                         //030123
   inline bool is_valid()                                                        //000306
      {  // Currently accept anything that is not an error as valid.
         return  (status < error_low_status) || (status > error_high_status);
      }
   inline Validation_status set_status(Validation_status new_status)             //000306
      { return status = new_status;}
   virtual const char *log_cstr(char *buffer)                              const;//030123
   virtual const char *get_value_c_str()                                   const = 0;//020812
private:
   void set_key(const char *i_key);                                              //020129
};
//______________________________________________________________________________
class Valid_number: public Valid_type
{public:
   uint8                uint8_decimals;
   float64              default_value;
   float64              min_warning;
   float64              max_warning;
   float64              min_error;
   float64              max_error;
   Units_clad           units_code;          // Use 0 to force units description to be displayed, 0 option is used when there is no common units code defined.   //030922
   Units_clad           shown_units_code;    // This is used by valid number editors to show a units that the user may select.                                   //030922
   Phrase_label         units_description;   // If specified, will override output of unit_code.
 public: // Save parameters
   const Units_code    *alt_units_codes;                                         //040414
   //     Null terminated array of units codes that can be user selected for show units.
   //     Usually will be a constant array, must remain in scope throughout existance of valid type.
 public:
   inline Valid_number
      (Units_code    i_units_code
      , const char  *i_key
      ,uint8         i_decimals
      ,float64       i_default_value
      ,float64       i_min_warning  = MINFLOAT
      ,float64       i_max_warning  = MAXFLOAT
      ,float64       i_min_error    = MINFLOAT
      ,float64       i_max_error    = MAXFLOAT
      ,Phrase_label  i_units        = OPTIONAL_PHRASE
      ,Phrase_label   description1   = OPTIONAL_PHRASE
      ,Phrase_label   description2   = OPTIONAL_PHRASE)
      :Valid_type          (i_key,description1,description2)                     //030922
      ,uint8_decimals      (i_decimals)
      ,default_value       (i_default_value)
      ,min_warning         (i_min_warning)
      ,max_warning         (i_max_warning)
      ,min_error           (i_min_error)
      ,max_error           (i_max_error)
      ,units_code          (i_units_code)
      ,shown_units_code    (i_units_code)
      ,units_description   (i_units)
      ,alt_units_codes(0)
      {}
   inline Valid_number(const Valid_number &from)
      :Valid_type(from)
      ,uint8_decimals(from.uint8_decimals)
      ,default_value(from.default_value)
      ,min_warning(from.min_warning)
      ,max_warning(from.max_warning)
      ,min_error(from.min_error)
      ,max_error(from.max_error)
      ,units_code(from.units_code)
      ,shown_units_code(from.shown_units_code)
      ,units_description(from.units_description)
      ,alt_units_codes(0)
      {}
    virtual Validation_status validate                                           //980401
       (char *message_text   // Caller must provide large enough buffer          //020129
       ,bool HTML_format) = 0; // pure
   inline virtual const char *get_units_label()                            const //000808
      { return units_description; }
   virtual const char *log_cstr(char *buffer)                              const;//030123
   Validation_status validate_value                                              //980401
      (char *message_text
      ,bool HTML_format, float64 i_value);
   void compose_range_message
      (char               *message_text  // Caller must provide large enough buffer //980401
      ,bool                HTML_format                                              //010305
		,bool                must
		,float64             low
		,float64             high
		,float64             value
		,Phrase_label        units
      ,Phrase_label        label1
      ,Phrase_label        label2
      ,Phrase_label        label3);
   inline void set_alt_units_codes(const Units_code *i_alt_units_codes)          //040414
      { alt_units_codes = i_alt_units_codes; }
};
//______________________________________________________________________________
class Valid_float64 : public Valid_number
{public:
   float64 &value;
public:
   inline Valid_float64
      (float64        &i_value
      ,Units_code      i_units_code
      ,const char     *i_key
      ,uint8           i_decimals
      ,float32         i_default_value
      ,float32        i_min_warning = MINFLOAT
      ,float32        i_max_warning = MAXFLOAT
      ,float32        i_min_error   = MINFLOAT
      ,float32        i_max_error   = MAXFLOAT
      ,Phrase_label    i_units       = OPTIONAL_PHRASE
      ,Phrase_label    description1  = OPTIONAL_PHRASE
      ,Phrase_label    description2  = OPTIONAL_PHRASE)
      :Valid_number
      (i_units_code
      ,i_key
      ,i_decimals
	 	,i_default_value
      ,i_min_warning
      ,i_max_warning
      ,i_min_error
      ,i_max_error
      ,i_units
      ,description1
      ,description2)
      ,value(i_value)
      { }
   inline Valid_float64(const Valid_float64 &from)
    :Valid_number(from)
    ,value(from.value){}

   inline virtual Validation_status validate                                    //980401
      (char *message_text
      ,bool  HTML_format)
      { return Valid_number::validate_value(message_text,HTML_format,value); }
   virtual const char *get_value_c_str()                                   const;//020812
};
//_1998-04-03___________________________________________________________________
class Valid_float32 : public Valid_number
{
public:
  float32 &value;
public:
   inline Valid_float32                                                             //980403
      (float32    &i_value
      ,Units_code  i_units_code
      ,const char *i_key
      ,uint8       i_decimals
      ,float32     i_default_value
      ,float32     i_min_warning =MINFLOAT
      ,float32     i_max_warning =MAXFLOAT
      ,float32     i_min_error   =MINFLOAT
      ,float32     i_max_error   =MAXFLOAT
      ,Phrase_label i_units       =OPTIONAL_PHRASE
      ,Phrase_label description1  =OPTIONAL_PHRASE
      ,Phrase_label description2  =OPTIONAL_PHRASE)
      :Valid_number
      (i_units_code
      ,i_key
      ,i_decimals
		,i_default_value
      ,i_min_warning
      ,i_max_warning
      ,i_min_error
      ,i_max_error
      ,i_units
      ,description1
      ,description2)
      ,value(i_value)
      {
         // Not setting the default value here because we may already have loaded the data
         // this problem was identified when I tried to setup geolocation in weather editor.
         //050505                  value = i_default_value;
      }

//080723 prototype template (float32    &i_value,Units_code  i_units_code,const char *i_key,uint8       i_decimals,float32     i_default_value,float32     i_min_warning =MINFLOAT,float32     i_max_warning =MAXFLOAT,float32     i_min_error   =MINFLOAT,float32     i_max_error   =MAXFLOAT,Phrase_label i_units       =OPTIONAL_PHRASE,Phrase_label description1  =OPTIONAL_PHRASE,Phrase_label description2  =OPTIONAL_PHRASE)

   inline Valid_float32(const Valid_float32 &from)                               //980403
      :Valid_number(from)
      ,value(from.value)
      {}
   inline virtual Validation_status validate                                     //980401
       (char *message_text,bool  HTML_format)
      { return Valid_number::validate_value(message_text,HTML_format,(float64)value);       //020129
      }
   inline virtual float32 get_value()                                      const
      { return value; }
   virtual const char *get_value_c_str()                                   const;//020812
 #ifdef __GNUC__
 public: // Not sure why GCC is giving non-static reference member ... cant use default assignment operator
    Valid_float32& operator= (const Valid_float32 &/*pa*/) {return *this;}           //150317
 #endif
};
//_1998-04-03___________________________________________________________________
class Valid_int16 : public Valid_number
{public:
   int16 &value;
public:
   inline Valid_int16
      (int16        &i_value
      ,const char   *i_key
      ,int16         i_default_value
      ,int16         i_min_warning  = -MAXSHORT
      ,int16         i_max_warning  = MAXSHORT
      ,int16         i_min_error    = -MAXSHORT
      ,int16         i_max_error    = MAXSHORT
      ,Phrase_label  i_units        = OPTIONAL_PHRASE
      ,Phrase_label  description1   = OPTIONAL_PHRASE
      ,Phrase_label  description2   = OPTIONAL_PHRASE)
      :Valid_number
		(0   // ints currently have no units codes
      ,i_key
      ,0   // decimals
		,i_default_value
      ,i_min_warning
      ,i_max_warning
      ,i_min_error
      ,i_max_error
      ,i_units
      ,description1
      ,description2)
      ,value(i_value)
      {}
   inline Valid_int16(const Valid_int16 &from)
      :Valid_number(from)
      ,value(from.value)
      {}
   inline virtual Validation_status validate                                     //980401
      (char *message_text                                                        //020129
      ,bool           HTML_format)
      {  return Valid_number::validate_value(/*vf*/message_text,HTML_format,(float64)value);
      }
   virtual const char *get_value_c_str()                                   const;//020812
};
//______________________________________________________________________________
class Valid_int32 : public Valid_number
{public:
   int32 &value;
 public:
   inline Valid_int32
      (int32        &i_value
      ,const char   *i_key
      ,int32         i_default_value
      ,int32         i_min_warning  = (int32)-MAXLONG
      ,int32         i_max_warning  = (int32)MAXLONG
      ,int32         i_min_error    = (int32)-MAXLONG
      ,int32         i_max_error    = (int32)MAXLONG
      ,Phrase_label  i_units        = OPTIONAL_PHRASE
      ,Phrase_label  description1   = OPTIONAL_PHRASE
      ,Phrase_label  description2   = OPTIONAL_PHRASE)
      :Valid_number
      (0   // ints currently have to units codes
      ,i_key
      ,0   // decimals
      ,i_default_value
      ,i_min_warning
      ,i_max_warning
		,i_min_error
		,i_max_error
		,i_units
		,description1
		,description2)
      ,value(i_value)
      {}
   inline Valid_int32(const Valid_int32 &from)
      :Valid_number(from)
      ,value(from.value)
      {}
   inline virtual Validation_status validate                                     //980401
      (char *message_text                                                        //020129
      ,bool HTML_format)
      {  return Valid_number::validate_value(/*vf*/message_text,HTML_format,(float64)value);
      }
   virtual const char *get_value_c_str()                                   const;//020812
};
//______________________________________________________________________________
}; // namespace CORN

#define CORN_valid_type       Valid_type
#define CORN_valid_string     Valid_string
#define CORN_valid_number     Valid_number
#define CORN_valid_int32      Valid_int32
#define CORN_valid_float64    Valid_float64
#define CORN_valid_converting_float CORN::Valid_converting_float

#endif
//validtyp

