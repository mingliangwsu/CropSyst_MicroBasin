#ifndef statsH
#define statsH
#ifndef constH
#  include "corn/const.h"
#endif
#  include "corn/dynamic_array/dynamic_array_T.h"
#ifndef labeled_enumH
# include "corn/labeled_enum.h"
#endif

#include <limits>

#include "corn/math/statistical/sample_cumulative_T.h"

namespace CORN {
//______________________________________________________________________________
class Statistical_baseX                // Rename this to Statistics_descriptive_base
{protected:
   mutable nat16  status;
   mutable float32 minimum;                                                      //020701
   mutable float32 maximum;                                                      //020701
   mutable float32 mean;               // actually arithmetic mean
   mutable float32 summation;
   mutable float32 standard_deviation; // actually sample_standard_deviation
   mutable float32 coefficient_of_variation;
   mutable float32 sum_of_squares;  // moved from Statistical_data_set           //020701
 public: // current is public because CropSyst daily UED record needs to access  //040919
   mutable float32 current;			// This is the more recent appended value.   //040812
 public:
   Statistical_baseX();
   virtual bool reset();                                                         //15025
   inline nat16 status_set(nat16 flags_to_set)                         provision_{ status |= flags_to_set; return status; }
   inline nat16 status_get(nat16 flags_to_get)                             const { return status & flags_to_get; }
   inline nat16 status_clear(nat16 flags_to_clear)                         const { status &= (nat16)(~flags_to_clear); return status; }
   inline void status_clear_all()                                   modification_{ status = 0; }

   void append_dataset                                                           //091217
      (const Dynamic_array<float32> &data_append
      ,nat32 append_count =
#ifdef __BCPLUSPLUS__
         std::numeric_limits<nat32>::max()
#else
         0xFFFFFFFF
#endif
		);       // By default append everything       ULONG_MAX

   inline virtual float32 append(float32 value)                   modification_; //040812
   inline virtual float32 get_current()                const { return current; } //040812
   inline virtual float32 get_min()                    const { return minimum; } //050107
   inline virtual float32 get_max()                    const { return maximum; } //050107
   inline virtual float32 get_sum()                  const { return summation; } //050507
   inline virtual float32 sum()                            { return summation; } //050107       // deprecated
   inline virtual float32 get_mean()                      const { return mean; } //050105       // should be const but need to check decendents
   inline virtual float32 get_sum_of_squares()   const { return sum_of_squares;} //050507
   virtual float32 get_standard_deviation()                           const = 0;
   virtual float32 get_coefficient_of_variation()                provision_ = 0; //091002
   virtual float32 get_median()                                  provision_ = 0; //010406
      // Only available with statistical datasets

