#include "common/geodesy/clustering.h"
#include "common/geodesy/geometry/terrestrial_geometry.h"
#include "corn/math/compare.hpp"
namespace CS
{
Terrestrial_geometry clustering_geometry;
//______________________________________________________________________________
Clustering::Cluster::Cluster
(float32 tolerance_km_)
:Geocoordinates()
,tolerance_km(tolerance_km_)
{}
//______________________________________________________________________________
nat32 Clustering::Cluster::take_potential_members(Geocoordinates &nonmembers)
{  nat32 taken = 0;
   FOR_EACH(member,Geocoordinate_item,each_member)
   {  FOR_EACH_IN(nonmember,Geocoordinate_item,nonmembers,each_nonmember)
      {  float32 distance = clustering_geometry.distance_between_km(*member,*nonmember);
         if (distance <= tolerance_km)
         {  nonmembers.detach(nonmember);
            take(nonmember);
            taken++;
         }
      } FOR_EACH_END(each_nonmember)
   } FOR_EACH_END(each_member)
   // Recurse until
   if (taken)
   {  nat32 more_taken = 0;
      while ((more_taken = take_potential_members(nonmembers)) != 0)
         taken += more_taken;
   }
   return taken;
}
//______________________________________________________________________________
Clustering::Clustering
(const Geocoordinates &all_points_
,float32 tolerance_km_)
: all_points(all_points_)
, tolerance_km(tolerance_km_)
, unclustered()
{}
//______________________________________________________________________________
nat32 Clustering::cluster_single()
{  Cluster *only_cluster = new Cluster(0);
   only_cluster->transfer_all_from(unclustered);
   clusters.take(only_cluster);
   return only_cluster->count();
}
//______________________________________________________________________________
nat32 Clustering::initialize()                                   initialization_
{  nat32 taken = 0;
   unclustered.clone_from(all_points);
   if (CORN::is_approximately<float32>(tolerance_km,0.0))
      taken = cluster_single();
   else
   {  const CORN::OS::Directory_name &netCDF_source_directory =
         get_netCDF_source_superdir();
      while (unclustered.count())
      {

         // Conceptual,  needed
         // Load list of existing clusters (if any)
         // (that may have been previously identified
         // render new clusters that
         // would have been contiguous with existing clusters
         // but would have to be now a new cluster

         Geocoordinate_item *geocoord_to_cluster
            = dynamic_cast<Geocoordinate_item *>(unclustered.pop_at_tail());
         Cluster *cluster = render_cluster(); //new Cluster(tolerance_km);
         cluster->take(geocoord_to_cluster);
         taken++;
         clusters.take(cluster);
         taken += cluster->take_potential_members(unclustered);
         std::string extent_name;
         cluster->provide_extent().compose_name(extent_name);
         CORN::OS::Directory_name_concrete *source_directory = new
            CORN::OS::Directory_name_concrete
               (get_netCDF_source_superdir(),extent_name);
         cluster->take_netCDF_extent_source_directory(source_directory);
      }
   }
   return taken;
}
//______________________________________________________________________________
} // namespace CS
