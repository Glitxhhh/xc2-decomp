// No game string names this file: named after its header skd/skd_collision_object.h. The game places these
// instantiations right after skd::CollionArray's constructor, which builds the three shape vectors.
#include "skd/skd_collision_object.h"

#include "mm_mtl/vector.h" // IWYU pragma: keep

template void mm::mtl::Vector<skd::ShpereCollObj>::resize(size_t);
template void mm::mtl::Vector<skd::CapsuleCollObj>::resize(size_t);
template void mm::mtl::Vector<skd::PlaneCollObj>::resize(size_t);
template void mm::mtl::Vector<skd::ShpereCollObj>::expand(size_t, size_t);
template void mm::mtl::Vector<skd::ShpereCollObj>::extend(size_t, size_t);
template void mm::mtl::Vector<skd::CapsuleCollObj>::expand(size_t, size_t);
template void mm::mtl::Vector<skd::CapsuleCollObj>::extend(size_t, size_t);
template void mm::mtl::Vector<skd::PlaneCollObj>::expand(size_t, size_t);
template void mm::mtl::Vector<skd::PlaneCollObj>::extend(size_t, size_t);
