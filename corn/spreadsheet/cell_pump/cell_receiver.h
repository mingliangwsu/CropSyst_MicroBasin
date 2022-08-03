#ifndef cell_receiverH
#define cell_receiverH
#include "corn/spreadsheet/cell.h"
namespace CORN {
/** Cell_pump is a spreadsheet reader
It essentially reads data cells and makes them available
**/
//______________________________________________________________________________
class Cell_receiver   // Interface
{
public:
   virtual bool take_numeric (Cell_numeric *cell)                       modification_ = 0; // not const because receiver may modify self with
   virtual bool take_textual (Cell_textual *cell)                       modification_ = 0;
   virtual void recognize_current_sheet_name(const std::string &)       modification_ = 0;
   virtual void recognize_current_sheet_index(nat16 current_sheet_index)modification_ = 0;
};
//______________________________________________________________________________
} // namespace CORN
#endif
