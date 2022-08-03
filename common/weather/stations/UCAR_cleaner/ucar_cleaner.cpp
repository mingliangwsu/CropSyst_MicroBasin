#include <corn/std/std_fstream.h>
#include <common/weather/stations/ucar_stations.h>
#include <common/simulation/paths.h>
//______________________________________________________________________________
void main()
{
   setup_simulation_paths(0,0,0,"");
   CORN::Association_list locations;
   cout << "loading UCAR stations" << endl;
   load_UCAR_stations(locations);

   CORN::Ustring last_location_unique_ID = "";

   CORN::Association_list clean_locations;
   for (UCAR_location *popped = (UCAR_location *)locations.pop_first()
       ;popped
       ;popped = (UCAR_location *)locations.pop_first())
   {
      if (popped->unique_ID == last_location_unique_ID)
         delete popped;
      else
      {  clean_locations.append(popped);
         last_location_unique_ID.assign(popped->unique_ID);
      };
   };
   cout << "writing abridged stations:" << endl;
   ofstream cleaned_locations_file("UCAR ds512.0 stationlib abridged.txt");
   clean_locations.write(cleaned_locations_file);
//   FOR_EACH_IN(location,UCAR_location,clean_locations,each_loc)
//   {
//      cout << location.unique_ID << '\r';
//      location->write(cleaned_locations_file);
//   } FOR_EACH_END(each_loc);

   cout << endl << "done" << endl;
   setdown_simulation_paths();
};
//______________________________________________________________________________
