#include "ai/ai_behavior_tree.h"

namespace ai {

SequenceNode::~SequenceNode() {}

const mm::mtl::RTTI *SequenceNode::getRTTI() const { return &m_rtti; }

bool SequenceNode::checkCondition(const BlackBoard &blackBoard) { return true; }

} // namespace ai
