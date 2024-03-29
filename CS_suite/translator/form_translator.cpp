//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "form_translator.h"
#include <corn/container/association.h>
#include <fstream>
#include <string>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
HFONT hFont;
//_______________________________________________________________________
#include "corn/application/translation.h"
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
   : TForm(Owner)
   , translations(0)
{
/* Not needed
   hFont = CreateFont
      (12                            // Height
      ,0                             // Width
      ,0                             // escapement
      ,0                             // orientation
      ,FW_NORMAL                     // weight
      ,FALSE                         // italic
      ,FALSE                         // underline
      ,FALSE                         // strikeout
      ,ANSI_CHARSET    // RUSSIAN_CHARSET             //
      ,OUT_DEFAULT_PRECIS            //
      ,CLIP_DEFAULT_PRECIS           //
      ,DEFAULT_QUALITY               //
      ,DEFAULT_PITCH | FF_DONTCARE   //
      ,"MS Sans Serif"  ); //    "XSerif Cyr"         //
*/
}
//---------------------------------------------------------------------------
static const long GWW_HINSTANCE = -6;
static const long GWW_ID = -12;


char enumed_window_text[100] = "\0";

//---------------------------------------------------------------------------
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
   if (hwnd)
   {

      int r = GetWindowText(hwnd, enumed_window_text, 100); //     ' Window text
//      TCHAR szTemp [1024];
//      SendMessage (hwnd, WM_GETTEXT, sizeof(enumed_window_text) / sizeof(TCHAR), (LPARAM)enumed_window_text);
//      strcpy(enumed_window_text,szTemp);
      Form2->output_subtext->Caption = enumed_window_text;
/* For debugging
      if (strcmp(enumed_window_text,"Land use") == 0)
      {
         SetWindowText(hwnd,"�arameter calibration");
         SendMessage(hwnd,WM_SETFONT,(WPARAM)hFont,TRUE); // LPARAM set to TRUE redraws window
      }
*/
//      if (enumed_window_text[0] == 0) return FALSE;
      /*
      if(sText[0]);
      {

         if ( sText.Find (pWndOp->m_sText, 0) != -1)
         {
            *((bool*)lParam) = true;
            return FALSE;
         }
      }
      */
      return TRUE;
   }
   else return false;
};
//---------------------------------------------------------------------------
void __fastcall TForm2::Timer1Timer(TObject *Sender)
{
   tagPOINT pt32 ;
   long ptx ;
   long pty ;
   char sWindowText[1024];  // Dim sWindowText As String * 100
   char sClassName[100]; // Dim sClassName As String * 100
   void */*long*/ hWndOver ;
   long hWndParent ;
   char sParentClassName[100]; // Dim sParentClassName As String * 100
   long wID ;
   long lWindowStyle ;
   long hInstance ;
   char sParentWindowText ; // sParentWindowText As String * 100
   char sModuleFileName ; // sModuleFileName As String * 100
   static    void */*long*/  hWndLast ;
   GetCursorPos(&pt32); //               ' Get cursor position
   ptx = pt32.x;
   pty = pt32.y;
   int r;
   hWndOver = WindowFromPoint(pt32); // WindowFromPointXY(ptx, pty)  ' Get window cursor is over
//   Label3->Caption = enumed_window_text;
   if (hWndOver != hWndLast)             //' If changed update display
   {
      hWndLast = hWndOver; //                   ' Save change
      //          Cls                                      ' Clear the form
      //   Print "Window Handle: &H"; Hex(hWndOver) ' Display window handle

      r = GetWindowText(hWndOver, sWindowText, 100); //     ' Window text
      output_english->Caption = sWindowText;
      //   Print "Window Text: " & Left(sWindowText, r)
      if (!r)
      {  output_english->Caption = "???";
         output_translation->Caption = "???";
      }
      else
      if (translations)
      {  output_english->Caption = sWindowText;
         const Translation *translated = dynamic_cast<const Translation *>
            (translations->find(sWindowText));
         if (translated)
         {
            output_translation->Caption = translated->get_translation();
         } else
            output_translation->Caption = "???";
      };

         bool bResult = false;
         LPARAM lParam = (LPARAM)(&bResult);
         EnumChildWindows (hWndOver, (WNDENUMPROC)EnumChildProc, lParam);

      r = GetClassName(hWndOver, sClassName, 100); //' Window Class
//      Label2->Caption = sClassName;

      //   Print "Window Class Name: "; Left(sClassName, r)

      // lWindowStyle = GetWindowLong(hWndOver, GWL_STYLE)   ' Window Style
      // Print "Window Style: &H"; Hex(lWindowStyle)

      //   ' Get handle of parent window:
      //   hWndParent = GetParent(hWndOver)

      //   ' If there is a parent get more info:
      //   If hWndParent <> 0 Then
      //      ' Get ID of window:
      //      wID = GetWindowWord(hWndOver, GWW_ID)
      //      Print "Window ID Number: &H"; Hex(wID)
      //      Print "Parent Window Handle: &H"; Hex(hWndParent)

      //      ' Get the text of the Parent window:
      //      r = GetWindowText(hWndParent, sParentWindowText, 100)
      //      Print "Parent Window Text: " & Left(sParentWindowText, r)

      //      ' Get the class name of the parent window:
      //      r = GetClassName(hWndParent, sParentClassName, 100)
      //      Print "Parent Window Class Name: "; Left(sParentClassName, r)
      //   Else
      //      ' Update fields when no parent:
      //      Print "Window ID Number: N/A"
      //      Print "Parent Window Handle: N/A"
      //      Print "Parent Window Text : N/A"
      //      Print "Parent Window Class Name: N/A"
      //   End If

      ///   ' Get window instance:
      //   hInstance = GetWindowWord(hWndOver, GWW_HINSTANCE)

      //   ' Get module file name:
      //   r = GetModuleFileName(hInstance, sModuleFileName, 100)
      //   Print "Module: "; Left(sModuleFileName, r)
   };
};
//---------------------------------------------------------------------------
char *language_codes[] =
{ "fr","es","it","ca",0};
void __fastcall TForm2::radiogroup_languageClick(TObject *Sender)
{
   int language_index = radiogroup_language->ItemIndex;
   load_phrases(language_codes[language_index]);

}
//---------------------------------------------------------------------------
void TForm2::load_phrases(const char *language_codes)
{
//   std::String phrases_dir("C:\\dev\\cropsyst\\phrases\\");
//   std::String phrases_file(phrases_dir);
//   phrases_file.append(
   if (translations) delete translations;
//   translations = new CORN::Association_list;
 translations = new CORN::Association_search_tree ;
   load_phrases_file(language_codes,"C:\\temp\\all_cropsyst.phr");

};
//---------------------------------------------------------------------------
void TForm2::load_phrases_file(const char *language_code,const char *filename)
{
   std::ifstream translation_file(filename);
   std::string line;
   Translation *translation = 0;
   while (!translation_file.eof())
   {
      std::getline(translation_file,line);
      if (line.c_str()[0] == '/')
      {
         translation = new Translation;
         translations->append(translation);
      };
      if (translation)
      {  if ((line.c_str()[0] == 'e') &&
             (line.c_str()[1] == 'n'))
         {
            translation->english = line.substr(3);
         } else if
            ((line.c_str()[0] == language_code[0]) &&
             (line.c_str()[1] == language_code[1]))
         {
            translation->translation = line.substr(3);
         };
      };
   };
};
//---------------------------------------------------------------------------
