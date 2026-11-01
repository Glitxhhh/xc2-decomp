// Original file name from the game string C:/Monolithsoft/BF2/prog/libs/aiLib/src/ailib/behavior/node/composite/ai_behavior_composite_node.cpp.
#include "ai/ai_behavior_tree.h"
#include "mm_mtl/vector.h" // IWYU pragma: keep
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

template void mm::mtl::Vector<ai::BehaviorNode *>::expand(size_t, size_t);
template void mm::mtl::Vector<ai::BehaviorNode *>::extend(size_t, size_t, ai::BehaviorNode *const &);
template void mm::mtl::Vector<ai::BehaviorNode *>::resize(size_t, ai::BehaviorNode *const &);

namespace ai {

CompositeNode::CompositeNode(const char *name, u32 childNum, mm::mtl::IAllocator *allocator) : BehaviorNode(name, 0), m_childNodes(allocator) { m_childNodes.resize(childNum, nullptr); }

CompositeNode::~CompositeNode() {}

const mm::mtl::RTTI *CompositeNode::getRTTI() const { return &m_rtti; }

} // namespace ai
