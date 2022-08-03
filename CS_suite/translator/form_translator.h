//---------------------------------------------------------------------------

#ifndef form_translatorH
#define form_translatorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include <corn/container/search_tree.h>
//#include <corn/container/association.h>
class TForm2 : public TForm
{
__published:	// IDE-managed Components
   TLabel *output_english;
   TTimer *Timer1;
   TLabel *Label4;
   TLabel *output_translation;
   TRadioGroup *radiogroup_language;
   TLabel *output_subtext;
   void __fastcall Timer1Timer(TObject *Sender);
   void __fastcall radiogroup_languageClick(TObject *Sender);
private:	// User declarations
   CORN::Association_search_tree  *translations;
//   CORN::Association_list *translations;
public:		// User declarations
   __fastcall TForm2(TComponent* Owner);
private:
   void load_phrases(const char *language_codes);
   void load_phrases_file(const char *language_code,const char *filename);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
