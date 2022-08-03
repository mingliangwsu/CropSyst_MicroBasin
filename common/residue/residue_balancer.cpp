#include <common/residue/residue_balancer.h>
#ifdef DETAILED_BALANCES
//______________________________________________________________________________
Residue_balancer *residue_mass_balance[OM_POSITION_COUNT] = {0,0,0,0};
   ///< residue_mass_balance are instanciationed in Land_unit_simulation_VX::initialize()
   /// These are given to the simulation engine which will delete them.
//_2009-04-07___________________________________________________________________
Residue_balancer::Residue_balancer(Organic_matter_position _position)
: Organic_biomatter_balancer()
, position(_position) // Setup with autoaggregate initialization
, incorporated (0)
, flattened    (0)
//120120 , current      (0)                                                               //090408
{}
//______________________________________________________________________________
bool Residue_balancer_surface_stubble_or_attached::end_day()  // returns the balance which should be 0.0 (approximately)
{  daily.minuses.set(3,incorporated);    incorporated = 0;
   // Normally there will probably be no tillage operations applied to residue attached to plant because tillage/residue operations will likely kill the plant (an exception maybe residue burning like sugar cane where the plant is not killed)
   daily.minuses.set(4,flattened);       flattened    = 0;
   return Residue_balancer::end_day();
}
//_2007-02-20___________________________________________________________________
bool Residue_balancer_surface_flat::end_day()  // returns the balance which should be 0.0 (approximately)
{  daily.minuses.set(3,incorporated);   incorporated = 0;
   daily.pluses .set(3,flattened);      flattened    = 0;
   return Residue_balancer::end_day();
}
//_2007-02-20___________________________________________________________________
bool Residue_balancer_subsurface::end_day()  // returns the balance which should be 0.0 (approximately)
{  daily.pluses .set(3,incorporated);
   incorporated = 0;
   flattened    = 0;
   return Residue_balancer::end_day();
//150123    return Residue_balancer::end_day(balance_file_daily);
}
//_2007-02-20___________________________________________________________________
float32 Residue_balancer::get_final()
{  return current; // Organic_biomatter_balancer::get_final();
}
//_2007-02-20___________________________________________________________________
#ifdef NYN
bool Residue_balancer_surface_stubble_or_attached::get_caption_plus
(nat32 index ,std::string &caption)                                        const
{  bool set = true;
   caption.append(organic_matter_position_label_table[position]);
   switch(index)
   {  default : set = Organic_biomatter_balancer::get_caption_plus(index,caption);
      break;
   }
   return set;
}
//_2009-04-09___________________________________________________________________
#endif
bool Residue_balancer_surface_flat::get_caption_plus
(nat32 index ,std::string &caption)                                        const
{  bool set = true;
   caption.append(organic_matter_position_label_table[position]);
   caption.append(" ");
   switch(index)
   {  case 3 :   caption.append ("flattened");  break;
      default : set = Organic_biomatter_balancer::get_caption_plus(index,caption);
      break;
   }
   return set;
}
//_2009-04-09___________________________________________________________________
bool Residue_balancer_subsurface::get_caption_plus
(nat32 index ,std::string &caption)                                        const
{  bool set = true;
   caption.append(organic_matter_position_label_table[position]);
   caption.append(" ");
   switch(index)
   {  case 3 : caption.append ("incorporated");                           break;
      default : set = Organic_biomatter_balancer::get_caption_plus(index,caption);  break;
   }
   return set;
}
//_2009-04-09___________________________________________________________________
bool Residue_balancer_surface_stubble_or_attached::get_caption_minus
(nat32 index,std::string &caption)                                         const
{  bool set = true;
   caption.append(organic_matter_position_label_table[position]);
   caption.append(" ");
   switch(index)
   {  case  3 :   caption.append("incorporated");                         break;
      case  4 :   caption.append("flattened");                            break;
      default : set = Organic_biomatter_balancer::get_caption_minus(index,caption); break;
   }
   return set;
}
//_2009-04-09___________________________________________________________________
bool Residue_balancer_surface_flat::get_caption_minus
(nat32 index,std::string &caption)                                         const
{  bool set = true;
   caption.append(organic_matter_position_label_table[position]);
   caption.append(" ");
   switch(index)
   {  case  3 : caption.append("incorporated");                                    break;
      default : set = Organic_biomatter_balancer::get_caption_minus(index,caption); break;
   }
   return set;
}
//_2009-04-09___________________________________________________________________
#ifdef NYN
bool Residue_balancer_subsurface::get_caption_minus
(nat32 index,std::string &caption)                                         const
{  bool set = true;
   caption.append(organic_matter_position_label_table[position]);
   caption.append(" ");
   switch(index)
   {
      default : set = Organic_biomatter_balancer::get_caption_minus(index,caption);
      break;
   }
   return set;
}
//_2009-04-09___________________________________________________________________
#endif
#endif
