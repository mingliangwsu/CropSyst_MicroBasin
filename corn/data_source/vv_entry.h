#ifndef VV_entryH
#define VV_entryH

#define NO_ANNOTATION 0
#include <string.h>
#include "corn/container/bilist.h"
#ifndef labeled_enumH
#  include "corn/labeled_enum.h"
#endif
#ifndef unitsH
#  include "corn/measure/units.h"
#endif
#ifndef validtypH
#  include "corn/validate/validtyp.h"
#endif
#ifndef data_type_enumH
#  include "corn/data_type_enum.h"
#endif
#if (!__BCPLUSPLUS__ || (__BCPLUSPLUS__ > 0x340))
// BC++ did not have std::string until after verison 5
#ifndef parameterH
#  include "corn/parameters/parameter.h"
#endif
#endif
#include "corn/chronometry/date_time_64.h"
#include "corn/chronometry/date_32.h"

namespace CORN
{
   enum VV_Data_type
   {  VV_char_array = DT_COUNT
   ,  VV_DEN  // directory_entry_name (file or directory)
   ,  VV_enum
   ,  VV_units
   ,  VV_byte
   ,  VV_datetime64
   ,  VV_COUNT  // count of VV_datatypes
   };

#define VV_filename     VV_DEN

#define VV_unknown    (unsigned char)DT_not_assigned
#define VV_string     (unsigned char)DT_string
#define VV_int8       (unsigned char)DT_int8
#define VV_int16      (unsigned char)DT_int16
#define VV_int32      (unsigned char)DT_int32
#define VV_nat8      (unsigned char)DT_nat8
#define VV_nat16     (unsigned char)DT_nat16
#define VV_nat32     (unsigned char)DT_nat32
#define VV_float32    (unsigned char)DT_float32
#define VV_float64    (unsigned char)DT_float64
#define VV_bool       (unsigned char)DT_bool
#define VV_date       (unsigned char)DT_date
#define VV_char_array (unsigned char)VV_char_array
//#define VV_filename   (unsigned char)14
//#define VV_enum       (unsigned char)15
//#define VV_datetime64 (unsigned char)16
//#define VV_units      (unsigned char)17

   class Generic_data_record;
   class Tabular_column;
   class Parameter_abstract;
   class Seclusion;                                                              //180515

