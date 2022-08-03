#ifndef CS_parameterH
#define CS_parameterH

#include "common/physics/property.h"
#include "corn/quality.h"
namespace CS
{
//______________________________________________________________________________
interface_ Parameter
: public extends_interface_ Physical::Property_interface
, public extends_interface_ CORN::Quality
{
   virtual const CORN::Quality &update()                       rectification_=0;
   virtual CORN::Quality_code invalidate(bool absolutely=true) rectification_=0;
};
//______________________________________________________________________________
} //namespace CS

#endif
