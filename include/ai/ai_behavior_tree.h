#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/unique_ptr.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ai {

struct Event;

// Layout evidence: BlackBoard::BlackBoard (0x7100941ae8) only stores the vtable, and the UniquePtr release in
// BehaviorTree::~BehaviorTree calls the deleting destructor at vtable slot 2.
class BlackBoard {
public:
  static mm::mtl::RTTI m_rtti;

  BlackBoard();
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~BlackBoard();
};

static_assert(sizeof(BlackBoard) == 0x08, "");

// Layout evidence: BehaviorNode::BehaviorNode (0x7100943408) stores the name FixStr at 0x0c (length at 0x2c), the
// active flag at 0x30 and the flags argument at 0x34; BehaviorTree::execute calls onEvent at vtable offset 0x30.
class BehaviorNode : public mm::mtl::ReferenceObject {
public:
  static mm::mtl::RTTI m_rtti;

  BehaviorNode(const char *name, u32 flags);
  ~BehaviorNode() override;
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual bool execute(BlackBoard &blackBoard);
  virtual bool checkCondition(const BlackBoard &blackBoard);
  virtual void setActiveNotiryChildren(BlackBoard &blackBoard, bool isActive);
  virtual void onEvent(BlackBoard &blackBoard, const Event &event);

  mm::mtl::FixStr<32> unknown0c; // Inferred role: name; original member name unknown.
  bool unknown30;                // Inferred role: active; original member name unknown.
  u32 unknown34;                 // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(BehaviorNode, unknown0c) == 0x0c, "");
static_assert(offsetof(BehaviorNode, unknown30) == 0x30, "");
static_assert(offsetof(BehaviorNode, unknown34) == 0x34, "");
static_assert(sizeof(BehaviorNode) == 0x38, "");

// Only the reference counted base is declared (reference count at 0x08 in Vector<IntrusivePtr<BehaviorNodeInfo>>::destroy):
// the members are not decompiled yet.
class BehaviorNodeInfo : public mm::mtl::ReferenceObject {};

// Layout evidence: RootNode::RootNode (0x71009434e0) clears the child node at 0x38, named by the assert of
// RootNode::attachChild.
class RootNode : public BehaviorNode {
public:
  static mm::mtl::RTTI m_rtti;

  RootNode();
  ~RootNode() override;
  const mm::mtl::RTTI *getRTTI() const override;
  bool execute(BlackBoard &blackBoard) override;
  void setActiveNotiryChildren(BlackBoard &blackBoard, bool isActive) override;
  void attachChild(BehaviorNode *node);
  void detachChild();

  BehaviorNode *m_pChildNode;
};

static_assert(offsetof(RootNode, m_pChildNode) == 0x38, "");
static_assert(sizeof(RootNode) == 0x40, "");

// Layout evidence: BehaviorTree::BehaviorTree (0x7100941b2c) constructs the root node at 0x00 and clears the black board
// at 0x40, the node vector at 0x48, the allocator at 0x70 and the setup flag at 0x78; the game has no BehaviorTree vtable.
// The member names m_pNodes, m_pAllocator and m_setup come from the asserts of the createTask template.
class BehaviorTree {
public:
  BehaviorTree();
  ~BehaviorTree();
  void beginSetup(u32 nodeNum, mm::mtl::IAllocator *allocator);
  void endSetup();
  void cleanup();
  void attachRoot(u32 nodeID);
  void attachComposite(u32 parentID, u32 childID, u32 index);
  void execute();

  // Inferred role: black board of the given type, null when it has another type; original name unknown.
  template <typename T> T *unknown001() const {
    BlackBoard *blackBoard = unknown40.get();
    if (blackBoard == nullptr) {
      return nullptr;
    }
    return mm::mtl::dynamicCast<T>(blackBoard);
  }

  RootNode unknown00;                       // Inferred role: root node; original member name unknown.
  mm::mtl::UniquePtr<BlackBoard> unknown40; // Inferred role: black board; original member name unknown.
  mm::mtl::Vector<mm::mtl::IntrusivePtr<BehaviorNode>> m_pNodes;
  mm::mtl::IAllocator *m_pAllocator;
  bool m_setup;
};

static_assert(offsetof(BehaviorTree, unknown40) == 0x40, "");
static_assert(offsetof(BehaviorTree, m_pNodes) == 0x48, "");
static_assert(offsetof(BehaviorTree, m_pAllocator) == 0x70, "");
static_assert(offsetof(BehaviorTree, m_setup) == 0x78, "");
static_assert(sizeof(BehaviorTree) == 0x80, "");

} // namespace ai