   namespace OS                                                                  //121108
   {  interface_ Directory_entry_name;                                           //121108
   }                                                                             //121108

// Note that get_cstr methods have been replaced with append_to_string           //150731

//______________________________________________________________________________
class VV_entry_item
: public extends_ Item
{
protected: // Contributes
   bool        encountered;  // This is set to true if the expected entry occurs in the file //010102
public:
   VV_entry_item();                                                              //090414
//180820 virtual const char *get_key()                                        const=0;
   //190726LML virtual const std::string &get_variable()                            const=0;  //180820
   virtual const std::string get_variable()                            const=0;  //180820
   inline bool was_encountered()                                           const //050927
      { return encountered ;}
   inline void set_encountered(bool _encountered)                  modification_ //010103
      { encountered = _encountered;}
   virtual bool set_str(const char *value_cstr)                 modification_=0;
      ///< Set the value for the respective type from a C style null terminated string representation.
      ///  Must be overridden by derived classes.
      /// \return true if the value could be set given the string (Usually returns true)
   inline virtual bool set_string(const std::string &value_string) modification_
      { return set_str(value_string.c_str()); }
      ///< Set the value for the respective type string representation.
      /// \return true if the value could be set given the string (Usually returns true)
   virtual bool write_wizard(std::ostream &wizard_stream) stream_IO_ {return true;}

};
//_2009-04-14___________________________________________________________________
class VV_abstract_entry
: public VV_entry_item
{
 protected:
   mutable Tabular_column *tabular_column;
      // When reading/writing tabular data sources, the tabular column information may be provided. Not owned by this //070524
 public:
   inline VV_abstract_entry() : VV_entry_item(),tabular_column(0)             {}
   virtual nat16 get_max_strlen()                                       const=0;
   virtual const std::string &append_to_string(std::string &buffer)     const=0; //140615
   virtual nat8 get_type()                                              const=0;
   // This must be overridden by derived classes.
   // This will get the value for the respective type from a string representation.
   // The derived class must convert the value from it's type to a string.
   inline const Tabular_column *set_tabular_column                               //070524
      (Tabular_column *tabular_column_)                                mutation_
      {tabular_column = tabular_column_; return tabular_column;}
   inline const Tabular_column *get_tabular_column()                       const //070524
      {return tabular_column;}
};
//_2011-11-07___________________________________________________________________
/*!
This abstract class normally does not need to be used by end programmers.
VV_xxx_entry classes correspond INI file entries, I.e.:
variable=value
Entries are extended in that entries may be associated one or two
optional annotations with the entrie that follows the data on the same line:
variable=value Annotation 1 Annotation 2
*/
//______________________________________________________________________________
class VV_base_entry
: public VV_abstract_entry
{
 protected: // Attributes
   std::string variable;          // or the label or the "key" of the field
   nat16       max_strlen;
   // max_strlen is used by dBase an other fixed field length records
   // to identified the field length that should be reserved when creating databases
   // this should be the maximum size of the value when represented as text
 public:
   std::string annotation1;   // Note this cannot be char * because of Recorder_float64 constructor  //090414 eventually rename to caption
      // This will generally be caption
   std::string annotation2;
      // This will generally be hint
   // conceptual ontology
 protected: // Contributes
   Validation_status *validation_status;     // optional, 0 if not used
 public:
   VV_base_entry
      (const char *variable_
      ,nat16 max_strlen_
      ,const char *annotation1_ = NO_ANNOTATION
      ,const char *annotation2_ = NO_ANNOTATION);
   virtual const char *label_string(std::string &buffer)                  const; //170423
   virtual bool write(std::ostream &f)                             performs_IO_; //150728
   inline virtual nat8 get_type()                   const { return VV_unknown; }
   virtual bool is_key_string(const std::string &key)              affirmation_; //180820
/*180820  was probably only used for find_cstr now using is_key

   virtual const char *get_key()                                          const;
*/
   inline virtual const char *key_string (std::string &buffer)            const  //170126
      { buffer = variable; return buffer.c_str();}
   //190727LML inline virtual const std::string &get_variable() const { return variable; }  //180820
   inline virtual const std::string get_variable() const { return variable; }  //180820

   inline void set
      (const char * annotation1_ = NO_ANNOTATION
      ,const char * annotation2_ = NO_ANNOTATION)                  modification_
   {  // This set is used only for INI classes
      annotation1 = annotation1_;
      annotation2 = annotation2_;
   }
   inline virtual nat16 get_max_strlen()                                   const
      { return max_strlen; }
   // This is used by dBase an other fixed field length records
   // to identified the field length that should be reserved when creating databases
   // this should be the maximum size of the value when represented as text
   inline virtual void bind_to_validation_status(Validation_status *_validation_status)
      { validation_status = _validation_status; }
   inline void set_validation_status(Validation_status _validation_status)
      { if (validation_status) *validation_status = _validation_status; }
   virtual bool write_wizard(std::ostream &wizard_stream)            stream_IO_;
};
//_1997-09-30___________________________________________________________________
#if (!__BCPLUSPLUS__ || (__BCPLUSPLUS__ > 0x340))
class VV_parameter_entry
: public VV_abstract_entry
{
protected:
   Parameter_abstract &parameter;
public:
   VV_parameter_entry(Parameter_abstract &_parameter);
   virtual bool is_key_string(const std::string &key)              affirmation_; //180820
   //190726LML virtual const std::string &get_variable()                              const;  //180820
   virtual const std::string get_variable()                              const;  //180820

/*180820  was probably only used for find_cstr now using is_key
   virtual const char *get_key()                                          const;
   */
   virtual bool set_str(const char *value_cstr)                   modification_;
   // BC++ did not have std until after verison 5
   virtual bool write(std::ostream &f)                             performs_IO_; //150728
   virtual nat16 get_max_strlen()                                         const; //111107
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   virtual nat8 get_type()                                                const;
   virtual bool write_wizard(std::ostream &wizard_stream)            stream_IO_;
};
#endif
//_2009-04-14___________________________________________________________________

class VV_unexpected_entry : public VV_base_entry
{
   // This class is seldom used by end programmers.
   // It used to store variable value entries that are not necessarily
   // 'expected' in the file.
   // This class is also used for INI_file and HTML_form classes
protected:
   std::string value;                                                            //111104
      // The program is not expecting this variable value pair,
      // but we will keep a local store of it so we can reproduce the file exactly.
public:
   VV_unexpected_entry
      (const char *key_
      ,const std::string &value_
      ,const char * annotation1_ = NO_ANNOTATION
      ,const char * annotation2_ = NO_ANNOTATION
      );
   inline virtual ~VV_unexpected_entry()                     {  value.clear(); } //120311
   inline virtual nat8 get_type()                   const { return VV_unknown; }
   inline std::string &get_value()                             { return value; }
   inline void set
      (const std::string  &value_
      ,const char * /*annotation1_ = NO_ANNOTATION*/
      ,const char * /*annotation2_ = NO_ANNOTATION*/
      )                                                            modification_
      { value.assign(value_); }
      //d            This method is used only for INI_file classes
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline virtual bool set_str(const char *value_str) { value.assign(value_str); return true;}//010103
};
//_1997-06-22___________________________________________________________________
class VV_string_entry : public VV_base_entry
{
 protected:
   std::string &value;  // reference to program data
 public:
   std::string format;                                                           //180515
      // ISO_xxx or simple pattern or regular expression
 public:
   VV_string_entry
      (const char                *key_
      ,modifiable_ std::string   &value_
      ,nat16                     max_strlen_                                     //010104
      ,const char * annotation1_ = NO_ANNOTATION
      ,const char * annotation2_ = NO_ANNOTATION
      );
   inline void set(const std::string &value_)                      modification_
      { value.assign(value_ ); }
   inline virtual nat8 get_type()                    const { return VV_string; }
   inline virtual bool set_str(const char *value_str)              modification_
      { set(value_str); return true;}                                            //010103
   virtual const std::string &append_to_string(std::string &buffer)        const;//140615
};
//_1997-09-30___________________________________________________________________
class VV_directory_entry_entry: public VV_base_entry
{protected:
   OS::Directory_entry_name &value;  // reference to value to modified I/O       //000211
 protected:
   provided_ Seclusion *seclusion;                                                          //180515
      // Seclusion can be set to apply filters and validate input
 public:
   VV_directory_entry_entry
      (const char   *key_
      ,modifiable_   OS::Directory_entry_name &value_
      ,nat16         max_strlen_                                                 //010104
      ,const char * annotation1_ = NO_ANNOTATION
      ,const char * annotation2_ = NO_ANNOTATION);
   void set(const OS::Directory_entry_name &value_ );
   void set(const std::string  &value_ );                                        //990824
   inline virtual nat8 get_type()                  const { return VV_filename; }
   virtual bool set_str(const char *value_str)                    modification_; //010103
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline virtual OS::Directory_entry_name &ref_value()  const { return value; } //161207

