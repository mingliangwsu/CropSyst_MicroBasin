#ifndef crop_canopy_biomass_GAIH
#define crop_canopy_biomass_GAIH

#error obsolete

#include "options.h"
#include "corn/container/bilist.h"
#include "crop/crop_types.h"

class Canopy_portion;
class Residue_decomposition_parameters;
class Organic_biomatter_V4_4;
class Residues_interface;
class Crop_nitrogen_interface;
class Crop_biomass;

// NYI I need to make an interface for Canopy_biomass_GAI
//______________________________________________________________________________
class Canopy_biomass_GAI
{
   class Canopy              // Canopy_accumulation
   : public CORN::Bidirectional_list
   {
    public:
      mutable Canopy_portion  *accum_today;     // Accumulated values todate.
    private:
      #if (CS_VERSION==4)
      Senesced_biomass_fate   senesced_biomass_fate_param;                       //060817
      #else
      Abscission              abscission;                                        //110911
      #endif
      bool                    from_previous_season;                              //060911
    public:
      Canopy(
            #if (CS_VERSION==4)
            Senesced_biomass_fate  _senesced_biomass_fate_param
            #else
            Abscission             _abscission                                   //110911
            #endif
            , bool _from_previous_season)
         : CORN::Bidirectional_list()
         , accum_today(0)
         #if (CS_VERSION==4)
         , senesced_biomass_fate_param(_senesced_biomass_fate_param)
         #else
         , abscission(_abscission)
         #endif
         , from_previous_season(_from_previous_season)
         {};
      virtual  ~Canopy();
      void invalidate()                                                 mutates_;
      float64 update()                                                  mutates_;
      // Returns the biomass sloughed
      float64 remove_biomass                                                  //040623
         (float64 GAI_remaining_available
         ,float64 biomass_to_remove
         ,float64 retain_vital_GAI        // biomass won't be removed if it takes the GAI below this level //060323
         ,bool remove_newest_first
         ,bool reserve_todays_history )                            modification_;
   };
   //_2906-09-11____________________________________________________
 private:
   Canopy_portion *untouchable_portion;                                          //071126
      // This is the initial green area index. It does not age or die.
      // We must keep it as long as the plant is alive.
      // After initial growth, the GAI value increases to the regrowth_GAI value
   mutable Canopy canopy_vital;                                                  //060911
   mutable Canopy canopy_effete;                                                 //060911
 private:
   mutable bool                        GAI_has_died_off;    uint32 resets;       //080515
   #if (CS_VERSION==4)
   Senesced_biomass_fate               senesced_biomass_fate_param;              //060817
   #else
   Abscission                          abscission;                               //110911
   #endif
   Residues_interface                 *residues;  // may be 0 if no residue submodel   //060816
   Crop_nitrogen_interface            *nitrogen; // may be 0 if not running nitrogen)
   Residue_decomposition_parameters   &residue_decomposition_params;
   float64                             regrowth_GAI;                             //080222
   bool                                is_continuous_grass;                      //080515
 public: // structors
   Canopy_biomass_GAI(
      #if (CS_VERSION==4)
       Senesced_biomass_fate               _senesced_biomass_fate_param          //060817
      #else
       Abscission                          _abscission                            //110911
      #endif
      ,float64                             _regrowth_GAI                         //080222
      ,Residue_decomposition_parameters   &_residue_decomposition_params         //060816
      ,Residues_interface                 *_residues                             //060816
      ,Crop_nitrogen_interface            *_nitrogen                             //060816
      ,bool                                _is_continuous_grass);                //080515
   virtual ~Canopy_biomass_GAI();
 public: // Accessors
   inline bool     is_valid()                                       affirmation_;
   float64 get_GAI(uint8 include_GAI)                                      const;
   float64 get_LAI()                                                       const;//060824
   float64 get_biomass_produced(uint8 include_biomass)                     const;//060601
      // All the biomass ever produced  (Warning, this is not including removed biomass!!! probably should rename this to get_biomass_vital_effette)
   float64 get_biomass_current(uint8 include_biomass)                      const;//060601
      // The current biomass (Some may have decomposed)
   float64 get_GAI_related_biomass()                                       const;
#ifdef CO2_CHANGE
CO2            float64 get_GAI_at_baseline_ppm()                           const;
CO2            float64 get_GAI_related_biomass_at_baseline_ppm()           const;
#endif
   float64 get_live_green_biomass(bool include_vital,bool include_effete)  const;
   float64 get_live_and_or_dead_biomass(bool include_vital,bool include_effete,bool include_dead) const; //060907
      // Returns the sum of the portion biomass that are not dead.
 public:
   void terminate();                                                             //080222
      // Makes the untouchable portion available for removal with biomass fate.
   bool take_portion(Canopy_portion  *todays_portion,bool initial_restart_vital,bool protect_it = false);
      // Used to add the portion of GAI/biomass produced today
   void respond_to_clipping()                                           modification_/*111011 mutation_*/;//080515
   void restart()                                                       mutates_;//080515
   void invalidate()                                                    mutates_;
   void age_by(float64 daily_age_deg_day,float64 leaf_duration_deg_day_f32);
   float64 remove_biomass
      (float64 biomass_to_remove
      ,float64 retain_GAI        // biomass won't be removed if it takes the GAI below this level. Use 0.0 for no limitation
      ,bool remove_newest_first
      ,bool reserve_todays_portion,Crop_biomass &removed_biomass);               //070412
         // Return about of biomass removed
   float64 remove_all_biomass
      (Crop_biomass &removed_biomass)                              modification_;//070627
      // This removes all canopy biomass from the plant (I.e. in the case of termination)
      // Returnsabout of biomass removed
   void die_back(float64 fraction_to_die);
   void dump_ages(std::ofstream &tostream);                                   //070705
   bool end_season(bool apply_dormancy)                            modification_;//080401
 public:
   bool update()                                                        mutates_;
};
//______________________________________________________________________________
#endif

