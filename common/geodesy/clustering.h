#ifndef clusteringH
#define clusteringH
#include "common/geodesy/geocoordinates.h"
namespace CS
{

//______________________________________________________________________________
class Clustering
{
 public:
   //___________________________________________________________________________
   class Cluster
   : public extends_ Geocoordinates
   , public implements_ CORN::Item
   {
      // moved to Geocoordinates Geocoordinates::Extent extent;
      float32 tolerance_km;
    public:
      Cluster(float32 tolerance_km_);
      nat32 take_potential_members(Geocoordinates &nonmembers);
      virtual inline bool take_netCDF_extent_source_directory
         (CORN::OS::Directory_name *source_directory)             appropriation_
         { return true; } // drived classes will override
    private:
      inline virtual const std::string &append_to_string(std::string &buffer) const { return buffer; }
            //180813 not currently used  may want to write in a preferred/specified format
   };
   //___________________________________________________________________________
 protected:
   nat32 cluster_single();
 public:
   nat32 initialize()                                           initialization_;
 private:
   const Geocoordinates &all_points;
   Geocoordinates unclustered;
 public:
   float32 tolerance_km;
 public:
   CORN::Unidirectional_list clusters;
 public:
   Clustering
      (const Geocoordinates &all_points
      ,float32 tolerance_km);
   virtual Cluster *render_cluster()                                  rendition_
      { return new Cluster(tolerance_km); }
 protected:
   virtual const CORN::OS::Directory_name &get_netCDF_source_superdir()const=0;
};
//_2017-08-15_______________________________________________________Clustering_/
} //namespace CS



#endif