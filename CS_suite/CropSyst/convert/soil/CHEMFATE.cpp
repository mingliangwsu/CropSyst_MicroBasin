
Not yet reimplemented.

   RLIB_filename dbs_filename(input_filename);
   dbs_filename.set_ext(".DBS");
   RLIB_filename dbh_filename(input_filename);
   dbh_filename.set_ext(".DBH");

   dBase_file dbs_file(dbs_filename.get());
   dBase_file dbh_file(dbh_filename.get());

060601 If I decide to implement this at some time again,
it should be a subclass and used dBase_datasource


   if (argc < 2)
   {
     cout << "This program converts CHEMFATE (Cooperative extension's version of CMLS)" << endl
          << "soil files to CropSyst soil files."<< endl << endl
          << "The program requires 1 argument:  The name of the CHEMFATE soil .DBS file." << endl
          << "The program produces CropSyst .SIL files" << endl;
   };

   boolean soil_record_exists;

   soil_file soil("deleteme.sil");

   for (soil_record_exists = dbs_file.goto_BOF()       ;soil_record_exists       ;soil_record_exists = dbs_file.goto_next())
   {  int code_buf;
      float last_depth = 0;

      int layer;
      for (layer = 1; layer <= MAX_soil_horizons; layer++)
      {
         soil.layer_thickness[layer] = 0.0;
         soil.bypass_coef[layer] = 0.0;
         soil.bulk_density[layer] = 0.0;
         soil.perm_wilt_point[layer] = 0.0;
         soil.field_capacity[layer] = 0.0;
      };


      layer = 1;

      char soil_code_buf[20];
      char soil_filename_buf[20];
      soil.filename.set(remove_special_chars(dbs_file.get_string("ID",soil_code_buf),soil_filename_buf));
      soil.filename.set_ext(".SIL");

      {
       char name_buf[80];
       soil.description.assign(dbs_file.get_string("NAME",name_buf));
       cout << endl << name_buf << endl;
      }
      {
       char texture_buf[80];
       dbs_file.get_string("TEXTURE",texture_buf);
       if (strncmp(texture_buf,"SILT LOAM",9) == 0)
       {
         soil.percent_sand = 20;
         soil.percent_clay = 15;
         soil.percent_silt = 65;
       }
       else if (strncmp(texture_buf,"SAND",4) == 0)
       { soil.percent_sand = 90;
         soil.percent_clay = 10;
         soil.percent_silt = 0;
       }
       else if (strncmp(texture_buf,"SANDY LOAM",10) == 0)
       { soil.percent_sand = 65;
         soil.percent_clay = 15;
         soil.percent_silt = 20;
       }
       else if (strncmp(texture_buf,"CLAY LOAM",9) == 0)
       { soil.percent_sand = 30;
         soil.percent_clay = 35;
         soil.percent_silt = 35;
       }
       else if (strncmp(texture_buf,"LOAM",4) == 0)
       {
         soil.percent_sand = 40;
         soil.percent_clay = 20;
         soil.percent_silt = 40;
       }
       else
         cout << "Texture:" << texture_buf << " not recognized" << endl;
       // Additional textures should be added here!
      };
      int dbh_code_buf;
      int dbs_code_buf = dbs_file.get_integer("CODE",dbs_code_buf);
      while (dbh_file.get_integer("CODE",dbh_code_buf) == dbs_code_buf)
      {  float buf;
         float depth = dbh_file.get_float("DEPTH",buf);
         float thickness = depth - last_depth;

         if (layer <= MAX_soil_horizons)
         {
          if ((layer == 1) && (thickness > 0.05))
          {
            soil.layer_thickness[1] = 0.05;
            soil.layer_thickness[2] = thickness - 0.05;
            soil.bypass_coef[1] = 0.0;
            soil.bulk_density[1] = dbh_file.get_float("P",buf);
            soil.perm_wilt_point[1] = dbh_file.get_float("VWCPWP",buf) /100.0;
            soil.field_capacity[1] = dbh_file.get_float("VWCFC",buf) / 100.0;
            layer = 2;
          }
          else
            soil.layer_thickness[layer] = thickness;

          cout << layer<< ' ';
          soil.bypass_coef[layer] = 0.0;
          soil.bulk_density[layer] = dbh_file.get_float("P",buf);
          soil.perm_wilt_point[layer] = dbh_file.get_float("VWCPWP",buf) / 100.0;  // mPa -> m3/m3
          soil.field_capacity[layer] = dbh_file.get_float("VWCFC",buf) / 100.0;    // mPa -> m3/m3

          soil.number_horizons = layer;
         };
         last_depth = depth;
         layer += 1;
         dbh_file.goto_next();
      };

      soil.write();
   };
