#ifndef labeled_bitmaskH
#define labeled_bitmaskH
namespace CORN {
//______________________________________________________________________________
template <typename T_char>
struct Label_description_bitmask
{  nat32 bitmask;
   const T_char *label;
   const T_char *description;
};
//_2015-08-04___________________________________________________________________
template <typename T_nat, typename T_char>
class Labeled_bitmask_cowl
: public implements_ Labeled_bitmask
{
 protected:
   T_nat &bitmask
   const Label_description_bitmask<T_char> *label_table_bitmask;
      // referenced (must be static)
 public:
   Labeled_bitmask
      (T_nat &_bitmask
      ,const Label_description_bitmask<T_char> *_label_table_bitmask)
      : bitmask(_bitmask)
      , label_table_bitmask(_label_table_bitmask)
      {}
   bool  is(nat32 other_bitmask)                                    affirmation_ { return (nat32)(bitmask == (T_nat)other_bitmask); }
   nat32 has(nat32 other_bitmask)                                   affirmation_ { return (nat32)(bitmask &  (T_nat)other_bitmask); }
   nat32 set(nat32 other_bitmask)                                  modification_ { return (nat32)(bitmask |= (T_nat)other_bitmask); }
   // The set string methods take one or more space delimited labels
   nat32 set_wstring(const std::wstring &labels)                    modification_
      {  return set_wstr(labels.c_str());
      }
   nat32 set_string (const std::string  &labels)                    modification_
      { return set_cstr(labels.c_str());  }
   nat32 set_wstr   (const wchar_t      *labels)                    modification_
      {
         T_char token[255]; nat8 t = 0;
         for (int l = 0; l < labels.length(); l++)
         {
            token[t] = labels_str[l];
            if (token[t] == 0)
            {  set_token(token);
               t = 0;
            } else t++;
         }
         return (nat32)bitmask;
      }
   nat32 set_cstr   (const char         *labels)                    modification_
      {
         T_char token[255]; nat8 t = 0;
         for (int l = 0; l < labels.length(); l++)
         {
            token[t] = labels_str[l];
            if (token[t] == 0)
            {  set_token(token);
               t = 0;
            } else t++;
         }
         return (nat32)bitmask;
      }
   // The following compose space labels
   virtual const std::wstring &append_to_wstring(std::wstring &buffer)     const
      {
         for (nat32 b = 0; label_table_bitmask[b] && !bit_set; b++)
            if (bitmask == label_table_bitmask[b].bitmask)
               for (nat8 l = 0; label_table_bitmask[b].label[l]; l++)
                  buffer += label_table_bitmask[b].label[l];
         return buffer;
      }
   virtual const std::string &append_to_string(std::string &buffer)        const
      {
         for (nat32 b = 0; label_table_bitmask[b] && !bit_set; b++)
            if (bitmask == label_table_bitmask[b].bitmask)
               for (nat8 l = 0; label_table_bitmask[b].label[l]; l++)
                  buffer += label_table_bitmask[b].label[l];
         return buffer;
      }
 private:
   nat32 set_token(const T_char *token)                            modification_
      {  bool bit_set = false;
         for (nat32 b = 0; label_table_bitmask[b] && !bit_set; b++)
         {  bool token_matches = true;
            for (nat8 t = 0; token[t] && token_matches; t++)
            {
               if ((token[t] == 0) && (label_table_bitmask[b].label[t] == 0))
               {
                  bitmask |= label_table_bitmask[b].bitmask;
                  bit_set = true;
               }
            }
         }
         return (nat32)bitmask;
      }
};
//_2015-08-04___________________________________________________________________
//______________________________________________________________________________
} // namespace CORN
#endif
