#ifndef labeled_enumH
#define labeled_enumH

#ifndef primitiveH
#  include "corn/primitive.h"
#endif
#include "corn/const.h"

class VV_enum_entry; // for friendship
//namespace CORN {
//______________________________________________________________________________
struct Label_description  //150904  Rename this to Label_description_enum
{
   const char *label;
   const char *description;
};
//_2005-09-29___________________________________________________________________
class Labeled_enum
{
friend class VV_enum_entry;
protected:
public: // temporarily public for debugging
   // Label tables may either be a simple array of strings specifying the labels in relative sequence.
   // Or an array of label and descriptions Label_description.
   // On or the other modes is used.
   const char **simple_label_table;
   Label_description *descriptive_label_table;                                   //050929
public:
   Labeled_enum();                                                               //050929
   Labeled_enum(const char **_label_table);
   // Constructor for simple_label_table_mode
   Labeled_enum(Label_description *_descriptive_label_table );                   //050929
      //
   // Constructor for descriptive label_table mode.
   virtual const char *get_label()                                        const;
   // Returns the character string label associated with the
   // current enumeration value.
   // This must be overridden to provide the label for the current enumeration
   virtual int32 set_label(const char *_label);
   // This must be overridden to set the enumeration value for the
   // specified label.
   virtual int32 get_int32()                                          const = 0;
   // This will return (casting) the current value to 32bit integer.
   // This must be overridden derived classes
   // RLN: Note if I had my druthers, enums would ALWAYS BE unsigned 32bits
   // But not all compiler vendors do this
   // Also using int32 will keep this class compatible with C# which damnably used signed 32bit integers ack!
   virtual int32 set_int32(int32 _value)                                   = 0 ;
   // This sets the value (casting)
   // This must be overridden derived classes
   virtual bool is_label(const char *_label)                       affirmation_;
   // return true if the label is in the label table
   // (used by CropSyst Crop parameter editor.
   virtual const char *get_description()                                  const; //050929
   // Returns the character string description associated with the current
   // enumeration value.
   // If it is a simple label table, the label is simply returned.
   inline virtual bool is_descriptive()                             affirmation_
      { return descriptive_label_table != 0; } //050929
   // Returns true if this is a descriptive enumeration
   virtual nat16 get_max_label_length()                                   const; //050929
   // Returns the longest label length.
   // This is used to determine the field size for Data_records enumeration attributes.
};
//______________________________________________________________________________

#define DECLARE_LABELED_ENUM(labeled_enum_class,enumeration,i_label_table)      \
class labeled_enum_class                                                        \
: public Labeled_enum                                                           \
{                                                                               \
   enumeration value;                                                           \
public:                                                                         \
   inline labeled_enum_class(enumeration default_value = (enumeration)0)        \
      :  Labeled_enum((const char **)i_label_table)                             \
      , value(default_value)                                                    \
      {}                                                                        \
   inline labeled_enum_class(const char *default_value_label)                   \
      :  Labeled_enum((const char **)i_label_table)                             \
      , value((enumeration)0)                                                   \
      { set_label(default_value_label);}                                        \
   inline virtual ~labeled_enum_class() {}                                      \
   inline virtual int32 get_int32()       const {return (int32)value; }         \
   inline enumeration get()               const {return value; }                \
   inline virtual int32 set_int32(int32 i_value){value = (enumeration)i_value; return i_value;} \
   inline enumeration set(enumeration i_value)  {value = i_value; return i_value;}              \
   inline bool is(enumeration _value)     const { return _value == value; }     \
};
//______________________________________________________________________________
#define DECLARE_DESCRIPTIVE_LABELED_ENUM(labeled_enum_class,enumeration,_descriptive_label_table) \
class labeled_enum_class                                                        \
: public Labeled_enum                                                           \
{                                                                               \
   enumeration value;                                                           \
public:                                                                         \
   inline labeled_enum_class(enumeration default_value = (enumeration)0)        \
      :  Labeled_enum((Label_description *)_descriptive_label_table)            \
      , value(default_value)                                                    \
      {}                                                                        \
   inline labeled_enum_class(const char *default_value_label)                   \
      :  Labeled_enum((Label_description *)_descriptive_label_table)            \
      , value((enumeration)0)                                                   \
      { set_label(default_value_label);}                                        \
   inline virtual ~labeled_enum_class() {}                                      \
   inline virtual int32 get_int32()       const {return (int32)value; }         \
   inline enumeration get()               const {return value; }                \
   inline virtual int32 set_int32(int32 _value){value = (enumeration)_value; return _value;}  \
   inline enumeration set(enumeration _value)  {value = _value; return _value;}               \
   inline bool is(enumeration _value)     const { return _value == value; }     \
};
//______________________________________________________________________________
#define DECLARE_LABELED_ENUM_COWL(labeled_enum_class,enumeration,_label_table) \
class labeled_enum_class                                                        \
: public Labeled_enum                                                           \
{                                                                               \
   enumeration &value;                                                          \
public:                                                                         \
   inline labeled_enum_class(enumeration &_value,enumeration default_value = (enumeration)0) \
      :  Labeled_enum((const char **)_label_table)                             \
      , value(_value)                                                           \
      { value = default_value; }                                                \
   inline labeled_enum_class(enumeration &_value,const char *default_value_label)\
      :  Labeled_enum((const char **)_label_table)                             \
      , value(_value)                                                           \
      {  value = (enumeration)0;                                                \
         set_label(default_value_label);}                                       \
   inline virtual ~labeled_enum_class() {}                                      \
   inline virtual int32 get_int32()       const {return (int32)value; }         \
   inline enumeration get()               const {return value; }                \
   inline virtual int32 set_int32(int32 _value){value = (enumeration)_value; return _value;}   \
   inline enumeration set(enumeration _value)  {value = _value; return _value;};               \
   inline bool is(enumeration _value)     const { return _value == value; };    \
};
//______________________________________________________________________________
#define DECLARE_DESCRIPTIVE_LABELED_ENUM_COWL(labeled_enum_class,enumeration,_descriptive_label_table) \
class labeled_enum_class                                                        \
: public Labeled_enum                                                           \
{                                                                               \
   enumeration &value;                                                          \
public:                                                                         \
   inline labeled_enum_class(enumeration &_value,enumeration default_value = (enumeration)0)        \
      :  Labeled_enum((Label_description *)_descriptive_label_table)            \
      , value(_value)                                                           \
      { value = default_value; }                                                \
   inline labeled_enum_class(enumeration &_value,const char *default_value_label)\
      :  Labeled_enum((Label_description *)_descriptive_label_table)            \
      , value(_value)                                                           \
      { value = (enumeration)0;                                                 \
        set_label(default_value_label);}                                        \
   inline virtual ~labeled_enum_class() {}                                      \
   inline virtual int32 get_int32()       const {return (int32)value; }         \
   inline enumeration get()               const {return value; }                \
   inline virtual int32 set_int32(int32 _value){value = (enumeration)_value; return _value;}  \
   inline enumeration set(enumeration _value)  {value = _value; return _value;}               \
   inline bool is(enumeration _value)     const { return _value == value; }     \
};
//______________________________________________________________________________
//} // namespace CORN
#endif
//labeled_enum

