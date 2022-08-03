#include "worksheet_BIFF2.h"
//___________________________________________________________________________
BIFF2_rec_INTEGER &Excel_worksheet::Row_set::provide_INTEGER_record(uint16 col) provides_
{  BIFF_record *rec =  dynamic_cast<BIFF_record *>(cell_records.find(col));
   if (!rec)
      rec =
#ifdef USE_XF
      (format >= BIFF5)      need to make an abstract class that can get and set integers (and floats) from which to derive BIFFx_rec_RK
      ? (BIFF_rec_numeric *)(new BIFFx_rec_RK(col,row_record->get_row(),0.0))
#endif
        dynamic_cast<BIFF_record *>(new BIFF2_rec_INTEGER(col,row_record->get_row(),BIFF_ATTR0_DEFAULT,BIFF_ATTR1_DEFAULT,BIFF_ATTR2_ALIGN_RIGHT,0.0));
   Binary_record_index_node_dynamic *rec_node = new Binary_record_index_node_dynamic(rec);
   take_record_node(rec_node);
   return *rec;
};
//______________________________________________________________________________
BIFF_rec_LABEL &Excel_worksheet::Row_set::provide_LABEL_record(uint16 col) provides_
{  BIFF_rec_LABEL *rec =
#ifdef USE_XF
      (format >= BIFF4)
      ? (BIFF_rec_LABEL *)(new BIFF4_rec_LABEL(col,row,xxxx,""))
#endif
       (BIFF_rec_LABEL *)(new BIFF_rec_LABEL(col,row_record->get_row(),BIFF_ATTR0_DEFAULT,BIFF_ATTR1_DEFAULT,BIFF_ATTR2_ALIGN_LEFT,   ""));
   Binary_record_index_node_dynamic *rec_node = new Binary_record_index_node_dynamic(rec);
   take_record_node(rec_node);
   return *rec;
};
//______________________________________________________________________________
BIFF_rec_NUMBER &Excel_worksheet::Row_set::provide_NUMBER_record(uint16 col) provides_
{  BIFF_rec_NUMBER *rec =
#ifdef USE_XF
      (format >= BIFF5)
      ? (BIFF_cell_record *)(new BIFFx_rec_RK(col,row_record->get_row(),0.0)) :
#endif
       (BIFF_rec_NUMBER *)(new BIFF_rec_NUMBER(col,row_record->get_row(),BIFF_ATTR0_DEFAULT,BIFF_ATTR1_DEFAULT,BIFF_ATTR2_ALIGN_RIGHT,0.0));
   Binary_record_index_node_dynamic *rec_node = new Binary_record_index_node_dynamic(rec);
   take_record_node(rec_node);
};
//______________________________________________________________________________