   virtual nat32  get_count()                                         const = 0; //010604
 public:  // These reference accessor are intened to allow the
          // statistical tallies to be hooked up to the user interface.
   inline float32 *bind_from_mean()               { return &mean; }
   inline float32 *bind_from_summation()          { return &summation; }
   inline float32 *bind_from_standard_deviation() { return &standard_deviation;}
   inline float32 *bind_from_sum_of_squares()     { return &sum_of_squares; }
   inline float32 *bind_from_minimum()            { return &minimum; }           //040217
   inline float32 *bind_from_maximum()            { return &maximum; }           //040217
#ifdef DISABLED
//070306  I always have problems with ostream this was for a special output anyway
 public: // Output
   virtual void dump_statistics
      (std::ostream &strm, nat16 statistics_to_dump=STAT_ALL, const char *section = 0); //050107
   // Outputs the selected calculated stats in the format stat=9.999 with 1 entry per line
   // If section is specified [section] is output first
#endif
};
//______________________________________________________________________________
class Statistical_data_setX               // Rename this to Statistics_descriptive_dataset
: public Dynamic_array<float32>                                                  //140610
, public Statistical_baseX                                                        //990401
{private: // updated by recompute
   mutable float32 coefficient_of_variation;
   mutable float32 median;                                                       //010406
 private: // statistical base pure overrides
   inline virtual bool get_changed()                         { return changed; }
 protected:
   float32 calc_median()                                                  const; //010406
 public:
   Statistical_data_setX();
   Statistical_data_setX(const Dynamic_array<float32> &data_to_copy);             //140610
   virtual bool reset();                                           modification_ //150825_040123
   inline virtual void clear()                                     modification_{ Dynamic_array<float32>::clear(); reset(); }  //140610_980310
   inline float32 probability(int at_i)                               provision_{ return  (float32)(at_i / (get_count() + 1.0) * 100.0); }
   // probability in a 1 based array
   inline virtual nat32  get_count()                                  provision_{ return (nat32)  Dynamic_array<float32>::get_count(); } //010604
   inline virtual float32 get_min()                                   provision_{ return (float32)Dynamic_array<float32>::get_min(); }  //050107
   inline virtual float32 get_max()                                   provision_{ return (float32)Dynamic_array<float32>::get_max(); }  //050107
   inline virtual float32 get_sum()                                   provision_{ return (float32)Dynamic_array<float32>::get_summation(); }  //150625_050507
   inline virtual float32 sum()  			                                      { return (float32)Dynamic_array<float32>::sum(); } // deprecated  050107
          virtual float32 get_median()                               provision_; //010406
   virtual float32 get_mean()                                        provision_;
   float32 get_coefficient_of_variation()                            provision_;
   virtual float32 get_standard_deviation()                          provision_;
   float32 get_probability_value(float32 percentage)                 provision_;
   void get_Weibull_alpha_beta(float32 &alpha, float32 &beta)             const; //980318
   // I  alpha is a unitless shape parameter and beta is the scale parameter
   // (same units as the generated value)
   virtual float32 append(float32 value);                                        //980305
   float64 get_weighted_value(int at_i)                                   const; //081024
 public:
   virtual void recompute()                                       modification_;
 private:
   float32 Weibull_f(float32 alpha)                                       const; //980318
   float32 bisection_method(float32 alpha_initial)                        const; //980318
 public: // The following are overridden so we can track dataset status
   inline virtual float32 set(nat32 index,float32 value)           modification_ //990401
   {  status_clear_all();
      return  Dynamic_array<float32>::set(index,value);
   }
   inline virtual float32 remove_at(nat32 at_index)                modification_ //141105_980721
   {  status_clear_all();
      return Dynamic_array<float32>::remove_at(at_index);
   }
 public:  // These reference accessor are intened to allow the
         // statistical tallies to be hooked up to the user interface.
   inline float32 *bind_from_coefficient_of_variation()
      { return &coefficient_of_variation; }
   inline float32 *bind_from_median()                        { return &median; }
#ifdef DISABLED
//070306  I always have problems with ostream this was for a special output anyway
	public: // Output
		virtual void dump_statistics(STD_NS ostream &strm, nat16 statistics_to_dump=STAT_ALL, const char *section = 0);  //050107
      // Outputs additional variables that can be computed from the dataset
#endif
};
//______________________________________________________________________________
class Statistical_running_tally          // Rename this to Statistics_running tally
: public Statistical_baseX
{private:
   nat32  count;
 public:
   Statistical_running_tally();
   virtual bool reset();
   virtual float32 append(float32 value);                                        //980305
   virtual float32 calc_standard_deviation()                              const;
   virtual float32 get_standard_deviation()                               const;
   virtual float32 calc_coefficient_of_variation()                        const; //091002
   virtual float32 get_coefficient_of_variation()                    provision_; //091002
   inline virtual float32 get_median()                     provision_{return 0;} //010406
      // This class is not able to calculate a median

   inline virtual float32 get_min()                    const { return minimum; } //001024
   inline virtual float32 get_max()                    const { return maximum; } //001024
   inline virtual nat32  get_count()                     const { return count; } //010604
 public:  // These reference accessor are intened to allow the
         // statistical tallies to be hooked up to the user interface.
   inline float32 *bind_from_minimum()                      { return &minimum; } //060929
   inline float32 *bind_from_maximum()                      { return &maximum; } //060929
   inline float32 &ref_current()                            { return  current; } //060929
};
//_class Statistical_running_tally__________________________________1999-03-31_/
class Statistical_running_indexX      // This is only used by CropSyst, probably should move it
: public Statistical_sample_cumulative<float32,float32>
{
public:
   float64 index; // 1 = max stress 0 = no stress So recorder can reference
public:
   Statistical_running_indexX(nat16 _applicable /*= STAT_ALL_bits*/);
   virtual float32 append(float32 value);
   virtual bool reset();                                                         //150825
};
//_2001-07-26___________________________________________________________________
} // namespace CORN

#endif
//stats

