// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/data/gf_bdat_unique_motion.cpp.
#include "gf/data/gf_bdat_unique_motion.h"

#include "mm_mtl/map.h"        // IWYU pragma: keep
#include "mm_mtl/unique_ptr.h" // IWYU pragma: keep
#include "mm_mtl/vector.h"     // IWYU pragma: keep

template mm::mtl::PtrSingleton<gf::GfBdatUniqueMotion>::~PtrSingleton();
template void mm::mtl::UniquePtr<gf::GfBdatUniqueMotion::Impl>::_safe_bool_helper::safe_bool_function() const;
template void mm::mtl::Vector<gf::GfBdatUniqueMotion::PresetInfo>::expand(size_t, size_t);

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<unsigned short, gf::GfBdatUniqueMotion::CharaInfo>::MapTraits<unsigned short, gf::GfBdatUniqueMotion::CharaInfo>> unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<unsigned short, gf::GfBdatUniqueMotion::CharaInfo> &);
template void unknown101::rebalance(unknown101::node *);
