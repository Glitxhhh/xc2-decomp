#include "ai/ai_behavior_tree.h"

namespace ai {

ParallelNode::~ParallelNode() {}

const mm::mtl::RTTI *ParallelNode::getRTTI() const { return &m_rtti; }

bool ParallelNode::checkCondition(const BlackBoard &blackBoard) { return true; }

} // namespace ai
