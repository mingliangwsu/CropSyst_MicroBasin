//---------------------------------------------------------------------------

#ifndef form_sampleH
#define form_sampleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AdvGridExcel.hpp"
#include "AdvGridWorkbook.hpp"
#include "AdvGrid.hpp"
#include "BaseGrid.hpp"
#include <Grids.hpp>
//---------------------------------------------------------------------------
class ED_tabular_file_format;
//---------------------------------------------------------------------------
class Tsample_form : public TForm
{
__published:	// IDE-managed Components
   TAdvGridExcelIO *AdvGridExcelIO_sample;
   TAdvGridWorkbook *AdvGridWorkbook_sample;
   TAdvStringGrid *string_grid_for_text;
   TAdvStringGrid *workbookgrid_for_excel;
private:	// User declarations
   ED_tabular_file_format *format;
   AnsiString           sample_file_name;
public:		// User declarations
   __fastcall Tsample_form(TComponent* Owner);

   void bind_to(ED_tabular_file_format *_format,const char *_sample_file_name);
   void update_sample_grid();
   bool update_sample_text_file_grid();
};
//---------------------------------------------------------------------------
extern PACKAGE Tsample_form *sample_form;
//---------------------------------------------------------------------------
#endif
