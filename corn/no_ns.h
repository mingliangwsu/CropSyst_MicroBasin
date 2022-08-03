#ifndef no_nsH
#define no_nsH
#  ifdef no_namespaces
#     define namespace_CORN_start
#	   define namespace_CORN_end
#     define CORN_NS
//#     define STD_NS
#     define using_namespace_CORN
#  else
#     define namespace_CORN_start namespace CORN {
#	   define namespace_CORN_end   };
#     define using_namespace_CORN using namespace CORN
#  endif
#endif
//no_ns

