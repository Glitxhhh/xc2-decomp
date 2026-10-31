#include "gf/object/component/pc/plugin/gf_pc_look_at_plugin.h"

#include "mm_mtl/map.h" // IWYU pragma: keep

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<gf::GF_OBJ_HANDLE *, gf::pc::LookAtPlugin::TargetInfo>::MapTraits<gf::GF_OBJ_HANDLE *, gf::pc::LookAtPlugin::TargetInfo>> unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<gf::GF_OBJ_HANDLE *, gf::pc::LookAtPlugin::TargetInfo> &);
template void unknown101::rebalance(unknown101::node *);
template void unknown101::erase(unknown101::node *);
template void unknown101::rebalance_after_erase(unknown101::node *);
