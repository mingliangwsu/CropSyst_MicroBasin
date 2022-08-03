//______________________________________________________________________________
float64 calc_source_limited_harvest_index
(float64 fraction_biomass_produced_during_yield_formation                        //161010
, float64 attainable_harvest_index                                               //120118  was sink_strength_based_harvest_index
, float64 translocation_fract_max)
{
   //attainable_harvest_index is on the order of 0.4
   //translocation_fract_max  is on the order of 0.2;
   if (attainable_harvest_index < 0.0001)
      return attainable_harvest_index;
      // Added by RLN because exp blows up when to small.
   float64 harvest_index = attainable_harvest_index;                             //130503
   if (attainable_harvest_index > translocation_fract_max)                       //130503
   {  float64 translocation_fraction_min = translocation_fract_max / 3.0;
      float64 max_fraction_biomass_produced_during_yield_formation =             //120118 was constant 0.6
         // THIS IS  Biomass fraction needed during grain filling so as to match expected unstressed HI at minimum translocation
         (attainable_harvest_index - translocation_fraction_min)
        /(1.0 - translocation_fraction_min);

      // Determine HI asymptote and decay coefficient
      float64 decay_coeff_max = (1.0 - translocation_fract_max)
         / (attainable_harvest_index - translocation_fract_max);
      float64 decay_coef = decay_coeff_max; /* initial value for iteration */
      #define fraction_near_zero  0.00001
      float64 HI_at_fraction_near_zero = fraction_near_zero +
         (1.0 - fraction_near_zero) * translocation_fract_max;
      float64 harvest_index_asymptote = 0.0;
      float64 error = 0.0;
      bool keep_searching = true;
      nat32 iters = 0;                                                           //160808

         // normally there will be less than 10 iterations but there could be
         // pathologic cases.
      do
      {
          harvest_index_asymptote = (attainable_harvest_index - translocation_fract_max
              * exp(-decay_coef * max_fraction_biomass_produced_during_yield_formation))
            / (1.0 - exp(-decay_coef * max_fraction_biomass_produced_during_yield_formation));
          float64 new_decay_coef =
             -log((harvest_index_asymptote - HI_at_fraction_near_zero)
                   / (harvest_index_asymptote - translocation_fract_max))
                 / fraction_near_zero;
          error = fabs(new_decay_coef - decay_coef);
          iters ++;                                                              //160808
          decay_coef = new_decay_coef;
          keep_searching
            = !((error < 0.0001) || (decay_coef < (0.1 * decay_coeff_max)));     //160808
      } while ((iters < 100) && keep_searching);                                 //160808
      //Calculate harvest index
      if (iters < 100)                                                           //160808
         harvest_index
         = harvest_index_asymptote
           - (harvest_index_asymptote - translocation_fract_max)
             * exp(-decay_coef * fraction_biomass_produced_during_yield_formation);
      } //  else  harvest_index is simply  attainable_harvest_index
   return harvest_index;
}                                                                                //End Function
//_2012-01-18___________________________________________________________________

