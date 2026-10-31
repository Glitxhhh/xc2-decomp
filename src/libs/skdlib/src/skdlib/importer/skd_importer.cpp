// Original file name from the game string C:/Monolithsoft/BF2/prog/libs/skdlib/src/skdlib/importer/skd_importer.cpp.
#include "skd/skd_dynamics.h" // IWYU pragma: keep

#include "mm_mtl/vector.h" // IWYU pragma: keep

template void mm::mtl::Vector<skd::ResSolver>::expand(size_t, size_t);
template void mm::mtl::Vector<skd::ResCollisionShpere>::push_back(const skd::ResCollisionShpere &);
template void mm::mtl::Vector<skd::ResCollisionCapsule>::push_back(const skd::ResCollisionCapsule &);
template void mm::mtl::Vector<skd::ResCollisionPlane>::push_back(const skd::ResCollisionPlane &);
template void mm::mtl::Vector<skd::ResHingeConstraint>::push_back(const skd::ResHingeConstraint &);
template void mm::mtl::Vector<skd::ResNodeCollision>::expand(size_t, size_t);
template void mm::mtl::Vector<skd::ResCollisionShpere>::expand(size_t, size_t);
template void mm::mtl::Vector<skd::ResCollisionCapsule>::expand(size_t, size_t);
template void mm::mtl::Vector<skd::ResCollisionPlane>::expand(size_t, size_t);
template void mm::mtl::Vector<skd::ResNode>::expand(size_t, size_t);
template void mm::mtl::Vector<skd::ResStickConstraint>::expand(size_t, size_t);
template void mm::mtl::Vector<skd::ResSpringConstraint>::expand(size_t, size_t);
template void mm::mtl::Vector<skd::ResHingeConstraint>::expand(size_t, size_t);
