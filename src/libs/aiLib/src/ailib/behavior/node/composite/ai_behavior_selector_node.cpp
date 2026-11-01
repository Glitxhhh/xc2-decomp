#include "ai/ai_behavior_tree.h"

namespace ai {

SelectorNode::~SelectorNode() {}

const mm::mtl::RTTI *SelectorNode::getRTTI() const { return &m_rtti; }

bool SelectorNode::checkCondition(const BlackBoard &blackBoard) { return true; }

} // namespace ai
