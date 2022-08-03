#ifndef CORN_DATAGRID_H
#define CORN_DATAGRID_H
/*
   The data grid is used for (often sparse) heterogeneous data in a 2 dimensional data structure
   Similar to a spreadsheet.
*/

namespace CORN {

class Grid
: public Association        // The key of the association is the name of the grid
, public Bidirectional_list // The grid consists of a list of cells
{
public: // Classes stored in a Grid
   class Cell
   : public Item
   {
      nat16 row;
      nat16 col;
   };

   class Col_or_row_label
   : public Association
   {
      std::string /*131115*/ label;
      nat16 row_or_col;
   };

   class Cell_label
   : public Association
   {
      std::string /*131115*/ label;
      nat16 row;
      nat16 col;
   };
protected:
   std::string /*131115*/          label;
   Bidirectional_list   row_labels;          // list of Col_or_row_label for row labels
   Bidirectional_list   col_labels;       // list of Col_or_row_label for column labels
   Bidirectional_list   cell_labels;         // list of Cell_labels

public:

   inline Grid(const char * i_label)
      :Association()
      ,label(i_label)
      ,row_labels()
      ,col_labels()
      ,cell_labels()
      {};

   void clear_row(nat16 row);
   void clear_col(nat16 col);
   void clear_cell(nat16 row, nat16 col);
   void clear_row(const char * row_label);
   void clear_col(const char * col_label);
   void clear_cell(const char * cell_label);

   Cell *get_cell(nat16 row, nat16 col) const ;

   void label_row(const char * label, nat16 row);
   void label_col(const char * label, nat16 col);
   void label_cell(const char * label, nat16 row, nat16 col);

   // use bilist append to add a cell the the grid
};
//______________________________________________________________________________
class Workbook
{
   // A workbook consists of a set of grids
   Bidirectional_list grids;
};
//______________________________________________________________________________
} // namespace CORN
#endif

