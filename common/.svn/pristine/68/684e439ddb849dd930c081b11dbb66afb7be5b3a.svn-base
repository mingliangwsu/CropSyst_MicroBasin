//______________________________________________________________________________
Weather_generated_on_the_fly_database::Weather_generated_on_the_fly_database(const char *ClimGen_location_filename)
{  generator->generated_weather = this; // Hooks up the storage to this database
};
//______________________________________________________________________________
void Weather_generated_on_the_fly_database::set_today(const CORN::Date &new_today)
{  generator->generate_DOY(new_today.get_DOY());
};
//______________________________________________________________________________
