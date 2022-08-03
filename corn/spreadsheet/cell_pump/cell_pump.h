//---------------------------------------------------------------------------
#ifndef cell_pumpH
#define cell_pumpH
#include <corn/spreadsheet/cell.h>

2010-0804 Obsolete used cell_receiver.h

//---------------------------------------------------------------------------
namespace CORN {

///< Cell_pump is a spreadsheet reader
///< It essentially reads data cells and makes them available

class Cell_receiver   // Interface
{

public:

   virtual bool take_numeric (Cell_numeric *cell)                                = 0; // not const because receiver may modify self with
   virtual bool take_textual (Cell_textual *cell)                                = 0;

};

}; // namespace CORN
#endif