   Seclusion &provide_seclusion()                                    provision_; //180515
};
//______________________________________________________________________________
#ifndef _MSC_VER
//100929 This is sort of deprecated because it is unsafe, it is currently only used in ClimGen.
class VV_char_array_entry : public VV_base_entry
{protected:
   char *value;  // reference to program data
 public:
   VV_char_array_entry
      (const       char *key_
      ,modifiable_ char *value_
      ,nat16             max_strlen_                                             //010104
      ,const char * annotation1_ = NO_ANNOTATION
      ,const char * annotation2_ = NO_ANNOTATION);
   inline void set(const std::string &value_)                      modification_
      { strcpy(value,value_ .c_str()); }
   inline virtual nat8 get_type()                const { return VV_char_array; }
   inline virtual bool set_str(const char *value_str)              modification_
       { set(value_str); return true;}                                           //010103
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
};
#endif
//_1997-06-22___________________________________________________________________
class VV_int8_entry : public VV_base_entry
{protected:
   int8 &value;
 public:
   VV_int8_entry(const char *key_,modifiable_ int8 &value_
      ,const char *annotation1_ = NO_ANNOTATION,const char *annotation2_ = NO_ANNOTATION);
   inline void set(const int8 value_)            modification_{ value = value_;}
   virtual bool set_str(const char *value_str)                    modification_; //010103
   inline virtual nat8 get_type()                      const { return VV_int8; }
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline int8 get_value()                                const { return value;} //030438
};
//_1998-04-05__1997-06-22_______________________________________________________
class VV_nat8_entry : public VV_base_entry
{protected:
   nat8 &value;
   nat8 radix;                                                                   //010523
 public:
   VV_nat8_entry(const char *key_,modifiable_ nat8 &value_,nat8 _radix
      ,const char * annotation1_ = NO_ANNOTATION,const char * annotation2_ = NO_ANNOTATION);
   inline void set(const nat8 value_)           modification_{ value = value_; }
   virtual bool set_str(const char *value_str)                    modification_; //010103
   inline virtual nat8 get_radix()                       const { return radix; }
   inline virtual nat8 get_type()                      const { return VV_nat8; }
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline nat8 get_value()                                const { return value;} //030438
};
//_1998-04-05__1997-06-22_______________________________________________________
class VV_byte_entry : public VV_base_entry
{protected:
   nat8 &value;
 public:
   VV_byte_entry(const char *key_,modifiable_ nat8 &value_
      ,const char * annotation1_ = NO_ANNOTATION,const char * annotation2_ = NO_ANNOTATION);
   inline void set(const unsigned char  value_) modification_{ value = value_; }
   virtual bool set_str(const char *value_str)                    modification_; //010103
   inline virtual nat8 get_type()                      const { return VV_byte; }
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline nat8 get_value()                               const { return value; } //030428
};
//_1997-06-22___________________________________________________________________
class VV_bool_entry : public VV_base_entry
{protected:
   bool &value;
 public:
   enum Form {form_1,form_t,form_T,form_true, form_True, form_TRUE};             //010104
   Form text_form;                                                               //010104
 public:
   VV_bool_entry
      (const char *key_
      ,modifiable_ bool &value_
      ,Form    _text_form                                                        //010104
      ,const char * annotation1_ = NO_ANNOTATION
      ,const char * annotation2_ = NO_ANNOTATION);
   inline void set(const bool value_ )         modification_{ value = value_ ; }
   virtual bool set_str(const char *value_str)                    modification_; //010103
   inline virtual nat8 get_type()                      const { return VV_bool; }
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline bool &get_value()                              const { return value; } //010926
};
//_1997-06-22___________________________________________________________________
class VV_int16_entry : public VV_base_entry
{protected:  friend class Generic_data_record;                                   //010213
  int16 &value;
 public:
   VV_int16_entry(const char *key_,modifiable_ int16 &value_
      ,const char * annotation1_ = NO_ANNOTATION
      ,const char * annotation2_ = NO_ANNOTATION);                               //970622
   inline void set(const int16 value_ )       modification_ { value = value_ ; }
   virtual bool set_str(const char *value_str)                    modification_; //010103
   inline virtual nat8 get_type()                     const { return VV_int16; }
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline int16 get_value()                              const { return value; } //030428
};
//_1998-04-05__1997-06-22_______________________________________________________
class VV_nat16_entry : public VV_base_entry
{protected:
   nat16 &value;
   nat8 radix;
 public:
   VV_nat16_entry(const char *key_,modifiable_ nat16 &value_ ,nat8 _radix
      ,const char * annotation1_ = NO_ANNOTATION
      ,const char * annotation2_ = NO_ANNOTATION);
   inline void set(const nat16 value_ )        modification_{ value = value_ ; }
   virtual bool set_str(const char *value_str)                    modification_;
   inline virtual nat8 get_type()                     const { return VV_nat16; }
   inline virtual nat8 get_radix()                       const { return radix; }
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline nat16 get_value()                              const { return value; }
};
//_1998-04-05__1997-06-22_______________________________________________________
class VV_int32_entry : public VV_base_entry
{protected:  friend class Generic_data_record;                                   //170511
   int32 &value;
 public:
   VV_int32_entry(const char *key_,modifiable_ int32 &value_
      ,const char * annotation1_ = NO_ANNOTATION
      ,const char * annotation2_ = NO_ANNOTATION);
   inline void set(int32 value_)                modification_{ value = value_; }
   virtual bool set_str(const char *value_str)                    modification_;
   inline virtual nat8 get_type()                     const { return VV_int32; }
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline int32 get_value()                              const { return value; }
};
//_1998-04-05__1997-06-22_______________________________________________________
class VV_nat32_entry : public VV_base_entry
{protected:
   nat32  &value;
   nat8    radix;
 public:
   VV_nat32_entry(const char *key_,modifiable_ nat32 &value_,nat8 _radix
      ,const char * annotation1_ = NO_ANNOTATION
      ,const char * annotation2_ = NO_ANNOTATION);
   inline void set(nat32 value_)                modification_{ value = value_; }
   virtual bool set_str(const char *value_str)                    modification_;
   inline virtual nat8 get_type()                     const { return VV_nat32; }
   inline virtual nat8 get_radix()                       const { return radix; }
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline nat32 get_value()                              const { return value; }
};
//_1998-04-05__1997-06-22_______________________________________________________
class VV_float32_entry : public VV_base_entry
{protected:
   float32 &value;
 public:
   VV_float32_entry(const char *key_,modifiable_ float32 &value_,const char * annotation1_ = NO_ANNOTATION,const char * annotation2_ = NO_ANNOTATION);
   inline void set(float32 value_)              modification_{ value = value_; }
   virtual bool set_str(const char *value_str)                    modification_;
   inline virtual nat8 get_type()                   const { return VV_float32; }
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline float32 get_value()                             const { return value;}
};
//_1998-04-05__1997-06-22_______________________________________________________
class VV_float64_entry : public VV_base_entry
{protected:
   float64 &value;
 public:
   VV_float64_entry(const char *key_,modifiable_ float64 &value_
      ,const char *annotation1_=NO_ANNOTATION,const char *annotation2_=NO_ANNOTATION);
   inline void set(float64 value_)               modification_{ value = value_;}
   virtual bool set_str(const char *value_str)                    modification_;
   inline virtual nat8 get_type()                   const { return VV_float64; }
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline float64 get_value()                             const { return value;}
};
//_1998-04-05__1997-06-22_______________________________________________________
class VV_date_entry : public VV_base_entry
{protected:
   CORN::Date_clad_32 &value;  // string is stored in word list
   bool        formatted;  // if true then it is assumed the value will be I/O with the value's format
                           // if false then always I/O as Date32
   contribute_ sint16 year_offset;                                               //120331
      // Normally 0, but may be 1900 (or 2000) if years in the data record
      // are only two digits.
 public:
   VV_date_entry(const char *key_,modifiable_ CORN::Date_clad_32 &value_
      ,bool formatted,sint16 year_offset
      , const char * annotation1_ = NO_ANNOTATION,const char * annotation2_ = NO_ANNOTATION);
   void set(const CORN::Date_const &value_ )                      modification_;
   virtual bool set_str(const char *value_str)                    modification_;
   inline virtual nat8 get_type()                      const { return VV_date; }
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline const CORN::Date_const &get_value()            const { return value; }
   long get_days_between(const CORN::Date_const &,bool inclusive = true)  const;
   virtual const Date_format &set_cstr(const char *format)        modification_; //141120
   # define OBJECT_PASCAL_DATE_BASE 1889365
};
//_1998-04-05__1997-06-22_______________________________________________________
class VV_datetime64_entry : public VV_base_entry
{protected:
   CORN::Date_time_clad_64 &value;  // string is stored in word list
   CORN::Date_format date_format;                                                //170525
   CORN::Time_format time_format;
   bool        formatted;  // if true then it is assumed the value will be I/O with the value's format
                           // if false then always I/O as Date32
   contribute_ sint16 year_offset;                                               //120331
      // Normally 0, but may be 1900 (or 2000) if years in the data record
      // are only two digits.
 public:
   VV_datetime64_entry(const char *key,modifiable_ CORN::Date_time_clad_64 &value
      ,bool formatted,sint16 year_offset
      ,const char * annotation1_ = NO_ANNOTATION,const char * annotation2_ = NO_ANNOTATION);
   void set(const CORN::Date_time &value)                         modification_;
   virtual bool set_str(const char *value_str)                    modification_;
   inline virtual nat8 get_type()                      const { return VV_date; }
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline const CORN::Date_time_clad_64 &get_value()      const { return value;}
   virtual bool set_cstr
        (const char *date_format
        ,const char *time_format)                                 modification_;
      //The format can include both date and/or time format strings
      // I.e.  YYYY-MM-DD HH:MM:SS
};
//_1997-06-22___________________________________________________________________

class VV_enum_entry : public VV_base_entry
{protected:
   Labeled_enum  &labeled_enum;
 public:
   VV_enum_entry(const char *key_
      ,Labeled_enum  &_labeled_enum
      ,const char * annotation1_ = NO_ANNOTATION
      ,const char * annotation2_ = NO_ANNOTATION);
   void                     set(const char *value_label_)         modification_;
   virtual bool             set_str(const char *value_str)        modification_;
   inline virtual unsigned char  get_type()            const { return VV_enum; }
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline int32 get_value()           const { return labeled_enum.get_int32(); }
};
//_1997-07-09___________________________________________________________________
class VV_units_entry : public VV_base_entry
{protected:
   Units_clad &units_code;
 public:
   VV_units_entry(const char *key_,Units_clad &_units_code);
   void                     set(Units_code _code)                 modification_;
   virtual bool             set_str(const char *value_str)        modification_;
   inline virtual unsigned char  get_type()           const { return VV_units; }
   virtual const std::string &append_to_string(std::string &buffer)       const; //140615
   inline Units_clad &get_value()                   const { return units_code; }
};
//_2004-04-14___________________________________________________________________
class VV_enumerated_section; // for forward ref
//______________________________________________________________________________
class VV_Section : public Item
{protected: friend class VV_enumerated_section;
   std::string label/*180821 section_label*/;
   bool        encountered;                                                      //020419
 public:
   CORN::Bidirectional_list entries;
 public:
   VV_Section(const std::string &_label);
   virtual bool        write(std::ostream &f)                      performs_IO_; //150728
   inline bool         set_encountered(bool _encountered)         modification_  //010103
      { encountered = _encountered; return encountered;}
   virtual const char *label_string(std::string &buffer)                  const; //170423
   inline virtual const std::string &append_to_string(std::string &buffer) const
      { return label_string(buffer); } //180813 not currently used
      // This wasnt previously and currently isnt used.
      // may want to write the entire section (including entries) in preferred/specified format

   inline virtual bool is_key_string(const std::string &key)       affirmation_; //180820

/*180820  was probably only used for find_cstr now using is_key
   virtual const char  *get_key()                                         const; //030117
   */
/*180821
   inline const std::string   &get_section_label()                        const  //010103
      { return section_label; }
*/
   inline const std::string &get_label()                 const { return label; } //180821


   inline bool         was_encountered()                                  const  //010103
      { return encountered ;}
   bool          was_entry_encountered(const char *entry_name)            const; //050927
   VV_base_entry *set_entry                                                      //111105_980426
      //080819 This should be called set entry because it checks if the entry already exists and updates if
      (const char *key                                                           //030117
      ,const char *value                                                         //030117
      ,bool unexpected_only)                                      modification_;
      ///<  Sets the entry value for the specified key in the current section.
      /// \return either a new entry (if added) or an existing entry (if one already existed).
   /*180101 No longer using alias mechanism to accomodate obsolete parameters
   inline void alias                                                             //011205
      (const char *actual_variable
      ,const char *alias_variable)                                modification_
      { entries.alias(actual_variable,alias_variable); }                         //011209
   */
};
//_1998-02-08___________________________________________________________________
} // namespace CORN
#endif

