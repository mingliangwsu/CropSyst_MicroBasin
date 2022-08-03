#ifndef biffH
#define biffH

#include "corn/format/spreadsheet/css_file.h"
#include "corn/format/spreadsheet/biffcode.h"

/*
   Binary file format used in Excel files

   This is can only be used to read/write BIFF2 BIFF3 and BIFF4 formats
   which do not have the concept of workbooks only a single sheet.
   (BIFF4 actually has workbooks but it is sort of a combination)
   This class can really only read BIFF2 correctly.
   It mostly writes only BIFF2 but most applications that can read BIFF files
   will accept BIFF2 as well.

   This class should not be used for reading BIFF3 or later  files
   Because it does not handle RK records (although I can easily add this now).
   It will have problems reading BIFF4 or BIFF5 or greater because it
   doesn't not recognize workbooks (It may work ok if there is a single sheet,
   but cells from all sheets would be read as if there was only one sheet.

   The default write format is set to BIFF4, this is because
   some BIFF readers will refuse to read BIFF2

   This class is still useful for writing simple XLS spreadsheets.
   I am currently working on a more advanced class than can read/write
   BIFF2 to BIFF8.

*/

using namespace CORN;
//______________________________________________________________________________
class Biff_file                   // rename this to BIFF234_File
: public Common_spreadsheet_file
{
 protected:
   BIFF_Format BIFF_format;                                                      //090618
               // 2=BIFF2 3=BIFF3 4=BIFF4 5=BIFF5 8=BIFF8  (There does not appear to be BIFF1,BIFF6,BIFF7 these versions were probably never released)
 protected: // Pane attributes
   bool has_frozen_panes;
   uint16 pane_left_most_column;
   uint16 pane_top_most_row;
   uint16 pane_active;
 public:
   Biff_file(const char *i_filename                                              //000211
      ,std::ios_base::openmode _openmode                                         //111108
      );
   Biff_file
      (const char *i_filename
      ,sint32 first_row  ,sint32 rows                                            //090618
      ,int16 first_col   ,int16 cols
      ,BIFF_Format i_BIFF_format = BIFF4                                         //000307
      );
   virtual ~Biff_file();                                                         //040929
   virtual void initialize();
 public:  // Writing methods
   virtual void write_end_of_document_records();                                 //000307
   virtual void write_BOF_record();
   virtual void write_EOF_record();
   virtual void write_dimensions
      (sint32 first_row  ,sint32 rows         // BIFF8 allows 32bits for row info  earlier version we 16 bit
      ,int16 first_col , int16 cols);
   virtual void write_cell_attributes
      (uint8 attribute_0
      ,uint8 attribute_1
      ,uint8 attribute_2);
   virtual void write_integer_cell
      (int16 at_col
      ,int16 at_row
      ,int16 value );
   virtual void write_number_cell
      (int16 at_col
      ,int16 at_row
      ,float64 value
      ,int8 precision);
   virtual void write_label_cell
      (int16 at_col
      ,int16 at_row
      ,CSS_justifications alignment
      ,const char *value);
#ifdef NYI
   virtual void write_date_cell
      (int16 at_col
      ,int16 at_row
      ,CSS_justifications alignment
      ,CORN::Date date);
#endif
   virtual void write_col_width(int16 from_col, int16 to_col, int16 col_width_in_chars ); //981006
   virtual void freeze_pane(int16 left_most_column , int16 top_most_row );       //981006

            // The following are somewhat unique to BIFF }
   virtual void write_pane();                                                    //981006

   virtual void write_window1                                                    //981006
      (int16 horizontal_pos
      ,int16 vertical_pos
      ,int16 width
      ,int16 height
      ,bool hidden);
   virtual void write_window2                                                    //981006
      (bool display_formulas
      ,bool display_grid
      ,bool display_headers
      ,bool freeze_window_panes
      ,bool display_zero_values
      ,int16 top_visible_row
      ,int16 left_visible_row
      ,bool use_default_gridline_color
      ,int8 grid_R //  { Color RGB }
      ,int8 grid_G
      ,int8 grid_B);
 public:  // reading methods
   virtual bool read_BOF_record();
   /*NOT VIRTUAL*/ int16 read_record();
   virtual Common_spreadsheet_file::Record_type read_next(Common_spreadsheet_file::Record_type filter_type = any_record);
   virtual void read_number_cell(bool expect_header = false) ;
   virtual void read_integer_cell(bool expect_header = false);
   virtual void read_label_cell(bool expect_header = false) ;
   virtual void read_cell_attributes();
 public:  // identification methods
   virtual uint16 get_BOF_code() const;
   virtual uint16 get_EOF_code() const;
};
//______________________________________________________________________________
#endif

